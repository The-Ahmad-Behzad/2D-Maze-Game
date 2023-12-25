#pragma once
#include "List.h"

// Class for Vertex of a Graph
class Vertex {
public:
	int vertexNo;
	List* AdjList;
	int edges;
	char val;
	static int totalVertices;
	bool isVisited;
	Vertex() {
		isVisited = false;
		val = innerWallChar;
		edges = 0;
		vertexNo = -1;
		AdjList = NULL;
	}
	// add a new vertex to adjacency list of a vertex
	void insertAdjVertex(int x, int w) {
		if (!AdjList) {
			AdjList = new List;
		}
		AdjList->insert(x, w);;
	}
};

int Vertex::totalVertices = 0;