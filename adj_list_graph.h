/**
 * @file adj_list_graph.h
 * @brief Adjacency list implementation of a graph where vertices are addressed by a hashmap.
 * @version 0.2
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <string>
#include <map>
#include <utility>

#include "vertex.h"

using std::string;
using std::map;
using std::pair;

// Source: NASA 
#define EARTH_RADIUS_KM 6378.137
#define DEBUG_F0 0

// Mappings of the fields of "airports.dat"
enum airport_field_indices {
    AIRPORT_ID,
    NAME,
    CITY,
    COUNTRY,
    IATA,
    ICAO,
    LATITUDE,
    LONGITUDE,
    ALTITUDE,
    TIMEZONE,
    DST,
    TZ,
    TYPE,
    SOURCE
};

// Mappings of the fields of "routes.dat"
enum routes_field_indices {
    AIRLINE,
    AIRLINE_ID,
    SRC_AIRPORT,
    SRC_ID,
    DST_AIRPORT,
    DST_ID,
    CODESHARE,
    STOPS,
    EQUIPMENT,
};

// Mathematical helper functions
double degrees_to_radians(const double degrees);
double great_circle_dist(const pair<double, double> &point1, const pair<double, double> &point2);

class Graph {
    public:
        Graph();
        Graph(const string &vertices_file_name, const string &edges_file_name);
        string probe_name(const string &IATA) const;
        string probe_IATA(const string &name) const; 

        double probe_dist(const string &src, const string &dst) const;
        bool directed();
        
        map<string, Vertex> vertices_;
    private:
        void insert_edge(const string &src, const string &dst, const double weight);
};