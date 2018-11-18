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
#include <queue>
#include <cstdlib>

using namespace std;

class EdgeList {
protected:
    int numNodes;
    int numEdges;
    int* dfs;
    int* bfs;
    int* v1;
    int* v2;
    int index = 0;
    int dfscount = 0; // Used to keep track of index in dfs
    int bfscount = 0; // Used to keep track of index in bfs
public:
    EdgeList();
    EdgeList(int n, int m);
    void createEdge(int x, int y);
    bool isAnEdge(int a, int b);
    vector<int> listNeighbors(int a);
    int* DFS(int start);
    void DFSRecur(int x, bool *visited);
    int* BFS(int start);
    void display(int start);
    void checkEdge(int a, int b);
    friend ostream& operator<<(ostream& out, EdgeList& edgelist);
    ~EdgeList();
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
    visited[x] = true;
    dfs[dfscount] = x;
    dfscount++;
    
    for (auto it = listNeighbors(x).begin(); it != listNeighbors(x).end(); it++) {
        if (*it < 0 || *it > numNodes) {
            break;
        }
        if (!visited[*it] && *it != 0) {
            DFSRecur(*it, visited);
        }
    }
}

int* EdgeList::BFS(int start) {
    // Keeps track of which nodes have been visited
    bool* visited = new bool[numNodes];
    for (int i = 0; i < (numNodes); i++) {
        visited[i] = false;
    }
    visited[0] = true;
    queue<int> toVisit; // Nodes to be visited in this specific order
    toVisit.push(start);
    
    while (!toVisit.empty()) {
        // Visit the node at the front of toVisit
        visited[toVisit.front()] = true;
        bfs[bfscount] = toVisit.front();
        bfscount++;
            for (auto it = listNeighbors(toVisit.front()).begin(); it != listNeighbors(toVisit.front()).begin(); it++) {
            // Do not use out-of-bound numbers
            if (*it < 0 || *it > numNodes) {
                break;
            }
            // push unvisited neighbors to the queue, and mark them as visited so they dont get added more than once
            if (!visited[*it]) {
                toVisit.push(*it);
                visited[*it] = true;
            }
        }
        toVisit.pop();
    }
    return bfs;
}

void EdgeList::display(int start) {
    DFS(start);
    BFS(start);
    // Print out BFS
    cout << "Printing BFS Ordering for starting node " << start << ": ";
    for (int i = 0; i < (*this).numNodes; i++) {
        cout << (*this).bfs[i] << " ";
    }
    cout << endl;
    
    // Print out DFS
    cout << "Printing DFS Ordering for starting node " << start << ": ";
    for (int i = 0; i < (*this).numNodes; i++) {
        cout << (*this).dfs[i] << " ";
    }
    cout << endl;
}

void EdgeList::checkEdge(int a, int b) {
    if (isAnEdge(a, b)) {
        vector<int> neighbors = listNeighbors(a);
        cout << "Edge exists, printing neighbors of node " << a << ": ";
        for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
    else {
        cout << "Edge does not exist." << endl;
    }
}

ostream& operator<<(ostream& out, EdgeList& edgelist) {
    // Print Out the Parallel Arrays
    out << "Printing Parallel Arrays:" << endl;
    out << "Array 1: ";
    for (int i = 0; i < edgelist.numEdges; i++) {
        out << edgelist.v1[i] << " ";
    }
    out << endl << "Array 2: ";
    for (int i = 0; i < edgelist.numEdges; i++) {
        out << edgelist.v2[i] << " ";
    }
    out << endl;
    
    return out;
}

EdgeList::~EdgeList() {
    delete[] dfs;
    delete[] bfs;
    delete[] v1;
    delete[] v2;
}


int main() {
    char c;
    cin.get(c);
    int nodes = c - 48;
    cin.get(c); // New Line Char
    cin.get(c);
    int edges = c - 48;
    cin.get(c); // New Line Char
    EdgeList* edgelist = new EdgeList(nodes, edges);
    while (!cin.eof()) {
        cin.get(c);
        int x = c - 48;
        cin.get(c); // This should be a space, so skip it
        cin.get(c);
        int y = c - 48;

        cout << "Creating edge between " << x << " and " << y << endl;
        (*edgelist).createEdge(x, y);
        cin.get(c); // New Line Char
    }

    
    
//    EdgeList* edgelist = new EdgeList(5, 7);
//    (*edgelist).createEdge(1, 5);
//    (*edgelist).createEdge(1, 4);
//    (*edgelist).createEdge(1, 3);
//    (*edgelist).createEdge(2, 5);
//    (*edgelist).createEdge(3, 3);
//    (*edgelist).createEdge(4, 3);
//    (*edgelist).createEdge(4, 5);
//    cout << (*edgelist).isAnEdge(1, 5) << endl;
//    cout << (*edgelist).isAnEdge(5, 1) << endl;
//    cout << (*edgelist).isAnEdge(1, 2) << endl;
//
//    cout << *edgelist << endl;
//    (*edgelist).display(5);
    
    srand(time(NULL));
    int random1 = rand() % 5 + 1;
    cout << "Random int 1: " << random1 << endl;
    int random2 = rand() % 5 + 1;
    cout << "Random int 2: " << random2 << endl;
    (*edgelist).checkEdge(random1, random2);
    
    return 0;
    
}


