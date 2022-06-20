#ifndef BST_HPP
#define BST_HPP

#include "bst.h"
using namespace cop4530;

// public member functions
// public member functions call their private counterparts
template<typename T>
BST<T>::BST(int th) : threshold{th} // constructor
{ } // init threshold and rootnode

template<typename T>
BST<T>::BST(const string input, int th) : threshold{th}  // init threshold and rootnode
{   buildFromInputString(input);   }    // constructor, call build from string

template<typename T>
BST<T>::BST(const BST &x)  // copy constructor
{   rootNode = clone(x.rootNode);   }   // call clone function

template<typename T>        
BST<T>::BST(BST &&x)      // move constructor
{   swap(rootNode, x.rootNode); }   // swap rootnodes

template<typename T>
BST<T>::~BST()  // destructor
{   makeEmpty();   }    // call make empty function

template<typename T>
void BST<T>::buildFromInputString(const string input)   // build tree from string
{
    makeEmpty(); // empty bst

    stringstream ss(input); // create stringstream object and init with input
    T tok;      // create T type to hold tokens in input
    while (ss >> tok)   // tokenize ss object
        { insert(tok); }    // insert each token into BST
}

template<typename T>
const BST<T> &BST<T>::operator=(BST<T> &x)  // copy assignment operator
{
    rootNode = clone(x.rootNode);   // clone rootNode
    return *this;
}

template<typename T>
const BST<T> &BST<T>::operator=(BST<T> &&x) // move assignment operator
{
    swap(x.rootNode,rootNode);  // swap rootNodes
    return *this;
}

template<typename T>
bool BST<T>::empty()    // check if tree is empty
{
    if (rootNode == nullptr)    // if root node is empty, rest of tree is empty
        return true;
    else 
        return false;    
}

template<typename T>
void BST<T>::printInOrder() const   
{   
    printInOrder(rootNode);
    cout<<endl;
}

template<typename T>
void BST<T>::printLevelOrder() const    // print elements in tree
{  printLevelOrder(rootNode);  }

template<typename T>
int BST<T>::numOfNodes() const  // return number of nodes in tree
{   return numOfNodes(rootNode);   }

template<typename T>
int BST<T>::height() const  // return height of tree
{   return height(rootNode);   }

template<typename T>
void BST<T>::makeEmpty()    // empty tree
{   makeEmpty(rootNode);   }

template<typename T>
void BST<T>::insert(const T& v)     // insert v into tree
{   insert(v, rootNode);   }

template<typename T>
void BST<T>::insert(T &&v)  // move version of insert
{   insert(move(v), rootNode);  }

template<typename T>
void BST<T>::remove(const T &v) // delete v from tree
{   remove(v, rootNode);   }

template<typename T>
bool BST<T>::contains(const T& v)   // search for v
{   return contains(v, rootNode);   }


// private member functions
template<typename T>
void BST<T>::printInOrder(BSTNode *t) const
{
    if (t!=nullptr) // check that bst isnt empty
    {
        printInOrder(t->leftNode);  // use recursion to print left and right nodes
        cout<<t->element<<" ";  // use pointers to access data
        printInOrder(t->rightNode); // more recursion
    }
}

template<typename T>
void BST<T>::printLevelOrder(BSTNode *t) const
{
    queue<BSTNode*> x;      // create queue of BSTNodes
    BSTNode* current = nullptr;     // init to null, used to iterate through tree

    if (t!=nullptr) {   // push root
        x.push(t);

        while(!x.empty()) { // continue until no longer empty
            current = x.front();    // update value of current element
            cout<<current->element<<" ";    // print contents

            if (current->leftNode != nullptr)   //check if node to the left is empty
                x.push(current->leftNode);      // print left node is not empty
            if (current->rightNode != nullptr)  // check if node to the right is empty
                x.push(current->rightNode);     // print right node is not empty
            x.pop();                            // call pop to remove current element from the queue
        }
    }
    cout<<endl; // formatting
}

template<typename T>
void BST<T>::makeEmpty(BSTNode* &t)
{
    if (t != nullptr)
    {
        makeEmpty(t->leftNode);     // recursively access left and right nodes to empty BST
        makeEmpty(t->rightNode);
        delete t;                   // delete element
    }
    t = nullptr;    // reinitialize t as nullptr
}

template<typename T>
void BST<T>::insert(const T& v, BSTNode *&t)
{
    if (t == nullptr)   // check if BST is empty
        { t = new BSTNode(v, nullptr, nullptr); }   // if empty, create new BSTNode object, w root v and null left and right nodes
    else if(v < t->element) // check values in order to insert in correct place in BST
        { insert(v, t->leftNode); }     // insert to left
    else if(t->element < v)
        { insert(v, t->rightNode); }    // insert to right
}

template<typename T>
void BST<T>::insert(T&& v, BSTNode *&t) // move version is the same as regular insert
{
    if (t == nullptr)  
        { t = new BSTNode(v, nullptr, nullptr); }
    else if(v < t->element)
        { insert(move(v), t->leftNode); }   // only difference is calling move function on v
    else if(t->element < v)
        { insert(move(v), t->rightNode); }
    else    
        return;
}

template<typename T>
void BST<T>::remove(const T& v, BSTNode *&t)
{
    if (t == nullptr)   // check if BST is empty
        { return; }
    else if (v < t->element)        // same logic as insert function here
        { remove(v, t->leftNode); }
    else if (t->element < v)
        { remove(v, t->rightNode); }
    else if (t->leftNode != nullptr && t->rightNode != nullptr) 
    {   // if left AND right nodes are not empty
            t->element = findMin(t->rightNode)->element;
            remove(t->element, t->rightNode);   
        }
    else 
    {
        BSTNode *oldNode = t;   //
        t = (t->leftNode != nullptr) ? t->leftNode : t->rightNode;
        delete oldNode;
    }
}

template<typename T>
bool BST<T>::contains(const T& v, BSTNode *&t)
{
    if (t == nullptr)   // check if BST is empty
        { return false ;}
    else if (v < t->element)    // use recursion to search tree
        { return contains(v, t->leftNode); }
    else if (t->element < v)
        { return contains(v, t->rightNode); }
    else
        { return true; }
}

template<typename T>
int BST<T>::numOfNodes(BSTNode *t) const
{
    if (t == nullptr)   // if BST is empty there is 0 nodes
        { return 0; }

    int n;
    n = n + numOfNodes(t->leftNode);    // use recursion to count # of nodes
    n = n + numOfNodes(t->rightNode);

    return n++; // account for root node
}

template<typename T>
int BST<T>::height(BSTNode *t) const
{
    if (t == nullptr)   // if BST is empty, tree has no height
        return -1;
    else
        return 1 + max(height(t->leftNode), height(t->rightNode));  // more recursion
}   // add 1 to account for root node

template<typename T>
typename BST<T>::BSTNode* BST<T>::clone(BSTNode* t) const
{
    if (t == nullptr)   // check if BST is empty
        return nullptr;
    else
        return new BSTNode{t->element, clone(t->leftNode), clone(t->rightNode)};    // if not call constructor, use new to create new object
}

template<typename T>
typename BST<T>::BSTNode* BST<T>::findMin(BSTNode* t) const // helper function from class examples
{
    if (t == nullptr)   // check if BST is empty
        return nullptr; 
    else if(t->leftNode == nullptr)
        return t;

    return findMin(t->leftNode);
}

template<typename T>
typename BST<T>::BSTNode* BST<T>::findMax(BSTNode *t) const // helper function from class examples
{
    if (t != nullptr)
        while(t->rightNode != nullptr)
            t = t->rightNode;
    return t;
}

#endif