/* 
 * File:   Token.h
 * Author: CXM072
 *
 * Created on October 3, 2013, 4:05 PM
 */

#ifndef TOKEN_H
#define	TOKEN_H
#include <string>
using namespace std;

enum token_type {letter, integer, op, eq, openbrace, closebrace, invalid};

class Token {
public:
    string token;
    int priority;
    token_type type;
    
    Token();
    Token(string s);
    void set(string s);
    int value() const;    
    void display() const;
    token_type get_type() const;
    string get_token() const;
    int get_priority()  const;
    
private:
};

#endif	/* TOKEN_H */

