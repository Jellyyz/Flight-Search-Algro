#pragma once
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <set>
using std::cout;
using std::endl;

#include "../adj_list_graph.h"
#include "dijikstra.h"  // Needed for the algorithm (weighted version)
using std::stack;
using std::queue;
using std::priority_queue;
using std::map;
using std::vector;
using std::set;

#define DEBUG_F2 0
#if DEBUG_F2
#define debug(x) std::cerr << x << endl;
#else
#define debug(x) do {} while (false)
#endif

#define MAX_ID 14111

// Based off Brandes' Algorithm for Betweenness Centrality
class Brandes {
    public:
        Brandes(const Graph &graph, int size);
        ~Brandes();
        vector<double> run();
        vector<double> distance_;
    private:
        size_t max_;    // Size of graph
        const Graph &G_; // Passed graph
        vector<double> C_;   // Centrality

        std::priority_queue<compair, vector<compair>, Comparator> Q;
};

void test_queue_compairs(); 