#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <iostream>
#include <map>
#include <stack>
#include "Node.h"

using namespace std;

class Graph {
public:
    Graph();
    ~Graph();
    map<int,Node> nodes;
    void dfsForest();
    void dfs(Node &x);
    void sccDFSForest();
    void sccDFS(Node &x);
    stack<Node> myStack;
    int postCount = 0;
    int sccCount = 0;
    set<int> temp;
    map<int, set<int>> scc;
};

#endif /* Graph_h */
