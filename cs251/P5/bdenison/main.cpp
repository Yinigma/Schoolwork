 #include <iostream>
 #include <string>
 #include "graph.h"
 
 using namespace std;
 
 // Part 1: Find tickets for an airline passenger
 void P5_part1()
 {
	 int nodes, edges;
	 int ncount = 0;
	 float cweight;
	 string n1,n2;
	 bool inList1;
	 bool inList2;
	 
	 
	 cin >> nodes;
	 cin >> edges;
	 float** g = new float*[nodes];
	 string* lookup = new string[nodes];
	 for (int i = 0; i < edges; i++) {

		 g[i] = new float[3];
		 
		 cin >> n1;
		 cin >> n2;
		 cin >> cweight;

		 g[i][2] = cweight;

		 inList1 = false;
		 inList2 = false;
		 for (int j = 0; j < ncount; j++) {
			 if (n1.compare(lookup[j])==0) {
				 inList1 = true;
				 g[i][0] = (float)j;
			 }
			 if (n2.compare(lookup[j])==0) {
				 inList2 = true;
				 g[i][1] = (float)j;
			 }
		 }
		 if (!inList1) {
			 lookup[ncount] = n1;
			 g[i][0] = (float) ncount;
			 ncount++;
		 }
		 if (!inList2) {
			 lookup[ncount] = n2;
			 g[i][1] = (float)ncount;
			 ncount++;
		 }
	 }

	 Graph graph(g,edges,nodes,lookup);

	 cin >> n1;
	 cin >> n2;

	 float a;
	 float b;

	 while(n1.compare("END") != 0) // Find tickets until END appears
	 {
		 for (int i = 0; i < nodes; i++) {
			 if (n1.compare(lookup[i])==0) {
				 a = i;
			 }
			 if (n2.compare(lookup[i])==0) {
				 b = i;
			 }
		 }
		 graph.find_ticket(a, b);

		 cin >> n1;
		 if (n1.compare("END") != 0) {
			 cin >> n2;
		 }

	 }
 }
 
 // Part 2: Perform an eulerian tour of the graph.
 void P5_part2()
 {
	 int nodes, edges;
	 int ncount = 0;
	 float cweight;
	 string n1, n2;
	 bool inList1;
	 bool inList2;


	 cin >> nodes;
	 cin >> edges;
	 float** g = new float*[nodes];
	 string* lookup = new string[nodes];
	 for (int i = 0; i < edges; i++) {

		 g[i] = new float[3];

		 cin >> n1;
		 cin >> n2;
		 cin >> cweight;

		 g[i][2] = cweight;

		 inList1 = false;
		 inList2 = false;
		 for (int j = 0; j < ncount; j++) {
			 if (n1.compare(lookup[j]) == 0) {
				 inList1 = true;
				 g[i][0] = (float)j;
			 }
			 if (n2.compare(lookup[j]) == 0) {
				 inList2 = true;
				 g[i][1] = (float)j;
			 }
		 }
		 if (!inList1) {
			 lookup[ncount] = n1;
			 g[i][0] = (float)ncount;
			 ncount++;
		 }
		 if (!inList2) {
			 lookup[ncount] = n2;
			 g[i][1] = (float)ncount;
			 ncount++;
		 }
	 }

	 Graph graph(g, edges, nodes, lookup);


	 cin >> n1;
	 float a;

	 for (int i = 0; i < nodes; i++) {
		 if (n1.compare(lookup[i]) == 0) {
			 a = i;
		 }
	 }

	 graph.eulerian_tour(a);

 }
 
 int main()
 {
	 int cmd;
	 cin >> cmd;
	 if(cmd == 1) P5_part1();
	 else if(cmd == 2) P5_part2();
	 return 0;
 }