#include "largest_same_path_finder.h"
#include <queue>

// Reads input, processes the graph, and outputs the largest common path
const void largest_same_path_finder::input_information_and_output_result(std::istream& is, std::ostream& os) {
    unsigned int num_city, num_query, temp_a, temp_b;

    // Read number of cities, queries, and define the capital and resort cities
    is >> num_city >> num_query >> this->capital >> this->resort;
    
    // Read the graph edges (connections between cities)
    for (unsigned int i = 1; i < num_city; i++) {
        is >> temp_a >> temp_b;
        this->adjacency_list[temp_a].push_back(temp_b);
        this->adjacency_list[temp_b].push_back(temp_a);
    }

    // Process each query
    for (unsigned int i = 0; i < num_query; i++) {
        is >> temp_a;          // Read the query city
        bfs(temp_a);           // Perform BFS from the query city
        set_path();            // Set the paths to capital and resort
        
        auto it_path_to_capital = this->path_to_capital.begin();
        auto it_path_to_resort = this->path_to_resort.begin();

        // Traverse both paths and find the largest common city
        while (
            (++it_path_to_capital != this->path_to_capital.end()) &&
            (++it_path_to_resort != this->path_to_resort.end())
        ) {
            if ((*it_path_to_capital) != (*it_path_to_resort)) {
                break;
            }
        }

        // Output the last common city
        os << *(--it_path_to_capital) << std::endl;
    }
}

// Constructor initializes capital and resort to zero
largest_same_path_finder::largest_same_path_finder(): capital(0), resort(0) {}

// Destructor to clear all data structures
largest_same_path_finder::~largest_same_path_finder() {
    this->adjacency_list.clear();
    this->vertex_to_capital.clear();
    this->vertex_to_resort.clear();
    this->path_to_capital.clear();
    this->path_to_resort.clear();
}

// Perform BFS starting from a specific city to find paths to the capital and resort
const void largest_same_path_finder::bfs(const unsigned int& from) {
    vertex initial_vertex;
    initial_vertex.color = 'w';             // White color means unvisited
    initial_vertex.parent = 0xFFFFFFFF;     // No parent initially
    initial_vertex.distance = 0xFFFFFFFF;   // Infinite distance initially

    // Initialize all vertices to default (unvisited)
    for (const auto& al : this->adjacency_list) {
        this->vertex_to_capital[al.first] = initial_vertex;
        this->vertex_to_resort[al.first] = initial_vertex;
    }

    // Perform BFS for capital
    this->vertex_to_capital[from].color = 'g';    // Mark start vertex as gray (visited)
    this->vertex_to_capital[from].distance = 0;   // Distance from itself is 0
    std::queue<unsigned int> q;
    q.push(from);                                 // Push start vertex onto queue

    unsigned int temp;
    while (!q.empty()) {
        temp = q.front();
        for (const auto& q_adj : this->adjacency_list[temp]) {
            if (this->vertex_to_capital[q_adj].color == 'w') { // If adjacent node is unvisited
                this->vertex_to_capital[q_adj].color = 'g';    // Mark as visited
                this->vertex_to_capital[q_adj].parent = temp;  // Set parent to the current node
                this->vertex_to_capital[q_adj].distance = this->vertex_to_capital[temp].distance + 1;
                q.push(q_adj);
            }
        }
        this->vertex_to_capital[temp].color = 'b'; // Mark current node as fully processed
        q.pop();
    }

    // Perform BFS for resort in a similar manner
    this->vertex_to_resort[from].color = 'g';
    this->vertex_to_resort[from].distance = 0;
    q.push(from);
    while (!q.empty()) {
        temp = q.front();
        for (const auto& q_adj : this->adjacency_list[temp]) {
            if (this->vertex_to_resort[q_adj].color == 'w') {
                this->vertex_to_resort[q_adj].color = 'g';
                this->vertex_to_resort[q_adj].parent = temp;
                this->vertex_to_resort[q_adj].distance = this->vertex_to_resort[temp].distance + 1;
                q.push(q_adj);
            }
        }
        this->vertex_to_resort[temp].color = 'b';
        q.pop();
    }
}

// Set the path to the capital and resort using BFS results
const void largest_same_path_finder::set_path() {
    unsigned int current_vertex;

    // Clear and set path to capital
    this->path_to_capital.clear();
    current_vertex = this->capital;
    this->path_to_capital.push_front(current_vertex);
    while (this->vertex_to_capital[current_vertex].distance > 0) {
        this->path_to_capital.push_front(this->vertex_to_capital[current_vertex].parent);
        current_vertex = this->vertex_to_capital[current_vertex].parent;
    }

    // Clear and set path to resort
    this->path_to_resort.clear();
    current_vertex = this->resort;
    this->path_to_resort.push_front(current_vertex);
    while (this->vertex_to_resort[current_vertex].distance > 0) {
        this->path_to_resort.push_front(this->vertex_to_resort[current_vertex].parent);
        current_vertex = this->vertex_to_resort[current_vertex].parent;
    }
}
