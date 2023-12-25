#pragma once
#include "Vertex.h"

// class for graph, used for making Map of Game
class Graph {
public:
	Vertex* vertexList;
	static int size;
	int totalRows, totalCols;
	Graph() {
		size = totalRows = totalCols = 0;
		vertexList = NULL;
	}
	// find no of adjacents visited, (a helping function)
	int noOfVisitedAdjacents(Vertex* v) {
		int visited = 0;
		if (!v) {
			return visited;
		}
		if (!v->AdjList) {
			return visited;
		}
		Node* curr = v->AdjList->head;
		while (curr) {
			Vertex* u = &getVertex(curr->getVertexNo());
			if (!u) {
				break;
			}
			if (u->isVisited) {
				visited++;
			}
			curr = curr->getNext();
		}
		return visited;
	}
	// find if an edge exists or not
	bool findEdge(int node = 0, int adjNode = 0) {
		while (node <= 0 || node > size) {
			cout << "Vertex No: ";
			cin >> node;
		}
		if (!findVertex(node)) {
			cout << "Edge not created.\nInvalid Node.\n";
			return false;
		}
		while (adjNode <= 0 || adjNode > size) {
			cout << "AdjVertex: ";
			cin >> adjNode;
		}
		if (!findVertex(adjNode)) {
			cout << "Edge not created.\nInvalid Adjacent Node.\n";
			return false;
		}
		Vertex& v = getVertex(node);
		Vertex& u = getVertex(adjNode);
		if (!v.AdjList) {
			return false;
		}
		else if (v.AdjList->findVertex(adjNode)) {
			return true;
		}
		return false;
	}
	// find if a vertex exists or not
	bool findVertex(int x) {
		for (int i = 0; i < size; i++) {
			if (vertexList[i].vertexNo == x) {
				return true;
			}
		}
		return false;
	}
	// getter for a vertex
	Vertex& getVertex(int x) {
		Vertex v;
		for (int i = 0; i < size; i++) {
			if (vertexList[i].vertexNo == x) {
				return vertexList[i];
			}
		}
		return v;
	}
	// insert or add an edge between two vertices not already connected
	void addEdge(int node = -1, int adjNode = -1, int weight = -1) {
		if (size < 2) {
			cout << "Edges cannot be created. (atleast 2 nodes must be present)\n";
			return;
		}
		while (node <= 0 || node > size) {
			cout << "Vertex No: ";
			cin >> node;
		}
		if (!findVertex(node)) {
			cout << "Edge not created.\nInvalid Node.\n";
			return;
		}
		while (adjNode <= 0 || adjNode > size) {
			cout << "AdjVertex: ";
			cin >> adjNode;
		}
		if (!findVertex(adjNode)) {
			cout << "Edge not created.\nInvalid Adjacent Node.\n";
			return;
		}
		while (weight <= 0) {
			cout << "weight: ";
			cin >> weight;
		}
		Vertex& v = getVertex(node);
		Vertex& u = getVertex(adjNode);
		if (v.edges >= 4 || u.edges >= 4) {
			cout << "Edge not created.\nEdges slot full.\n";
			return;
		}
		v.insertAdjVertex(adjNode, weight);
		u.insertAdjVertex(node, weight);
		v.edges++;
		u.edges++;
	}
	// insert or add a vertex to the graph
	void addVertex() {
		Vertex* V = new Vertex;
		Vertex*& v = V;
		v->vertexNo = ++Vertex::totalVertices;
		Vertex* newList = new Vertex[++size];
		for (int i = 0; i < size; i++) {
			if (i == size - 1) {
				newList[i] = *v;
				break;
			}
			newList[i] = vertexList[i];
		}
		vertexList = new Vertex[size];
		vertexList = newList;
		//cout << "Node " << vertexList[graphSize - 1].vertexNo << " created.\n";
	}

	// METHODS FOR PRINTING FOR DIFFERENT MODES

	void printBombsAndCoinsHidden() {
		for (int i = 0; i < size; i++) {
			if (i % totalCols == 0) {
				cout << "\n";
			}
			//if (vertexList[i].val == bombChar) {
			//	cout << Red;
			//}
			//else if (vertexList[i].val == coinChar) {
			//	cout << yellow;
			//}
			else if (vertexList[i].val == carChar) {
				cout << green;
			}
			else if (vertexList[i].val == nodeChar) {
				cout << BrightGreen;
			}
			else {
				cout << cyan;
			}
			if (vertexList[i].val == bombChar || vertexList[i].val == coinChar) {
				if (vertexList[i].isVisited == true) {
					cout << vertexList[i].val << " " << reset;
				}
				else {
					cout << nodeChar << " " << reset;
				}
			}
			else {
				cout << vertexList[i].val << " " << reset;
			}
		}
		cout << endl;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			if (i % totalCols == 0) {
				cout << "\n";
			}
			if (vertexList[i].val == bombChar) {
				cout << Red;
			}
			else if (vertexList[i].val == coinChar) {
				cout << yellow;
			}
			else if (vertexList[i].val == carChar) {
				cout << green;
			}
			else if (vertexList[i].val == nodeChar) {
				cout << BrightGreen;
			}
			else {
				cout << cyan;
			}
			cout << vertexList[i].val << " " << reset;
		}
		cout << endl;
	}
	void printHidden() {
		for (int i = 0; i < size; i++) {
			if (i % totalCols == 0) {
				cout << "\n";
			}
			if (vertexList[i].val == carChar) {
				cout  << green << vertexList[i].val << " " << reset;
			}
			else if (isNeighborOfCar(i / totalCols, i % totalCols)) {
				if (vertexList[i].val == bombChar) {
					cout << Red;
				}
				else if (vertexList[i].val == coinChar) {
					cout << yellow;
				}
				cout  <<  vertexList[i].val << " " << reset;
				continue;
			}
			else {
				cout << "  ";
			}
		}
		cout << endl;
	}

	// helping function for printingHidden()
	bool isNeighborOfCar(int i, int j) {
		for (int k = i - 1; k < i + 2; k++) {
			for (int l = j - 1; l < j + 2; l++) {
				if (i + k < totalRows) {
					if (vertexList[(k * totalCols) + l].val == carChar) {
						return true;
					}
				}
				if (i - k > 0) {
					if (vertexList[(k * totalCols) + l].val == carChar) {
						return true;
					}
				}
				if (j + k < totalCols) {
					if (vertexList[(k * totalCols) + l].val == carChar) {
						return true;
					}
				}
				if (j - k > 0) {
					if (vertexList[(k * totalCols) + l].val == carChar) {
						return true;
					}
				}
			}
		}
		return false;
	}

};

int Graph::size = 0;