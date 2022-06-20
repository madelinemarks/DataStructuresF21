#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <vector>

namespace cop4530 {

    template <typename T>
    class Stack {
        public:

        Stack();        // create empty stack
        ~Stack();       // destructor

        Stack(const Stack &rhs);    // copy constructor; create the new stack with the elements of existing stack rhs
        Stack(Stack &&rhs);         // move constructor; create the new stack with the elements of existing stack rhs

        Stack& operator=(const Stack &rhs);     // coppy assignment operator
        Stack& operator=(Stack &&rhs);      // move assignment operator

        bool empty() const;     // return true if stack is empty, false otherwise

        T& top();       // return reference to first element in the stack
        const T& top() const;   // const version

        void pop();     // remove first element in stack and discard
        void push(const T& val);         // add new element to stack
        void push(T&& val);         // add new element to stack; val should be moved instead of copied if possible

        int size() const;           // return the number of elements in the current stack

        private:
        std::vector<T> stack;
    };  // end of namespace cop4530
    #include "Stack.hpp"
}
#endif
