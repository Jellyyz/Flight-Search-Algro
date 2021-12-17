#pragma once
#include <stack> 
#include <queue>
#include <vector>
#include <climits>
#include <map>
#include "main.h"
#include "adj_list_graph.h"

using namespace std; 

class BFS{
    public:
    BFS(const Graph &graph); 
    vector<string> bfs(Vertex start, Vertex end); 
    private:
    map<string, bool> visited; 
    queue<string> q; 
    const Graph &G;

    };