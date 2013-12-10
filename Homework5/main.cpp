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

string replaceInString(string originalString, string toReplace)
{
    string newString = "";
    //Check if the expression has equals, that'll determine
    //if we replace the letters, ex: a+b-c*d/e;a=1;b=2;c=3;d=4;e=5;                
    if(toReplace.find("=") != -1)
    {
        string variableReplacing = toReplace.substr(0,1);
        string valueToReplaceWith = toReplace.substr(2,toReplace.size());
        if(originalString.find(variableReplacing) != -1)
        {
                newString = originalString.replace(originalString.find(variableReplacing),
                        valueToReplaceWith.size(), valueToReplaceWith);
        }
    }else
    {
        if(originalString.find(toReplace) != -1)
        {
                newString = originalString.replace(originalString.find(toReplace), 1, " ");
        }else {
            newString = originalString;
        }
    }
    return newString;
}

int main(int argc, char** argv) {
    //string input ="";
    string input = "a+b-c*d/e;a=1;b=2;c=3;d=4;e=5;"; 
    //string input = "(2+3)*4;2+3*4;";
    //string input = "2+3;";
    string action = "=";
    string additionalInput = "";
    string originalExpression = "";
    string stringToReplace;
    bool continueExecution = true;
    Expression inputExpression;
    char * expressionToEvaluate;
    cout << "=== expression evaluation program starts ===" << endl;
    do
    {
        if(input == "")
        {
            do{                
                cout <<"Input: ";
                cin >> input;
            }while(input.find(";") == -1);            
        }
        
        cout << "Action:";        
        cin >> action;
        
        //todo clean up the code below
        //todo Add additional comments so you can follow what i'm doing
        //todo implement the parenthesis output
        //todo add error checking and try catch 
        
        if(action[0] == '=' || action[0] == '<' || action[0] == '>')
        {
            expressionToEvaluate = strdup(input.c_str());
            char * nextString;
            nextString = strtok (expressionToEvaluate, ";");
            originalExpression= string(expressionToEvaluate);
            stringToReplace = originalExpression;
            for(int i=0; nextString != NULL; i++)
            {  
                if(input.find("=") == -1)
                {
                    expressionToEvaluate = strdup(replaceInString(nextString, ";").c_str());
                }else
                {
                    if(i > 0)
                    {
                        expressionToEvaluate = strdup(replaceInString(expressionToEvaluate, nextString).c_str());  
                    }
                }             
                
                inputExpression.tokenized.clear();
                inputExpression.set(expressionToEvaluate);

                nextString = strtok(NULL, ";"); 
                
                switch(tolower(action.c_str()[0]))
                {
                    case '=' :   
                        if(input.find("=") == -1)
                        {
                            cout << expressionToEvaluate << " = " 
                              << inputExpression.evaluateExpression() << endl;
                        }else
                        {
                            if(nextString == NULL)
                            {
                                
                                 cout << originalExpression << " = " 
                                        << inputExpression.evaluateExpression() << endl;
                            }
                        }
                        break;
                    case '>' :
                        cout << "Prefix of " << originalExpression << " is: " 
                               << inputExpression.convertToPreFix() << endl;
                        break;
                    case '<' :
                        cout << "Postfix of " << originalExpression << " is: " 
                               << inputExpression.getPostfixString() << endl;
                        break;
                    default : break;
                } 
            }
                            continueExecution = false;

        }else
        {
            switch(tolower(action.c_str()[0]))
            {
                case 'f' :
                    //todo convert each expression in the sequence of expressions to the equivalent
                    //fully parenthesized expression.
                    break;
                case 'c' :
                    do{                
                        cout <<"Additional Input: ";
                        cin >> additionalInput;
                    }while(additionalInput.find(";") == -1);        
                    input += additionalInput;
                    break;
                case 'q' :
                        continueExecution = false;
                        break;
                case 's' :
                        input = "";
                        break;
                default :                
                    cout << "Invalid action" << endl;                
                    break;      
            }
        }
    }while (continueExecution);
    
    return 0;
}

