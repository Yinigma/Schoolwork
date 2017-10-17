#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

#include"MPP.h"

void playSong(int time){

	system("gpio mode 27 output");
	int pid = fork();
	printf("read: %d\n",time);
	if(pid<0){
		perror("You done goofed.\n");
		exit(1);
	}
	else if(pid==0){
		char* song;
		if(time==0){
			song = "el_toro.mp3";
			system("gpio write 27 1");
			
		}
		else if(time==1){
			song = "chiptune_memories.mp3";
		}
		else{
			song = "airbase.mp3";
		}
		char* cmd[] = {"mpg321",song,(char*)0};
		
		execv("/usr/bin/mpg321",cmd);
	}
	else{
		
		sleep(15);
		if(time<EVENING){
			system("gpio write 27 0");
		}
		kill(pid,9);
	}

}