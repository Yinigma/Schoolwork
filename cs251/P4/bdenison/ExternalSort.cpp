#include "ExternalSort.h"
#include <iostream>
#include <fstream>
#include <string>

/*
	External Sorting algorithm.
	Step 1: Reads the input file one chunk at a time
	Step 2: Sorts each chunk
	Step 3: Writes each chunk to a temporary file
	Step 4: Performs a k-wise merge on the temporary files

*/
void extern_sort(string in_fname, string out_fname, string chunk_location, int chunk_size){
	ifstream toSort;
	int vomCount = 0; //number of entries in the current chunk
	int chunkNum = 0; //number of chunks
	toSort.open(in_fname);
	string* data = new string[chunk_size];
	while(toSort.is_open()) {
		vomCount = -1;
		for (int i = 0; i < chunk_size; i++) {
			if (!toSort.eof()) {
				getline(toSort, data[i]);
			}
			else {
				vomCount = i;
				toSort.close();
				break;
			}
		}
		if(vomCount==-1){
			vomCount = chunk_size;
		}
		if(!toSort.is_open()){
			break;
		}
		sort(data,0,vomCount-1);

		char * filename = (char*) malloc(11*sizeof(char));
		sprintf(filename,"chunk%05d",chunkNum+1);
		string dir = chunk_location + filename;
		ofstream curChunk(dir);
		free(filename);
		for(int i = 0; i<vomCount; i++){
			curChunk << data[i] << endl;
		}
		chunkNum++;
	}
	delete[] data;
	k_merge(chunk_location, out_fname, chunkNum);
	return;
} 

/*
	Your favorite n*log(n) sorting algorithm.
	Be sure that you use an in-place version of the algorithm.
	i.e. It does not generate a new array to return, but rather
	works by swapping elements in the input array.
	
	Possible options:
		-Quicksort
		-Mergesort
		-Heapsort
		
*/

void sort(string* data, int left, int right) {
	if ((right - left) <= 0) {
		return;
	}
	int begin = left;
	int end = right;
	string pivot = data[left++];
	string temp;
	while (left<=right) {
		while (left <= right&&data[left].compare(pivot) < 0) {
			left++;
		}
		while (left<=right&&data[right].compare(pivot) > 0) {
			right--;
		}
		if (left <= right) {
			temp = data[right];
			data[right] = data[left];
			data[left] = temp;
			left++;
			right--;
		}
	}
	data[begin] = data[right];
	data[right] = pivot;
	sort(data, begin, right-1);
	sort(data, right+1, end);
	return;
}

// Merges the k temporary files
void k_merge(string chunk_location, string out_fname, int num_chunks)
{
	bool allEOF = false;
	ifstream* chunks = new ifstream[num_chunks];
	//chunk_location = "/homes/bdenison/project4/P4_Skeleton/testcases/chunks1/";	
	for (int i = 0; i < num_chunks; i++) {
		char * filename = (char*) malloc(11*sizeof(char));
		sprintf(filename,"chunk%05d",i+1);
		string dir = chunk_location + filename;
		chunks[i].open(dir);
		free(filename);
	}
	
	ofstream out(out_fname); //"/homes/bdenison/project4/P4_Skeleton/kmergetest"

	string* heads = new string[num_chunks];


	for(int i = 0; i< num_chunks; i++){
		getline(chunks[i], heads[i]);
	}
	
	while (!allEOF) {
		string max = "";
		string current = "";
		allEOF = true;
		bool initMax = false;
		int mDex;
		for (int i = 0; i < num_chunks; i++) {
			if (!chunks[i].eof()) {
				allEOF = false;
				if (initMax) {
					current = heads[i];
					if(max.compare(current)>0){
						max = current;
						mDex = i;
					}
				}
				else {
					max = heads[i];
					initMax = true;
					mDex = i;
				}
			}
			else{ 
				if(chunks[i].is_open()){
					chunks[i].close();
				}
			}
		}
		if(!allEOF){
			getline(chunks[mDex],heads[mDex]);
			out<<max<<endl;
		}
	}
	out.close();
	return;
}
