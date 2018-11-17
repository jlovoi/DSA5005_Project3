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
    int* dfs;
    int* bfs;
    int* v1;
    int* v2;
    int index = 0;
    int count = 0;
public:
    EdgeList();
    EdgeList(int n, int m);
    void createEdge(int x, int y);
    //~EdgeList();
    bool isAnEdge(int a, int b);
    vector<int> listNeighbors(int a);
    int* DFS(int start);
    void DFSRecur(int x, bool* visited);
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
    dfs = new int[numNodes-1];
    bfs = new int[numNodes-1];
}

void EdgeList::createEdge(int x, int y) {
    v1[index] = x;
    v2[index] = y;
    index++;
}

bool EdgeList::isAnEdge(int a, int b) {
    int curr = 0;
    bool ret = false;
    while (curr < sizeof(v1)) {
        if ((v1[curr] == a && v2[curr] == b) || (v1[curr] == b && v2[curr] == a)) {
            ret = true;
        }
        curr++;
    }
    return ret;
}

vector<int> EdgeList::listNeighbors(int a) {
    int curr = 1;
    vector<int>* ret = new vector<int>();
    while (curr < sizeof(v1)) {
        if (isAnEdge(a, curr)) {
            ret->push_back(curr);
        }
        curr++;
    }
    return (*ret);
}

int* EdgeList::DFS(int start) {
    // Keeps track of which nodes have been visited
    bool* visited = new bool[numNodes];
    for (int i = 0; i < (numNodes); i++) {
        visited[i] = false;
    }
    
    // Start recurrence sequence
    DFSRecur(start, visited);
    return dfs;
}

void EdgeList::DFSRecur(int x, bool *visited) {
    // This node, x, has now been visited
    cout << "ISSA " << x << endl;
    visited[x] = true;
    dfs[count] = x;
    cout << "added " << x << " at " << count << endl;
    count++;
    
    for (auto it = listNeighbors(x).begin(); it != listNeighbors(x).end(); it++) {
        if (*it < 0 || *it > numNodes) {
            break;
        }
        if (!visited[*it] && *it != 0) {
            DFSRecur(*it, visited);
        }
    }
}

int main() {
    EdgeList* edgelist = new EdgeList(5, 7);
    (*edgelist).createEdge(1, 5);
    (*edgelist).createEdge(1, 4);
    (*edgelist).createEdge(1, 3);
    (*edgelist).createEdge(2, 5);
    (*edgelist).createEdge(3, 3);
    (*edgelist).createEdge(4, 3);
    (*edgelist).createEdge(4, 5);
//    cout << (*edgelist).isAnEdge(1, 5) << endl;
//    cout << (*edgelist).isAnEdge(5, 1) << endl;
//    cout << (*edgelist).isAnEdge(1, 2) << endl;
    vector<int> one = (*edgelist).listNeighbors(2);
    for (auto it = one.begin(); it != one.end(); it++) {
        cout << *it << endl;
    }
    int* arr = (*edgelist).DFS(5);
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << endl;
    }
}
