/**
 * @file vertex.h
 * @brief Vertex implementation for adjacency list graph.
 * @version 0.3
 * @date 2021-12-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include <list>
#include <memory>
using std::string;
using std::list;

class Vertex {
    private:
        struct Edge {   // Nodes in the linked list.
            Edge() : dst_(nullptr), weight_(0) {
            };
            Edge(const Vertex *dst, const double weight) : dst_(dst), weight_(weight) {
            };
            ~Edge() {
            };
            bool operator>(const Edge &rhs) const {
                return weight_ > rhs.weight_;
            };

            const Vertex *dst_;
            double weight_;        
        };

    public:
        typedef std::shared_ptr<struct Edge> edge_ptr;
        Vertex(const string &key, const string &name, const size_t index);
        Vertex();
        ~Vertex();

        const string &get_name() const;
        list<edge_ptr> &get_adj_list();
        size_t get_index() const;
        const string &get_key() const;
        
        const edge_ptr index_edge(const size_t airport_ID) const;
        const edge_ptr find_edge(const string &airport_name) const;
        const edge_ptr hash_edge(const string &airport_key) const;
        
        bool find_(string name);
        list<edge_ptr> adj_list_;   // STL Linked list of smart edge pointers.

        void insert_neighbor(const Vertex &dst, const double &weight);
    private: 
        string key_;    // Airport IATA (3-character) code.
        string name_;   // Actual airport name.
        size_t index_;  // Airport ID code (unique number to index to).
};