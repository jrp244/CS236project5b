/*
 * Rule.cpp
 *
 *  Created on: Sept 28, 2021
 *      Author: Jaren
 */

#include "Rule.h"
#include <sstream>

Rule :: Rule(){
    headPredicate = Predicate();
    predicateList = vector<Predicate>();
}

Rule :: ~Rule() {
    
}

Rule :: Rule(Predicate p){
    headPredicate = p;
    predicateList = vector<Predicate>();
}

Rule :: Rule(Predicate p, vector<Predicate> pList){
    headPredicate = p;
    predicateList = pList;
}


void Rule :: addPredicate(Predicate pred){
    predicateList.push_back(pred);
}
Predicate Rule :: getHeadPredicate(){
    return headPredicate;
}
vector<Predicate> Rule :: getPredicateList(){
    return predicateList;
}

string Rule :: toString(){
    stringstream ss;
    ss << headPredicate.toString() << " :- ";
    for(int i = 0; i < (int)predicateList.size(); i++){
        if(i == 0) {
            ss << predicateList[i].toString();
        }
        else {
            ss << "," + predicateList[i].toString();
        }
    }
    ss << ".";
    return ss.str();
}
