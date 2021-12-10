/*
 * Parser.cpp
 *
 *  Created on: Sept 28, 2021
 *      Author: Jaren
 */


#include "Parser.h"
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

Parser :: Parser(vector<Token> vector) {
    tokenVector = vector;
    current = tokenVector.at(0);
}

Parser :: ~Parser() {
    
}

void Parser :: parse() {
    /* datalogProgram -> SCHEMES COLON scheme schemeList
                         FACTS COLON factList
                         RULES COLON ruleList
                         QUERIES COLON query queryList
     */
    try {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        
        match(FACTS);
        match(COLON);
        factList();
        
        match(RULES);
        match(COLON);
        ruleList();
        
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        
        match(END);
        
    }
    catch(Token error) {
        cout << "Failure!" << endl << "  ";
        error.printToken();
    }
    
}

void Parser :: match(TokenType t) {
    if(t == current.getTokenType()) {
        tokenVector.erase(tokenVector.begin() + 0);
        if((int)tokenVector.size() > 0){
            current = tokenVector[0];
        }
        
    }
    else { // Error
        throw current;
    }
}

void Parser :: scheme() {
    //scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    if (current.getTokenType() == ID){
         p.addParameter(Parameter(current.getValue(), current.toString()));
    }
    match(ID);
    idList();
    match(RIGHT_PAREN);
    data.addScheme(p);
}

void Parser :: schemeList() {
    // schemeList -> scheme schemeList | lambda
    if (current.getTokenType() != FACTS){
        scheme();
        schemeList();
    }
}

void Parser :: idList() {
    // idList -> COMMA ID idList | lambda
    if(current.getTokenType() != RIGHT_PAREN) {
        match(COMMA);
        if (current.getTokenType() == ID){
             p.addParameter(Parameter(current.getValue(), current.toString()));
        }
        match(ID);
        idList();
    }
}

void Parser :: fact() {
    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    if (current.getTokenType() == STRING){
         p.addParameter(Parameter(current.getValue(), current.toString()));
    }
    match(STRING);
    stringList();
    match(RIGHT_PAREN);
    match(PERIOD);
    data.addFact(p);
}

void Parser :: factList() {
    // factList -> fact factList | lambda
    if(current.getTokenType() != RULES){
        fact();
        factList();
    }
}

void Parser :: stringList() {
    // stringList -> COMMA STRING stringList | lambda
    if(current.getTokenType() != RIGHT_PAREN) {
        match(COMMA);
        if (current.getTokenType() == STRING){
             p.addParameter(Parameter(current.getValue(), current.toString()));
        }
        match(STRING);
        stringList();
    }
    
}

void Parser :: rule() {
    // rule ->  headPredicate COLON_DASH predicate predicateList PERIOD
    p = headPredicate();
    r = Rule(p);
    match(COLON_DASH);
    r.addPredicate(predicate());
    predicateList();
    match(PERIOD);
    data.addRule(r);
}

void Parser :: ruleList() {
    // ruleList ->  rule ruleList | lambda
    if(current.getTokenType() != QUERIES){
        rule();
        ruleList();
    }
}

void Parser :: query() {
    // query -> predicate Q_MARK
    data.addQuery(predicate());
    match(Q_MARK);
}

void Parser :: queryList() {
    // queryList -> query queryList | lambda
    if(current.getTokenType() != END){
        query();
        queryList();
    }
}
Predicate Parser :: headPredicate() {
    // headPredicate ->  ID LEFT_PAREN ID idList RIGHT_PAREN
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    if (current.getTokenType() == ID){
        p.addParameter(Parameter(current.getValue(), current.toString()));
    }
    match(ID);
    idList();
    match(RIGHT_PAREN);
    return p;
}

Predicate Parser :: predicate() {
    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    p.addParameter(parameter());
    parameterList();
    match(RIGHT_PAREN);
    return p;
}

void Parser :: predicateList(){
    // predicateList -> COMMA predicate predicateList | lambda
    if(current.getTokenType() != PERIOD && current.getTokenType() != QUERIES) {
        match(COMMA);
        r.addPredicate(predicate());
        predicateList();
    }
}

Parameter Parser :: parameter() {
    //  parameter -> STRING | ID | expression
    Parameter newParam;
    if(current.getTokenType() == STRING){
        newParam.setValue(current.getValue());
        newParam.setIsConstant(true);
        match(STRING);
    }
    else if(current.getTokenType() == ID) {
        newParam.setValue(current.getValue());
        newParam.setIsConstant(false);
        match(ID);
    }
    else if(current.getTokenType() == LEFT_PAREN) {
        string val;
        val += expression();
        newParam.setValue(val);
    }
    else {
        throw current;
    }
    return newParam;
}

void Parser :: parameterList() {
    // parameterList -> COMMA parameter parameterList | lambda
    if(current.getTokenType() != RIGHT_PAREN) {
        match(COMMA);
        p.addParameter(parameter());
        parameterList();
    }
}

string Parser :: expression() {
    // expression -> LEFT_PAREN parameter operator parameter RIGHT_PAREN
    string temp = "(";
    match(LEFT_PAREN);
    temp += parameter().getValue();
    temp += operate();
    temp += parameter().getValue();
    match(RIGHT_PAREN);
    temp += ")";
    return temp;
}

string Parser :: operate(){
    // operator -> ADD | MULTIPLY
    if (current.getTokenType() == ADD) {
        match(ADD);
        return "+";
    }
    else if (current.getTokenType() == MULTIPLY) {
        match(MULTIPLY);
        return "*";
    }
    else {
        throw current;
    }
}

vector<Token> Parser :: getTokenVector() {
    return tokenVector;
}

DatalogProgram Parser :: getData(){
    return data;
}

Predicate Parser :: getPredicate() {
    return p;
}

Rule Parser :: getRule() {
    return r;
}
