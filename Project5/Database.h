/*
 * Database.h
 *
 *  Created on: October 24, 2021
 *      Author: Jaren Petersen
 Don't use an unorder map. It won't work
 */

#ifndef Database_h
#define Database_h

#include <stdio.h>
#include <map>
#include <string>
#include "Relation.h"

using namespace std;

class Database : public map<string, Relation> {
public:
    Database();
    ~Database();
    int getSize();
private:
    
};

#endif /* Database_h */
