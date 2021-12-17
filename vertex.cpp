/**
 * @file vertex.cpp
 * @brief Definitions of the functions declared in "vertex.h".
 * @version 0.3
 * @date 2021-12-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "vertex.h"
#include <iostream>
using std::cout;
using std::endl;

/**
 * @brief Construct a new vertex given its key and actual name. 
 * 
 * @param key = IATA (3-character) code.
 * @param name = Actual airport name.
 */
Vertex::Vertex(const string &key, const string &name, const size_t index) : key_(key), name_(name), index_(index) {
}

/**
 * @brief Destroy the vertex instance (and its linked list).
 * 
 */
Vertex::~Vertex() {
    adj_list_.clear();
}

/**
 * @brief Default constructor for vertex
 * 
 */
Vertex::Vertex() {
    adj_list_ = *(new list<edge_ptr>());
}

/** insert_neighbor
 * @brief Insert a new edge that connects the current vertex to an adjacent vertex.
 * 
 * @param dst = Adjacent vertex.
 * @param weight = Edge weight.
 */
void Vertex::insert_neighbor(const Vertex &dst, const double &weight) {
    adj_list_.push_front(edge_ptr(new Edge(&dst, weight)));
}

/** get_name
 * @brief Getter of the `name_` member.
 * 
 * @return const string& = `name_`.
 */
const string &Vertex::get_name() const {
    return name_;
}

/**
 * @brief Getter of the `adj_list_` member
 * 
 * @return const list<edge_ptr> 
 */
list<Vertex::edge_ptr> &Vertex::get_adj_list() {
    return adj_list_;
}

size_t Vertex::get_index() const {
    return index_;
}

const string &Vertex::get_key() const {
    return key_;
}

/** hash_edge
 * @brief Determine the edge that connects from this vertex to the destination airport with key `airport_key`.
 * 
 * @param airport_key = IATA (3-character) code of the destination airport.
 * @return Vertex::edge_ptr = Smart pointer to the edge if it exists (else, nullptr).
 */
const Vertex::edge_ptr Vertex::hash_edge(const string &airport_key) const {
    for (const edge_ptr e : adj_list_) {
        if (e->dst_ && e->dst_->key_ == airport_key) {
            return e;
        }
    }
    return nullptr;
}

/** find_edge
 * @brief Determine the edge that connects from this vertex to the destination airport with name `airport_name`.
 * 
 * @param airport_name = Actual airport name of the destination airport.
 * @return Vertex::edge_ptr = Smart pointer to the edge if it exists (else, nullptr).
 */
const Vertex::edge_ptr Vertex::find_edge(const string &airport_name) const {
    for (const edge_ptr e : adj_list_) {
        if (e->dst_ && e->dst_->name_ == airport_name) {
            return e;
        }
    }
    return nullptr;
}

const Vertex::edge_ptr Vertex::index_edge(const size_t airport_ID) const {
    for (const edge_ptr e : adj_list_) {
        if (e->dst_ && e->dst_->index_ == airport_ID) {
            return e;
        }
    }
    return nullptr;
}


bool Vertex::find_(string name) {
    // Returns true if the vertex with name = `name` is adjacent to the current vertex
    for (const auto edges : adj_list_) {
        if (edges->dst_->get_key() == name) {
            return true;
        }
    }
    return false;
}