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
    //ostream& operator << (EdgeList& printThis);
protected:
    int numNodes;
    int numEdges;
    int* v1;
    int* v2;
    int index = 0;
public:
    EdgeList();
    EdgeList(int n, int m);
    void createEdge(int x, int y);
    //~EdgeList();
    bool isAnEdge(int a, int b);
    //vector<int> listNeighbors(int a);
    //int* DFS(int start);
    //int* BFS(int start);
};

EdgeList::EdgeList() {
    numNodes = 0;
    numEdges = 0;
    v1 = new int[1];
    v2 = new int[1];
}

EdgeList::EdgeList(int n, int m) {
    numNodes = n;
    numEdges = m;
    v1 = new int[m];
    v2 = new int[m];
}

void EdgeList::createEdge(int x, int y) {
    v1[index] = x;
    v2[index] = y;
    index++;
}

bool EdgeList::isAnEdge(int a, int b) {
    int curr = 0;
    bool ret = false;
    while (ret != true || curr < sizeof(v1)) {
        if ((v1[curr] == a && v2[curr] == b) || (v1[curr] == b && v2[curr] == a)) {
            ret = true;
        }
    }
    return ret;
}
