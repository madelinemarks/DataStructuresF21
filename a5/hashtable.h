#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

namespace cop4530
{

template <typename T>
class HashTable
{
	public:
		HashTable(size_t size = 101);
        ~HashTable();
        
        bool contains(const T &x);

        bool insert(const T &x);
        bool insert(T &&x);
        bool remove(const T &x);

        void clear();
        
        bool load(const char *filename);
        void dump();

        bool write_to_file(const char *filename);

        int getSize();


	private:
		void makeEmpty();
        void rehash();

        size_t myhash(const T &x);

        unsigned long prime_below(long n);
        void setPrimes(std::vector<long> &vprimes);

        static const unsigned int default_capacity = 11;
        static const unsigned int max_prime = 1301081;

        std::vector<std::list<T>> theLists;
        int currentSize;

};

#include "hashtable.hpp"

}
#endif
