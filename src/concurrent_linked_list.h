//
// Created by Chris
//

#ifndef CONCURRENT_LINKEDLIST_CONCURRENT_LINKED_LIST_H
#define CONCURRENT_LINKEDLIST_CONCURRENT_LINKED_LIST_H

#include <random>
#include <mutex>
#include <climits>

template <class DataType>
struct NODE {

    DataType value;
    bool marked;
    NODE<DataType> *next;
    std::mutex n_lock;

    explicit NODE(DataType value) : value(value) , next(nullptr), marked(false){};
};

template <class DataType>
class LINKED_LIST {
private:
    NODE<DataType> *head;
    NODE<DataType> *tail;
    DataType min = std::numeric_limits<DataType>::min();
    DataType max = std::numeric_limits<DataType>::max();
public:
    LINKED_LIST();
    void find(NODE<DataType> *&curr, NODE<DataType> *&pred, DataType data);
    bool remove(DataType data);
    bool insert(DataType data);
    bool validate(NODE<DataType> *pred, NODE<DataType> *curr);
    void print();

};

template<class DataType>
bool LINKED_LIST<DataType>::validate(NODE<DataType> *pred, NODE<DataType> *curr) {
    return !pred->marked && !curr->marked && pred->next == curr;
}


template<class DataType>
void LINKED_LIST<DataType>::print() {
    if (head == nullptr) {
        std::cout << "HEAD -> NULL" << std::endl;
    } else {
        std::cout << "HEAD -> ";
        for (auto *i = head; i; i = i->next) {
            std::cout << i->value << " -> ";
        }
        std::cout << "NULL" << std::endl;
    }
}

template<class DataType>
bool LINKED_LIST<DataType>::insert(DataType data) {
    bool flag = false;
    while (true) {
        NODE<DataType> *pred = head;
        NODE<DataType> *curr = head->next;
        find(curr, pred, data);
        pred->n_lock.lock();
        curr->n_lock.lock();

        if (validate(pred, curr)) {
            if (curr->value == data) {
                flag = false;
            }
            else {
                NODE<DataType> *n_node = new NODE<DataType>(data);
                n_node->next = curr;
                pred->next = n_node;
                flag = true;
            }
            pred->n_lock.unlock();
            curr->n_lock.unlock();
            return flag;
        }
        pred->n_lock.unlock();
        curr->n_lock.unlock();
    }
}

template<class DataType>
bool LINKED_LIST<DataType>::remove(DataType data) {
    bool flag = false;
    while (true) {
        NODE<DataType> *pred = head;
        NODE<DataType> *curr = head->next;
        find(curr, pred, data);
        pred->n_lock.lock();
        curr->n_lock.lock();

        if (validate(pred, curr)) {
            if (curr->value != data) {
                flag = false;
                curr->n_lock.unlock();
            }
            else {
                curr->marked = true;
                pred->next = curr->next;
                curr->n_lock.unlock();
                delete curr;
                flag = true;
            }
            pred->n_lock.unlock();
            return flag;
        }
        pred->n_lock.unlock();
        curr->n_lock.unlock();
    }
}

template<class DataType>
void LINKED_LIST<DataType>::find(NODE<DataType> *&curr, NODE<DataType> *&pred, DataType data){
    while (curr->value < data) {
        pred = curr;
        curr = curr->next;
    }
}

template<class DataType>
LINKED_LIST<DataType>::LINKED_LIST() {
    head = new NODE<DataType>(min);
    tail = new NODE<DataType>(max);
    head->next = tail;
}


#endif //CONCURRENT_LINKEDLIST_CONCURRENT_LINKED_LIST_H
