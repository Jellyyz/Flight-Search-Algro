#include "../Algorithms/dijikstra.h"
#include "../adj_list_graph.h"
#include "../parser.h"
#include "../BFS.h"
#include <math.h>
#include <iostream>
#include <cmath> 

#include "../catch/catch.hpp"
#include <iomanip> 
using namespace std;
TEST_CASE("probe_name", "[weight=1][part=1]") {
  Graph g("airports.dat", "routes.dat");
  string testname0 = g.probe_name("AER");
  string testname1 = g.probe_name("ACH");
  string testname2 =  g.probe_name("EBA");
  string testname00 = g.probe_name("ECE"); 

  REQUIRE(testname0 == "Sochi International Airport");
  REQUIRE(testname1 == "St Gallen Altenrhein Airport");
  REQUIRE(testname2 == "Marina Di Campo Airport");
  REQUIRE(testname00 == "\\N");

}

TEST_CASE("probe_dist", "[weight=1][part=1]"){
  Graph g("airports.dat", "routes.dat");
  double testdist0 = g.probe_dist("ACH", "EBA");
  testdist0 = floor(100*testdist0)/100; 
  REQUIRE(testdist0 == 528.63);  

}

TEST_CASE("probe_dist_zero_case", "[weight=1][part=1]"){
  Graph g("airports.dat", "routes.dat");
  double testdist1 = g.probe_dist("CS", "ECE"); 

  REQUIRE(testdist1 == 0);   
}

TEST_CASE("BFS_route_w_layover", "[weight=1][part=1]"){
  Graph g("airports.dat", "routes.dat");
  BFS b(g);
  string start = "DXB"; 
  string end = "ORD"; 
  string start_name = g.probe_name(start);                      // everything here 
  string end_name = g.probe_name(end);                          // here 
  auto start_num = g.vertices_.find(start);                     // until       
  auto end_num = g.vertices_.find(end);                         // this 
  size_t start_key = start_num ->second.get_index();            // line
  size_t end_key = end_num ->second.get_index();                // here shall just be used to make the vertexes for both BFS and Dijkstra
  Vertex startV(start, start_name, start_key);
  Vertex endV(end, end_name, end_key); 
  vector<string> testing = b.bfs(startV, endV);

  REQUIRE(testing.at(0) == "DXB");
  REQUIRE(testing.at(1) == "ZRH");
  REQUIRE(testing.at(2) == "ORD");

}

TEST_CASE("BFS_distance", "[weight=1][part=1]"){
  Graph g("airports.dat", "routes.dat");
  BFS b(g);
  string start = "DXB"; 
  string end = "ORD"; 
  string start_name = g.probe_name(start);                      // everything here 
  string end_name = g.probe_name(end);                          // here 
  auto start_num = g.vertices_.find(start);                     // until       
  auto end_num = g.vertices_.find(end);                         // this 
  size_t start_key = start_num ->second.get_index();            // line
  size_t end_key = end_num ->second.get_index();                // here shall just be used to make the vertexes for both BFS and Dijkstra
  Vertex startV(start, start_name, start_key);
  Vertex endV(end, end_name, end_key); 
  vector<string> bdir = b.bfs(startV, endV);
  double distance = 0; 
  for(size_t i = 0; i <= bdir.size(); i++){
      //cout << "i: " << i << endl; 
      string scc = bdir.at(i); 
      string dcc = bdir.at(i + 1); 
      distance += g.probe_dist(scc,dcc); 
      if(dcc == end){
          break; 
   }
  }
  REQUIRE(distance <= 11912);
  REQUIRE(distance >= 11911.8);
}
TEST_CASE("BFS_empty_Edge_case", "[weight=1][part=1]"){
  Graph g("airports.dat", "routes.dat");
  BFS b(g);
  string start = "ORD"; 
  string end = "ORD"; 
  string start_name = g.probe_name(start);                      // everything here 
  string end_name = g.probe_name(end);                          // here 
  auto start_num = g.vertices_.find(start);                     // until       
  auto end_num = g.vertices_.find(end);                         // this 
  size_t start_key = start_num ->second.get_index();            // line
  size_t end_key = end_num ->second.get_index();                // here shall just be used to make the vertexes for both BFS and Dijkstra
  Vertex startV(start, start_name, start_key);
  Vertex endV(end, end_name, end_key); 
  vector<string> bdir = b.bfs(startV, endV);

  bool x = bdir.empty(); 
  REQUIRE(x == 1);
}


TEST_CASE("Dijkstra_route_w_layover_distance", "[weight=1][part=1]"){
  min_dist dis;
  Graph g("airports.dat", "routes.dat");
  BFS b(g);
  string start = "DXB"; 
  string end = "ORD"; 
  Dijkstra d(g);
  // code from main for testing
  map<string, min_dist> distances = d.src(start);
  ofstream myfile ("DIJKSTRA_Log.txt");

  string s; 
  min_dist n; 
  if (myfile.is_open()) {
      for (const auto &item : distances) {
          if(item.first == end){
              dis = item.second;
          }
      }
      myfile.close();
  }
  if(dis == INFINITY){
      s = "No routes have been found between the starting airport and the destination airport."; 
  }
  else{
      n = dis; 
  }
  min_dist x(11653.8);

  // Margin of error with computations
  REQUIRE(std::abs(n.val_ - x.val_) < 0.1); 
}



