/* 
 * File:   Expression.cpp
 * Author: cxm072
 * 
 * Created on October 8, 2013, 12:02 PM
 */

#include "Expression.h"
#include <iostream>
using namespace std;

Expression::Expression() {
    type = illegal;
    original = "";
    valid = false;
}
Expression::Expression(const string& s)
{
    set(s);
}
void Expression::set(const string& s)
{   
    original = s;
    int begin, end;
    begin = tokenstart(0,s);
    while(begin < s.length())
    {
        end = tokenend(begin,s);
        Token expressionToken = Token(s.substr(begin, (end-begin)+1));
        tokenized.push_back(expressionToken);
        begin = tokenstart(end+1, s);
   }    
}
int Expression::tokenstart(int pos, string s)
{
    //removes leading whitespace
    while(pos < s.length() && s[pos] == ' ') pos++;
    return pos;
}
int Expression::tokenend(int pos, string s)
{
    int start = pos;
    //Loops until finds token and then returns that position
    while(pos < s.length() 
            && s[pos] != '('
            && s[pos] != ')'
            && s[pos] != '+'
            && s[pos] != '-'
            && s[pos] != '*'
            && s[pos] != '/'
            && s[pos] != '%'
            && s[pos] != '='
            && s[pos] != ' ')
    {        
        pos++;
    }
    if(start != pos)
    {
        pos--;
    }
    return pos;
}
void Expression::display() const
{
    for(int i =0; i <tokenized.size(); i++)
    {        
        tokenized[i].display();
    }
}
string Expression::convertToPostFix()
{
    string postfixString = "";
    stack<Token> tokenStack; 
    Token currentToken;
    for(int i =0; i <tokenized.size(); i++)
    {        
        currentToken = tokenized[i];
        if(currentToken.type == op || currentToken.type == openbrace 
                || currentToken.type == closebrace)
        {
            if(tokenStack.empty())//if operator add to stack
            {
                tokenStack.push(currentToken);
            }else //If stack is not empty check priority of top operator
            {
                //if lower precedence push to stack
                if(tokenStack.top().priority < currentToken.priority)
                {
                    tokenStack.push(currentToken);
                }else if(currentToken.type == closebrace)
                {
                    while(tokenStack.top().type != openbrace)
                    {
                        postfixString += tokenStack.top().token;
                        postfixString += " "; 
                        tokenStack.pop();
                    }   
                }
                else //else if, higher, or equal pop and add to postfix string
                {         
                    postfixString += tokenStack.top().token;
                    postfixString += " "; 
                    tokenStack.pop();
                }   
            }
        }else if(currentToken.type == integer)//if not operator add to postfix string
        {
            postfixString += tokenized[i].token;
            postfixString += " "; 
        }              
    }
    //if stack is not empty pop rest of characters to postfix string
    while(!tokenStack.empty())
    {
        if(tokenStack.top().type != openbrace)
        {
            postfixString += tokenStack.top().token;
            postfixString += " ";
        }
        tokenStack.pop();
    }

    return postfixString;
}
string Expression::get_original() const
{
    return original;
}
vector<Token> Expression::get_tokenized() const
{
    return tokenized;
}
vector<Token> Expression::get_postfix() const
{
    return postfix;
}
bool Expression::get_valid() const
{
    return valid;
}
exp_type Expression::get_type() const
{
    return type;
}
