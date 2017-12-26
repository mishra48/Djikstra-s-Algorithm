# Djikstra-s-Algorithm

This project implements the famous Djiktra's algorithm.

INPUT
You will be given two input files. The first input file will represent a map, which is an undirected graph whose vertices are points on a plane and are connected by edges whose weights are Euclidean distances. Think of the vertices as cities and the edges as roads connected to them. To represent such a map in a file, we list the number of vertices and edges on the first line, then list all the vertices (index followed by its x and y coordinates), and then list all the edges (pairs of vertices). 

Goal: 
Given a map file and a query file as inputs, this code computes the shortest path from each source listed in the query file to the corresponding destination using Dijkstra’s algorithm. Program takes the name of the map file and the name of the query file. Given these files, the program should then compute the shortest path for each query in the query file. 


compile using: 

gcc -Wall -Werror -lm shortest_path.c -o output

