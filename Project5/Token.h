/*
 * Token.h
 *
 *  Created on: Sept 10, 2021
 *      Author: Jaren Petersen
 */
#ifndef Token_h
#define Token_h

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum TokenType {
    COMMA, PERIOD, COLON_DASH, COLON, Q_MARK,
    MULTIPLY, ADD, SCHEMES, FACTS, RULES,
    QUERIES, STRING, COMMENT, END, UNDEFINED,
    LEFT_PAREN, RIGHT_PAREN, ID
};

class Token {
public:
    Token();
    Token(TokenType t, string val, int numLine);
    ~Token();
    string toString();
    void printToken();
    TokenType getTokenType();
    string getValue();
private:
    TokenType type;
    string value;
    int lineNum;
};

#endif /* Token.h */
