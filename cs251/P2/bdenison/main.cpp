#include <iostream>
#include <string>
#include "stack.h"
#include "deque.h"

using namespace std;


//Runs in "Nice job, you shitty programmer" time! This also looks kinda like a pathfinding problem...
//Bet you couldn't tell by looking at it, but this crashes for whatever reason if you try and send the first array with any data at all. I have no clue why.
bool nextLetter(std::string toFind, char** search, int nr, int nc, Stack& s, int r, int c, Stack& t) {



	bool contin = false;
	s.push(pair<int, int>(r, c));
	if (s.getSize() == toFind.length()) {

		for (int i = 0; i < toFind.length(); i++) {
			std::pair<int, int> pop = s.pop();
			t.push(pair<int, int>(pop.first, pop.second));
		}
		return true;
	}
	if (r > 0) {
		if (c > 0) {
			if (search[r-1][c-1] == toFind.at(s.getSize())) {
				contin = contin || nextLetter(toFind, search, nr, nc, s, r - 1, c - 1,t);
			}
		}
		if (c < nc) {
			if (search[r - 1][c + 1] == toFind.at(s.getSize())) {
				contin = contin || nextLetter(toFind, search, nr, nc, s, r - 1, c + 1, t);
			}
		}
		if (search[r - 1][c] == toFind.at(s.getSize())) {
			contin = contin || nextLetter(toFind, search, nr, nc, s, r - 1, c, t);
		}
	}
	if (r < nr) {
		if (c > 0) {
			if (search[r + 1][c - 1] == toFind.at(s.getSize())) {
				contin = contin || nextLetter(toFind, search, nr, nc, s, r + 1, c - 1, t);
			}
		}
		if (c < nc) {
			if (search[r + 1][c + 1] == toFind.at(s.getSize())) {
				contin = contin || nextLetter(toFind, search, nr, nc, s, r + 1, c + 1, t);
			}
		}
		if (search[r + 1][c] == toFind.at(s.getSize())) {
			contin = contin || nextLetter(toFind, search, nr, nc, s, r + 1, c, t);
		}
	}
	if (c > 0) {
		if (search[r][c-1] == toFind.at(s.getSize())) {
			contin = contin || nextLetter(toFind, search, nr, nc, s, r, c - 1, t);
		}
	}
	if (c < nc) {
		if (search[r][c+1] == toFind.at(s.getSize())) {
			contin = contin || nextLetter(toFind, search, nr, nc, s, r, c + 1, t);
		}
	}
	if (!contin) {
		std::pair<int, int> pop = s.pop();
	}
	return contin;

}

void read_part_1(){
	//Read the number of commands to execute
    int n;
    cin >> n;
    
	Stack stack = Stack();
    
    char command1;
    int value1,value2;
    
    while (n--) 
    {
        cin >> command1;
        if (command1 == 'i')
        {
            cin >> value1 >> value2;
            
			stack.push(pair<int,int>(value1,value2));
        }
        if (command1 == 'p')
        {
			
			if (stack.isEmpty()) {
				cout << "empty" << endl;
			}
			else {
				std::pair<int, int> pop = stack.pop();
				cout << pop.first << " " << pop.second << endl;
			}
			
        }
    }
}

void read_part_2()
{
	int num_rows = 0, num_cols = 0;
	std::string word;
	Stack wordLoc = Stack();
	Stack whyDoIExist = Stack();
	
	//Read in the number of rows and cols in the puzzle

	cin >> num_rows >> num_cols;

	//Declare the word search array

	//Fill in the array

	char** wordUp = new char*[num_rows];
	for (int i = 0; i < num_rows; i++) {
		wordUp[i] = new char[num_cols];
		for (int j = 0; j < num_cols; j++) {
			cin >> wordUp[i][j];
		}
	}

	//Read in the word we're looking for

	//...yeah, this is probably a stupid way to do this...
	cin >> word;


	//TODO: Part 1b: Run the word search
	bool found = false;
	for(int i = 0; i < num_rows; i++) {
		if (found) {
			continue;
		}
		for (int j = 0; j < num_cols; j++) {
			if (found) {
				continue;
			}
			if (wordUp[i][j] == word[0]) {
				found = nextLetter(word, wordUp, num_rows, num_cols, wordLoc, i, j, whyDoIExist);
			}
		}
	}
	if (found) {
		int s = whyDoIExist.getSize();
		for (int i = 0; i < s; i++) {
			std::pair<int, int> pop = whyDoIExist.pop();
			cout << pop.first << " " << pop.second << endl;
		}
	}
	else {
		cout << "not found" << endl;
	}
}

void read_part_3()
{
	//Read in the number of commands to execute
	int n, val = 0;
	cin >> n;
	char command1,command2;
	Deque deq = Deque();
	while(n--)
	{
		cin >> command1;
		if (command1 == 'e') {
			cin >> command2;
			cin >> val;
			if (command2 == 'f') {
				deq.enqueue_front(val);
			}
			else if (command2 == 'b') {
				deq.enqueue_back(val);
			}
		}
		else if (command1 == 'd') {
			cin >> command2;
			if (command2 == 'f') {
				cout<<deq.dequeue_front()<<endl;
			}
			else if (command2 == 'b') {
				cout << deq.dequeue_back() << endl;
			}
		}
		else if (command1 == 's') {
			cout << deq.get_array_size() << endl;
		}
	}
}

void read_input()
{
	int project_part;
	//Read the first line of the test case
	cin >> project_part;
	
	switch(project_part)
	{
		case 1:
			read_part_1();
			break;
		case 2:
			read_part_2();
			break;
		case 3:
			read_part_3();
			break;
	}
}

int main()
{
	// Read in the test case
	read_input();
	return 0;
}