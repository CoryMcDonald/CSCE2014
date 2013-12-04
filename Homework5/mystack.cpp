/* 
 * File:   mystack.cpp
 * Author: Cory
 * 
 * Created on December 3, 2013, 7:43 PM
 */

#include "mystack.h"

template <class T>
stack<T>::stack() {

    cap = 4;
    index = 0;
    arr = new int[cap];
}
template <class T>
stack<T>::~stack() {
    delete [] arr;
    cout << "destructed stack" << endl;
}
template <class T>
bool stack<T>::empty() const {

    return (index == 0);
}
template <class T>
unsigned int stack<T>::size() const {
    
    return index;
}
template <class T>
T& stack<T>::top() {

    if (!empty())
    {
        return arr[index-1];
    }
}
template <class T>
const T& stack<T>::top() const 
{
    if (!empty())
    {
        return arr[index-1];
    }
}
template <class T>
void stack<T>::push(const T& x)
{
    if (index > cap-1) {
        cap = cap*2;
        int * newarr = new int[cap];
        for (int i = 0; i < index;i++) {
            newarr[i] = arr[i];
        }
        delete arr;
        arr = newarr;
        cout << "capacity doubled" << endl;
    }
    arr[index]= x;
    index++;
}
template <class T>
void stack<T>::pop() 
{
    if (!empty())
    {
        index--;
    }
}
template <class T>
void stack<T>::display()
{
    if (!empty()) {
        for (int i = index-1; i >= 0;i--) {
            cout << "index : " << i << " : val : " << arr[i] << endl;
        }
    }
    else {
        cout << "empty stack" << endl;
    }
}