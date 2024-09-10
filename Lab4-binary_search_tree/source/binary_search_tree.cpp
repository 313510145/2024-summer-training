#include "binary_search_tree.h"

// Method to process input commands and output results based on the operation
const void binary_search_tree::input_operation_and_output_result(std::istream& is, std::ostream& os) {
    char command; 
    int parameter, high;
    
    // Read commands from input stream
    while (is >> command) {
        switch (command) {
            case 'i':  // Insert command
                is >> parameter;
                insert_node(parameter);
                break;
            case 's':  // Search command
                is >> parameter;
                search_value(os, parameter);
                break;
            case 'm':  // Output max and min values
                output_max_min(os);
                break;
            case 'r':  // Output nodes in a given range
                is >> parameter >> high;
                os << "nodes in range [" << parameter << ", " << high << "]: ";
                output_range_query(os, parameter, high, this->root);
                os << std::endl;
                break;
            case 't':  // Output tree traversals (pre-order, in-order, post-order)
                os << "pre-order: ";
                recursive_pre_order(os, this->root);
                os << "\nin-order: ";
                recursive_in_order(os, this->root);
                os << "\npost-order: ";
                recursive_post_order(os, this->root);
                os << std::endl;
                break;
            case 'p':  // Output in-order traversal
                os << "in-order: ";
                recursive_in_order(os, this->root);
                os << std::endl;
                break;
        }
    }
}

// Method to search for a specific value in the BST and output the result
const void binary_search_tree::search_value(std::ostream& os, const int& value) const {
    node* temp = this->root;
    os << "search " << value << ": ";
    
    // Traverse the tree to find the value
    while (temp != nullptr) {
        if (temp->data == value) {
            os << "found\n";
            return;
        }
        else if (value < temp->data) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    os << "not found\n";
}

// Method to output the maximum and minimum values in the BST
const void binary_search_tree::output_max_min(std::ostream& os) const {
    node *max_ptr = this->root, *min_ptr = this->root;
    
    // Find the minimum value
    while (min_ptr->left != nullptr) {
        min_ptr = min_ptr->left;
    }
    
    // Find the maximum value
    while (max_ptr->right != nullptr) {
        max_ptr = max_ptr->right;
    }
    
    os << "max: " << max_ptr->data << ", min: " << min_ptr->data << std::endl;
}

// Constructor to initialize the root node as nullptr
binary_search_tree::binary_search_tree(): root(nullptr) {}

// Destructor to clean up all nodes in the BST
binary_search_tree::~binary_search_tree() {
    delete_all_node(this->root);
}

// Method to insert a new node with a given value into the BST
const void binary_search_tree::insert_node(const int& value) {
    node *n = new node, *temp;
    n->data = value;
    n->left = nullptr;
    n->right = nullptr;
    
    // If the tree is empty, set the new node as the root
    if (this->root == nullptr) {
        this->root = n;
        return;
    }
    
    temp = this->root;
    
    // Traverse the tree to find the correct position for the new node
    while (true) {
        if (value < temp->data) {
            if (temp->left == nullptr) {
                temp->left = n;
                break;
            } else {
                temp = temp->left;
            }
        } else if (value > temp->data) {
            if (temp->right == nullptr) {
                temp->right = n;
                break;
            } else {
                temp = temp->right;
            }
        } else {
            break;
        }
    }
}

// Recursive method to output nodes within a specified range [low, high]
const void binary_search_tree::output_range_query(std::ostream& os, const int& low, const int& high, const node* const n) {
    if (n == nullptr) {
        return;
    }
    
    // Traverse the left subtree
    output_range_query(os, low, high, n->left);
    
    // Output the node if it falls within the range
    if (n->data >= low && n->data <= high) {
        os << n->data << " ";
    }
    
    // Traverse the right subtree
    output_range_query(os, low, high, n->right);
}

// Recursive method to perform pre-order traversal (Root, Left, Right)
const void binary_search_tree::recursive_pre_order(std::ostream& os, const node* const n) {
    if (n == nullptr) {
        return;
    }
    os << n->data << " ";
    recursive_pre_order(os, n->left);
    recursive_pre_order(os, n->right);
}

// Recursive method to perform in-order traversal (Left, Root, Right)
const void binary_search_tree::recursive_in_order(std::ostream& os, const node* const n) {
    if (n == nullptr) {
        return;
    }
    recursive_in_order(os, n->left);
    os << n->data << " ";
    recursive_in_order(os, n->right);
}

// Recursive method to perform post-order traversal (Left, Right, Root)
const void binary_search_tree::recursive_post_order(std::ostream& os, const node* const n) {
    if (n == nullptr) {
        return;
    }
    recursive_post_order(os, n->left);
    recursive_post_order(os, n->right);
    os << n->data << " ";
}

// Recursive method to delete all nodes in the tree
const void binary_search_tree::delete_all_node(node* const n) {
    if (n == nullptr) {
        return;
    }
    delete_all_node(n->left);
    delete_all_node(n->right);
    delete n;  // Delete the node after its children are deleted
}
