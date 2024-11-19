#pragma once
#ifndef SEPERATE_CHAINING_HPP_
#define SEPERATE_CHAINING_HPP_

#include "HashTable.hpp"
#include <iostream>
#include <list>
#include <vector>

class SeparateChainingHashTable : public HashTable {
private:
    std::vector<std::list<int>> table;
    int capacity;
    float loadFactor;
    int size;
    const double A = 0.6180339887; // Knuth's suggestion for multiplication hash

    int hash(int key) {
        // Multiplication Hash Function
        double frac = key * A;
        frac = frac - (int)frac;
        return (int)(capacity * frac);
    }

    void resize() {
        std::vector<std::list<int>> oldTable = table;
        capacity *= 2;
        table = std::vector<std::list<int>>(capacity);
        size = 0;

        for (auto& chain : oldTable) {
            for (int key : chain) {
                insert(key);
            }
        }
    }

public:
    SeparateChainingHashTable(int cap) : capacity(cap), size(0), loadFactor(0.75) {
        table.resize(capacity);
    }

    void insert(int key) {
        if ((float)size / capacity >= loadFactor) {
            resize();
        }
        int index = hash(key);
        table[index].push_back(key);
        size++;
    }

    bool find(int key) {
        int index = hash(key);
        for (int x : table[index]) {
            if (x == key) {
                return true;
            }
        }
        return false;
    }

    void deleteKey(int key) {
        int index = hash(key);
        table[index].remove(key);
        size--;
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            std::cout << i << ": ";
            for (auto& x : table[i]) {
                std::cout << x << " -> ";
            }
            std::cout << "NULL" << std::endl;
        }
    }
};

#endif // !SEPERATE_CHAINING_HPP_