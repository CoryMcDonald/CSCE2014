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
    convertToPostFix();
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
void Expression::convertToPostFix()
{
    //This function converts the inputExpression passes into a vector of tokens
    vector<Token> postfixVector;
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
                        postfixVector.push_back(tokenStack.top());
                        tokenStack.pop();
                    }   
                    tokenStack.pop(); //pop openbrace
                }
                else //else if, higher, or equal pop and add to postfix string
                {         
                    while(!tokenStack.empty() && tokenStack.top().priority >= currentToken.priority)
                    {
                        postfixVector.push_back(tokenStack.top());
                        tokenStack.pop();
                    }
                    tokenStack.push(currentToken);
                }   
            }
        }else if(currentToken.type == integer || currentToken.type == letter)//if not operator add to postfix string
        {
            postfixVector.push_back(tokenized[i]);
        }              
    }
    //if stack is not empty pop rest of characters to postfix string
    while(!tokenStack.empty())
    {
        postfixVector.push_back(tokenStack.top());        
        tokenStack.pop();
    }   
    postfix = postfixVector;
}
string Expression::getPostfixString()
{
    string postfixString ="";
    for(int i=0; i< postfix.size(); i++)
    {
        postfixString += postfix[i].token + " "; 
    }
    return postfixString;
}
bool Expression::isValidExpression()
{
    //Wing Lee's notes on valid expressions
    bool eqtrue = false; // set to true if = is encountered
    states state = operand; // initial state value
    int pcount = 0; // for checking braces   
    valid = true; // a field in Expression class
    Token currentToken;
    
    //Loops through, compares the states and makes sure we don't run out of tokens
    for(int i =0; state != done && i < tokenized.size(); i++)
    {        
        currentToken = tokenized[i];
        
        switch(state)
        {
            case operand: 
                    if(currentToken.type == openbrace)
                    {
                        pcount++; //Increases parenthesis count so we can compare later
                    }else if(currentToken.type == integer || currentToken.type == letter)
                    {
                        state = func;
                    }else //invalid
                    {                       
                        valid = false;
                        state = done;
                    }
                 break;
            case func:
                if(currentToken.type == closebrace)
                {
                    pcount--;
                    if(pcount < 0)
                    {
                        valid = false;
                        state = done;
                    }
                }else if(currentToken.type == eq)
                {
                    eqtrue = true;
                    state = operand;
                }else if(currentToken.type == op)
                    state = operand;
                else {
                    valid = false;
                    state = done;
                }
                break;
            case done:
                break;
            default: break;
        }   
    }
    if(pcount != 0)
    {
        valid =false;
    }
   
    if( state == operand)
    {
        valid = false;
    }
    if(valid)
    {   
        if(eqtrue == true && tokenized.size() >= 2)
        {
            if(tokenized[0].type == letter &&  tokenized[2].type == integer)
            {
                type = assignment;
            }else
            {
                valid = false;
            }
        }       
    }
    return valid;
}
string Expression::convertToPreFix()
{
    string prefixString = "";
    stack<Token> operatorStack; 
    stack<string> outputStack; 

    Token currentToken;
    //Loops through each token and reads it to be in prefix mode
    for(int i =0; i < tokenized.size(); i++)
    {        
        currentToken = tokenized[i];
        //If it's a token let's add it to the stack
        if(currentToken.type == integer || currentToken.type == letter)
        {
            outputStack.push(currentToken.token);
        } //If it's an operator push it, but check to make sure stack doesn't have tokens on it
        else if(currentToken.type == openbrace || operatorStack.empty() || currentToken.priority > operatorStack.top().priority)
        {
            operatorStack.push(currentToken);
        }//If the type is a close brace we gotta make sure we close it right
        else if(currentToken.type == closebrace)
        {
            while(operatorStack.top().type != openbrace)
            {
                string right = outputStack.top(); //Get right operand                   
                outputStack.pop();
                
                string left = outputStack.top(); //Left operand                
                outputStack.pop();
                
                outputStack.push(operatorStack.top().token + " " + left + " " + right); //Microprefix
                operatorStack.pop();
            }
            operatorStack.pop();
        } 
        else if(currentToken.priority <= operatorStack.top().priority)
        {
            while(!operatorStack.empty() 
            && currentToken.priority <= operatorStack.top().priority)
            {
                string right = outputStack.top(); //Right                   
                outputStack.pop();
                
                string left = outputStack.top(); //Left                  
                outputStack.pop();
                
                outputStack.push(operatorStack.top().token + " " + left + " " + right); //Operator
                operatorStack.pop();
            }
            operatorStack.push(currentToken);
        }
    }
    //Add any leftover operators to the output
    while(!operatorStack.empty())
    {
        string right = outputStack.top(); //Right                   
        outputStack.pop();

        string left = outputStack.top(); //Left                  
        outputStack.pop();

        outputStack.push(operatorStack.top().token + " " + left + " " + right); //Operator
        operatorStack.pop();
    }
    //Adding it to the output
    while(!outputStack.empty())
    {
        prefixString += outputStack.top();
        outputStack.pop();
    }
    return prefixString;
}
string Expression::convertToParenthesis()
{
    //Basically the same as prefix however it rearranges the order of the operators and adds parenthesis
    string parenthesisString = "";
    stack<Token> operatorStack; 
    stack<string> outputStack; 

    Token currentToken;
    //Basic concept is that we loop and add to the stack if letter or number
    //If the operator is higher than that the exists, pop the last two operands off
    //wrap in parenthesis and then readd that to the stack.
    
    for(int i =0; i < tokenized.size(); i++)
    {        
        currentToken = tokenized[i];
      
        if(currentToken.type == integer || currentToken.type == letter)
        {
            outputStack.push(currentToken.token);
        }else if(currentToken.type == openbrace || operatorStack.empty() || currentToken.priority > operatorStack.top().priority)
        {
            operatorStack.push(currentToken);
        }else if(currentToken.type == closebrace)
        {
            while(operatorStack.top().type != openbrace)
            {
                string right = outputStack.top(); //Right                   
                outputStack.pop();
                
                string left = outputStack.top(); //Left                  
                outputStack.pop();
                
                outputStack.push("(" + left + " " + operatorStack.top().token + " " + right +")"); //Operator
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if(currentToken.priority <= operatorStack.top().priority)
        {
            while(!operatorStack.empty() 
            && currentToken.priority <= operatorStack.top().priority)
            {
                string right = outputStack.top(); //Right                   
                outputStack.pop();
                
                string left = outputStack.top(); //Left                  
                outputStack.pop();
                
                outputStack.push("(" + left + " " + operatorStack.top().token + " " + right +")"); //Operator
                operatorStack.pop();
            }
            operatorStack.push(currentToken);
        }
    }
    //Remove any other operators on the stack
    while(!operatorStack.empty())
    {
        string right = outputStack.top(); //Right                   
        outputStack.pop();

        string left = outputStack.top(); //Left                  
        outputStack.pop();

        outputStack.push("(" + left + " " + operatorStack.top().token + " " + right +")"); //Operator
        operatorStack.pop();
    }
    //Actually adding them to the string
    while(!outputStack.empty())
    {
        parenthesisString += outputStack.top();
        outputStack.pop();
    }
    return parenthesisString;
}
int Expression::evaluateExpression()
{     
    //Takes the postfix tokens and then evaluates them
    
    stack<Token> operatorStack; 
    stack<int> outputStack; 
    Token currentToken;
    int right = -1;
    int left = -1;
    for(int i =0; i < postfix.size(); i++)
    {    
        currentToken = postfix[i];
        //If it's an integer then add the int and wait for an operator
        if(currentToken.type == integer)
        {
            outputStack.push(atoi(currentToken.token.c_str()));
        }else if(currentToken.type == op)
        {
            //Make sure the stack isn't empty (basic validation) then do operation
            operatorStack.push(currentToken); 
            if(!outputStack.empty())
            {
                right = outputStack.top();
                outputStack.pop();
            }
            
            if(!outputStack.empty())
            {
                left = outputStack.top();
                outputStack.pop();
            }
            //Operate!
            if(operatorStack.top().token == "+")
                outputStack.push(left+right);
            else if(operatorStack.top().token == "-")
                outputStack.push(left-right);
            else if(operatorStack.top().token == "*")
                outputStack.push(left*right);
            else if(operatorStack.top().token == "/")
                outputStack.push(left/right);
            else if(operatorStack.top().token == "%")
                outputStack.push(left%right);

            operatorStack.pop();
        }
    }
    return outputStack.top();
}
string Expression::get_original() const
{
    return original;
}
vector<Token> Expression::get_tokenized() const
{
    return tokenized;
}
bool Expression::get_valid() const
{
    return valid;
}
exp_type Expression::get_type() const
{
    return type;
}
