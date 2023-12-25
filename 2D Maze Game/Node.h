#pragma once
#include <iostream>
using namespace std;


// VARIABLES TO STORE REPITITIVELY USED VALUES
int minGridSize = 5;  // to make sure a suitable grid is made for the game
char nodeChar = 'o', verticalEdgeChar = 179, horizontalEdgeChar = 196, crossingChar = 197,
	 bombChar = 'b', coinChar = 'c', verticalWallChar = ' ', horizontalWallChar = ' ',
	 innerWallChar = 219, carChar = 'C';
string reset = "\033[0m";
string bold = "\033[1m";
string green = "\033[32m";
string yellow = "\033[33m";
string cyan = "\033[36m";
string Red = "\033[31m";
string BrightGreen = "\033[32;1m";


// Class for Node of Adjacency List Of Graph
class Node {
public:
	int weight;
	Node* next;
	int vertexNo;
	Node() {
		vertexNo = -1;
		weight = 0;
		next = NULL;
	}
	int getVertexNo() {
		return vertexNo;
	}
	void setVertexNo(int x) {
		vertexNo = x;
	}
	int getWeight() {
		return weight;
	}
	void setWeight(int x) {
		weight = x;
	}
	Node* getNext() {
		return next;
	}
	void setNext(Node* n) {
		next = n;
	}
};