#include<iostream>
#include<climits>     
#include <algorithm>
#include <functional>
#include <stack>
using namespace std;
#include "dijikstra.h"
using std::stack;

// From source, obtain shortest distances map (copied from pseudo code)
map<string, min_dist> Dijkstra::src(const string &key) {        
	map<string, min_dist> dist;
	dist.insert(pair<string, double>(key, 0));

    std::priority_queue<compair, vector<compair>, Comparator> Q;

	auto src_iterator = G_.vertices_.find(key);
	
    Q.push(compair(&src_iterator->second, 0));
	dist[key] = 0;

	while (!Q.empty()) {
		const Vertex *min_v = Q.top().src_;
		Q.pop();

		for (const auto &adj : min_v->adj_list_) {
			const Vertex *neighbor = adj->dst_;
			min_dist edge_weight(adj->weight_);
			if ((dist[neighbor->get_key()] > dist[min_v->get_key()] + edge_weight)) {
				dist[neighbor->get_key()] = dist[min_v->get_key()] + edge_weight;
				Q.push(compair(neighbor, dist[neighbor->get_key()]));
			}
		}
	}

	return dist;
}

min_dist Dijkstra::src(const string &key, const string &dst) {        
	map<string, min_dist> dist;

	// Change 14111 depending on the max index
	vector<pair<int, string>> prev(14111, pair<int, string>(-1, "\n"));
	dist.insert(pair<string, min_dist>(key, min_dist(0)));

    std::priority_queue<compair, vector<compair>, Comparator> Q;


	auto src_iterator = G_.vertices_.find(key);
	
    Q.push(compair(&src_iterator->second, 0));

	//dist[src] = 0;

	while (!Q.empty()) {
		const Vertex *min_v = Q.top().src_;
		Q.pop();

		for (const auto &adj : min_v->adj_list_) {
			const Vertex *neighbor = adj->dst_;
			min_dist edge_weight(adj->weight_);

			if (min_v->get_key() == dst) {
				return dist[dst];
			}

			if (dist[neighbor->get_key()] > dist[min_v->get_key()] + edge_weight) {
				dist[neighbor->get_key()] = (dist[min_v->get_key()] + edge_weight);
				Q.push(compair(neighbor, dist[neighbor->get_key()]));
			}
		}
	}
	return min_dist();
}

// Copied from Wikipedia and Geeks - adapted to our classes
vector<pair<int, string>> Dijkstra::path(const string &src, const string &dst) {
	map<string, min_dist> dist;

	// Change 14111 depending on the max index
	vector<pair<int, string>> prev(14111, pair<int, string>(-1, "\n"));
	dist.insert(pair<string, min_dist>(src, min_dist(0)));

    std::priority_queue<compair, vector<compair>, Comparator> Q;


	auto src_iterator = G_.vertices_.find(src);
	
    Q.push(compair(&src_iterator->second, 0));

	dist[src] = 0;

	while (!Q.empty()) {
		const Vertex *min_v = Q.top().src_;
		Q.pop();

		if (min_v->get_key() == dst) {
			return prev;
		}
		
		for (const auto &adj : min_v->adj_list_) {
			const Vertex *neighbor = adj->dst_;
			min_dist edge_weight(adj->weight_);

			if (dist[neighbor->get_key()] > dist[min_v->get_key()] + edge_weight) {
				//cout << "Added at " << neighbor->get_index() << " (" << min_v->get_index() << "," << min_v->get_name() << ")" << endl;
				dist[neighbor->get_key()] = (dist[min_v->get_key()] + edge_weight);
				prev[neighbor->get_index()] = pair<int, string>(min_v->get_index(), min_v->get_name());
				Q.push(compair(neighbor, dist[neighbor->get_key()]));
			}
			//cout << "out" << endl;
		}
	}
	return prev;
}

void Dijkstra::print_path(const string &src, const string &dst) {

	cout << "The route with the least distance that you can travel on is:";
	cout << endl; 
	vector<pair<int, string>> prev = path(src, dst);
	stack<string> ordered_path;
	int source = G_.vertices_.find(src)->second.get_index();
	int target = G_.vertices_.find(dst)->second.get_index();
	string source_name = G_.vertices_.find(src)->second.get_name();
	string target_name = G_.vertices_.find(dst)->second.get_name();

	//cout << "target = " << target << endl;
	//cout << "source = " << source << endl;
	//ordered_path.push(source_name);
	if (prev[target].first != -1) {
		while (target > 0 && prev[target].first != 1 && target != source) {
			ordered_path.push(prev[target].second);
			//cout << "Pushed = " << prev[target].second << endl;
			target = prev[target].first;
			//cout << "New target = " << target << endl;
		}
	}

	while (!ordered_path.empty()) {
		cout << ordered_path.top() << " -> ";
		ordered_path.pop();
	}

	cout << target_name << " -> Finished." << endl;
}