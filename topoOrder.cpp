//
//  main.cpp
//  Project2
//
//  Created by Billy Miller on 2/13/14.
//  Copyright (c) 2014 Billy Miller. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class TopoOrder{
public:
    class Node{
    public:
        friend class TopoOrder;
        int inDegree, outDegree, *adjNodes;
    };
    TopoOrder(string);

private:
    int *topoOrder, numNodes;
    Node *nodes;

    void readDigraphAndComputeIndegrees(string dataFile);
    void computeTopoOrder();
    void printDigraphInput();
};

TopoOrder::TopoOrder(string dataFile){
    readDigraphAndComputeIndegrees(dataFile);
    printDigraphInput();
    computeTopoOrder();
}

void TopoOrder::printDigraphInput(){
    cout << "Input Digraph:" << endl;
    for (int i = 0; i < numNodes; ++i){
        cout << "node = " << i;
        cout << " inDegree = " << nodes[i].inDegree;
        cout << " outDegree = " << nodes[i].outDegree;
        cout << " adjNodes = [";
        if (nodes[i].outDegree == 0)
            cout << "  ";
        for (int j = 0; j < nodes[i].outDegree; ++j)
            cout << nodes[i].adjNodes[j] << ", ";
        cout << "\b\b" << "]" << endl;
    }
    cout << endl;
}

void TopoOrder::readDigraphAndComputeIndegrees(string dataFile){
    ifstream file(dataFile.c_str());
    int index, oDegree, aNode;

    if (!file)
        cout << "Error opening topoOrder.dat" << endl;

    file >> numNodes;
    nodes = new Node[numNodes];
    file.ignore(100, '\n');
    for (int i = 0; i < numNodes; ++i){
        file >> index;
        file.ignore(2, '(');
        file >> oDegree;
        file.ignore(3, ':');

        nodes[index].outDegree = oDegree;
        nodes[index].adjNodes = new int[oDegree];

        for (int j = 0; j < oDegree; ++j){
            file >> aNode;
            nodes[index].adjNodes[j] = aNode;
            nodes[aNode].inDegree++;
        }
        file.ignore(100, '\n');
    }
}

void TopoOrder::computeTopoOrder(){
    topoOrder = new int[numNodes];
    int stack[numNodes], stackSize = 0, index = 0, topoCount = 0;

    cout << "inDegrees = [";
    for (int i = 0; i < numNodes; ++i)
        cout << nodes[i].inDegree << ", ";
    cout << "\b\b" << "]" << endl;

    for (int i = 0; i < numNodes; ++i){
        if (nodes[i].inDegree == 0)
            stack[stackSize++] = i;
    }

    cout << "stack = [";
    for (int i = 0; i < stackSize; ++i)
        cout << stack[i] << ", ";
    cout << "\b\b" << "], node selected = ";

    while (stackSize > 0){
        index = stack[--stackSize];
        Node root = nodes[index];
        topoOrder[topoCount++] = index;
        cout << index << endl;

        for (int i = 0; i < root.outDegree; ++i){
            Node *adjNode = &nodes[root.adjNodes[i]];
            adjNode->inDegree--;
            if (adjNode->inDegree == 0)
                stack[stackSize++] = root.adjNodes[i];
        }

        cout << "reduced inDegrees = [";
        for (int j = 0; j < numNodes; j++)
            cout << nodes[j].inDegree << ", ";
        cout << "\b\b" <<"]" << endl;

        if (stackSize == 0){
            cout << "stack = empty, node selected = none" << endl;
            break;
        }

        cout << "stack = [";
        for (int i = 0; i < stackSize; ++i)
            cout << stack[i] << ", ";
        cout << "\b\b" << "], node selected = ";

    }

    cout << endl << "topoOrder = [";
    for (int i = 0; i < numNodes; ++i)
        cout << topoOrder[i] << ", ";
    cout << "\b\b" << "]" << endl;
}

int main(int argc, const char * argv[])
{
    TopoOrder("topoOrder.txt");
    return 0;
}