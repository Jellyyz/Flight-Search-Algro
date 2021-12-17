// https://pdodds.w3.uvm.edu/research/papers/others/2001/brandes2001a.pdf (PG 10)
// https://www.researchtrend.net/ijet/pdf/A%20Fast%20Computation%20of%20Betweenness%20Centrality%20in%20Large%20Scale%20Unweighted%20Graphs%20NH%20NGUYEN%2017167.pdf (PG 3)
// Might be useful resources
#include "betweencentrality.h"

Brandes::Brandes(const Graph &graph, int size) : G_(graph) {
    if (size < 0) {
        max_ = MAX_ID;
    }
    else {
        max_ = size;
    }
}
        
Brandes::~Brandes() {}

vector<double> Brandes::run() {
    C_.resize(max_);
    for (size_t i = 0; i < max_; i++) {
        C_[i] = 0;
    }
    stack<const Vertex *> S;
    vector<vector<const Vertex *>> P;   // Predecessors
    P.resize(max_);
    distance_.resize(max_);
    vector<double> sigma;  // # of shortest paths from s to v
    sigma.resize(max_);
    vector<double> delta;  // Pair-dependency
    delta.resize(max_); 
    //double dist_s_d = 0;
    Dijkstra dist_finder(G_);
    
    size_t s, v, w;
    // foreach s in V do
    for (const auto &key_vertex : G_.vertices_) {
        // assign s
        s = key_vertex.second.get_index();
        debug("s = " << s);
        // S <- empty stack
        S = {};
        // P[w] <- empty list, w in V
        for (size_t i = 0; i < max_; i++) {
            P[i] = {};
        }
        // sigma[t] <- 0, t in V
        for (size_t i = 0; i < max_; i++) {
            sigma[i] = 0;
        }
        // sigma[s] <- 1
        sigma[s] = 1;
        // distance[t] <- -1, t in V
        for (size_t i = 0; i < max_; i++) {
            distance_[i] = INFINITY;
        }
        // distance[s] <- 0
        debug("s = " << s);
        distance_[s] = 0;
        // Q <- empty queue
        Q = {};
        // enqueue s -> Q
        Q.push(compair(&key_vertex.second, distance_[s]));
        map<string, min_dist> dict = dist_finder.src(key_vertex.second.get_key());
        
        // while Q not empty do
        while (!Q.empty()) {

            debug("Non-empty");
            // dequeue v <- Q
            const Vertex *v_v = Q.top().src_;
            v = v_v->get_index();
            debug("v : " <<  v);
            debug("v is identified by " << v_v->get_name());
            Q.pop();
            // push v -> S
            S.push(v_v);
            // foreach neighbor w of v do
            for (const auto &w_v : v_v->adj_list_) {
                w = w_v->dst_->get_index();
                debug("w : " << w);
                debug("There exists a neighbor w identified by " << w_v->dst_->get_name());
                // if d[w] < 0 then
                debug("distance_[v] = " << distance_[v] << " for index = " << v);
                debug("weight = " << w_v->weight_);
                if (distance_[w] > distance_[v] + w_v->weight_) {
                    // enqueue w -> Q
                    Q.push(compair(w_v->dst_, dict.find(w_v->dst_->get_key())->second));
                    // d[w] <- d[v] + 1 | d[w] <- d[v] + weight(?)
                    distance_[w] = distance_[v] + w_v->weight_;
                    sigma[w] = 0;
                    P[w] = {};
                    // end
                }
                // shortest path to w via v?
                // if d[w] = d[v] + 1 then
                if (distance_[w] == distance_[v] + w_v->weight_) {
                    // sigma[w] = sigma[w] + sigma[v]
                    sigma[w] = sigma[w] + sigma[v];
                    // append v -> P[w]
                    P[w].push_back(v_v);
                    // end
                }
                // end
            }
            // end
        }

        // sigma[v] <- 0, v in V
        for (size_t i = 0; i < max_; i++) {
            delta[i] = 0;
        }

        // while S not empty do
        while (!S.empty()) {
            // pop w <- S
            const Vertex *w_v = S.top();
            //const Vertex *w_v = S.top();
            S.pop();
            w = w_v->get_index();
            debug("w = " << w);
            // for v in P[w] do delta[v] <- delta[v] + (sigma[v] / sigma[w]) * (1 + delta[w])
            for (const auto &v_v : P[w]) {
                v = v_v->get_index();
                delta[v] = delta[v] + (sigma[v] / sigma[w]) * (1 + delta[w]);
            }
            // if w =/= s then C[w] <- C[w] + delta[w]
            if (w != s) {
                C_[w] = C_[w] + delta[w];
            }
            // end
        }
        // end
    }
    debug("Leaving frame");
    return C_;
}

void test_queue_compairs() {
    std::priority_queue<compair, vector<compair>, Comparator> q;
    q.push(compair(nullptr, 5));
    q.push(compair(nullptr, 3));
    q.push(compair(nullptr, 9));
    while (! q.empty() ) {
        cout << q.top().d_ << "\n";
        q.pop();
    }
}