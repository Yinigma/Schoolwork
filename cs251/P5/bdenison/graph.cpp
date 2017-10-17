#include <iostream>
#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

/*
	Graph class for use in Project 5.
	
	This provided code does not include any specific data structure
	for storing a graph, only a list of methods that will be called 
	from main. Based on the project handout and the lecture slides,
	select a method for storing the graph and implement it here.

*/

// Constructor for Graph. Read in data from the input
// and set up your data structures here.
Graph::Graph(float** edges, int nEdges, int nNodes, string* k)
{
	data = edges;
	numEd = nEdges;
	numNo = nNodes;
	key = k;
	pathLengths = new float*[numNo];
	for (int i = 0; i < numNo; i++) {
		pathLengths[i] = new float[numNo];
	}
	paths = new float**[numNo];
	for (int i = 0; i < numNo; i++) {
		paths[i] = new float*[numNo];
		for (int j = 0; j < numNo; j++) {
			paths[i][j] = NULL;
		}
	}
	ran = new bool [numNo];
	for (int i = 0; i < numNo; i++) {
		ran[i] = false;
	}
}


void Graph::genTree(float origin)
{
	ran[(int)origin] = true;
	float* visits = new float[numNo];
	int visSize = 0;
	for (int i = 0; i < numNo; i++) {
		pathLengths[(int) origin][i] = -1;
	}
	pathLengths[(int)origin][(int)origin] = 0;
	paths[(int)origin][(int)origin] = NULL;
	float cWeight = 0;
	float cNode = origin;
	float min = -1;
	int pathlen = 1;
	float initPath[1] = {0};
	float* cPath = initPath;


	while(visSize<numNo) {

		for (int i = 0; i < numEd; i++) {
			float cLength = 0;
			int nodex = -1;
			if (data[i][0] == cNode) {
				nodex = 1;
			}
			if (data[i][1] == cNode) {
				nodex = 0;
			}
			if (nodex!=-1) {
				cLength = pathLengths[(int)origin][(int)data[i][nodex]];
				if (cLength == -1 || cLength >(data[i][2] + cWeight)) {
					pathLengths[(int)origin][(int)data[i][nodex]] = data[i][2] + cWeight;

					if (paths[(int)origin][(int)data[i][nodex]] != NULL) {
						delete paths[(int)origin][(int)data[i][nodex]];
						paths[(int)origin][(int)data[i][nodex]] = NULL;
					}

					paths[(int)origin][(int)data[i][nodex]] = new float[((int)cPath[0]) + 2];
					paths[(int)origin][(int)data[i][nodex]][0] = ((int)cPath[0]) + 1;
					for (int j = 1; j < (int)cPath[0]+1; j++) {
						paths[(int)origin][(int)data[i][nodex]][j] = cPath[j];
					}

					paths[(int)origin][(int)data[i][nodex]][(int)cPath[0]+1] = cNode;
				}
			}


		}

		visits[visSize] = cNode;
		visSize++;
		min = getMin(numNo,visSize,pathLengths[(int) origin],visits,&cNode);
		if (min == -1) {
			return;
		}
		cPath = paths[(int)origin][(int)cNode];
		cWeight = pathLengths[(int)origin][(int)cNode];
	}
}

// Code for part 1. Print out the sequence of airports and price
// of the trip.
void Graph::find_ticket(float origin, float dest){
	if (ran[(int)origin] == false) {
		Graph::genTree(origin);
	}
	if (pathLengths[(int)origin][(int)dest] == -1) {
		cout << "not possible" << endl;
		return;
	}
	else {
		for (int i = 1; i < paths[(int)origin][(int)dest][0]+1; i++) {
			if (i != 1) {
				cout << " ";
			}
			cout << key[(int)paths[(int)origin][(int)dest][i]];
		}
		cout << " " << key[(int)dest];
		printf(" %.2f\n", pathLengths[(int)origin][(int)dest]);
	}
}

// Code for part 2. Print out the tour sequence or "not possible"
// if not all cities can be visited.
void Graph::eulerian_tour(float origin)
{
	if (ran[(int)origin] == false) {
		Graph::genTree(origin);
	}
	for (int i = 0; i < numNo; i++) {
		if (pathLengths[(int)origin][i] == -1) {
			cout << "not possible" << endl;
			return;
		}
	}
	for (int i = 0; i < numNo; i++) {
		if (i != (int)origin) {
			for (int j = 1; j < paths[(int)origin][i][0] + 1; j++) {
				cout << " " << key[(int)paths[(int)origin][i][j]];
			}
		}
		cout << endl;
	}
	rec_tour(origin, origin, 1);
	return;
}

void Graph::rec_tour(float origin, float node, int steps) {
	cout << key[(int) node] << endl;
	int nmat = 0;
	float* ends = searchSort(origin, node, steps, &nmat);
	if (nmat == 0) {
		return;
	}
	else {
		for (int i = 0; i < nmat;i++) {
			rec_tour(origin, ends[i], steps + 1);
		}
	}
}

float* Graph::searchSort(float origin, float node, int steps, int* nmat) {
	float* temp = new float[numNo];
	int numMatch = 0;
	for (int i = 0; i < numNo; i++) {
		if (i != (int)origin) {
			if (((int)paths[(int)origin][i][0] == steps) && (paths[(int)origin][i][steps] == node)) {
				temp[numMatch] = i;
				numMatch++;
			}
		}
	}
	*nmat = numMatch;
	if (numMatch == 0) {
		return NULL;
	}
	float* endNodes = new float[numMatch];
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < numMatch-1; i++) {
			if (key[(int)temp[i]].compare(key[(int)temp[i + 1]])>0) {
				float tdex = temp[i];
				temp[i] = temp[i + 1];
				temp[i + 1] = tdex;
				sorted = false;
			}
		}
	}
	for (int i = 0; i < numMatch; i++) {
		endNodes[i] = temp[i];
	}
	delete temp;
	return endNodes;
}



bool Graph::visited(int size, float node, float* check) {
	for (int k = 0; k < size; k++) {
		if (node == check[k]) {
			return true;
		}
	}
	return false;
}

float Graph::getMin(int wSize, int vSize, float* weights, float* visits, float* cnode) {
	int min = -1;
	for (int k = 0; k < wSize; k++) {
		if (!visited(vSize,k,visits)) {
			if (min == -1 || (min > weights[k]&&weights[k]!=-1)) {
				min = weights[k];
				*cnode = k;
			}
		}
	}
	return min;
}