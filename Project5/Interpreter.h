/*
 * Interpreter.h
 *
 *  Created on: October 24, 2021
 *      Author: Jaren Petersen
	A relation has a name, a header, and a set of tuples
	Write classes that implement a simple relational database. Your design must include at least the following classes: Database, Relation, Header, and Tuple. Provide functions in the Relation class for each of the relational operations (select, project, and rename). Each of these functions operates on an existing relation and returns a new Relation (the result of the operation).

	The Relation class must use a set data type to hold the tuples in the relation.
 */

#ifndef Interpreter_h
#define Interpreter_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"
#include "Node.h"

using namespace std;

class Interpreter {
public:
    Interpreter();
    Interpreter(DatalogProgram data);
    ~Interpreter();
    Relation evalOnePredicate(Predicate myPredicate);
    void evalOneRule(Rule myRule);
    void evalAllRules();
    void evalAllQueries();
    void buildDependency();
    void buildReverse();
    //Testing stuff. Fun times.
    void test1();
private:
    DatalogProgram datalog;
    vector<Predicate> schemeVector;
    vector<Predicate> factVector;
    vector<Rule> ruleVector;
    vector<Predicate> queryVector;
    Database database;
    Graph myGraph;

};

#endif /* Interpreter_h */
