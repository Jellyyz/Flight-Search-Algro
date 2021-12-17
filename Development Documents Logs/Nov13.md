Team Communication goes here~!

-----November 13, 2021-----
*First concern is address the email sent out by our mentor*
Dataset Acquisition and Processing

How is the data formatted? What fields does it have?
-> The data is formatted through a .csv, has data fields of [airport name][airport city][country][IATA airport code][ICAO airport code][latitude][longtitude]

How is the data going to be stored?
-> We can keep all the data seperate and organized in more "user-friendly" code; with classes or with things that can be easily accessed in the future. 

How are you going to address errors in the data?
-> Try to build the code so that it can be easily improved upon in the future, and easier to adapt if any changes appear-
Ex. Putting all the variables inside the private: instead of inside a function so that we can scale easier in the future.

None of these questions are answered by your proposal.


Is your goal to find the shortest time between airports or shortest distance? Because the two are not necessarily correlated.
->Our goal is to find the shortest distance between two airports. 

Graph Algorithms

You cannot use the Landmark algorithm for your project as it is not listed on the Project Goals Document and because it's too simple of an algorithm 
(it's pretty much equivalent to Dijkstra's). It was listed by mistake on the OpenFlights dataset description document but has since been removed. 
You will not lose any points for choosing this algorithm now, but please come up with another one for the graph algorithm not studied in class.


There is no discussion about the specific inputs and outputs of the algorithms chosen.

-> Dijikstra's algorithm
    ->Input: Starting_flight (node), Ending_flight(node), entire graph (array,map, etc.)
    ->Output: Path for the flight (vector of what vertexes we pass through)
-> Betweeness centrality
    ->Input: Shortest paths, the airport we are calculating for
    ->Output: Amounts of [shortest] paths going through the airport

Proposed timeline:
When are you planning to finish the BFS implementation or write tests for your code?
-> We can finish the BFS implementation 11/18
-> Write tests for code 12/7

*Second concern is to structure the project and to assign roles to each person for each function to work on*

Setting up classes and objects, 

Processing of csv files, 

Breadth First Search, 
Dijisktra's Algorithm,
Betweeness Centrality, everyone

*if we have time* make a PNG file to look pretty

Endgame(video documentation and also presentation)

