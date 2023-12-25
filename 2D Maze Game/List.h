#pragma once
#include "Node.h"

// Class for Adjacency List of a Vertex of a Graph
class List {
public:
	Node* head;
	List() {
		head = NULL;
	}
	List(Node n) {
		head = &n;
	}
	~List() {
		Node* currNode = head;
		Node* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->getNext();
			delete currNode;
			currNode = nextNode;
		}
		head = NULL;
	}
	// Find a vertex in Adjacency List
	bool findVertex(int x) {
		if (!head) {
			return false;
		}
		Node* curr = head;
		while (curr) {
			if (curr->getVertexNo() == x) {
				return true;
			}
			curr = curr->getNext();
		}
		return false;
	}
	// Insert a vertex in Adjacency List
	void insert(int x, int w) {
		if (findVertex(x)) {
			cout << "Egde already exists.\n";
			return;
		}
		Node* curr = head;
		Node* newNode = new Node;
		newNode->setVertexNo(x);
		newNode->setWeight(w);
		if (head == NULL) {
			head = newNode;
			return;
		}
		while (curr->getNext() != NULL) {
			curr = curr->getNext();
		}
		curr->setNext(newNode);
	}
	//Clear Adjacency List
	void clear() {
		Node* currNode = head;
		Node* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->getNext();
			delete currNode;
			currNode = nextNode;
		}
		head = NULL;
	}
	// Check is List is Empty or not
	bool isEmpty() {
		return (head == NULL);
	}
	// Display all adjacent vertices and their weights
	void display() {
		if (head == NULL) {
			cout << "List is empty\n";
			return;
		}
		Node* curr = head;
		while (curr != NULL) {
			cout << curr->getVertexNo() << "(weight " << curr->getWeight() << ")";
			if (curr->getNext()) {
				cout << ", ";
			}
			curr = curr->getNext();
		}
	}
};