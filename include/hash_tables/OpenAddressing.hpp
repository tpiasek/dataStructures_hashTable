#pragma once
#ifndef OPEN_ADDRESSING_HPP_
#define OPEN_ADDRESSING_HPP_

#include "HashTable.hpp"
#include <iostream>
#include <vector>

class OpenAddressingHashTable : public HashTable {
private:
    std::vector<int> table;
    int capacity;
    int size;
    float loadFactor;

    int hash(int key) {
        // Division Hash Function
        return key % capacity;
    }

    void resize() {
        std::vector<int> oldTable = table;
        capacity *= 2;
        table = std::vector<int>(capacity, -1);
        size = 0;

        for (int key : oldTable) {
            if (key != -1 && key != -2) { // Skip empty and deleted slots
                insert(key);
            }
        }
    }

public:
    OpenAddressingHashTable(int cap) : capacity(cap), size(0), loadFactor(0.75) {
        table.resize(capacity, -1); // -1 indicates empty slot
    }

    void insert(int key) {
        if ((float)size / capacity >= loadFactor) {
            resize();
        }
        int index = hash(key);
        while (table[index] != -1 && table[index] != -2) { // Skip deleted slots
            index = (index + 1) % capacity; // Linear probing
        }
        table[index] = key;
        size++;
    }

    bool find(int key) {
        int index = hash(key);
        int startIndex = index;
        while (table[index] != -1) {
            if (table[index] == key) {
                return true;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) break; // Table is full and looped back to start
        }
        return false;
    }

    void deleteKey(int key) {
        int index = hash(key);
        int startIndex = index;
        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -2; // -2 indicates deleted slot
                size--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) break; // Table is full and looped back to start
        }
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1 && table[i] != -2) {
                std::cout << table[i] << " ";
            } else if (table[i] == -2) {
                std::cout << "D ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }
};

#endif // !OPEN_ADDRESSING_HPP_