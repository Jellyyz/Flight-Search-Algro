#pragma once
#include <map>
#include <utility>
#include <ostream>
#include <cmath>
#include <vector>
#include <queue>
#include "../vertex.h"
#include "../adj_list_graph.h"
using std::vector;
using std::map;
using std::pair;
using std::ostream;
using std::queue;

struct min_dist {
    min_dist() {
    };
    min_dist(double val) {
        val_ = val;
    };
    void operator=(const min_dist &other) {
        val_ = other.val_;
    };
    min_dist operator+(const min_dist &other) const {
        return min_dist(val_ + other.val_);
    };
    bool operator>(const min_dist &other) const {
        return val_ > other.val_;
    };
    bool operator==(const min_dist &other) const {
        return val_ == other.val_;
    };
    friend ostream &operator<<(ostream &os, const min_dist &ref) {
        return os << ref.val_;
    };

    double val_ = INFINITY;
};

class Dijkstra {
    public:
        Dijkstra(const Graph &G) : G_(G) {};
        map<string, min_dist> src(const string &key);
        vector<pair<int, string>> path(const string &src, const string &dst); 
        void print_path(const string &src, const string &dst);
        min_dist src(const string &key, const string &dst);
    private:
        const Graph &G_;
};

struct compair {
    compair(const Vertex *src, min_dist d) : src_(src), d_(d) {
    }
    const Vertex *src_;
    min_dist d_;
};

struct Comparator {
    bool operator()(compair &lhs, compair &rhs) {
        return lhs.d_ > rhs.d_;
    }
};