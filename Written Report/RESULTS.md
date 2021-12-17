# Final CS225 Project Report 
By Gally Huang, Jason Liu, Sakshi Rane, Veronica Perez

In this project we implemented a BFS and Dijkstra Algorithm to traverse airports throughout the world. We supplemented this with a Betweeness Centrality algorithm as well to help
the user understand which airports are most important.

![Dijkstra-test](https://github-dev.cs.illinois.edu/cs225-fa21/ghuang23-vperez35-jliu246-ssrane2/blob/main/Dijkstra's%20test.png?raw=true)

Since Dijkstra’s algorithm prints to the console rather than outputting a variable whose values can be checked, we manually tested by inserting source and destination airports in the main to made sure that the path and distances were correct. The program cout's the path immediately so this cannot be tested, but for the distances we have successfully implented a test for it. Therefore there are is only a test for distance for Dijkstra's Algorithm in the testing suite but we have confirmed all then paths to be correct by calculating the distances correctly. We can see that Dijkstra's Algorithm sucessfully checks for the shortest path a plane may take for trying to get from one location to another location. 

![BFS-test](https://github-dev.cs.illinois.edu/cs225-fa21/ghuang23-vperez35-jliu246-ssrane2/blob/main/bfs%20test.png?raw=true)

In order to test BFS we constructed a graph and called the algorithm on the known graph. The expected result is then compared to the actual output. In the picture above we tested routes with layovers while in the picture below we tested distances. This algorithm can be tested fully in our test suite for both the pathing and the distance. We can see it successfully tries and find out the path that had the least amount of layovers while also checking on the distance of this path, 

![BFS-testtwo](https://github-dev.cs.illinois.edu/cs225-fa21/ghuang23-vperez35-jliu246-ssrane2/blob/main/bfs%20test%202.png?raw=true)

![BetweenessCentrality](https://github-dev.cs.illinois.edu/cs225-fa21/ghuang23-vperez35-jliu246-ssrane2/blob/main/output2.png?raw=true)

The output of the betweenness centrality algorithm is a map of items where the keys matched the centrality measure of the vertex. Since betweenness centrality depended on Dijikstra’s algorithm, the development time was not fully realized. Test cases with directed unweighted graphs appeared to pass, but when weights were introduced, the output did not seem completely accurate. We expected O'Hare (airport ID = 3830) to have high centrality (it had 3.63723e+06) and, although it was in the top percentile for centrality, there was unexpected airports that appeared to have higher centrality than O'Hare. Our betweenness centrality outputs to the BC log file for easy read access. 

Therefore, for betweenness centrality, the run time is very long if we had to run it on the full airport files. We ran it and it took 2+ hours to run through the algorithm for our airports dataset. In accordance to Wikipedia, the run time is O(nm + n^2 * log(n)), as well as from Brandes. Because of this, we do not print the betweenness centrality into the console, but we shall rather print it into a file so it will be easier for the grader to grade and for the user to see all the data points. We did however create a much smaller dataset to test our betweenness centrality and we see that the centrality is correct for unweighted graphs. However, for a weighted graph it is really hard to tell if this is accurate by it appears to be **correct** from what we have been given. 

The only unexpected outcome for our results appear to be the betweenness centrality which has a long runtime. Due to this being the hard algorithm as well as not being discussed in class, we cannot confirm our results for the centrality but they appear to mimic correct behavior for some of the data (like O'Hare).

Our betweenness data appears to be working and we can see the output file for the betweenness centrality data that our program outputs in the .txt file logs. 

master/BFS_Log_2.txt ; centrality for ALL airports

master/BFS_Log_3.txt ; centrality for a small sample vertex.



In conclusion, our program performs BFS and Dijkstra Algorithm correctly on a set of real world data. We see that it traverse through these points correctly and we can verify this
by figuring out the distances by hand. Our betweenness centrality algorithm also performs the correct amount of centrality calculation for our overall dataset as well as an example one, albiet without us knowing the confirmed results.

Below are pictures of sample successful runs of our algorithms.
![Conclusion-picone](https://github-dev.cs.illinois.edu/cs225-fa21/ghuang23-vperez35-jliu246-ssrane2/blob/main/output.png?raw=true)

![Conclusion-pictwo](https://github-dev.cs.illinois.edu/cs225-fa21/ghuang23-vperez35-jliu246-ssrane2/blob/main/output2.png?raw=true)

