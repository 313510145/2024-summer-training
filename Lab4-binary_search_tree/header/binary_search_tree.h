#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

// Struct representing a node in the binary search tree
struct node {
    int data;       // Value stored in the node
    node* left;     // Pointer to the left child node
    node* right;    // Pointer to the right child node
};

// Binary search tree (BST) class, which provides methods for inserting nodes,
// searching, and performing various operations on the tree
class binary_search_tree {
    public:
        // Method to input commands and produce the corresponding output
        void input_operation_and_output_result(std::istream& is, std::ostream& os);
        
        // Method to search for a specific value in the BST
        void search_value(std::ostream& os, const int& value) const;
        
        // Method to output the maximum and minimum values in the BST
        void output_max_min(std::ostream& os) const;
        
        // Constructor to initialize the BST
        binary_search_tree();
        
        // Destructor to clean up all nodes in the BST
        ~binary_search_tree();
    
    private:
        node* root;  // Pointer to the root node of the BST
        
        // Method to insert a new node into the BST
        void insert_node(const int& value);
        
        // Static method to output nodes within a specified range
        static void output_range_query(std::ostream& os, const int& low, const int& high, const node* const n);
        
        // Static method to recursively perform pre-order traversal
        static void recursive_pre_order(std::ostream& os, const node* const n);
        
        // Static method to recursively perform in-order traversal
        static void recursive_in_order(std::ostream& os, const node* const n);
        
        // Static method to recursively perform post-order traversal
        static void recursive_post_order(std::ostream& os, const node* const n);
        
        // Method to recursively delete all nodes in the BST
        static void delete_all_node(node* const n);
};

#endif  // BINARY_SEARCH_TREE_H
