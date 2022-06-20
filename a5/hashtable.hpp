#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "hashtable.h"

template <typename T>
HashTable<T>::HashTable(size_t size): theLists{prime_below(size)}
{  currentSize = 0; }   // constructor

template <typename T>
HashTable<T>::~HashTable()
{   makeEmpty();   }    // destructor 

template <typename T>
bool HashTable<T>::contains(const T& x) // check if x is in the hashtable
{	
    auto & whichList = theLists[myhash(x)];
    return std::find(begin(whichList), end(whichList), x) != end (whichList);
}

template <typename T>
bool HashTable<T>::insert(const T &x)   // insert function
{	
    auto & whichList = theLists[ myhash(x) ];
    if (std::find(begin(whichList), end(whichList), x) != end(whichList))
        return false;

    whichList.push_back(x);

    if(++currentSize > theLists.size())
        rehash();

    return true;
}

template <typename T>
bool HashTable<T>::insert(T &&x)    // move version of insert
{	
    auto & whichList = theLists[ myhash(std::move(x)) ];
    if (std::find(begin(whichList), end(whichList), x) != end(whichList))
        return false;

    whichList.push_back(x);

    if(++currentSize > theLists.size())
        rehash();

    return true;
}

template <typename T>
bool HashTable<T>::remove(const T& x)   // remove x from hashtable
{	
    auto & whichList = theLists[ myhash(x) ];
    auto itr = std::find(begin(whichList), end(whichList), x);

    if (itr == end(whichList))
        return false;
    
    whichList.erase(itr);
    --currentSize;
    return true;
}

template <typename T>
void HashTable<T>::clear()  // clear hashtable
{   makeEmpty();   }

template <typename T>
bool HashTable<T>::load(const char* filename)   // load content of file into hashtable
{	
    std::ifstream in;
    std::string tok;

    in.open(filename);

    if(!in)
        return false;
    else
    {
        while(getline(in, tok))
        insert(tok);
        
        in.close();
        in.clear();

        return true;
    }

}

template <typename T>
void HashTable<T>::dump()   // print contents of hashtable
{	
    for(int i = 0; i<theLists.size(); i++)
	{
		std::cout<<"v["<<i<<"]: ";

		for(auto itr=theLists[i].begin(); itr!=theLists[i].end(); itr++)
			{ std::cout<<*itr<<"\t"; }

		std::cout<<std::endl;
	}
}

template <typename T>
bool HashTable<T>::write_to_file(const char* filename)  // write contents of hashtable to file
{	
    std::ofstream out;

    out.open(filename);
    if (!out)
        return false;

    else {
        for(int i = 0; i < theLists.size(); i++)
            for(auto itr = theLists[i].begin(); itr!=theLists[i].end(); itr++)
            out<<*itr<<std::endl;
        
        out.close();
        return true;
    }
}

template <typename T>
int HashTable<T>::getSize() // helper function to return current size
{   return currentSize;  }

template <typename T>
void HashTable<T>::makeEmpty()  // empty hashtable
{	
    for (auto & thisList : theLists)
        { thisList.clear(); }
    currentSize = 0;
}

template <typename T>
void HashTable<T>::rehash() // rehash to resize
{	
    std::vector<std::list<T>> oldLists = theLists;

    theLists.resize(prime_below(2*oldLists.size()));
    for (auto & e : theLists)
        { theLists.clear(); }
    
    currentSize = 0;
    for(auto & e : oldLists) 
    {
        for (auto & x : e)
        insert(std::move(x));
    }
}

template <typename T>
size_t HashTable<T>::myhash(const T& x) // return index of x
{	
    size_t i;
    for (auto & e : x)
        i = i * 37 + e;
    
    return i%(theLists.size());
}
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below (long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
    std::cerr << "** input too small \n";
      return 0;
    }

    // now: 2 <= n < max_prime
    std::vector <long> v (n+1);
    setPrimes(v);
    while (n > 2)
      {
        if (v[n] == 1)
    return n;
        --n;
      }

    return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

#endif
