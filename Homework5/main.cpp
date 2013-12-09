/* 
 * File:   main.cpp
 * Author: Cory
 *
 * Created on November 20, 2013, 7:58 PM
 */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "Token.h"
#include "Expression.h"

using namespace std;

int main(int argc, char** argv) {
    string input = "a+b-c*d/e"; 
    //string input = "(2+3)*4";
    //string input = "2+3*4";
    //string input = "2+3";
    string action = ">";
    string additionalInput = "";
    bool continueExecution = true;
    Expression inputExpression;
        
    cout << "=== expression evaluation program starts ===" << endl;
    do
    {
        if(input == "")
        {
            cout <<"Input: ";
            cin >> input;    
        }
        
        cout << "Action:";        
        //cin >> action;
        
        switch(tolower(action.c_str()[0]))
        {
            case '=' :
                //Check if the expression has equals, that'll determine
                //if we replace the letters, ex: a+b-c*d/e;a=1;b=2;c=3;d=4;e=5;
                if(input.find(";"))
                {
                    char * inputCString = strdup(input.c_str());
                    char * nextString;
                    nextString = strtok (inputCString, ";");
                    while (nextString != NULL)
                    {
                        nextString = strtok(NULL, ";'");
                    }
                }else {
                    //evaluate like normal
                }
                break;
            case '>' :
                inputExpression.tokenized.clear();
                inputExpression.set(input);
                cout << "Prefix of " << input << " is: " 
                       << inputExpression.convertToPreFix() << endl;
                continueExecution = false;
                break;
            case '<' :
                inputExpression.tokenized.clear();
                inputExpression.set(input);
                cout << "Postfix of " << input << " is: " 
                       << inputExpression.getPostfixString() << endl;
                continueExecution = false;
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
                    break;
            default :                
                cout <<"Invalid action" << endl;                
                break;      
        }
    }while (continueExecution);
    
    return 0;
}

