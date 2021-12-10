/*
 * DatalogProgram.h
 *
 *  Created on: September 28, 2021
 *      Author: Jaren
 */

#ifndef DatalogProgram_h
#define DatalogProgram_h

#include <stdio.h>
#include <vector>
#include <set>
#include "string"
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram {
public:
    DatalogProgram();
    ~DatalogProgram();
    
    string toString();
    
    vector<Predicate> getSchemes();
    vector<Predicate> getFacts();
    vector<Rule> getRules();
    vector<Predicate> getQueries();
    set<string> getDomain();
    
    void addScheme(Predicate s);
    void addFact(Predicate f);
    void addRule(Rule r);
    void addQuery(Predicate q);
    void addDomain(vector<Parameter> pList);
    
    string stringSchemes();
    string stringFacts();
    string stringRules();
    string stringQueries();
    string stringDomain();
    
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;
    
};


#endif /* DatalogProgram_h */
