/* 
 * File:   main.cpp
 * Author: Cory
 *
 * Created on November 20, 2013, 7:58 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

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

//STACKS/////////////////////////////////////////////////////////////////////||
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
string lowerCaseStringorAppendInput(string input, bool continueInput)
{
    if(continueInput)
    {
        string tempInput;
        cout << "Continue Input:";
        cin >> tempInput;    
        input += tempInput;
    }
    string temp;
    //Convert input to lowercase (since case does not matter)
    for (string::size_type i=0; i<input.length(); i++)
       temp += tolower(input[i]);    
    return temp;
}

int main(int argc, char** argv) {
    string input = "(2+3)*4, 2+3*4"; 
    string action = "=";
    
    cout << "=== expression evaluation program starts ===" << endl;
    bool continueExecution = true;
    do
    {
        if(input == "")
        {
            cin >> input;
            input = lowerCaseStringorAppendInput(input, false);
        }
        
        cout << "Action:";        
        cin >> action;
        //Lower casing action so don't have to look for q || Q && c || C, etc       
        switch(tolower(action.c_str()[0]))
        {
            case 'f' :
                //parenthesized 
                break;
            case 'c' :
                input = lowerCaseStringorAppendInput(input, true);
                break;
            case 'q' :
                    continueExecution = false;
                    break;
            case 's' :
                    input = "";
                    break;
            default :                
                cout <<"Invalid Input" << endl;                
                break;      
        }
    }while (continueExecution);
    
    //TODO Evaluate user input
//    = : evaluate each expression in the sequence of expressions.
//>
//: convert each expression in the sequence of expressions to the equivalent
//prefix expression.
//<
//: convert each expression in the sequence of expressions to the equivalent
//postfix expression.
//f : convert each expression in the sequence of expressions to the equivalent
//fully parenthesized expression.
//q : quit the program.
//c : continue inputting a sequence of expressions (the current sequence
//appends to the the previous sequence)
//    s : start over for a new sequence of expressions
    return 0;
}

