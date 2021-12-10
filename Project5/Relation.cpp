/*
 * Relation.h
 *
 *  Created on: October 24, 2021
 *      Author: Jaren Petersen
	A relation has a name, a header, and a set of tuples
	Write classes that implement a simple relational database. Your design must include at least the following classes: Database, Relation, Header, and Tuple. Provide functions in the Relation class for each of the relational operations (select, project, and rename). Each of these functions operates on an existing relation and returns a new Relation (the result of the operation).

	The Relation class must use a set data type to hold the tuples in the relation.
 */
#include "Relation.h"

Relation :: Relation() {
    
}

Relation :: Relation(string n, Scheme s) {
    name = n;
    scheme = s;
}

Relation :: Relation(string n, set<Tuple> s) {
    name = n;
    tupleSet = s;
}

Relation :: Relation(string n) {
    name = n;
}

Relation :: ~Relation() {
    
}

string Relation :: toString() {
    stringstream ss;
    for(Tuple x : tupleSet) {
        if(x.empty()) {
            
        }
        else {
            ss << endl << "  ";
            for(int i = 0; i < (int)x.size(); ++i) {
                ss << scheme.at(i) << "=" << x.at(i);
                if(i == (int)x.size()-1) {
                    
                }
                else {
                    ss << ", ";
                }
            }
        }
        
    }
    return ss.str();
}

bool Relation :: addTuple(Tuple t) {
    pair<set<Tuple>::iterator,bool> insert = tupleSet.insert(t);
    bool inserted = insert.second;
    return inserted;
}


string Relation :: getName() {
    return name;
}

Scheme Relation :: getScheme() {
    return scheme;
}

set<Tuple> Relation :: getSet() {
    return tupleSet;
}

void Relation :: setScheme(Scheme s) {
    scheme = s;
}

Relation Relation :: select(string constant, int index, Relation relation) {
    Relation newRelation(relation.getName(), relation.getScheme());
    for(Tuple x : relation.getSet()) {
        if(x.at(index) == constant) {
            newRelation.addTuple(x);
        }
    }
    return newRelation;
}

Relation Relation :: select(int index1, int index2, Relation relation) {
    Relation newRelation(relation.getName(), relation.getScheme());
    for(Tuple x : relation.getSet()) {
        if(x.at(index1) == x.at(index2)) {
            newRelation.addTuple(x);
        }
    }
    return newRelation;
}

Relation Relation :: project(vector<int> positions, Relation relation) {
    Relation newRelation(relation.getName());
    for(Tuple x : relation.getSet()) {
        Tuple temp;
        for(int j = 0; j < (int)positions.size(); j++){
            temp.push_back(x.at(positions.at(j)));
        }
        newRelation.addTuple(temp);
    }
    return newRelation;
}



Relation Relation :: rename(vector<string> variables, Relation relation) {
    Relation newRelation(relation.getName(), relation.getSet());
    Scheme temp;
    for(int i = 0; i < (int)variables.size(); i++) {
        temp.push_back(variables.at(i));
    }
    newRelation.setScheme(temp);
    return newRelation;
}

Relation Relation :: join(Relation relation1, Relation relation2) {
    // Find matching and unique columns
    Scheme newScheme = relation1.getScheme();
    map<int, int> matching;
    for(int i = 0; i < (int)(relation2.getScheme()).size(); ++i){
        bool match = false;
        for(int j = 0; j < (int)(relation1.getScheme()).size(); ++j) {
            if(relation2.getScheme().at(i) == relation1.getScheme().at(j)){
                matching.insert(pair<int, int>(j, i));
                match = true;
            }
        }
        if(match == false) {
            newScheme.push_back(relation2.getScheme().at(i));
        }
    }
    
    Relation joinedRelation(name, newScheme);
    bool isJoinable = false;
    bool noMatches = false;
    for(Tuple t1 : relation1.getSet()){
        for(Tuple t2 : relation2.getSet()){
            //Test if joinable
            if(matching.empty()) {
                isJoinable = true;
                noMatches = true;
            }
            else {
                for(map<int, int>::iterator it = matching.begin(); it!=matching.end(); it++){
                    if(t1.at(it->first) == t2.at(it->second)) {
                        isJoinable = true;
                    }
                    else{
                        isJoinable = false;
                        break;
                    }
                }
            }
            // If joinable, join them
            
            if(isJoinable == true) {
                Tuple newTuple = t1;
                if(noMatches == true) {
                     for(int i = 0; i < (int)t2.size(); i++){
                         newTuple.push_back(t2.at(i));
                     }
                }
                else {
                    for(int i = 0; i < (int)t2.size(); i++){
                        bool isUnique = true;
                        for(map<int, int>::iterator it = matching.begin(); it!=matching.end(); it++){
                            if(it->second == i) {
                                isUnique = false;
                            }
                        }
                        if(isUnique == true) {
                            newTuple.push_back(t2.at(i));
                        }
                    }
                }
                joinedRelation.addTuple(newTuple);
            }
        }
    }
    return joinedRelation;
}

void Relation :: unite(Relation relation1){ //Bruh this unite function
    for(Tuple x : relation1.getSet()) {
        // Check for duplicates
        if(this->addTuple(x) == false) {
            //If tuple is already in the relation set, do nothing
        }
        else {
            cout << endl << "  ";
            for(int i = 0; i < (int)this->scheme.size(); i++) {
                cout << this->scheme.at(i) << "=" << x.at(i);
                if(i == (int)this->scheme.size()-1) {
                    
                }
                else {
                    cout << ", ";
                }
            }
        }
    }
}

