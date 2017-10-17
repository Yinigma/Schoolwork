#include <iostream>
#include <string>

using namespace std;

class Graph
{
	public:
		// Constructor
		Graph(float** edges,int nEdges, int nNodes, string* k);
		
		// Part 1: Find a ticket using Dijkstra
		void find_ticket(float origin, float dest);
		
		// Part 2: Try to do a tour of all cities
		void eulerian_tour(float origin); 
	
	// Add any needed private methods here
	private:
		void rec_tour(float origin, float node, int steps);
		void genTree(float origin);
		float* searchSort(float origin, float node, int steps, int* nmat);
		string* key;
		bool* ran;
		float** data;
		int numEd;
		int numNo;
		float** pathLengths;
		float*** paths;
		bool visited(int size, float node, float* check);
		float getMin(int wSize, int vSize, float* weights, float* visited, float* cnode);

};