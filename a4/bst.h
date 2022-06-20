#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;
namespace cop4530 {


template <typename T>
class BST {
    public:

        BST(int th=1);  // constructor
        BST(const string input, int th=1);  // constructor

        BST(const BST &x);  // copy constructor
        BST(BST &&x);   // move constructor

        ~BST(); // destructor

        void buildFromInputString(const string input);  // for building BST from a string

        const BST& operator=(BST &x);   // copy assignment operator
        const BST& operator=(BST &&x);  // move assignment operator

        bool empty();   // check if empty

        void printInOrder() const;  // print inorder traversal
        void printLevelOrder() const;   // print levelorder 

        int numOfNodes() const; // count # of nodes
        int height() const; // count levels of BST

        void makeEmpty();   // empty the BST

        void insert(const T& v);    // insert an element
        void insert(T &&v); // move version of insert
        void remove(const T& v);    // delete an element

        bool contains(const T& v);  // search for an element

        // added find min and find max functions from class examples
        const T& findMin() const;
        const T& findMax() const;

        

    private:

        struct BSTNode{ // BSTNode struct w/ member data
            T element;          // elements of BST
            BSTNode* rightNode;     // right and left nodes
            BSTNode* leftNode;

            BSTNode(const T& theElement, BSTNode *lt, BSTNode *rt)  // constructors
                : element{theElement}, leftNode{lt}, rightNode {rt} {}
            BSTNode(T&& theElement, BSTNode *lt, BSTNode *rt)       // move constructor
                : element{move(theElement)}, leftNode{lt}, rightNode {rt} {}
            
        };

        // private versions of public member functions, where actual implementation will be
        void printInOrder(BSTNode *t) const;
        void printLevelOrder(BSTNode *t) const;

        void makeEmpty(BSTNode* &t);

        void insert(const T& v, BSTNode *&t);
        void insert(T&& v, BSTNode *&t);
        void remove(const T& v, BSTNode *&t);

        bool contains(const T& v, BSTNode *&t);

        int numOfNodes(BSTNode *t) const;
        int height(BSTNode *t) const;

        BSTNode *clone(BSTNode *t) const;

        BSTNode* rootNode = nullptr;    // root node, init to null ptr
        int default_threshold_value = 1;
        int threshold;

        // added findmin and findmax from class examples
        BSTNode* findMin(BSTNode* t) const;
        BSTNode* findMax(BSTNode* t) const;
        

    };
  #include "bst.hpp"
} 
#endif
