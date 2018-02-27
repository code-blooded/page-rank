This program can be run either on the wiki dataset or on a random graph.

To run this program on a random graph,
Run "g++ main.cpp -o main", this produces the output(ie. the pageranks in "Page_Rank_rg.txt") for every node

Note: To generate a new graph
Run "javac random_graph_generation" followed by "java random_graph_generation"
This creates a new graph in "rg.txt"

To run this program on the wiki dataset, 
1) On line 133 change "rg.txt" to "edges.txt" 
2) On line 121 change "Page_Rank_rg.txt" to "Page_Rank.txt"
Run "g++ main.cpp -o main", this produces the output(ie. the pageranks in "Page_Rank.txt") for every node