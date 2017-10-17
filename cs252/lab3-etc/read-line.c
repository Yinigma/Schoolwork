#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_LINE 2048

#define NUL 0
#define BSP 8
#define NEWLN 10
#define ESC 27
#define SPACE 32
#define DEL 127

// Buffer where line is stored
int line_length;
char * line_buffer;


int history_index = 0;
char * history [MAX_HISTORY_LINES];
char bsp = BSP;
char spc = SPACE;


//Alright, bitches. Linked list time

typedef struct charLink{
	char data;
	struct charLink * next;
	struct charLink * prev;
};
struct charLink * sentinel;

void deleteList(struct charLink* s){
	struct charLink * toFree = s->next;
	struct charLink * temp;
	while(toFree!=s){
		temp = toFree;
		toFree = toFree->next;
		free(temp);
	}
	free(s);
}

void insertAt(struct charLink* insertPoint, char c){
	struct charLink * toInsert = (struct charLink *)malloc(sizeof(struct charLink));
	toInsert->data = c;
	toInsert->next = insertPoint->next;
	toInsert->prev = insertPoint;
	insertPoint->next->prev = toInsert;
	insertPoint->next = toInsert;
}

char * dump(int buffersize, struct charLink * s){
	char * out = (char *) malloc(buffersize * sizeof(char));
	struct charLink * current = s->next;
	for(int i = 0; i < buffersize-2; i++){
		out[i] = current->data;
		current = current->next;
	}
	out[buffersize-2] = NEWLN;
	out[buffersize-1] = NUL;
	return out;
}

void * removeLink(struct charLink * toRemove, struct charLink * s){
	if(toRemove!=s){
		toRemove->next->prev = toRemove->prev;
		toRemove->prev->next = toRemove->next;
		free(toRemove);
	}
}

void refresh(struct charLink * insert){
		struct charLink * temp = insert;
		int counter = 0;
			
		while(temp->next!=sentinel){			//copies all characters from temp to sentinel
			write(1,&(temp->next->data),1);
			temp = temp->next;
			counter++;
		}
		write(1,&spc,1);
		write(1,&bsp,1);
		while(counter){							//resets stdout cursor
			write(1,&bsp,1);
			counter--;
		}
}

char * read_line() {

	sentinel = malloc(sizeof(struct charLink));
	sentinel->data = -1;
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
	struct charLink * insertPoint = sentinel;

	// Set terminal in raw mode

	tty_raw_mode();

	line_length = 2;

	// Read one line until enter is typed

	while (1) {

		char ch;									// Read one character in raw mode.
		read(0, &ch, 1);

		if(ch>=SPACE&&ch!=DEL) {					//space is the first printable character
			if (line_length==MAX_BUFFER_LINE-2){	// If max number of character reached, replace last character
				write(1,&bsp,1);
				insertPoint = insertPoint->prev;
				line_length--;						//prints the backspace character, setting the cursor back one
			}
			write(1,&ch,1);							//put character in stdout
			insertAt(insertPoint, ch);				//add char to list
			insertPoint = insertPoint->next;


			refresh(insertPoint);


			line_length++;
		}
		else if(ch==NEWLN) {
			write(1,&ch,1);							// Print newline
			break;
		}
		else if(ch==ESC){
			char esc1;
			char esc2;
			read(0, &esc1, 1);
			read(0, &esc2, 1);
			if(esc2=='C'&&insertPoint->next!=sentinel){
				insertPoint=insertPoint->next;
				write(1,&(insertPoint->data),1);
			}
			if(esc2=='D'&&insertPoint!=sentinel){
				insertPoint=insertPoint->prev;
				write(1,&bsp,1);
			}
		}
		else if(((ch==DEL)||(ch==DEL))&&(insertPoint!=sentinel)){//if insertPoint = sentinel, then there are no characters
			struct charLink * temp = insertPoint;
			insertPoint = insertPoint->prev;
			removeLink(temp, sentinel);
			line_length--;
			write(1,&bsp,1);
			refresh(insertPoint);
		}
	}

	// Add eol and null char at the end of string
	line_buffer = dump(line_length, sentinel);
	printf("%s\n",line_buffer);
	deleteList(sentinel);

	//return line_buffer;
}

