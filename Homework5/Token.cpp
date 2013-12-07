/* 
 * File:   Token.cpp
 * Author: CXM072
 * 
 * Created on October 3, 2013, 4:05 PM
 */

#include "Token.h"
#include <iostream>
#include <stdlib.h>

 using namespace std;

 Token::Token() {
    //Default constructor
    type = invalid; 
    token = "";
    priority = -1;
}
Token::Token(string s) {
    set(s);    
}
void Token::set(string s) {    
    size_t LetterPosition = s.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"); 
    size_t NumberPosition = s.find_first_of("0123456789");
    size_t ParenthesisPosition = s.find_first_of("()");
    size_t OperatorPosition = s.find_first_of("+-*/%=");
    
    //Just making sure this gets set
    type = invalid;
    if(s.length() > 1)
    {
        //Will only work if there's only numbers in the string
        if(s[0] != 0 && NumberPosition != string::npos 
            && LetterPosition == string::npos
            && ParenthesisPosition == string::npos
            && OperatorPosition == string::npos)
        {
            type = integer;
        }
        //Type is already invalid so no need to do else
    }
    else if (s.length() == 1)
    {        
        if(LetterPosition != string::npos)
        {            
            type=letter;
        }else if(NumberPosition != string::npos)
        {
            type=integer;     
        }
        else
        {           
            switch(s[0])
            {
                case '=': 
                    type=eq;
                    break;
                case '+': 
                    type=op; 
                    priority = 4;
                    break;
                case '-': 
                    type=op;
                    priority = 4;
                    break;
                case '*': 
                    type=op;
                    priority = 5;                    
                    break;
                case '/': 
                    type=op;
                    priority = 5;                                        
                    break;
                case '%': 
                    type=op;
                    priority = 5;                                        
                    break;
                case '(': type=openbrace;
                    break;
                case ')': type=closebrace;
                    break;
                default:
                    type=invalid;
                    break;
            }
        }
    }
    else
    {
        cout << "Error no token passed"; //in the future this will throw exception
    }   
    token = s;
    //Assigning priority to token based on order of operations
    if(type == openbrace) 
        priority =1;
    else if (type == closebrace)
        priority =1;
    else if(type == integer)        
        priority=2; 
    else if(type == letter)
        priority = 3;  
    else if(type == eq) 
        priority = 6;
    else if(type == invalid)    
        priority =-1;

}
int Token::value() const {
    int returnValue = -1;
    if(type == integer)
    {
        //Converting token to be an int
        returnValue = atoi(token.c_str());
    }
    return returnValue;
}
void Token::display() const{    
    cout << "Token: " << token <<endl;
    cout << "Token Type: ";
    if(type == letter)
        cout << "letter" <<endl;
    else if(type == integer)        
        cout << "integer" <<endl;
    else if(type ==op)     
        cout << "op" <<endl;
    else if(type == eq) 
        cout << "eq" <<endl;
    else if(type ==openbrace) 
        cout << "openbrace" <<endl;
    else if (type == closebrace)
        cout << "closebrace" <<endl;
    else if(type == invalid)    
        cout << "invalid" <<endl;
    
    cout << "Priority: " << priority <<endl;
}
token_type Token::get_type() const
{
 return type;
}
string Token::get_token() const
{
    return token;
}
int Token::get_priority()  const
{ 
    return priority;
}
