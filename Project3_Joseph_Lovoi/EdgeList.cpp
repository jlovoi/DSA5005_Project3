//
//  EdgeList.cpp
//  Project3_Joseph_Lovoi
//
//  Created by Joseph Lovoi on 11/12/18.
//  Copyright © 2018 Joseph Lovoi. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class EdgeList {
    ostream& operator << (EdgeList& printThis);
protected:
    int numNodes;
    int numEdges;
    int* v1;
    int* v2;
public:
    EdgeList();
    EdgeList(int n, int m);
    ~EdgeList();
    bool isAnEdge(int a, int b);
    vector<int> listNeighbors(int a);
    int* DFS(int start);
    int* BFS(int start);
};

EdgeList::EdgeList() {
    numNodes = 0;
    numEdges = 0;
}

EdgeList::EdgeList(int n, int m) {
    numNodes = n;
    numEdges = m;
}

