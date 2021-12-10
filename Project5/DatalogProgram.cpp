/*
 * DatalogProgram.cpp
 *
 *  Created on: September 28, 2021
 *      Author: Jaren
 */

#include "DatalogProgram.h"
#include <iostream>
#include <sstream>

DatalogProgram :: DatalogProgram(){
    schemes = vector<Predicate>();
    facts = vector<Predicate>();
    rules = vector<Rule>();
    queries = vector<Predicate>();
    domain = set<string>();
}

DatalogProgram :: ~DatalogProgram() {
    
}

string DatalogProgram :: toString() {
    stringstream ss;
    ss << "Success!";
    ss << endl << stringSchemes();
    ss << endl << stringFacts();
    ss << endl << stringRules() ;
    ss << endl << stringQueries();
    ss << endl << stringDomain();
    return ss.str();
}

vector<Predicate> DatalogProgram :: getSchemes(){
    return schemes;
}

vector<Predicate> DatalogProgram :: getFacts() {
    return facts;
}

vector<Rule> DatalogProgram :: getRules() {
    return rules;
}

vector<Predicate> DatalogProgram :: getQueries() {
    return queries;
}

set<string> DatalogProgram :: getDomain() {
    return domain;
}

void DatalogProgram::addScheme(Predicate s){
    schemes.push_back(s);
}

void DatalogProgram::addFact(Predicate fact){
    facts.push_back(fact);
    addDomain(fact.getParameters());
}

void DatalogProgram::addRule(Rule rule){
    rules.push_back(rule);
    addDomain(rule.getHeadPredicate().getParameters());

}

void DatalogProgram::addQuery(Predicate query){
    queries.push_back(query);

}

void DatalogProgram::addDomain(vector<Parameter> paramList){
    for(int i = 0; i < (int)paramList.size(); i++){ 
        if(paramList[i].getType() == "STRING") {
            domain.insert(paramList[i].getValue());
        }
    }
    
}

string DatalogProgram::stringSchemes(){
    stringstream ss;
    ss << "Schemes(" << schemes.size() << "):";
    for(int i = 0; i < (int)schemes.size(); i++) {
        ss << "\n  " << schemes[i].toString();
    }
    return ss.str();
}

string DatalogProgram::stringDomain(){
    stringstream ss;
    ss << "Domain(" << domain.size() << "):";
    set<string>::iterator myIterator;
    for(myIterator = domain.begin(); myIterator != domain.end(); myIterator++) {
        ss << "\n  " << (*myIterator);
    }
    return ss.str();
}

string DatalogProgram::stringFacts(){
    stringstream ss;
    ss << "Facts(" << facts.size() << "):";
    for(int i = 0; i < (int)facts.size(); i++) {
        ss << "\n  " << facts[i].toString() << ".";
    }
    return ss.str();
}

string DatalogProgram::stringQueries(){
    stringstream ss;
    ss << "Queries(" << queries.size() << "):";
    for(int i = 0; i < (int)queries.size(); i++)
        ss << "\n  " << queries[i].toString() << "?";
    return ss.str();
}

string DatalogProgram::stringRules(){
    stringstream ss;
    ss << "Rules(" << rules.size() << "):";
    for(int i = 0; i < (int)rules.size(); i++)
        ss << "\n  " << rules[i].toString();
    return ss.str();
}


