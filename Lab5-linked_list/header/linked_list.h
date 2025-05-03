#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

struct node {
    int data;
    node* next;
};

class linked_list {
    public:
        void input_operation_and_output_result(std::istream& is, std::ostream& os);
        void output_list(std::ostream& os) const;
        linked_list();
        ~linked_list();
    private:
        node* head;
        void insert_at_beginning(const int& value);
        void insert_at_end(const int& value);
        void delete_by_value(const int& value);
        void reverse_list();
        void remove_duplicate();
        void delete_all_node();
};

#endif  // LINKED_LIST_H
