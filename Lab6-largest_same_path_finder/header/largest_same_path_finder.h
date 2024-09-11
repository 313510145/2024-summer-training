#ifndef LARGEST_SAME_PATH_FINDER_H
#define LARGEST_SAME_PATH_FINDER_H

#include <iostream>
#include <unordered_map>
#include <list>

// Structure representing a vertex in the graph with BFS information
struct vertex {
    char color;         // Color for BFS traversal (white: 'w', gray: 'g', black: 'b')
    unsigned int parent; // Parent node in BFS tree
    unsigned int distance; // Distance from the source node
};

class largest_same_path_finder {
    public:
        // Reads input and performs BFS, then outputs the result
        const void input_information_and_output_result(std::istream& is, std::ostream& os);
        
        // Constructor to initialize the graph finder
        largest_same_path_finder();
        
        // Destructor to clean up memory
        ~largest_same_path_finder();
        
    private:
        // Performs BFS from a given starting vertex
        const void bfs(const unsigned int& from);
        
        // Sets the paths to capital and resort using BFS results
        const void set_path();
        
        // Adjacency list representing the graph
        std::unordered_map<unsigned int, std::list<unsigned int>> adjacency_list;
        
        // Maps to store BFS results for vertices in two scenarios (capital and resort)
        std::unordered_map<unsigned int, vertex> vertex_to_capital, vertex_to_resort;
        
        // Stores the path from a city to the capital and resort
        std::list<unsigned int> path_to_capital, path_to_resort;
        
        unsigned int capital, resort; // Store the capital and resort cities
};

#endif  // LARGEST_SAME_PATH_FINDER_H
