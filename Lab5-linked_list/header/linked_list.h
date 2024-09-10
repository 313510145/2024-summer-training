#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

// Node structure for the linked list
struct node {
    int data;         // Data stored in the node
    node* next;       // Pointer to the next node in the list
};

class linked_list {
    public:
        // Processes commands from input and outputs results
        const void input_operation_and_output_result(std::istream& is, std::ostream& os);
        
        // Outputs the current state of the linked list
        const void output_list(std::ostream& os) const;
        
        // Constructor to initialize an empty linked list
        linked_list();
        
        // Destructor to deallocate all nodes
        ~linked_list();
        
    private:
        node* head;  // Pointer to the head of the linked list
        
        // Inserts a value at the beginning of the list
        const void insert_at_beginning(const int& value);
        
        // Inserts a value at the end of the list
        const void insert_at_end(const int& value);
        
        // Deletes nodes with a specific value
        const void delete_by_value(const int& value);
        
        // Reverses the linked list
        const void reverse_list();
        
        // Removes duplicate values from the list
        const void remove_duplicate();
        
        // Deletes all nodes in the linked list
        const void delete_all_node();
};

#endif  // LINKED_LIST_H
