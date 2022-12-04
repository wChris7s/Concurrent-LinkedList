#include <iostream>
#include <vector>
#include <thread>

#include "concurrent_linked_list.h"
#include "random_data.h"

using namespace std;

template<class DataType>
struct add {
    int min, max;
    LINKED_LIST<DataType> *ptr;

    add(int min, int max, LINKED_LIST<DataType> *ptr) : min(min), max(max), ptr(ptr) {};

    void operator()(int op) {
        random_data rd(min, max);
        for (int i = 0; i < op; i++) {
            ptr->insert(rd.get_random_int());
        }
    }
};

template<class DataType>
struct rem {
    int min, max;
    LINKED_LIST<DataType> *ptr;

    rem(int min, int max, LINKED_LIST<DataType> *ptr) : min(min), max(max), ptr(ptr) {};

    void operator()(int op) {
        random_data rd(min, max);
        for (int i = 0; i < op; i++) {
            ptr->remove(rd.get_random_int());
        }
    }
};

int main() {
    unsigned int th = thread::hardware_concurrency();
    unsigned int op = 20000;
    int min = 1, max = 20000;

    LINKED_LIST<int> LE;
    vector<thread *> add_t, rem_t;
    cout << "Threads: " << th << endl;
    for (int i = 0; i < th; i++) {
        thread *insert_th = new thread(add(min, max, &LE), op);
        add_t.push_back(insert_th);
    }
    for (int i = 0; i < th; i++) {
        add_t[i]->join();
    }
    // LE.print(); // Mostrar datos insertados.
    for (int i = 0; i < th; i++) {
        thread *rem_th = new thread(rem(min, max, &LE), op);
        rem_t.push_back(rem_th);
    }
    for (int i = 0; i < th; i++) {
        rem_t[i]->join();
    }
    LE.print();
    return 0;
}