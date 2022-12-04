//
// Created by Chris
//

#ifndef CONCURRENT_LINKEDLIST_RANDOM_DATA_H
#define CONCURRENT_LINKEDLIST_RANDOM_DATA_H

#include <random>
#include <iostream>


struct random_data {
public:
    random_data(int min, int max) : min(min), max(max) {};
    int get_random_int() const;
    double get_random_float() const;

private:
    int min;
    int max;
};

int random_data::get_random_int() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}

double random_data::get_random_float() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(gen);
}


#endif //CONCURRENT_LINKEDLIST_RANDOM_DATA_H
