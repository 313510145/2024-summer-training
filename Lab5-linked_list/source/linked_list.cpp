#include "linked_list.h"
#include <unordered_set>

void linked_list::input_operation_and_output_result(std::istream& is, std::ostream& os) {
    char command;
    int parameter;
    while (is >> command) {
        switch (command) {
            case 'b':
                is >> parameter;
                insert_at_beginning(parameter);
                break;
            case 'e':
                is >> parameter;
                insert_at_end(parameter);
                break;
            case 'd':
                is >> parameter;
                delete_by_value(parameter);
                break;
            case 'r':
                reverse_list();
                break;
            case 'c':
                remove_duplicate();
                break;
            case 'p':
                output_list(os);
                break;
        }
    }
}

void linked_list::output_list(std::ostream& os) const {
    node* temp = this->head;
    while (temp != nullptr) {
        os << temp->data << " ";
        temp = temp->next;
    }
    os << std::endl;
}

linked_list::linked_list(): head(nullptr) {}

linked_list::~linked_list() {
    delete_all_node();
}

void linked_list::insert_at_beginning(const int& value) {
    node* n = new node;
    n->data = value;
    n->next = this->head;
    this->head = n;
}

void linked_list::insert_at_end(const int& value) {
    node *n = new node, *end;
    n->data = value;
    n->next = nullptr;
    if (this->head == nullptr) {
        this->head = n;
        return;
    }
    end = this->head;
    while (end->next != nullptr) {
        end = end->next;
    }
    end->next = n;
}

void linked_list::delete_by_value(const int& value) {
    node *previous = nullptr, *current = this->head, *next;
    while (current != nullptr) {
        next = current->next;
        if (current->data == value) {
            if (previous == nullptr) {
                this->head = next;
            }
            else {
                previous->next = current->next;
            }
            current->next = nullptr;
            delete current;
        }
        else {
            previous = current;
        }
        current = next;
    }
}

void linked_list::reverse_list() {
    node *previous = nullptr, *current = this->head, *next;
    while (current != nullptr) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    this->head = previous;
}

void linked_list::remove_duplicate() {
    std::unordered_set<int> s;
    node *temp_node = this->head, *first = nullptr, *tail = nullptr;
    while (temp_node != nullptr) {
        long unsigned int previous_size = s.size();
        s.insert(temp_node->data);
        if (previous_size != s.size()) {
            node* n = new node;
            n->data = temp_node->data;
            n->next = nullptr;
            if (tail != nullptr) {
                tail->next = n;
            }
            else {
                first = n;
            }
            tail = n;
        }
        temp_node = temp_node->next;
    }
    delete_all_node();
    this->head = first;
}

void linked_list::delete_all_node() {
    while (this->head != nullptr) {
        node* temp = this->head;
        this->head = this->head->next;
        temp->next = nullptr;
        delete temp;
    }
}
