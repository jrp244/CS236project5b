#include "Graph.h"

Graph :: Graph() {
    
}

Graph :: ~Graph() {
    
}

void Graph :: dfsForest() {
    for(auto &node : nodes) {
        if(node.second.visited == false){
            dfs(node.second);
        }
    }
}

void Graph :: dfs(Node &x) {
    x.visited = true;
    for(auto i : x.reverseSet) {
        if(nodes.at(i).visited == false)  {
            dfs(nodes.at(i));
        }
    }
    postCount++;
    x.postOrderNum = postCount;
    myStack.push(x);
}

void Graph :: sccDFSForest() {
    for(auto &node : nodes) {
        node.second.visited = false;
    }
    while(myStack.empty() == false) {
        int index = myStack.top().id;
        if(nodes.at(index).visited == false) {
            temp.clear();
            sccDFS(nodes.at(index));
            sccCount++;
            scc.insert(pair<int, set<int>>(sccCount,temp));
        }
        myStack.pop();
    }
}

void Graph :: sccDFS(Node &x) {
    x.visited = true;
    temp.insert(x.id);
    for(auto i : x.dependSet) {
        if(nodes.at(i).visited == false)  {
            sccDFS(nodes.at(i));
        }
    }
}
