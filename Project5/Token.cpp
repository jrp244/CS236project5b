/*
 * Token.cpp
 *
 *  Created on: Sept 10, 2021
 *      Author: Jaren Petersen
 */
#include "Token.h"
#include <iostream>


Token :: Token() {
    
}

Token :: Token(TokenType t, string val, int numLine) {
    type = t;
    value = val;
    lineNum = numLine;
}

Token :: ~Token() {
    
}


string Token :: toString() {
    switch(type) {
        case(COMMA):
            return "COMMA";
            break;
        case(PERIOD):
            return "PERIOD";
            break;
        case(COLON_DASH):
            return "COLON_DASH";
            break;
        case(COLON):
            return "COLON";
            break;
        case(Q_MARK):
            return "Q_MARK";
            break;
        case(MULTIPLY):
            return "MULTIPLY";
            break;
        case(ADD):
            return "ADD";
            break;
        case(SCHEMES):
            return "SCHEMES";
            break;
        case(FACTS):
            return "FACTS";
            break;
        case(RULES):
            return "RULES";
            break;
        case(QUERIES):
            return "QUERIES";
            break;
        case(STRING):
            return "STRING";
            break;
        case(COMMENT):
            return "COMMENT";
            break;
        case(END):
            return "EOF";
            break;
        case(UNDEFINED):
            return "UNDEFINED";
            break;
        case(LEFT_PAREN):
            return "LEFT_PAREN";
            break;
        case(RIGHT_PAREN):
            return "RIGHT_PAREN";
            break;
        case(ID):
            return "ID";
            break;
        default:
            return "";
            break;
    }
}

void Token :: printToken() {
    cout << "(" << toString() << "," << "\"" << value << "\"," << lineNum << ")";
}

TokenType Token :: getTokenType() {
    return type;
}

string Token :: getValue() {
    return value;
}

