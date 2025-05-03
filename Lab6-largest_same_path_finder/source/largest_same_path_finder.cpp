#include "largest_same_path_finder.h"
#include <queue>

void largest_same_path_finder::input_information_and_output_result(std::istream& is, std::ostream& os) {
    unsigned int num_city, num_query, temp_a, temp_b;
    is >> num_city >> num_query >> this->capital >> this->resort;
    for (unsigned int i = 1; i < num_city; i++) {
        is >> temp_a >> temp_b;
        this->adjacency_list[temp_a].push_back(temp_b);
        this->adjacency_list[temp_b].push_back(temp_a);
    }
    for (unsigned int i = 0; i < num_query; i++) {
        is >> temp_a;
        bfs(temp_a);
        set_path();
        auto it_path_to_capital = this->path_to_capital.begin();
        auto it_path_to_resort = this->path_to_resort.begin();
        while (
            (++it_path_to_capital != this->path_to_capital.end()) &&
            (++it_path_to_resort != this->path_to_resort.end())
        ) {
            if ((*it_path_to_capital) != (*it_path_to_resort)) {
                break;
            }
        }
        os << *(--it_path_to_capital) << std::endl;
    }
}

largest_same_path_finder::largest_same_path_finder(): capital(0), resort(0) {}

largest_same_path_finder::~largest_same_path_finder() {
    this->adjacency_list.clear();
    this->vertex_to_capital.clear();
    this->vertex_to_resort.clear();
    this->path_to_capital.clear();
    this->path_to_resort.clear();
}

void largest_same_path_finder::bfs(const unsigned int& from) {
    vertex initial_vertex;
    initial_vertex.color = 'w';
    initial_vertex.parent = 0xFFFFFFFF;
    initial_vertex.distance = 0xFFFFFFFF;
    for (const auto& al : this->adjacency_list) {
        this->vertex_to_capital[al.first] = initial_vertex;
        this->vertex_to_resort[al.first] = initial_vertex;
    }
    this->vertex_to_capital[from].color = 'g';
    this->vertex_to_capital[from].distance = 0;
    std::queue<unsigned int> q;
    q.push(from);
    unsigned int temp;
    while (!q.empty()) {
        temp = q.front();
        for (const auto& q_adj : this->adjacency_list[temp]) {
            if (this->vertex_to_capital[q_adj].color == 'w') {
                this->vertex_to_capital[q_adj].color = 'g';
                this->vertex_to_capital[q_adj].parent = temp;
                this->vertex_to_capital[q_adj].distance = this->vertex_to_capital[temp].distance + 1;
                q.push(q_adj);
            }
        }
        this->vertex_to_capital[temp].color = 'b';
        q.pop();
    }
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

void largest_same_path_finder::set_path() {
    unsigned int current_vertex;
    this->path_to_capital.clear();
    current_vertex = this->capital;
    this->path_to_capital.push_front(current_vertex);
    while (this->vertex_to_capital[current_vertex].distance > 0) {
        this->path_to_capital.push_front(this->vertex_to_capital[current_vertex].parent);
        current_vertex = this->vertex_to_capital[current_vertex].parent;
    }
    this->path_to_resort.clear();
    current_vertex = this->resort;
    this->path_to_resort.push_front(current_vertex);
    while (this->vertex_to_resort[current_vertex].distance > 0) {
        this->path_to_resort.push_front(this->vertex_to_resort[current_vertex].parent);
        current_vertex = this->vertex_to_resort[current_vertex].parent;
    }
}
