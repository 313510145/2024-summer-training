#include "linked_list.h"
#include <unordered_set>

// Processes commands from input and outputs results
const void linked_list::input_operation_and_output_result(std::istream& is, std::ostream& os) {
    char command;  // Command character
    int parameter; // Parameter for the command
    
    // Read commands and process them
    while (is >> command) {
        switch (command) {
            case 'b': // Insert at beginning
                is >> parameter;
                insert_at_beginning(parameter);
                break;
            case 'e': // Insert at end
                is >> parameter;
                insert_at_end(parameter);
                break;
            case 'd': // Delete by value
                is >> parameter;
                delete_by_value(parameter);
                break;
            case 'r': // Reverse the list
                reverse_list();
                break;
            case 'c': // Remove duplicates
                remove_duplicate();
                break;
            case 'p': // Print the list
                output_list(os);
                break;
        }
    }
}

// Outputs the current state of the linked list
const void linked_list::output_list(std::ostream& os) const {
    node* temp = this->head; // Start from the head
    while (temp != nullptr) { // Traverse the list
        os << temp->data << " "; // Print data
        temp = temp->next; // Move to the next node
    }
    os << std::endl; // Newline after printing the list
}

// Constructor to initialize an empty linked list
linked_list::linked_list(): head(nullptr) {}

// Destructor to deallocate all nodes
linked_list::~linked_list() {
    delete_all_node(); // Clear all nodes
}

// Inserts a value at the beginning of the list
const void linked_list::insert_at_beginning(const int& value) {
    node* n = new node; // Create a new node
    n->data = value; // Set the node's data
    n->next = this->head; // Point to the current head
    this->head = n; // Update head to the new node
}

// Inserts a value at the end of the list
const void linked_list::insert_at_end(const int& value) {
    node *n = new node, *end; // Create a new node
    n->data = value; // Set the node's data
    n->next = nullptr; // New node is the last node
    
    if (this->head == nullptr) { // Empty list
        this->head = n; // Head points to the new node
        return;
    }
    end = this->head; // Start from the head
    while (end->next != nullptr) { // Traverse to the end
        end = end->next;
    }
    end->next = n; // Link the new node at the end
}

// Deletes nodes with a specific value
const void linked_list::delete_by_value(const int& value) {
    node *previous = nullptr, *current = this->head, *next;
    
    while (current != nullptr) {
        next = current->next; // Save next node
        if (current->data == value) { // Found the node to delete
            if (previous == nullptr) { // Node is the head
                this->head = next;
            } else {
                previous->next = current->next; // Bypass the node
            }
            current->next = nullptr; // Clear the next pointer
            delete current; // Delete the node
        } else {
            previous = current; // Move to the next node
        }
        current = next; // Move to the next node
    }
}

// Reverses the linked list
const void linked_list::reverse_list() {
    node *previous = nullptr, *current = this->head, *next;
    
    while (current != nullptr) {
        next = current->next; // Save the next node
        current->next = previous; // Reverse the link
        previous = current; // Move previous forward
        current = next; // Move current forward
    }
    this->head = previous; // Update head to the new first node
}

// Removes duplicate values from the list
const void linked_list::remove_duplicate() {
    std::unordered_set<int> s; // Set to track seen values
    node *temp_node = this->head, *first = nullptr, *tail = nullptr;
    
    while (temp_node != nullptr) {
        long unsigned int previous_size = s.size(); // Track set size before insert
        s.insert(temp_node->data); // Insert data into the set
        if (previous_size != s.size()) { // New value found
            node* n = new node; // Create a new node
            n->data = temp_node->data; // Set data
            n->next = nullptr; // New node will be at end
            if (tail != nullptr) {
                tail->next = n; // Link to the end
            } else {
                first = n; // First node in the new list
            }
            tail = n; // Update tail to the new node
        }
        temp_node = temp_node->next; // Move to the next node
    }
    delete_all_node(); // Delete old nodes
    this->head = first; // Set the head to the new list
}

// Deletes all nodes in the linked list
const void linked_list::delete_all_node() {
    while (this->head != nullptr) {
        node* temp = this->head; // Save the head node
        this->head = this->head->next; // Move head forward
        temp->next = nullptr; // Clear the next pointer
        delete temp; // Delete the old head node
    }
}
