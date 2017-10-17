
/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>


#include "command.h"

SimpleCommand::SimpleCommand()
{
	/*// Set a command word to save myself a headache EDIT: are you fucking kidding me?
	_commandWord = com;*/
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_arguments = (char **) malloc( _numberOfAvailableArguments * sizeof( char * ) );
	_arguments[0] = NULL;
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,  _numberOfAvailableArguments * sizeof( char * ) );
	}
	
	_arguments[ _numberOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	_numberOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numberOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numberOfAvailableSimpleCommands == _numberOfSimpleCommands ) {
		_numberOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numberOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numberOfSimpleCommands ] = simpleCommand;
	_numberOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numberOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inputFile ) {
		free( _inputFile );
	}

	if ( _errFile ) {
		free( _errFile );
	}

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inputFile?_inputFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}

void
Command::execute()
{
	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	// Print contents of Command data structure
	// print();


	//+3 fds for storing default I/O
	int defaultin = dup( 0 );
	int defaultout = dup( 1 );
	int defaulterr = dup( 2 );


	//Redirect error
	int eFile = 0;
	if(_errFile){
		if(_append){
			eFile = open(_errFile, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
		}
		else{
			eFile = open(_errFile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		}
	}
	dup2(eFile, 2);

	//Redirect initial input
	int currentInput = 0;
	int inFile = 0;
	if(_inputFile){
		//+1 fd for opening input file
		inFile = open(_inputFile, O_RDONLY, 1);
		currentInput = inFile;
	}
	else{
		currentInput = defaultin;
	}

	//Allocate space for pipes	
	int inPipe[2];
	int outPipe[2];

	//Make two new fd's out of our current input (they get closed later, don't worry)
	inPipe[0] = dup(currentInput);
	inPipe[1] = dup(currentInput);
	
	//This loop should end with a pipe from which we get input for the last command
	for ( int i = 0; i<( _numberOfSimpleCommands-1 ); i++ ) {
		
		//+2 fds with new pipe
		if(pipe(outPipe)==-1){
			//perror("");
			exit(2);
		}
		
		int pid = fork();
		if(pid==0){
			//This gets rid of all 7-8 possible file descriptors
			dup2(inPipe[0], 0);
			dup2(outPipe[1], 1);
			//-3 fds close all defaults
			close(defaultin);
			close(defaultout);
			close(defaulterr);
			//-4 fds close all pipes
			close(inPipe[0]);
			close(inPipe[1]);
			close(outPipe[0]);
			close(outPipe[1]);
			if(_errFile){
				close(eFile);
			}
			if(_inputFile){
				//-1 fd close input file
				close(inFile);
			}
			execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
			//perror("");
			exit(2);
			
		}
		//-2 fds for closing old pipe
		close(inPipe[0]);
		close(inPipe[1]);
		inPipe[0] = outPipe[0];
		inPipe[1] = outPipe[1];
		//I don't close the stuff in outPipe because I'm still using it.
		
	}
	//loop ends with 5-6 file descriptors, those being the contents of the two pipes (should be the exact same) the defaults, and our possible input file


	//Redirect output
	int oFile = 0;
	if(_outFile){
		if(_append){
			oFile = open(_outFile, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
		}
		else{
			oFile = open(_outFile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		}
	}


	int pid = fork();
	if(pid==0){
		//This gets rid of all 7-8 possible file descriptors
		dup2(inPipe[0], 0);
		if(oFile){
			dup2(oFile, 1);
		}
		else{
			dup2(defaultout, 1);
		}
		//-3 fds close all defaults
		close(defaultin);
		close(defaultout);
		close(defaulterr);
		//-2 fds close content of pipes
		close(inPipe[0]);
		close(inPipe[1]);
		if(_errFile){
			//-1 fd close output file
			close(eFile);
		}
		if(_inputFile){
			//-1 fd close input file
			close(inFile);
		}
		if(_outFile){
			//-1 fd close output file
			close(oFile);
		}
		execvp(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[0], _simpleCommands[_numberOfSimpleCommands-1]->_arguments);
		//perror("");
		exit(2);
	}
	//-2 fds close content of pipes
	close(inPipe[0]);
	close(inPipe[1]);
	
	//Restore defaults
	dup2(defaultin, 0);
	dup2(defaultout, 1);
	dup2(defaulterr, 2);
	//-3 fds closing defaults
	close(defaultin);
	close(defaultout);
	close(defaulterr);
	
	if(_errFile){
		close(eFile);
	}
	if(_inputFile){
		close(inFile);
	}
	if(_outFile){
		close(oFile);
	}
	
	if(!_background){
		waitpid(pid, NULL, 0);
	}

	// Clear to prepare for next command
	clear();
	
	// Print new prompt
	if(isatty(1)){
		prompt();
	}
}

void killZombie( int sig ){
	int kidpid = waitpid(-1, NULL, 0);
	if(kidpid>0){
		printf("[%d] exited.\n", kidpid);
	}
}

// Shell implementation

void Command::prompt()
{
	printf("myshell>");
	fflush(stdout);
}
void Command::quit(){
	printf("\n\n...\n");
	sleep(1);
	printf("\n\nI never loved you.\n\n\n");
	sleep(2);
	exit(0);
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);

main()
{
	if(isatty(1)){
		Command::_currentCommand.prompt();
	}
	sigignore(SIGINT);
	/*struct sigaction signalAction;
	signalAction.sa_handler = killZombie;
	sigemptyset(&signalAction.sa_mask);
	signalAction.sa_flags = SA_RESTART;
	int error = sigaction(SIGCHLD, &signalAction, NULL );*/
	if ( error ) {
		perror( "sigaction" );
		exit(-1);
	}
	yyparse();
}

