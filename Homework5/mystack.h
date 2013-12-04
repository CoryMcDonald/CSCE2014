/* 
 * File:   mystack.h
 * Author: Cory
 *
 * Created on December 3, 2013, 7:43 PM
 */

#ifndef MYSTACK_H
#define	MYSTACK_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <class T>
class stack{
public:
    stack();
    ~stack();
    bool empty() const;
    unsigned int size() const;
    T& top();
    const T& top() const;
    void push(const T& x);
    void pop();
    void display();
private:
    T * arr;
    unsigned int cap; //capacity
    int index;        //index of array
};


#endif	/* MYSTACK_H */

