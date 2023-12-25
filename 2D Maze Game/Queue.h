#pragma once
#include <iostream>
using namespace std;
#include "QueueNode.h"

// Class for Queue Data Structure
class Queue {
public:
	QueueNode* front, * rear;
	int numItems;
	Queue() {
		numItems = 0;
		front = rear = NULL;
	}
	bool isEmpty() {
		return (front == NULL);
	}
	void Enqueue(int x, int y) {
		while (x < 0) {
			cout << "Invalid X Position.\Enqueue Failed.\n ";
			return;
		}
		while (y < 0) {
			cout << "Invalid Y Position.\Enqueue Failed.\n ";
			return;
		}
		if (isEmpty()) {
			QueueNode* newNode = new QueueNode(x, y);
			front = rear = newNode;
		}
		else {
			QueueNode* newNode = new QueueNode(x, y);
			rear->next = newNode;
			rear = rear->next;
		}
	}
	int* Dequeue() {
		if (isEmpty()) {
			cout << "Queue is Empty\n";
			return NULL;
		}
		else if (front == rear) {
			int* pos = front->position;
			front = rear = NULL;
			return pos;
		}
		else {
			int* pos = front->position;
			front = front->next;
			return pos;
		}
	}
	int* ShowFront() {
		return front->position;
	}
};