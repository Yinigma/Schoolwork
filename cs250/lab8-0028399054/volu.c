#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include<sys/types.h>
#include<unistd.h>

#define PLUS 29
#define MINUS 28

int volButt(){

	int pid = fork();
	printf("New volume fork.\n");
	
	if(pid<0){
		perror("You done goofed.\n");
		exit(1);
	}
	else if(pid==0){

		pinMode(PLUS, INPUT);
		pinMode(MINUS, INPUT);
	

		int loud;
		int soft;	

		while(1){
		
			loud = digitalRead(PLUS);
			soft = digitalRead(MINUS);
		

			if(loud==HIGH&&soft!=HIGH){
		
				system("sudo ./vol +");
				
			}

			if(soft==HIGH&&loud!=HIGH){

				system("sudo ./vol -");
			}

			sleep(1);
		}
	}
	else{
		return pid;
	}
}