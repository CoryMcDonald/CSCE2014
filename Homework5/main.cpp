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
//This function is used to substitute variables with ints 
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
    string input ="";
    //string input = "a+b-c*d/e;a=1;b=2;c=3;d=4;e=5;"; 
    //string input = "(2+3)*4;2+3*4;";
    //string input = "2+3;";
    string action = "";
    string additionalInput = "";
    string originalExpression = "";
    string stringToReplace;
    bool continueExecution = true;
    bool expressionHasSubstituion = false;
    bool inputIsInvalid = false;
    char * expressionToEvaluate;
    char * inputTokenized;
    Expression inputExpression;

    cout << "=== expression evaluation program starts ===" << endl;
    do
    {
        if(input == "")
        {
            //So this input is a little complicated i'll do the rundown
            //Take in input, make sure it can be tokenized
            //If it can, then separate it into it's different expressions and then validate
            //If all that is good then we can continue, else just loop until good
            do{                
                cout <<"Input: ";
                cin >> input;
                inputIsInvalid=false;
                
                if(input.find(";") != -1)
                {
                    inputTokenized = strdup(input.c_str());
                    char * nextInput;
                    nextInput = strtok (inputTokenized, ";");                

                    for(int i=0; nextInput != NULL; i++)
                    {  
                       inputExpression.tokenized.clear();
                       inputExpression.set(nextInput); 
                       if(!inputExpression.isValidExpression())
                       {
                           cout << "Invalid input" << endl;
                           inputIsInvalid = true;
                           break;
                       }                       
                       nextInput = strtok(NULL, ";");
                    }
                }else
                {
                    cout << "Invalid input" << endl;
                    inputIsInvalid = true;
                }
            }while(inputIsInvalid);            
        }
        
        //Reading in action
        cout << "Action:";        
        cin >> action;
        
        //If action requires us to work with the multiple expressions
        if(action[0] == '=' || action[0] == '<' || action[0] == '>' || action[0] == 'f')
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
                        expressionHasSubstituion = true;
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
                        if(!expressionHasSubstituion)
                        {
                             cout << "Prefix of " << expressionToEvaluate << " is: " 
                               << inputExpression.convertToPreFix() << endl;
                        }else if(i==0)
                        {
                             cout << "Prefix of " << originalExpression << " is: " 
                               << inputExpression.convertToPreFix() << endl;
                        }
                        break;
                    case '<' :
                        if(!expressionHasSubstituion)
                        {
                            cout << "Postfix of " << expressionToEvaluate << " is: " 
                                   << inputExpression.getPostfixString() << endl;
                        }else if(i==0)
                        {
                             cout << "Postfix of " << originalExpression << " is: " 
                               << inputExpression.getPostfixString() << endl;
                        }
                        break;
                    case 'f' :
                        if(!expressionHasSubstituion)
                        {
                           cout << "Parenthesis of " << expressionToEvaluate << " is: " 
                               << inputExpression.convertToParenthesis() << endl;
                        }else if(i==0)
                        {
                            cout << "Parenthesis of " << originalExpression << " is: " 
                               << inputExpression.convertToParenthesis() << endl;
                        }
                        break;
                    default : break;
                } 
            }           
        }else
        {
            switch(tolower(action.c_str()[0]))
            {
                case 'c' :
                do{          
                    //So this input is a little complicated i'll do the rundown
                    //Take in input, make sure it can be tokenized
                    //If it can, then separate it into it's different expressions and then validate
                    //If all that is good then we can continue, else just loop until good

                    cout <<"Additional Input: ";
                    cin >> additionalInput;
                    inputIsInvalid=false;

                    if(additionalInput.find(";") != -1)
                    {
                        inputTokenized = strdup(additionalInput.c_str());
                        char * nextInput;
                        nextInput = strtok (inputTokenized, ";");                

                        for(int i=0; nextInput != NULL; i++)
                        {  
                           inputExpression.tokenized.clear();
                           inputExpression.set(nextInput); 
                           if(!inputExpression.isValidExpression())
                           {
                               cout << "Invalid input" << endl;
                               inputIsInvalid = true;
                               break;
                           }                       
                           nextInput = strtok(NULL, ";");
                        }
                    }else
                    {
                        cout << "Invalid input" << endl;
                        inputIsInvalid = true;
                    }
                }while(inputIsInvalid);    
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
    cout << "Thanks for all your hard work this semester! You were great!" << endl;
    cout << "=== expression evaluation program ends ===" <<endl;
    return 0;
}

