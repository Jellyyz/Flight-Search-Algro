/**
 * @file adj_list_graph.cpp
 * @brief Definitions of the functions declared in "adj_list_graph.h".
 * @version 0.2
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <fstream>
#include <cmath>

#include "adj_list_graph.h"
#include "parser.h"

using std::ifstream;
using std::getline;
using std::cout;
using std::endl;
using std::pair;

/**
 * @brief Default constructor for graph
 * 
 */
Graph::Graph() {}

/** 
 * @brief Construct a new `Graph` instance given an "airports.dat" version and "routes.dat" version.
 * 
 * @param vertices_file_name = "airports.dat", contains data about each vertex (airport). 
 * @param edges_file_name = "routes.dat", contains data about each edge (airplane route between airports).
 */
Graph::Graph(const string &vertices_file_name, const string &edges_file_name) {
    string line;
    ifstream file(vertices_file_name);

    // Use a hashmap on the stack since its information will be useless after construction (used to compute distances/edge weights).
    /* Key: IATA code (3-character code of an airport) -- GLOBAL-USED key
       Value: Pair/tuple of (Latitude in degrees, Longitude in degrees) */
    map<string, pair<double, double>> lat_long;
    bool exists_already = false;

    // First, store a vertex map.
    if (file.is_open()) {
        while (getline(file, line)) {
            // fields contains <field value, ..., last field value> where the zeroth index maps to the leftmost field in the line.
            vector<string> fields = parse_line(line);

            // Store information in the fields to a new vertex and a new tuple of coordinates.
            vertices_.insert(pair<string, Vertex>(fields[IATA], Vertex(fields[IATA], fields[NAME], std::stoi(fields[AIRPORT_ID]))));
            lat_long.insert(pair<string, pair<double, double>>(fields[IATA], pair<double, double>(std::stod(fields[LATITUDE]), std::stod(fields[LONGITUDE]))));
        }
        file.close();
    }

    file.clear();

    file.open(edges_file_name);

    // Finally, store edge lists.
    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> fields = parse_line(line);

            // Test code used to check whether any airports were identified with their ICAO and not IATA code.
            // Conclusion: Only IATA (3-character) codes were used - no edge case found.
            /*
            if (fields[SRC_AIRPORT].length() == 4 || fields[DST_AIRPORT].length() == 4) {
                cout << "ICAO code spotted" << endl;    // There are literally 0 ICAO codes in the dataset. 
            }*/

            //debug("SRC = " << fields[SRC_AIRPORT]);
            auto vertex_iterator = vertices_.find(fields[SRC_AIRPORT]);

            //debug("DST = " << fields[DST_AIRPORT]);
            if (vertex_iterator != vertices_.end() && vertex_iterator->second.find_(fields[DST_AIRPORT])) {
                exists_already = true;
            }
            else {
                exists_already = false;
            }
            // For the given source airport (vertex), insert route from source airport to destination airport (edge).
            if (!exists_already) {
                insert_edge(fields[SRC_AIRPORT], fields[DST_AIRPORT], 
                    great_circle_dist(lat_long.find(fields[SRC_AIRPORT])->second, lat_long.find(fields[DST_AIRPORT])->second));
            }
        }
        file.close();
    }
}

/** Graph::probe_dist
 * @brief Determines the distance (in kilometers) from the airport mapped to `src` to the airport mapped to `dst`.
 * 
 * @param src = IATA (3-character) code of the source airport (launch place).
 * @param dst = IATA (3-character) code of the destination airport (landing place).
 * @return double = The distance between the two airports (0 if impossible or no distance was covered).
 */
double Graph::probe_dist(const string &src, const string &dst) const {
    auto src_prober = vertices_.find(src), dst_prober = vertices_.find(dst);
    //cout << "Starting scan for {" << src << "} to {" << dst << "}." << endl;

    // Case where the source airport is not in the graph.
    if (src_prober == vertices_.end()) {
        cout << "Airport with IATA {" << src << "} not found." << endl;
        return 0;
    }
    // Case where the destination airport is not in the graph.
    else if (dst_prober == vertices_.end()) {
        cout << "Airport with IATA {" << dst << "} not found." << endl;
        return 0;
    }
    auto vertex = src_prober->second.hash_edge(dst);

    // Case where no traversal via edges exists between the two existent airports.
    if (vertex == nullptr) {
        cout << "No route from source {" << src << "} to {" << dst << "} exists." << endl; 
        return 0;
    }

    // Case where no errors were found - a distance exists in the form of the edge weight.
    return vertex->weight_;
}

/** Graph::probe_name
 * @brief Return the actual airport name associated with the airport mapped to the argument.
 * 
 * @param IATA = (3-character) Code that maps to the airport in question.
 * @return string = \N if the airport in question does not exist, else the actual name.
 */
string Graph::probe_name(const string &IATA) const {
    auto prober = vertices_.find(IATA);
    return (prober == vertices_.end()) ? "\\N" : prober->second.get_name();
}

string Graph::probe_IATA(const string &name) const{
    auto prober = vertices_.find(name);
    return (prober == vertices_.end()) ? "\\N" : prober->second.get_key();
}

/** Graph::insert_edge
 * @brief Insert an edge to the linked list from the vertex associated with `src` argument.
 * 
 * @param src = IATA (3-character) code that maps to the vertex to insert an edge to.
 * @param dst = IATA (3-character) code that maps to the vertex to set as the destination.
 * @param weight = Distance in kilometers between the airports passed as arguments.
 */
void Graph::insert_edge(const string &src, const string &dst, const double weight) {
    auto src_iterator = vertices_.find(src);
    auto dst_iterator = vertices_.find(dst);
    if (src_iterator != vertices_.end() && dst_iterator != vertices_.end()) {
        src_iterator->second.insert_neighbor(dst_iterator->second, weight);
    }
}

/** degrees_to_radians
 * @brief Convert from degrees to radians.
 * 
 * @param degrees = Degree value to convert.
 * @return double = Radian value of `degrees`.
 */
double degrees_to_radians(const double degrees) {
    return (degrees * M_PI) / 180;
}

/** great_circle_dist
 * @brief Compute the distance between two points of the form (Latitude in degrees, Longitude in degrees) using the Haversine formula.
 * 
 * @param point1 = A coordinate pair.
 * @param point2 = A coordinate pair.
 * @return double = Great-circle distance between the given points.
 */
double great_circle_dist(const pair<double, double> &point1, const pair<double, double> &point2) {
    double lat_rad1 = degrees_to_radians(point1.first);
    double long_rad1 = degrees_to_radians(point1.second);
    double lat_rad2 = degrees_to_radians(point2.first);
    double long_rad2 = degrees_to_radians(point2.second);
    double diff_lat = sin((lat_rad2 - lat_rad1) / 2);
    double avg_lat = sin((lat_rad2 + lat_rad1) / 2);
    double diff_long = sin((long_rad2 - long_rad1) / 2);

    return 2 * EARTH_RADIUS_KM * asin(sqrt(diff_lat * diff_lat + (diff_long * diff_long) * (1 - diff_lat * diff_lat - avg_lat * avg_lat)));
}


bool Graph::directed() {
    bool undirected = false;
    for (auto &vpair : vertices_) {
        string desired = vpair.second.get_name();
        cout << "DESIRED : " << desired << endl;
        for (auto &e : vpair.second.adj_list_) {
            // Find the other vertex
            for (auto &other : e->dst_->adj_list_) {
                if (other->dst_->get_name() == desired) {
                    undirected = true;
                    break;
                }
                else {
                    undirected = false;
                }
            }
            cout << "UNDIRECTED? : " << undirected << endl;

            if (!undirected) {
                return false;
            }
        }
    }
    return undirected;
}