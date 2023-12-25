#pragma once
#include <iostream>
using namespace std;


// Class for node of Queue Data Structure
class QueueNode {
public:
	int* position;
	const int posSize = 2;
	QueueNode* next;
	QueueNode(int x, int y) {
		position = new int[posSize];
		position[0] = x;
		position[1] = y;
		next = NULL;
	}
};
