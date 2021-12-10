/*
 * Parameter.cpp
 *
 *  Created on: Sept 28, 2021
 *      Author: Jaren
 */

#include "Parameter.h"

Parameter :: Parameter() {
    value = "";
    type = "";
}

Parameter :: Parameter(string val) {
    value = val;
    type = "";
}

Parameter :: Parameter(string val, string tokenType) {
    value = val;
    type = tokenType;
}

Parameter :: ~Parameter() {
    
}

string Parameter :: getValue() {
    return value;
}

string Parameter :: toString() {
    return value;
}

string Parameter::getType(){
    return type;
}

void Parameter :: setValue(string val) {
    value = val;
}

bool Parameter :: getIsConstant() {
    return isConstant;
}

void Parameter :: setIsConstant(bool tf) {
    isConstant = tf;
}
