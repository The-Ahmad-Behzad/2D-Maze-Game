

// DS Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<conio.h>
#include<windows.h>
#include <iomanip>
#include<fstream>
#include<string>
using namespace std;
#include "Graph.h"
#include "Queue.h"


// Function to Validate Bool Values
void validateForBool(int& val) {
	while (val != 1 && val != 0) {
		cout << "Invalid Input.\nEnter Again: ";
		cin >> val;
	}
}

// Function to set Nodes at random locations
void setNodesRandomly(Graph*& g, int i, int j) {
	Vertex vx = g->vertexList[(i * g->totalCols) + j];
	// if i and/or j are out of boundary, return
	if (i < 0 || i >= g->totalRows - 1 || j < 0 || j >= g->totalCols - 1) {
		return;
	}
	// if vertex is already visited, return
	if (g->vertexList[(i * g->totalCols) + j].isVisited) {
		return;
	}
	// if place is already too crowded with nodes, return
	if (g->noOfVisitedAdjacents(&g->vertexList[(i * g->totalCols) + j]) > 2) {
		return;
	}
	g->vertexList[(i * g->totalCols) + j].isVisited = true;
	// boundary check
	if (i == 0 || i == g->totalCols - 1 || j == 0 || j == g->totalRows - 1) {
		// do nothing
	}
	else {
		g->vertexList[(i * g->totalCols) + j].val = nodeChar;
	}
	Node* curr = new Node[4];
	int totalAdjs = 0;
	if (!(&g->vertexList[(i * g->totalCols) + j])) {
		// do nothing
	}
	else if (!(&g->vertexList[(i * g->totalCols) + j].AdjList)) {
		// do nothing 
	}
	else if (!(g->vertexList[(i * g->totalCols) + j].AdjList->head)) {
		// do nothing
	}
	else {
		Node* current = g->vertexList[(i * g->totalCols) + j].AdjList->head;
		while (current) {
			curr[totalAdjs++] = *current;
			current = current->getNext();
		}
	}
	bool* arr = new bool[totalAdjs];
	for (int i = 0; i < totalAdjs; i++) {
		arr[i] = false;
	}
	int k = 0;
	while (k < totalAdjs) {
		int random = rand() % totalAdjs;
		if (!arr[random] && &curr[random]) {
			setNodesRandomly(g, (curr[random].getVertexNo() / g->totalCols), (curr[random].getVertexNo() % g->totalCols) - 1);
		}
		k++;
	}
}

// function to set edges randomly
void setEdgesRandomly(Graph*& g, int i, int j) {
	Vertex vx = g->vertexList[(i * g->totalCols) + j];
	// if i and/or j are out of boundary, return
	if (i < 0 || i >= g->totalRows - 1 || j < 0 || j >= g->totalCols - 1) {
		return;
	}
	// if already visited, return
	if (g->vertexList[(i * g->totalCols) + j].isVisited) {
		return;
	}
	// if place is already too crowded with nodes, return
	if (g->noOfVisitedAdjacents(&g->vertexList[(i * g->totalCols) + j]) > 2) {
		return;
	}
	g->vertexList[(i * g->totalCols) + j].isVisited = true;
	// boundary check
	if (i == 0 || i == g->totalRows - 1 || j == 0 || j == g->totalRows - 1) {
		// do nothing
	}
	else {
		if (g->vertexList[((i - 1) * g->totalCols) + j].val == nodeChar && g->vertexList[((i + 1) * g->totalCols) + j].val == nodeChar) {
			g->vertexList[(i * g->totalCols) + j].val = verticalEdgeChar;
		}
		if (g->vertexList[(i * g->totalCols) + j - 1].val == nodeChar && g->vertexList[(i * g->totalCols) + j + 1].val == nodeChar) {
			g->vertexList[(i * g->totalCols) + j].val = horizontalEdgeChar;
		}
		if ((g->vertexList[((i - 1) * g->totalCols) + j].val == nodeChar || g->vertexList[((i + 1) * g->totalCols) + j].val == nodeChar) && (g->vertexList[(i * g->totalCols) + j - 1].val == nodeChar || g->vertexList[(i * g->totalCols) + j + 1].val == nodeChar)) {
			g->vertexList[(i * g->totalCols) + j].val = crossingChar;
		}
	}
	Node* curr = new Node[4];
	int totalAdjs = 0;
	if (!(&g->vertexList[(i * g->totalCols) + j])) {
		// do nothing
	}
	else if (!(&g->vertexList[(i * g->totalCols) + j].AdjList)) {
		// do nothing 
	}
	else if (!(g->vertexList[(i * g->totalCols) + j].AdjList->head)) {
		// do nothing
	}
	else {
		Node* current = g->vertexList[(i * g->totalCols) + j].AdjList->head;
		while (current) {
			curr[totalAdjs++] = *current;
			current = current->getNext();
		}
	}
	bool* arr = new bool[totalAdjs];
	for (int i = 0; i < totalAdjs; i++) {
		arr[i] = false;
	}
	int k = 0;
	while (k < totalAdjs) {
		int random = rand() % totalAdjs;
		if (!arr[random] && &curr[random]) {
			setEdgesRandomly(g, (curr[random].getVertexNo() / g->totalCols), (curr[random].getVertexNo() % g->totalCols) - 1);
		}
		k++;
	}
}

void makeRandomGraph(Graph*& g, int tn = 0) {
	// making sure graph has a suitable size 
	while (tn <= minGridSize) {
		cout << "Total Nodes in Graph: ";
		cin >> tn;
	}
	g = new Graph();
	Vertex::totalVertices = 0;
	int tv = 0;
	int i = 0;

	// adding all vertices to the graph
	while (i < tn * tn) {
		g->addVertex();
		i++;
	}
	g->totalRows = sqrt(g->size);
	g->totalCols = sqrt(g->size);
	tv = (rand() % ((4 * (tn - 1)) - (tn - 1))) + tn - 1;
	i = 0;
	// connecting vertices 
	for (int i = 0; i < g->totalRows; i++) {
		for (int j = 0; j < g->totalCols; j++) {
			if (i - 1 >= 0) {
				g->vertexList[(i * g->totalCols) + j].insertAdjVertex(((i * g->totalCols) + j - g->totalCols + 1), 1);
			}
			if (i + 1 < g->totalRows) {
				g->vertexList[(i * g->totalCols) + j].insertAdjVertex(((i * g->totalCols) + j + g->totalCols + 1), 1);
			}
			if (j - 1 >= 0) {
				g->vertexList[(i * g->totalCols) + j].insertAdjVertex(((i * g->totalCols) + j - 1 + 1), 1);
			}
			if (j + 1 < g->totalRows) {
				g->vertexList[(i * g->totalCols) + j].insertAdjVertex(((i * g->totalCols) + j + 1 + 1), 1);
			}
		}
	}

	setNodesRandomly(g, 0, 0);
	for (int i = 0; i < g->size; i++) {
		g->vertexList[i].isVisited = false;
	}
	setEdgesRandomly(g, 0, 0);
	// boundary clean up 
	for (int i = 0; i < g->totalRows; i++) {
		for (int j = 0; j < g->totalCols; j++) {
			if (i == 0 || i == g->totalRows - 1) {
				if (g->vertexList[(i * g->totalCols) + j].val == innerWallChar) {
					g->vertexList[(i * g->totalCols) + j].val = horizontalEdgeChar;
				}
				if (g->vertexList[(i * g->totalCols) + j].val == verticalEdgeChar) {
					g->vertexList[(i * g->totalCols) + j].val = crossingChar;
				}
			}
			if (j == 0 || j == g->totalCols - 1 ) {
				if (g->vertexList[(i * g->totalCols) + j].val == innerWallChar) {
					g->vertexList[(i * g->totalCols) + j].val = verticalEdgeChar;
				}
				if (g->vertexList[(i * g->totalCols) + j].val == horizontalEdgeChar) {
					g->vertexList[(i * g->totalCols) + j].val = crossingChar;
				}
			}
		}
	}
	//for (int i = 0; i < g->totalRows; i++) {
	//	for (int j = 0; j < g->totalCols; j++) {
	//		if (i == 0 || i == g->totalRows - 1) {
	//			g->vertexList[(i * g->totalCols) + j].val = horizontalWallChar;
	//		}
	//		if (j == 0 || j == g->totalCols - 1) {
	//			g->vertexList[(i * g->totalCols) + j].val = verticalWallChar;
	//		}
	//	}
	//}
}

// function to add Bombs to the Map, using Queue
void addBombs(Graph*& g, Queue*& Bombs, int totalBombs) {
	int i = 0;
	while (i < totalBombs) {
		int randomX = rand() % g->totalRows, randomY = rand() % g->totalCols;
		if (g->vertexList[(randomX * g->totalCols) + randomY].val == nodeChar) {
			Bombs->Enqueue(randomX, randomY);
			g->vertexList[(randomX * g->totalCols) + randomY].val = bombChar;
			i++;
		}
	}
}

// function to add Coins to the Map, using Queue
void addCoins(Graph*& g, Queue*& Coins, int totalBombs) {
	int i = 0;
	while (i < totalBombs) {
		int randomX = rand() % g->totalRows, randomY = rand() % g->totalCols;
		if (g->vertexList[(randomX * g->totalCols) + randomY].val == nodeChar) {
			Coins->Enqueue(randomX, randomY);
			g->vertexList[(randomX * g->totalCols) + randomY].val = coinChar;
			i++;
		}
	}
}

// // function to hide Bombs and Coins from the Map
void hideBombsandCoins(Graph*& g) {
	for (int i = 0; i < g->size; i++) {
		if (g->vertexList[i].val == bombChar || g->vertexList[i].val == coinChar) {
			g->vertexList[i].val = nodeChar;
		}
	}
}


// Function that moves the car
void controls(Graph*& g, int& car, int& score, int& t, char& pre)
{
	int ch;
	int sign = 0;
	int inc = car;
	ch = _getch();
	if (ch == 0 || ch == 224)
	{
		switch (_getch())
		{
		case 72:
		{
			if (g->vertexList[car - g->totalCols].val == verticalEdgeChar || g->vertexList[car - g->totalCols].val == nodeChar || g->vertexList[car - g->totalCols].val == bombChar || g->vertexList[car - g->totalCols].val == coinChar || g->vertexList[car - g->totalCols].val == crossingChar)
			{
				while (g->vertexList[inc].val != nodeChar)
				{
					inc -= g->totalCols;
					if (g->vertexList[inc].val == bombChar)
					{
						score -= 7;

						sign = 1;
						break;
					}
					if (g->vertexList[inc].val == coinChar)
					{
						score += 5;
						sign = 1;


						break;
					}
					if (g->vertexList[inc].val == innerWallChar)
					{
						return;
					}

				}
				score = score + 5;
				g->vertexList[inc].val = carChar;
				g->vertexList[car].val = pre;
				if (sign == 0)
				{
					pre = nodeChar;
				}
				else
					if (sign == 1)
					{
						pre = bombChar;
					}
					else
						if (sign == 2)
						{
							pre = coinChar;
						}
				car = inc;
			}
			else
				if (g->vertexList[car + 1].val == crossingChar)
				{
					inc = car + 1;
					while (g->vertexList[inc].val != nodeChar)
					{
						inc -= g->totalCols;
						if (g->vertexList[inc].val == bombChar)
						{
							score -= 7;


							sign = 1;
							break;
						}
						if (g->vertexList[inc].val == coinChar)
						{
							score += 5;
							sign = 2;


							break;
						}
						if (g->vertexList[inc].val == innerWallChar)
						{
							return;
						}

					}
					score = score + 5;
					g->vertexList[inc].val = carChar;
					g->vertexList[car].val = pre;
					if (sign == 0)
					{
						pre = nodeChar;
					}
					else
						if (sign == 1)
						{
							pre = bombChar;
						}
						else
							if (sign == 2)
							{
								pre = coinChar;
							}
					car = inc;

				}
				else
					if (g->vertexList[car - 1].val == crossingChar)
					{
						inc = car + 1;
						while (g->vertexList[inc].val != nodeChar)
						{
							inc -= g->totalCols;
							if (g->vertexList[inc].val == bombChar)
							{
								score -= 7;
								sign = 1;


								break;
							}
							if (g->vertexList[inc].val == coinChar)
							{
								score += 5;
								sign = 2;


								break;
							}
							if (g->vertexList[inc].val == innerWallChar)
							{
								return;
							}

						}
						score = score + 5;
						g->vertexList[inc].val = carChar;
						g->vertexList[car].val = pre;
						if (sign == 0)
						{
							pre = nodeChar;
						}
						else
							if (sign == 1)
							{
								pre = bombChar;
							}
							else
								if (sign == 2)
								{
									pre = coinChar;
								}
						car = inc;
					}
			break;
		}
		case 80:
		{
			if (g->vertexList[car + g->totalCols].val == verticalEdgeChar || g->vertexList[car + g->totalCols].val == nodeChar || g->vertexList[car + g->totalCols].val == bombChar || g->vertexList[car + g->totalCols].val == coinChar || g->vertexList[car + g->totalCols].val == crossingChar || g->vertexList[car + g->totalCols].val == 'E')
			{
				while (g->vertexList[inc].val != nodeChar)
				{
					inc += g->totalCols;
					if (g->vertexList[inc].val == innerWallChar)
					{
						return;
					}
					if (g->vertexList[inc].val == bombChar)
					{
						score -= 7;
						sign = 1;


						break;
					}
					if (g->vertexList[inc].val == coinChar)
					{
						score += 5;
						sign = 2;


						break;
					}
					if (g->vertexList[inc].val == 'E')
					{
						t = 0;
						break;
					}

				}
				score = score + 5;
				g->vertexList[inc].val = carChar;
				g->vertexList[car].val = pre;
				if (sign == 0)
				{
					pre = nodeChar;
				}
				else
					if (sign == 1)
					{
						pre = bombChar;
					}
					else
						if (sign == 2)
						{
							pre = coinChar;
						}
				car = inc;

			}
			else
				if ((g->vertexList[car + 1].val == crossingChar))
				{
					inc = car + 1;
					while (g->vertexList[inc].val != nodeChar)
					{
						inc += g->totalCols;
						if (g->vertexList[inc].val == bombChar)
						{
							score -= 7;


							sign = 1;
							break;
						}
						if (g->vertexList[inc].val == coinChar)
						{
							score += 5;
							sign = 2;


							break;
						}
						if (g->vertexList[inc].val == 'E')
						{
							t = 0;
							break;
						}
						if (g->vertexList[inc].val == innerWallChar)
						{
							return;
						}
					}
					score = score + 5;
					g->vertexList[inc].val = carChar;
					g->vertexList[car].val = pre;
					if (sign == 0)
					{
						pre = nodeChar;
					}
					else
						if (sign == 1)
						{
							pre = bombChar;
						}
						else
							if (sign == 2)
							{
								pre = coinChar;
							}
					car = inc;

				}
				else
					if ((g->vertexList[car - 1].val == crossingChar))
					{
						inc = car - 1;
						while (g->vertexList[inc].val != nodeChar)
						{
							inc += g->totalCols;
							if (g->vertexList[inc].val == bombChar)
							{
								score -= 7;
								sign = 1;


								break;
							}
							if (g->vertexList[inc].val == coinChar)
							{
								score += 5;
								sign = 2;


								break;
							}
							if (g->vertexList[inc].val == 'E')
							{
								t = 0;
								break;
							}
							if (g->vertexList[inc].val == innerWallChar)
							{
								return;
							}
						}
						score = score + 5;
						g->vertexList[inc].val = carChar;
						g->vertexList[car].val = pre;
						if (sign == 0)
						{
							pre = nodeChar;
						}
						else
							if (sign == 1)
							{
								pre = bombChar;
							}
							else
								if (sign == 2)
								{
									pre = coinChar;
								}
						car = inc;
					}
			break;
		}
		case 75:
		{
			if (g->vertexList[car - 1].val == horizontalEdgeChar || g->vertexList[car - 1].val == nodeChar || g->vertexList[car - 1].val == bombChar || g->vertexList[car - 1].val == coinChar || g->vertexList[car - 1].val == crossingChar||g->vertexList[car -1].val == 'E')
			{
				while (g->vertexList[inc].val != nodeChar)
				{
					inc -= 1;
					if (g->vertexList[inc].val == bombChar)
					{
						score -= 2;
						sign = 1;

						return;
						break;
					}
					if (g->vertexList[inc].val == coinChar)
					{
						score += 5;
						sign = 2;

						return;
						break;
					}
					if (g->vertexList[inc].val == 'E')
					{
						t = 0;
						break;
					}
					if (g->vertexList[inc].val == innerWallChar)
					{
						return;
					}
				}
				score = score + 5;
				g->vertexList[inc].val = carChar;
				g->vertexList[car].val = pre;
				if (sign == 0)
				{
					pre = nodeChar;
				}
				else
					if (sign == 1)
					{
						pre = bombChar;
					}
					else
						if (sign == 2)
						{
							pre = coinChar;
						}
				car = inc;

			}
			else
				if (g->vertexList[car + g->totalCols].val == crossingChar)
				{
					inc = car + g->totalCols;

					while (g->vertexList[inc].val != nodeChar)
					{
						inc -= 1;
						if (g->vertexList[inc].val == bombChar)
						{
							score -= 7;
							sign = 1;


							break;
						}
						if (g->vertexList[inc].val == coinChar)
						{
							score += 5;
							sign = 2;


							break;
						}
						if (g->vertexList[inc].val == 'E')
						{
							t = 0;
							break;
						}
						if (g->vertexList[inc].val == innerWallChar)
						{
							return;
						}
					}
					score = score + 5;
					g->vertexList[inc].val = carChar;
					g->vertexList[car].val = pre;
					if (sign == 0)
					{
						pre = nodeChar;
					}
					else
						if (sign == 1)
						{
							pre = bombChar;
						}
						else
							if (sign == 2)
							{
								pre = coinChar;
							}
					car = inc;

				}
				else
					if (g->vertexList[car - g->totalCols].val == crossingChar)
					{
						inc = car - g->totalCols;

						while (g->vertexList[inc].val != nodeChar)
						{
							inc -= 1;
							if (g->vertexList[inc].val == bombChar)
							{
								score -= 7;
								sign = 1;


								break;
							}
							if (g->vertexList[inc].val == coinChar)
							{
								score += 5;
								sign = 2;


								break;
							}
							if (g->vertexList[inc].val == 'E')
							{
								t = 0;
								break;
							}
							if (g->vertexList[inc].val == innerWallChar)
							{
								return;
							}
						}
						score = score + 5;
						g->vertexList[inc].val = carChar;
						g->vertexList[car].val = pre;
						if (sign == 0)
						{
							pre = nodeChar;
						}
						else
							if (sign == 1)
							{
								pre = bombChar;
							}
							else
								if (sign == 2)
								{
									pre = coinChar;
								}
						car = inc;
					}
			break;
		}
		case 77:
		{
			if (g->vertexList[car + 1].val == horizontalEdgeChar || g->vertexList[car + 1].val == nodeChar || g->vertexList[car + 1].val == bombChar || g->vertexList[car + 1].val == coinChar || g->vertexList[car + 1].val == crossingChar||g->vertexList[car + 1].val == 'E')
			{
				while (g->vertexList[inc].val != nodeChar)
				{
					inc += 1;
					if (g->vertexList[inc].val == bombChar)
					{
						score -= 7;
						sign = 1;


						break;
					}
					if (g->vertexList[inc].val == coinChar)
					{
						score += 5;
						sign = 2;


						break;
					}
					if (g->vertexList[inc].val == 'E')
					{
						t = 0;
						break;
					}
					if (g->vertexList[inc].val == innerWallChar)
					{
						return;
					}
				}
				score = score + 5;
				g->vertexList[inc].val = carChar;
				g->vertexList[car].val = pre;
				if (sign == 0)
				{
					pre = nodeChar;
				}
				else
					if (sign == 1)
					{
						pre = bombChar;
					}
					else
						if (sign == 2)
						{
							pre = coinChar;
						}
				car = inc;

			}
			else
				if (g->vertexList[car + g->totalCols].val == crossingChar)
				{
					inc = car + g->totalCols;

					while (g->vertexList[inc].val != nodeChar)
					{
						inc += 1;
						if (g->vertexList[inc].val == bombChar)
						{
							score -= 7;
							sign = 1;


							break;
						}
						if (g->vertexList[inc].val == coinChar)
						{
							score += 5;
							sign = 2;


							break;
						}
						if (g->vertexList[inc].val == 'E')
						{
							t = 0;
							break;
						}
						if (g->vertexList[inc].val == innerWallChar)
						{
							return;
						}
					}
					score = score + 5;
					g->vertexList[inc].val = carChar;
					g->vertexList[car].val = pre;
					if (sign == 0)
					{
						pre = nodeChar;
					}
					else
						if (sign == 1)
						{
							pre = bombChar;
						}
						else
							if (sign == 2)
							{
								pre = coinChar;
							}
					car = inc;

				}
				else
					if (g->vertexList[car - g->totalCols].val == crossingChar)
					{
						inc = car - g->totalCols;

						while (g->vertexList[inc].val != nodeChar)
						{
							inc += 1;
							if (g->vertexList[inc].val == bombChar)
							{
								score -= 7;
								sign = 1;


								break;
							}
							if (g->vertexList[inc].val == coinChar)
							{
								score += 5;
								sign = 2;


								break;
							}
							if (g->vertexList[inc].val == 'E')
							{
								t = 0;
								break;
							}
							if (g->vertexList[inc].val == innerWallChar)
							{
								return;
							}
						}
						score = score + 5;
						g->vertexList[inc].val = carChar;
						g->vertexList[car].val = pre;
						if (sign == 0)
						{
							pre = nodeChar;
						}
						else
							if (sign == 1)
							{
								pre = bombChar;
							}
							else
								if (sign == 2)
								{
									pre = coinChar;
								}
						car = inc;
					}
			break;
		}
		case 71:
		{
			t = 0;
			break;
		}

		}
	}
}

void updateLeaderboard(string name, int score) {
	for (int i = 0; i < name.length(); i++) {
		name[i] = toupper(name[i]);
	}
	fstream file("leaderboard.txt", ios::in | ios::app);
	string s;
	int pos = 1;
	for (int i = 0; getline(file, s); i++) {
		if (i % 2 == 1) {
			if (stoi(s) < score) {
				break;
			}
			else {
				pos++;
			}
		}
	}
	file.close();
	file.open("leaderboard.txt", ios::in | ios::app);
	string arr[10];
	if (pos <= 5) {
		for (int j = 0; j < 10; j++) {
			if (j == (pos * 2) - 2) {
				arr[j] = name;
			}
			else if (j == (pos * 2) - 1) {
				arr[j] = to_string(score);
			}
			else {
				getline(file, s);
				arr[j] = s;
			}
		}
	}
	file.close();
	file.open("leaderboard.txt", ios::out);
	for (int j = 0; j < 10; j++) {
		file << arr[j] << "\n";
	}
	file.close();
}

void DisplayLeaderboard() {
	cout << setw(90) << "L E A D E R   B O A R D\n\n";
	fstream file("leaderboard.txt", ios::in | ios::app);
	string s;
	int pos = 1;
	for (int i = 0; i < 10; i++) {
		getline(file, s);
		if (i % 2 == 0) {
			cout << setw(60) << i / 2 + 1 << ") " << s;
			for (int k = 0; k < 20 - s.length(); k++) {
				cout << " ";
			}
		}
		else {
			cout << setw(10) << s << endl;
		}
	}
	file.close();

}

int main()
{
	srand(time(NULL));
	int ch;
	Graph* gr = new Graph;
	Graph*& g = gr;
	Queue* b = new Queue, * c = new Queue;
	Queue*& bombs = b;
	Queue*& coins = c;

	makeRandomGraph(g, 20);
	int vertices = 0, edges = 0;
	for (int i = 0; i < g->totalRows; i++) {
		for (int j = 0; j < g->totalCols; j++) {
			if (g->vertexList[(i * g->totalCols) + j].val == nodeChar) {
				vertices++;
			}
		}
	}
	if (vertices >= g->size / 4) {
		system("Color 03");
		int totalBombs = rand() % vertices / 8;
		addBombs(g, bombs, totalBombs);
		vertices -= totalBombs;
		int totalCoins = rand() % vertices / 4;
		addCoins(g, coins, totalCoins);
		vertices -= totalCoins;
		for (int i = 0; i < 10; i++) {
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t L O A D I N G .";
			Sleep(20);
			system("cls");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t L O A D I N G . .";
			Sleep(20);
			system("cls");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t L O A D I N G . . .";
			Sleep(20);
			system("cls");
		}
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\n";
		cout << "\t\t\t\t\t	SSSS  U   U PPPP  EEEE  RRRR       CCCCCC  AAA   RRRR   III  OOO\n";
		cout << "\t\t\t\t\t	S     U   U P  P  E     R   R      C      A   A  R   R   I  O   O\n";
		cout << "\t\t\t\t\t	SSSS  U   U PPPP  EEEE  RRRR       C      AAAAA  RRRR    I  O   O\n";
		cout << "\t\t\t\t\t           S  U   U P	  E     R  R       C      A   A  R  R    I  O   O\n";
		cout << "\t\t\t\t\t	SSSS   UUU  P     EEEE  R   R      CCCCCC A   A  R   R  III  OOO\n";
		cout << "\n\t\t\t\t\t\t\t\t";
		system("pause");
		system("cls");

		int score = 0;

		int i = 0;
		int r = 0;
		string name;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t N A M E : ";
		cin >> name;
		cout << "\t\t\t\t\t\t\t\t";
		system("pause");
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tM A I N    M E N U\n\n\t\t\t\t\t\t\t\t\t1. PLAY\n\t\t\t\t\t\t\t\t\t2. LEADERBOARD \n\t\t\t\t\t\t\t\t\t3. EXIT\n\t\t\t\t\t\t\t\t\tChoice: ";
		cin >> i;
		cout << "\t\t\t\t\t\t\t\t";
		system("pause");
		system("cls");
		if (i == 1)
		{
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tC H O O S E   M O D E\n\n\t\t\t\t\t\t\t\t\t1. NORMAL MODE\n\t\t\t\t\t\t\t\t\t2. LIGHTS OUT \n\t\t\t\t\t\t\t\t\tChoice: ";
			cin >> r;
			int car = g->totalCols + 1;
			char pre = 'S';
			//for (int i = 0; i < g->size; i++) {
			//	g->vertexList[i].isVisited = false;
			//}
			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl; cout << "                                        ";
					for (int i = 0; i < 10; i++)
					{
						cout << innerWallChar;
					}
					Sleep(200);
				}
				else
					if (i == 1)
					{
						system("cls");

						cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl; cout << "                                       ";
						for (int i = 0; i < 20; i++)
						{
							cout << innerWallChar;
						}
						Sleep(200);
					}
					else
						if (i == 2)
						{
							system("cls");
							cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl; cout << "                                       ";
							for (int i = 0; i < 30; i++)
							{
								cout << innerWallChar;
							}
							Sleep(200);
						}
			}
			system("cls");
			cout << "\nlocations: " << nodeChar << endl;
			cout << "Straight paths: " << verticalEdgeChar << endl;
			cout << "crossings: " << crossingChar << endl;
			cout << "Boombs: " << bombChar << endl;
			cout << "Coins: " << coinChar << endl;
			g->vertexList[21].val = carChar;
			g->vertexList[378].val = 'E';

			g->print();
			for (int i = 0; i < g->size; i++) {
				g->vertexList[i].isVisited = false;
			}

			if (r == 1)
			{
				int t = 1;
				while (t == 1)
				{
					g->vertexList[car].isVisited = true;
					controls(g, car, score, t, pre);
					system("cls");
					cout << "press Home to terminate" << endl;
					cout << "Score: " << score << endl;

					g->printBombsAndCoinsHidden();
				}
				updateLeaderboard(name, score);
			}
			else if (r == 2)
			{
				int t = 1;
				while (t == 1)
				{
					controls(g, car, score, t, pre);
					system("cls");
					cout << "press Home to terminate" << endl;
					cout << "Score: " << score << endl;
					g->printHidden();


				}
				updateLeaderboard(name, score);
			}
		}
		else if (i == 2) {
			DisplayLeaderboard();
		}
		else {
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t G O O D   B Y E ! ! ! . . .";
			exit(0);
		}

		return 0;
	}
}
