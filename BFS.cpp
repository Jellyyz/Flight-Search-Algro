#include "BFS.h"
#include "vertex.h"

BFS::BFS(const Graph &graph) : G(graph){
}

vector<string> BFS::bfs(Vertex start, Vertex end) {
    vector<string> path;
    map<string, Vertex> graph = G.vertices_;
    list<Vertex> queue;
    map<string, bool> visited;
    map<string, double> dist;
    map<string, Vertex> pred;
    bool connected = false;

    map<string, Vertex>::iterator it;
    for (it = graph.begin(); it != graph.end(); ++it) {
        Vertex curr = it->second;

        visited.insert(pair<string, bool> (curr.get_key(), false));
        dist.insert(pair<string, double> (curr.get_key(), INT_MAX));
        pred.insert(pair<string, Vertex> (curr.get_key(), Vertex("invalid", "invalid", 0)));

    }
    
    string startName = start.get_key();
    visited.find(startName)->second = true;
    dist.find(startName)->second = 0;
    queue.push_back(start);

    while (!queue.empty()) {
        Vertex curr = queue.front();
        queue.pop_front();
        list<Vertex::edge_ptr> adjVertices = (graph.find(curr.get_key()))->second.get_adj_list();

        for (Vertex::edge_ptr edge : adjVertices) {
            Vertex other = *edge->dst_;
            string otherName = edge->dst_->get_key();
            if (!visited.find(otherName)->second) {
                visited.find(otherName)->second = true;
                dist.find(otherName)->second = (dist.find(curr.get_key()))->second + 1;
                pred.find(otherName)->second = curr;
                queue.push_back(other);
                if (end.get_key() == other.get_key()){
                    connected = true;
                    break;
                }
            }
        }
    }


    if (!connected) {
        cout << "No routes have been found between the starting airport and the destination airport." << endl;
        return path;
    }

    Vertex back = end;
    path.push_back(back.get_key());
    while (back.get_key() != "invalid") {
        string backName = back.get_key();
        path.push_back(pred.find(backName)->second.get_key());
        back = pred.find(backName)->second;
    }

    path.pop_back();
    reverse(path.begin(),path.end());

    return path;

}
