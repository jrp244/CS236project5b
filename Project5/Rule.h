/*
 * Rule.h
 *
 *  Created on: Sept 28, 2021
 *      Author: Jaren
 */

#ifndef Rule_h
#define Rule_h

#include <stdio.h>
#include "Predicate.h"

using namespace std;

class Rule {
public:
    Rule();
    ~Rule();
    Rule(Predicate p);
    Rule(Predicate pred, vector<Predicate> predList);
    void addPredicate(Predicate pred);
    vector<Predicate> getPredicateList();
    Predicate getHeadPredicate();
    string toString();
private:
    vector<Predicate> predicateList;
    Predicate headPredicate;
};

#endif /* Rule_h */
