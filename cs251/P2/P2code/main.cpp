#include <iostream>
#include "stack.h"
#include "deque.h"

using namespace std;



void read_part_1()
{
	//Read the number of commands to execute
    int n;
    cin >> n;
    
    // Initialize your stack here...
    
    char command1;
    int value1,value2;
    
    while (n--) 
    {
        cin >> command1;
        if (command1 == 'i')
        {
            cin >> value1 >> value2;
            
            // push the values in your stack here.
        }
        if (command1 == 'p')
        {
            // Call Pop here, and print the values.
        }
    }
}

void read_part_2()
{
	int num_rows,num_cols;
	
	//Read in the number of rows and cols in the puzzle

	//Declare the word search array

	//Fill in the array

	//Read in the word we're looking for
	
	//TODO: Part 1b: Run the word search
}

void read_part_3()
{
	//Read in the number of commands to execute
	int n;
	cin >> n;
	char command1,command2;
	while(n--)
	{
		cin >> command1 >> command2;
		
		// process command1 and command2
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