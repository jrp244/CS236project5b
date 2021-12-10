#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <set>

using namespace std;

class Node {
public:
    Node();
    Node(int id);
    ~Node();
    int id;
    set<int> dependSet;
    set<int> reverseSet;
    bool visited;
    int postOrderNum;
    
};

#endif /* Node_h */
