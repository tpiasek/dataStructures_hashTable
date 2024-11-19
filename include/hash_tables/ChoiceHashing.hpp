#pragma once
#ifndef CHOICE_HASHING_HASH_TABLE_H_
#define CHOICE_HASHING_HASH_TABLE_H_

#include "HashTable.hpp"
#include <iostream>
#include <vector>
#include <random>


class ChoiceHashingHashTable : public HashTable {
private:
    std::vector<int> table;
    int capacity;
    int size;
    float loadFactor;
    int prime;
    int a, b; // Random coefficients for universal hashing

    int hash1(int key) {
        // Universal Hash Function 1
        return ((a * key + b) % prime) % capacity;
    }

    int hash2(int key) {
        // Universal Hash Function 2
        return (key / capacity) % capacity;
    }

    void resize() {
        std::vector<int> oldTable = table;
        capacity *= 2;
        table = std::vector<int>(capacity, -1);
        size = 0;

        for (int key : oldTable) {
            if (key != -1) {
                insert(key);
            }
        }
    }

public:
    ChoiceHashingHashTable(int cap) : capacity(cap), size(0), loadFactor(0.75), prime(101) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, prime - 1);
        a = dis(gen);
        b = dis(gen);
        table.resize(capacity, -1); // -1 indicates empty slot
    }

    void insert(int key) {
        if ((float)size / capacity >= loadFactor) {
            resize();
        }

        int index1 = hash1(key);
        if (table[index1] == -1) {
            table[index1] = key;
        } else {
            int index2 = hash2(key);
            if (table[index2] == -1) {
                table[index2] = key;
            } else {
                // Collision resolution by linear probing
                int i = (index1 + 1) % capacity;
                while (table[i] != -1 && i != index1) {
                    i = (i + 1) % capacity;
                }
                if (i != index1) {
                    table[i] = key;
                }
            }
        }
        size++;
    }

    bool find(int key) {
        int index1 = hash1(key);
        if (table[index1] == key) {
            return true;
        }
        int index2 = hash2(key);
        if (table[index2] == key) {
            return true;
        }
        // Check the entire table if necessary
        for (int i = 0; i < capacity; i++) {
            if (table[i] == key) {
                return true;
            }
        }
        return false;
    }

    void deleteKey(int key) {
        int index1 = hash1(key);
        if (table[index1] == key) {
            table[index1] = -1;
            size--;
            return;
        }
        int index2 = hash2(key);
        if (table[index2] == key) {
            table[index2] = -1;
            size--;
            return;
        }
        // Check the entire table if necessary
        for (int i = 0; i < capacity; i++) {
            if (table[i] == key) {
                table[i] = -1;
                size--;
                return;
            }
        }
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }
};

#endif //!CHOICE_HASHING_HASH_TABLE_H_