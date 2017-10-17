
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
#include <dirent.h>
#include <libgen.h>
#include <regex.h>


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
Command::execute()
{
	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	//+3 fds for storing default I/O
	int defaultin = dup( 0 );
	int defaultout = dup( 1 );
	int defaulterr = dup( 2 );

	int commInput = 0;
	int commErr = 0;
	int commOut = 0;

	//Redirect error +1 fd either way
	if(_errFile){
		if(_append){
			commErr = open(_errFile, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
		}
		else{
			commErr = open(_errFile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		}
	}
	else{
		commErr = dup(defaulterr);
	}
	dup2(commErr, 2);

	//Redirect initial input +1 fd either way
	if(_inputFile){
		commInput = open(_inputFile, O_RDONLY, 1);
	}
	else{
		commInput = dup(defaultin);
	}

	//Allocate space for pipes	
	int inPipe[2];
	int outPipe[2];

	//Make two new fd's out of our command's input (they get closed later, don't worry)
	inPipe[0] = dup(commInput);
	inPipe[1] = dup(commInput);
	
	//This loop should end with a pipe from which we get input for the last command
	for ( int i = 0; i<( _numberOfSimpleCommands-1 ); i++ ) {
		
		//+2 fds with new pipe
		if(pipe(outPipe)==-1){
			exit(2);
		}
		//Test for built-in commands
		//Setenv
		if(strcmp(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[0],"setenv")==0){
			if(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[1]!=NULL){
				setenv(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[1],_simpleCommands[_numberOfSimpleCommands-1]->_arguments[2],1);
			}
			else{
				//cshell just does a printenv on null argument
				dup2(inPipe[0], 0);
				dup2(outPipe[1], 1);
				this->Command::printenv();
			
			}
		}
		else if(strcmp(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[0],"printenv")==0){
				dup2(inPipe[0], 0);
				dup2(outPipe[1], 1);
				this->Command::printenv();
		}
		else{
			int pid = fork();
			if(pid==0){
				//Rediredt I\O to the output end of the outgoing pipe and the input end of the incoming pipe
				dup2(inPipe[0], 0);
				dup2(outPipe[1], 1);
				//-3 fds close all defaults
				close(defaultin); close(defaultout); close(defaulterr);
				//-4 fds close all pipes
				close(inPipe[0]); close(inPipe[1]); 
				close(outPipe[0]); close(outPipe[1]);
				//-2 fds close redirects
				close(commInput); close(commErr);

				execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
				perror("");
				exit(2);
			
			}
		}
		//-2 fds for closing old pipe
		close(inPipe[0]);
		close(inPipe[1]);
		inPipe[0] = outPipe[0];
		inPipe[1] = outPipe[1];
		
	}
	
	//Redirect output
	if(_outFile){
		if(_append){
			commOut = open(_outFile, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
		}
		else{
			commOut = open(_outFile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		}
	}
	else{
		commOut = dup(defaultout);
	}
	int pid = -1;
	//Test for built-in commands. Keep this all as one if-then statment!!!
	//setenv
	if(strcmp(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[0],"setenv")==0){
		if(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[1]!=NULL){
			setenv(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[1],_simpleCommands[_numberOfSimpleCommands-1]->_arguments[2],1);
		}
		else{
			//redirect output
			dup2(inPipe[0], 0);
			dup2(commOut, 1);
			this->Command::printenv();
			
		}
	}
	else if(strcmp(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[0],"printenv")==0){
			//redirect output
			dup2(inPipe[0], 0);
			dup2(commOut, 1);
			this->Command::printenv();
	}
	else{
		pid = fork();
		if(pid==0){
			dup2(inPipe[0], 0);
			dup2(commOut, 1);
			//-3 fds close all defaults
			close(defaultin); close(defaultout); close(defaulterr);
			//-2 fds close content of pipes
			close(inPipe[0]); close(inPipe[1]);
			//-3 fds close redirects
			close(commInput); close(commOut); close(commErr);
			execvp(_simpleCommands[_numberOfSimpleCommands-1]->_arguments[0], _simpleCommands[_numberOfSimpleCommands-1]->_arguments);
			perror("");
			exit(2);
		}
	}

	//Restore defaults
	dup2(defaultin, 0);
	dup2(defaultout, 1);
	dup2(defaulterr, 2);
	//-3 fds closing defaults
	close(defaultin); close(defaultout); close(defaulterr);
	//-2 fds close content of pipes
	close(inPipe[0]); close(inPipe[1]);
	//-3 fds close redirects
	close(commInput); close(commOut); close(commErr);
	
	if(!_background&&pid!=-1){
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
	
}

// Shell implementation

void Command::prompt()
{
	printf("myshell>");
	fflush(stdout);
}
void Command::quit(){
	printf("Lies for the weak...\n");
	exit(0);
}
void Command::printenv(){
	char** temp = environ;
	for(int i = 0; temp[i]; i++){
		printf("%s\n", temp[i]);
	}
	return;
}

//Header file? What's a header file?
//inDir the pain
//I wanna die. Why did you do this to me?
void Command::wildCardExpansion(char * inDir, SimpleCommand * s){
	//printf("indir: %s\n", inDir);
	if(inDir==NULL||inDir[0]=='\0'){
		if(inDir[1]!='\0'){
			//printf("Character %c was blocked by terminator!\n",inDir[1]);
		}
		//printf("There was nothing in inDir\n");
		return;
	}
	int inLen = strlen(inDir);
    int wild = 0;
	int rDex = -1;
	int lDex = -1;
	char * finished = '\0';
	char * remaining = '\0';
	char * pattern = '\0';
	//printf("Checking directory characters\n");
	for(int i = 0; i < inLen; i++){
		if(i==0&&inDir[i]=='/'){
			continue;
		}
		if(inDir[i]=='*'||inDir[i]=='?'){
			wild = 1;
		}
		if(inDir[i]=='/'){
			if(wild==1&&(i!=(inLen-1))){
				rDex = i;
				break;
			}
			else{
				lDex = i;
			}
		}
		
	}
	if(wild==0){
		
		char * ret = (char*) calloc((inLen+1), sizeof(char)); 
		for(int i = 0; i< inLen; i++){
			ret[i] = inDir[i];
		}
		ret[inLen] = '\0';
		//printf("Returning %s\n",ret);
		s->insertArgument(ret);
		return;
	}
	//printf("Seperating directory\n");
	int rlen = 0;
	int flen = 0;
	int plen = 0;
	if(lDex!=-1){
		flen = lDex+1;
		finished = (char*) malloc(flen*sizeof(char));		
		memcpy(finished, inDir, flen-1);
		finished[flen-1] = '\0';
	}
	if(rDex!=-1){
		rlen = inLen-rDex;
		remaining = (char*) malloc(rlen*sizeof(char));		
		memcpy(remaining, (inDir+rDex+1), rlen-1);
		remaining[rlen-1] = '\0';
	}
	plen = inLen-rlen-flen+1;
	pattern = (char*) malloc(plen*sizeof(char));
	memcpy(pattern, (inDir+lDex+1), plen-1);
	pattern[plen-1] = '\0';
	//printf("finshed: %s\n",finished);
	//printf("pattern: %s\n",pattern);
	//printf("remaining: %s\n",remaining);
	
	char * conv = (char *) calloc(2*plen+1, sizeof(char));
	conv[0] = '^';
	//convert pattern
	int numAster = 0;
	
	for(int i = 0; i<(plen-1); i++){
		if(pattern[i]=='?'){
			conv[i+numAster+1]='.';
		}
		else if(pattern[i]=='*'){
			conv[i+numAster+1]='.';
			numAster++;
			conv[i+numAster+1]='*';
		}
		else{
			conv[i+numAster+1]=pattern[i];
		}
	}
	conv[plen+numAster] = '$';
	conv[plen+numAster+1] = '\0';
	realloc(conv, plen+numAster);
	//printf("converted: %s\n",conv);


	//Everythings seperated. Let's go to hell.

	//printf("Setting up regex\n");
	//set up regex
	regex_t re;
	int result = regcomp( &re, conv,  REG_EXTENDED|REG_NOSUB);
	if(result != 0) {
		fprintf( stderr, "Bad regex\n");
    }

	DIR* tameDir;
	struct dirent* dp;
	if(lDex!=-1){
		if((tameDir = opendir(finished)) == NULL){
			//don't do anything
			return;
		}
	}
	else{
		tameDir = opendir(".");
	}

	int numMatches = 0;
	while ((dp = readdir(tameDir)) != NULL) {
		if(dp->d_type==DT_DIR||rDex==-1){
			
			//Regex matching

			regmatch_t match;
			result = regexec( &re, dp->d_name, 1, &match, 0 );
			
			if(result==0&&dp->d_name[0]!='.'){
				numMatches++;
			}
		}
	}
	closedir(tameDir);
	if(numMatches==0){
		//Nothing in the directory matches. Don't do anything
		//printf("No matches!\n");
		return;
	}
	//Oh my god I'm actually doing this stupid shit.
	if(lDex!=-1){
		tameDir = opendir(finished);
	}
	else{
		tameDir = opendir(".");
	}
	char * matches[numMatches];
	int counter = 0;
	//Like holy fuck, I get the feeling this is not safe at all
	//I just can't think of a way to get a reliable buffer other than make it fucking huge or bring in an adt to this already ugly af function
	while ((dp = readdir(tameDir)) != NULL) {
		if(dp->d_type==DT_DIR||rDex==-1){
			regmatch_t match;
			result = regexec( &re, dp->d_name, 1, &match, 0 );
			
			if(result==0&&dp->d_name[0]!='.'){
				//need to deep copy or it goes kaput?
				int len = strlen(dp->d_name);
				matches[counter] = (char*) malloc(len+1 * sizeof(char));
				for(int i = 0; i<len; i++){
					matches[counter][i] = dp->d_name[i];
				}
				matches[counter][len] = '\0';
				counter++;
				
			}
		}
	}
	closedir(tameDir);
	//sort
	int sorted = 0;
	while(!sorted){
		sorted = 1;
		for(int i = 0; i< numMatches-1; i++){
			if(strcmp(matches[i],matches[i+1])>0){
				char * temp = matches[i];
				matches[i] = matches[i+1];
				matches[i+1] = temp;
				sorted=0;
			}
		}
	}
	//printf("Final loop\n");
	int outlen = 0;
	for(int i = 0; i< numMatches; i++){
		//When you have torn all your hair out from trying to get a list of alphabetized files, then you have my permission to recurse
		outlen = strlen(matches[i]);
		char cOutDir[flen+rlen+outlen+1];
		//Reassemble the directory
		if(lDex!=-1){
			//Okay, I'm done. show me the goddamn body
			//snprintf(cOutDir, flen, "%s/", finished);
			memcpy(cOutDir, finished, flen-1);
			cOutDir[flen-1]='/';
		}
		memcpy(cOutDir+flen, matches[i], outlen);
		if(rDex!=-1){
			cOutDir[flen+outlen] = '/';
			memcpy(cOutDir+flen+outlen+1, remaining, rlen-1);
		}
		cOutDir[flen+rlen+outlen] = '\0';
		//LOOK THERE IT IS
		Command::_currentCommand.wildCardExpansion(cOutDir, s);	
	}
	//We're done. Wow.
	return;
}

int Command::isWild(char * inDir){
	//I'm wild, yeah!
	int inLen = strlen(inDir);
	for(int i = 0; i < inLen; i++){
		if(inDir[i]=='*'||inDir[i]=='?'){
			return 1;
		}
	}
	return 0;
}


void Command::expandEnv(char * arg){
	int len = strlen(arg);
	if(arg[0]=='$'&&arg[1]=='{'&&arg[len-1]=='}'&&len>3){
		char * env = (char *) calloc(len-2, sizeof(char));
		memcpy(env, arg+2, len-3);
		env = getenv(env);
		//You all put these guys on the heap. You scared me!
		free(arg);
		len = strlen(env);
		arg = (char *) calloc(len+1, sizeof(char));
		memcpy(arg, env, len);
	}
	return;
}

char* Command::removeQuotes(char * arg){
	int len = strlen(arg);
	if(arg[0]=='"'&&arg[len-1]=='"'&&len>2){
		if(len<=2){
			char * quot = (char *) calloc(1, sizeof(char));
			free(arg);
			return quot;
		}
		char* quot = (char *) malloc(len-1 * sizeof(char));
		memcpy(quot, arg+1, len-2);
		quot[len-2] = '\0';
		free(arg);
		return quot;
	}
	int numEscapes = 0;
	char* escEdit = (char *) malloc(len+1 * sizeof(char));
	for(int i = 0; i<len; i++){
		if(arg[i] != '\\'){
			escEdit[i-numEscapes] = arg[i];
		}
		else{
			numEscapes++;
		}
	}
	if(numEscapes!=0){
		realloc(escEdit, len+1-numEscapes);
		escEdit[len-numEscapes] = '\0';
		free(arg);
		return escEdit;
	}
	return arg;
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
	int error = sigaction(SIGCHLD, &signalAction, NULL );
	if ( error ) {
		perror( "sigaction" );
		exit(-1);
	}*/
	yyparse();
}

