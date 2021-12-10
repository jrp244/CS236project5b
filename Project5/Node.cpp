#include "Node.h"

Node :: Node(){
    
}

Node :: Node(int name) {
    id = name;
    visited = false;
    postOrderNum = 5;
}

Node :: ~Node() {
    
}
