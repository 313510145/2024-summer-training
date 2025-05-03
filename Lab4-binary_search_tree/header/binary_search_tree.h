#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

struct node {
    int data;
    node* left;
    node* right;
};

class binary_search_tree {
    public:
        void input_operation_and_output_result(std::istream& is, std::ostream& os);
        void search_value(std::ostream& os, const int& value) const;
        void output_max_min(std::ostream& os) const;
        binary_search_tree();
        ~binary_search_tree();
    
    private:
        node* root;
        void insert_node(const int& value);
        static void output_range_query(std::ostream& os, const int& low, const int& high, const node* const n);
        static void recursive_pre_order(std::ostream& os, const node* const n);
        static void recursive_in_order(std::ostream& os, const node* const n);
        static void recursive_post_order(std::ostream& os, const node* const n);
        static void delete_all_node(node* const n);
};

#endif  // BINARY_SEARCH_TREE_H
