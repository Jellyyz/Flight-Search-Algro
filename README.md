# ghuang23-vperez35-jliu246-ssrane2
Final Project for ghuang23-vperez35-jliu246-ssrane2

## Location of all our code, data, results:
code location for:

0. Main Parser -> master/parser.cpp 
1. BFS -> master/BFS.cpp
2. Dijkstra -> master/Algorithms/Dijikstra.cpp 
3. Betweencentrality -> master/Algorithms/betweencentrality.cpp 
4. Makefile -> master/Makefile
5. Tests -> master/testing/tests.cpp 
6. Outputs -> master/outputx.png 
    These outputs show what a basic output of our program can do. 
7. All the written reports -> master/Written Report/... 
8. Dev logs -> master/Development Documents Logs/... 
9. Project presentation -> https://youtu.be/G8IwalLcLeo

## How to compile our code: 

### For the testing suite:
1. Created general tests for the BFS algorithm that can test specific airports
2. Dijkstra prints to the console so it's harder to test. We have to manually verify the distance, and also manually check if it is the shortest route.
3. BC prints to the console so it's hard to test too. We have to manually verify the centrality of the airport by comparing amount of shortest path that pass through airport. 

Be in the root directory:

0. make clean 
1. make test
2. ./test


### For the code itself:
Be in the root directory:

0. make clean && make && clear && ./flight

After running the code, enter IATA data for airports and the program should do the rest. Here are a few sample ones. Enjoy!

ORD - Chicago O'Hare
DXB - Dubai 
LAX - Los Angeles
CDG - Paris
SOV - Moscow 
CAN - Cancun
