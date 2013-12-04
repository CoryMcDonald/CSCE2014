/* 
 * File:   main.cpp
 * Author: Cory
 *
 * Created on November 20, 2013, 7:58 PM
 */

#include <cstdlib>
#include <iostream>
#include "Token.h"
#include "Expression.h"


using namespace std;

#include <cstdlib>
#include <iostream>
using namespace std;

#ifndef STACK_H
#define	STACK_H

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

#endif	/* STACK_H */

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


int main(int argc, char** argv) {
    string input = "2+3"; 
    string action = "=";
    string additionalInput = "";
    bool continueExecution = true;
    stack<int> expressionStack;
    
    cout << "=== expression evaluation program starts ===" << endl;
    
    do
    {
        if(input == "")
        {
            cin >> input;
        }
        
        cout << "Action:";        
        cin >> action;
        
        //Lower casing action so don't have to look for q || Q && c || C, etc
        //todo Determine if it's neccessary to validate if action is > 1 char
        switch(tolower(action.c_str()[0]))
        {
            case '=' :
                //todo implement evaluation of expression
                break;
            case '>' :
                //todo implement prefix notion
                break;
            case '<' :
                //todo implement postfix notion
                break;
            case 'f' :
                //todo convert each expression in the sequence of expressions to the equivalent
                //fully parenthesized expression.
                break;
            case 'c' :
                cout << "Input: ";
                cin >> additionalInput;
                input += additionalInput;
                break;
            case 'q' :
                    continueExecution = false;
                    break;
            case 's' :
                    input = "";
                    //    s : start over for a new sequence of expressions
                    break;
            default :                
                cout <<"Invalid action" << endl;                
                break;      
        }
    }while (continueExecution);
    
    return 0;
}

