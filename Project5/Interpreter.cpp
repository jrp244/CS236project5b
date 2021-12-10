/*
 * Interpreter.cpp
 *
 *  Created on: October 24, 2021
 *      Author: Jaren Petersen
	A relation has a name, a header, and a set of tuples
	Write classes that implement a simple relational database. Your design must include at least the following classes: Database, Relation, Header, and Tuple. Provide functions in the Relation class for each of the relational operations (select, project, and rename). Each of these functions operates on an existing relation and returns a new Relation (the result of the operation).

	The Relation class must use a set data type to hold the tuples in the relation.
 */

#include "Interpreter.h"

Interpreter :: Interpreter() {

}

Interpreter :: Interpreter(DatalogProgram data) {
    // Store the DatalogProgram as a data member
    datalog = data;
    schemeVector = data.getSchemes();
    factVector = data.getFacts();
    ruleVector =  data.getRules();
    queryVector = data.getQueries();

    // Make a Relation for each scheme Predicate, and put that Relation in the Database data member
    for(int i = 0; i < (int)schemeVector.size(); ++i){
        string schemeName = schemeVector.at(i).getID();
        vector<Parameter> schemeParams = schemeVector.at(i).getParameters();
        Scheme scheme;
        for(int j = 0; j < (int)schemeParams.size(); ++j){
            string value = schemeParams.at(j).getValue();
            scheme.push_back(value);
        }
        Relation newRelation(schemeName, scheme);
        database.insert(pair<string, Relation>(schemeName, newRelation));
    }

    // Make a Tuple for each fact Predicate, and put that Tuple in the appropriate Relation in the Database
    for(int i = 0; i < (int)factVector.size(); ++i){
        string factName = factVector.at(i).getID();
        vector<Parameter> factParams = factVector.at(i).getParameters();
        Tuple tuple;
        for(int j = 0; j < (int)factParams.size(); ++j){
            string value = factParams.at(j).getValue();
            tuple.push_back(value);
        }
        (database.at(factName)).addTuple(tuple);
    }
    buildDependency();
    buildReverse();
    myGraph.dfsForest();
    myGraph.sccDFSForest();
}

Interpreter :: ~Interpreter() {

}

Relation Interpreter :: evalOnePredicate(Predicate myPredicate) {
    string predicateName = myPredicate.getID();
    Relation myRelation = database.at(predicateName);
    vector<Parameter> predParams = myPredicate.getParameters();
    vector<int> positions;
    vector<string> variableNames;
    map<string, int> variables;
    for(int i = 0; i < (int)predParams.size(); i++) {
        if((predParams.at(i).getIsConstant()) == true) {
            myRelation = myRelation.select(predParams.at(i).getValue(), i, myRelation);
        }
        else {
            map<string, int> :: iterator duplicate = variables.find(predParams.at(i).getValue());
            if(duplicate == variables.end()) {
                positions.push_back(i);
                variableNames.push_back(predParams.at(i).getValue());
                variables.insert(pair<string, int>(predParams.at(i).getValue(), i));
            }
            else {
                myRelation = myRelation.select(duplicate->second, i, myRelation);
            }
        }

    }
    myRelation = myRelation.project(positions, myRelation);
    myRelation = myRelation.rename(variableNames, myRelation);

    return myRelation;
}

void Interpreter :: evalOneRule(Rule myRule) {

    vector<Predicate> rulePreds = myRule.getPredicateList();
    vector<Relation> relVec;
    for(Predicate x : rulePreds) {
        Relation newRelation = evalOnePredicate(x);
        relVec.push_back(newRelation);
    }
    int relVecSize = (int)relVec.size();
    for(int i = 0; i < relVecSize; i++) {
        if(i == relVecSize - 1) {
            break;
        }
        else {
            relVec.at(i+1) = relVec.at(i).join(relVec.at(i), relVec.at(i+1));
        }
    }
    Relation newRelation = relVec.at(relVecSize-1);

    Predicate headPredicate = myRule.getHeadPredicate();
    vector<Parameter> headPredParams = headPredicate.getParameters();
    int headPredSize = (int)headPredParams.size();
    int relParamSize = (int)newRelation.getScheme().size();
    vector<int> positions;
    vector<string> renameVals;
    for(int i = 0; i < headPredSize; i++){
        for(int j = 0; j < relParamSize; j++) {
            if(headPredParams.at(i).getValue() == newRelation.getScheme().at(j)){
                positions.push_back(j);
            }
        }
    }
    Relation tempRel = database.at(headPredicate.getID());
    for(int i = 0; i < (int)tempRel.getScheme().size(); i++){
        renameVals.push_back(tempRel.getScheme().at(i));
    }

    newRelation = newRelation.project(positions, newRelation);
    newRelation = newRelation.rename(renameVals, newRelation);
    database.at(headPredicate.getID()).unite(newRelation);
}

void Interpreter :: evalAllRules() {
    cout << "Rule Evaluation" << endl;
    for(auto x : myGraph.scc){
        int numPasses = 0;
        cout << "SCC: ";
        int temp;
        for(set<int> :: iterator s = x.second.begin(); s != x.second.end(); ++s) {
            if(s != x.second.begin()) {
                cout << ",";
            }
            cout << "R" << *s;
            temp = *s;
        }
        cout << endl;

        if(x.second.size() == 1 && (x.second.size() == 1 && myGraph.nodes.at(temp).dependSet.find(temp) == myGraph.nodes.at(temp).dependSet.end())) { //If an SCC contains only one rule and that rule does not depend on itself, the rule is only evaluated once.
            cout << ruleVector.at(temp).toString();
            evalOneRule(ruleVector.at(temp));
            cout << endl;
            numPasses++;
        }
        else {//If an SCC contains more than one rule or a single rule that depends on itself, repeat the evaluation of the rules until the evaluation reaches a fixed point.
            //When an SCC contains more than one rule, evaluate the rules in the SCC in the numeric order of the rule identifiers.
            int sizeBefore = 0;
            int sizeAfter = 0;
            numPasses = 0;
            do{
                sizeBefore = database.getSize();
                for(int i : x.second){
                    cout << ruleVector.at(i).toString();
                    evalOneRule(ruleVector.at(i));
                    cout << endl;
                }
                sizeAfter = database.getSize();
                numPasses++;
            } while(sizeBefore != sizeAfter);
        }
        cout << numPasses << " passes: ";
        for(set<int> :: iterator s = x.second.begin(); s != x.second.end(); ++s) {
            if(s != x.second.begin()) {
                cout << ",";
            }
            cout << "R" << *s;
        }
        cout << endl;
    }
    cout << endl;
}

void Interpreter :: evalAllQueries() {
    cout << "Query Evaluation" << endl;
    for(int i = 0; i < (int)queryVector.size(); ++i) {
        Relation newRelation = evalOnePredicate(queryVector.at(i));
        cout << queryVector.at(i).toString() << "? ";
        if(newRelation.getSet().empty()) {
            cout << "No";
        }
        else {
            cout << "Yes(" << (int)newRelation.getSet().size() << ")";
            cout << newRelation.toString();
        }
        if(i != (int)queryVector.size()-1) {
            cout << endl;
        }
    }
    cout << endl;
}

void Interpreter :: buildDependency() {
    for(int i = 0; i < (int)ruleVector.size(); i++){
        Rule myRule = ruleVector.at(i);
        Node myNode(i);
        for(int j = 0; j < (int)myRule.getPredicateList().size(); j++){
            Predicate myPred = myRule.getPredicateList().at(j);
            for(int k = 0; k < (int)ruleVector.size(); k++){
                if(myPred.getID() == ruleVector.at(k).getHeadPredicate().getID()){
                    myNode.dependSet.insert(k);
                }
            }
        }
        myGraph.nodes.insert(pair<int, Node>(i, myNode));
    }
    cout << "Dependency Graph" << endl;
    for(map<int,Node>::iterator it=myGraph.nodes.begin(); it!=myGraph.nodes.end(); ++it) {
        cout << "R" << it->first << ":";
        set<int> mySet = it->second.dependSet;
        for(set<int> :: iterator s = mySet.begin(); s != mySet.end(); ++s) {
          if(s != mySet.begin()) {
            cout << ",";
          }
            cout << "R" << *s;

        }
        cout << endl;
    }
    cout << endl;
}

void Interpreter :: buildReverse() {
    for(map<int,Node> :: iterator i=myGraph.nodes.begin(); i!=myGraph.nodes.end(); ++i) {
        set<int> mySet = i->second.dependSet;
        for(set<int> :: iterator j = mySet.begin(); j != mySet.end(); ++j) {
            myGraph.nodes.at(*j).reverseSet.insert(i->first);
        }
    }
}

void Interpreter :: test1() {
     Relation relation1 = database.at("snap");
     Relation relation2 = database.at("csg");
     Relation newRelation = database.at("Grades");
     newRelation = newRelation.join(relation1, relation2);
     cout << newRelation.toString();
     cout << endl;
}
