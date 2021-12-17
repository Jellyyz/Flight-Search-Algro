#include "main.h"

// use "make clean && make && clear && ./flight" to compile this program !!!
int main(){
    // use make && ./flight
    Graph g("airports.dat", "routes.dat");

    string start = " ";
    string end = " "; 

    // prompts user for starting airport
    cout << "Enter the starting airport(IATA): " << endl; 
    cin >> start;
    // prompts user for ending airport
    cout << "Enter the destination airport(IATA): " << endl;
    cin >> end;
    // converts the IATA into the name to create a vertex 
    string start_name = g.probe_name(start);                      // everything here 
    string end_name = g.probe_name(end);                          // here 
    auto start_num = g.vertices_.find(start);                     // until       
    auto end_num = g.vertices_.find(end);                         // this 
    size_t start_key = start_num ->second.get_index();            // line
    size_t end_key = end_num ->second.get_index();                // here shall just be used to make the vertexes for both BFS and Dijkstra



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Everything here below this line is BFS is working ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // creates BFS instance 
    BFS b(g);   
    if(start_name == "\\N" || end_name == "\\N"){
        cout << "Wrong input detected. Try again." << endl; 
        return 0;
    }
    cout << "===Breadth_First_Search Start========" << endl;
    cout << "The route with the least amount of layovers is: " << endl;
    Vertex startV(start, start_name, start_key);
    Vertex endV(end, end_name, end_key); 
    vector<string> bdir = b.bfs(startV, endV);
    if(bdir.empty()){
        return 0;
    }
    double distance = 0; 
    
    vector<string> bdirconverted;
    for(size_t i = 0; i < bdir.size(); i++){
        bdirconverted.push_back(g.probe_name(bdir.at(i)));
        cout << bdirconverted.at(i) << " -> ";
    }
    cout << "Finished." << endl;

    for(size_t i = 0; i <= bdir.size(); i++){
        string scc = bdir.at(i); 
        string dcc = bdir.at(i + 1); 
        distance += g.probe_dist(scc,dcc); 
        if(dcc == end){
            break; 
        }
    }
    
    cout << "This route takes " << distance << " kilometres." << endl; 

    cout << "===Breadth_First_Search End==========" << endl; 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Everything here above this line is BFS is working ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Everything here below this line is Dijkstra is working ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    min_dist dis;
    Dijkstra d(g);
    map<string, min_dist> distances = d.src(start);
    ofstream myfile ("DIJKSTRA_Log.txt");
    if (myfile.is_open()) {
        for (const auto &item : distances) {
            if(item.first == end){
                dis = item.second;
            }
        }
        myfile.close();
    }
    cout << endl;
    cout << "========Dijikstra_Start==============" << endl; 
    if(dis == INFINITY){
        cout << "No routes have been found between the starting airport and the destination airport." << endl; 
    }
    else{
        d.print_path(start, end);
        cout << "This route takes " << dis << " kilometres." << endl; 
    }
    cout << "========Dijikstra_End================" << endl; 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Everything here above this line is Dijkstra is working ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    Brandes brandes(g, -1); 
    string run_brandes = " ";
    
    cout << endl;
    cout << "========Betweenness_Centrality_Start==============" << endl; 
    cout << "Would you like to run Brandes Algorithm? (1 - Yes, else - No): " << endl; 
    cin >> run_brandes;
    if (run_brandes == "1") {
        vector<double> C = brandes.run();
        ofstream myfile2 ("BC_Log.txt");
        if (myfile2.is_open()) {
            for (size_t i = 0; i < C.size(); i++) {
                myfile2 << "Airports[" << i << "] has a centrality of " << C[i] << endl;
            }
            myfile2.close();
        }
        cout << "Stored results to `BC_Log.txt`." << endl;
    }
    cout << "========Betweenness_Centrality_End==============" << endl; 
    return 0;
}

