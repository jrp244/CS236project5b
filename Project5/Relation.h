/*
 * Relation.h
 *
 *  Created on: October 24, 2021
 *      Author: Jaren Petersen
	A relation has a name, a header, and a set of tuples
	Write classes that implement a simple relational database. Your design must include at least the following classes: Database, Relation, Header, and Tuple. Provide functions in the Relation class for each of the relational operations (select, project, and rename). Each of these functions operates on an existing relation and returns a new Relation (the result of the operation).

	The Relation class must use a set data type to hold the tuples in the relation.
 */

#ifndef Relation_h
#define Relation_h

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include "Tuple.h"
#include "Scheme.h"


using namespace std;

class Relation {
public:
    Relation();
    Relation(string n, Scheme s);
    Relation(string n, set<Tuple> s);
    Relation(string n);
    ~Relation();
    
    string toString();
    
    bool addTuple(Tuple t);
    
    string getName();
    Scheme getScheme();
    set<Tuple> getSet();
    void setScheme(Scheme s);
    
    Relation select(string constant, int index, Relation relation);
    Relation select(int index1, int index2, Relation relation);
    Relation project(vector<int> positions, Relation relation);
    Relation rename(vector<string> variables, Relation relation);
    
    Relation join(Relation relation1, Relation relation2);
    void unite(Relation relation1);
private:
    string name; // Name of Scheme
    Scheme scheme; // Scheme is one vector of attributes
    set<Tuple> tupleSet; // These are Facts
};

#endif /* Relation_h */
