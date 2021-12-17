# CS 225 Final Project - Proposal (Complete Product)
Final Project for ghuang23-vperez35-jliu246-ssrane2.

1. **Leading Question**  
Your final project should have a clear conclusion or target goal – given a dataset and a code base that implements some graph algorithms, what can you learn from the dataset? Are you hoping to solve a specific problem? Are you hoping to produce a general search tool? Make sure that your entire team is on the same page for what a ‘successful’ project will look like. Be sure that your motivating question is solvable or your proposed final deliverable is reasonable as you will be expected to accomplish it.

*The goal of our final project is to utilize the [OpenFlights dataset](https://openflights.org/data.html) of airline routes and airports to find the preferred route from one airport to another, which is the route with the shortest flight distance. This can be useful in planning an optimal trip to a far-away land (but note that you may have to pay more money for a more efficient flight path). We will use the Betweenness Centrality Algorithm in order to try and figure out how many preferred routes will pass through a specific airport. This can be useful in determining whether centrality is a good measure of whether an airport is destroyed (i.e. do airports with low centrality get demolished? - note that OpenFlights data is some years old, so we can check).*

2. **Dataset Acquisition and Processing**  
Your final project must use at least one publicly accessible dataset and your proposal must clearly describe what dataset you have chosen to use. As part of this description, you must state how you will download, store, and process your data. This includes succinctly describing the data format and clearly identifying how said data will be used in your proposed graph data structures. Be advised that real world data is often messy and your proposed datasets may have errors or missing entries. Your proposal should also briefly describe how your group will handle these potential errors.

*With the OpenFlights database, our goal is to utilize the data to find the shortest flight path(s) from an airport to another. In order to achieve this, we will utilize the data to find the distance between airports and, in turn, determine the shortest path of airports (i.e. a flight path can be airport A, airport B, airport C, ..., on the way to the destination airport).  
Therefore, the airports will be the vertices and the edges will be the airline routes between airports. The edges have weights that denote the distance traveled between two vertices or airports (note that this will be a non-linear path between airports - refer to [great-circle distances](https://en.wikipedia.org/wiki/Great-circle_distance) for more information). Since real world data is often messy, we may find common errors and address them. We can build the code so that it can be easily improved upon in the future and easier to adapt if any changes appear.*

*However if the .dat file (contains data pertaining to OpenFlights) contains errors, which we will assume so, we can hard code some of the errors away by directly fixing the .dat file. We can also allow for the program to output "ERROR: This combination {combination in question} is invalid." or something within those lines in order to try and fix the issue when it appears during testing. We can recognize what combination is invalid and check the data against our code to catch the error in parsing. Of course, we must discard all broken values when they occur so then the user will not use them. But they will be marked down, so during testing, we can try to catch all of them.*

*Every dataset is formatted in comma-separated values. Airport data (airports.dat) is formatted such that each line has data fields of [airport id][airport name][airport city][country][IATA airport code][ICAO airport code][latitude][longtitude]. We can keep all the data separate and organized in more "user-friendly" code; with classes or with things that can be easily accessed or debugged in the future. Data files are stored directly inside of the repo (hard copied), and we shall have function(s) within our program that imports all the data by parsing the lines. A vertex signifies a unique airport (assign a unique identifier to each vertex found in the data while parsing - optionally add more members per vertex so that we can specify the airport more conveniently - ex. the airport name). Edges between two vertices signify the distance between the two airports.*


3. **Graph Algorithms**  
Your final project must implement at least two graph data algorithms as well as a graph traversal from the list of example goals or you must propose an algorithm or set of graph algorithms that represent an equivalent amount of coding development. Accordingly, your proposal should clearly state what algorithms you will complete by the projects end. When describing your choices, be sure to include the following: What are the inputs you expect each method to take in? What output are you expecting for each method? If there are multiple ways to implement an algorithm, what is your target big O or efficiency benchmark? For the more complex algorithms, be sure to include as part of the input any additional information you might need. For example, A* search requires a heuristic. If you choose to do A*, what are some possible heuristics you might use?

*The two graph data algorithms that we will be utilizing are Dijkstra's Algorithm and the Betweenness Centrality Algorithm.*

*By utilizing Dijkstra's Algorithm, we will calculate the shortest flight path(s) between two airports (i.e. a source airport and a destination airport) given that the graph of airports and airlines is initialized. Given that the graph is initialized, our graph class can accept two inputs, which are the source airport and the destination airport. There may be multiple ways to format the input airports (pointer to the vertex, unique OpenFlights identifier, unique IATA code, possibly more). The output will be the shortest flight path(s) from the source airport to the destination airport. This can be formatted as a vector of visited airports in the shortest flight path.*

*By utilizing the Betweenness Centrality Algorithm, we will compute the centrality of all airports (i.e. how many shortest flight paths pass through a given airport). We will require an initialized graph of airports and airlines. There may be additional / optional flags or arguments we pass to the algorithm. For example, we may want to exclude destination airports from gaining centrality or we may want to approximate the centrality (higher speed, lower accuracy). Testing the algorithm may enlighten us on flags we may want to include. The output will be a map such that each item or pair is (airport key - depends on vertex implementation, measure of centrality).*

*We will be using the BFS traversal algorithm to traverse through all the airports given a starting location and final destination. The goal is to utilize BFS to find the shortest flight path(s), basing it off the minimum number of connecting flights.*

4. **Timeline**  
As a team, identify a list of tasks such as data acquisition, data processing, completion of each individual algorithm, production of final deliverables, etc… and write a proposed timeline for the completion of these tasks. You are not required to adhere strictly to this timeline but it should represent a reasonable set of benchmarks to strive for. For example, stating that you will finish all graph algorithms over the span of a single week is not reasonable. You will be expected to accomplish at least some of these tasks by the mid-project checkin.

Proposed timeline:  
- [x] *Data acquisition:* 11/12  
- [x] *Data processing:* 11/18  
- [x] *Completion of BFS traversal* 11/18  
- [x] *Completion of Dijkstra's algorithm:*  11/24    
- [x] *Completion of Betweenness-Centrality:* 12/7  
- [x] *Write tests for the algorithms as they complete* 11/18, 11/24, 12/7, etc.  
- [x] *Production of final deliverables:* 12/10

**Signatures:**
Gally Huang, Veronica Perez, Jason Liu, Sakshi Rane