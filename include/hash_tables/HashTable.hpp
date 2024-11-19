#ifndef HASH_TABLE_HPP_
#define HASH_TABLE_HPP_

#include <iostream>
#include <vector>
#include <list>

class HashTable {
public:
	virtual void insert(int key) = 0;
	virtual bool find(int key) = 0;
	virtual void remove(int key) = 0;
	virtual void print() = 0;
};

#endif // !HASH_TABLE_HPP_