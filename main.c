/*
 * Author:  Atzamis Iosif 
 * Purpose: C Shell Implementation
 * E-mail: csd3094@csd.uoc.gr
 * Language:  C
 */

#include "main.h"
#define MAX_CHAR 1024
#define TRUE 1 	/* This is always true */
#define clear() printf("\033[H\033[J") /* clears the screen */

/*
 *	Function : Print_prompt
 *	--------------------------
 *	Tupwnei to prompt  
 *	 
 */

void Print_prompt(){
  printf("%s@cs345sh/%s/$ ",
  		getlogin(), 					/* user login */
  		strrchr(getcwd(NULL,0), '/')+1 /*current user directory */
  		);

}

/*
 *	Function : Read_command
 *	--------------------------
 *	Dexetai eisodo apo to plhktrologio kai sthn sunexeia parsarei to input
 *	gia na dei ti uparxei kai bazei flags analoga me to input tou xrhsth
 *
 *	 
 */
void Read_command(){
	int counter=0,i=0,dir,sizeof_input;
	int first_params_counter=0,second_params_counter=0,third_params_counter=0;
	int PIPE_ONE =0 , INPUT =0 , OUTPUT=0 , APPEND =0;
	char *directory_path;
	char * current_path = getcwd(NULL,0);
	char * input_token = malloc(sizeof(char)* MAX_CHAR);;
	char * input = malloc(sizeof(char)* MAX_CHAR);
	char * command = malloc(sizeof(char)* MAX_CHAR);
	char **params =malloc(sizeof(char*)*MAX_CHAR);
	char * homedir = getenv("HOME"); /* home directory*/
	char **first_params =malloc(sizeof(char*)*MAX_CHAR);
	char **second_params =malloc(sizeof(char*)*MAX_CHAR);
	char **third_params =malloc(sizeof(char*)*MAX_CHAR);
	fgets(input,MAX_CHAR,stdin);
	sizeof_input=strlen(input) ;

	if(input[sizeof_input - 1] == '\n'){ 			/* we terminate our string */
		input[sizeof_input - 1] = '\0'; 			/* replace \n*/
	}

	input_token = strtok(input, " "); 			/* Gets the first token */
		if (input_token == NULL)				/* Elenxos gia to empty input */
	{											/*standard mem alloc test*/
		return;
	} 
	if(strcmp(input_token,"exit")==0){				/*exits program */
		exit(EXIT_SUCCESS);
	}
	if(strcmp(input_token," ")==0){				/*exits program */
		return ;
	}
	while( input_token != NULL ) {
		if (counter == 0){
			counter++;
			command = input_token; 			/* Prwto arg (command) */
		}
		params[i]=malloc(sizeof(char)* MAX_CHAR);
      	params[i] = input_token; 			/*  Deutero arg (param) */
		 
		if(strcmp(params[i], "|")==0){		/* Pipe*/
			PIPE_ONE=1;
		}
		else if (strcmp(params[i],"<")==0){ /* Input */
			INPUT =1; 	
		}
		else if (strcmp(params[i],">")==0){ /* Output */
			OUTPUT =1; 	
		}
		else if (strcmp(params[i],">>")==0){ /* Append */
			APPEND =1;
		}
		i++;
      	input_token = strtok(NULL, " ");

   }
	if (strcmp(command,"cd")==0){ 			/* cd command */
  		if (params[1] != NULL) { 			/* Ean exei nohma h cd*/	
			strcat(current_path,"/");		/* Enwnw sto current path to directory path pou zhtaei h entolh*/
			directory_path=strdup(current_path);
			strcat(directory_path,params[1]);
			dir=chdir(directory_path);		/* change working directory*/
			Print_prompt();

  		}else{								/* Otan h cd den exei nohma */
			dir=chdir(homedir);		/* change working directory back to home*/
			Print_prompt();  		
		}
	}
	Execute_command(command,params,i,PIPE_ONE,INPUT,OUTPUT,APPEND);
      	


}

/*
 *	Function : Append_prep
 *	--------------------------
 * 	Dexetai enan ** params pinaka kai xwrizei to input sto aristero melos
 *	ths enotlhs kai sto deksio. Sthn sunexeia  tha ektelestei h entolh h deuterh 
 *	entolh kai tha epistrepsei enan ** first_params me thn prwth entolh.	
 *	@param ** params  oloklhrh h entolh
 *	@param num_of_params to megethos tou pinaka **params
 *	@return epistrefei enan double * array
 */
char ** Append_prep(char ** params , int num_of_params){

	char **first_params =malloc(sizeof(char*)*MAX_CHAR);
	char **second_params =malloc(sizeof(char*)*MAX_CHAR);
	int i=0,sec=0,first=0,second=0;

		while (i<num_of_params){
		if (strcmp(params[i],">>")==0){
			sec=1;
			i++;
		}
		if (sec==0){	
			first_params[i]=malloc(sizeof(char)* MAX_CHAR);	
			first_params[i]=params[i];
			first++;
		}
		if (sec==1){	
			second_params[second]=malloc(sizeof(char)* MAX_CHAR);		
			second_params[second]=params[i];
			second++;

		}
		i++;
	}
		if(second_params[0] == NULL){
			perror("-Bash : syntax error near unexpected token `newline' \n");
		}
		if(first_params[0] == NULL){
			perror("-Bash : syntax error near unexpected token `newline' \n");
		}
	int output=open(second_params[0], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
																	/*  O_TRUNC : If the file already exists and is a regular file and the open 
																				mode allows writing (i.e., is O_RDWR or O_WRONLY) it will be truncated to 
																				length 0. If the file is a FIFO or terminal device file, the O_TRUNC 
																				flag is ignored. Otherwise the effect of O_TRUNC is
																		 		unspecified.
																		O_CREAT : If the file does not exist it will be created. 
																		S_IRUSR : 00400 user has read permission 
																		S_IRGRP : 00040 group has read permission 
																		S_IWGRP : 00020 group has write permission 
																		S_IWUSR : 00200 user has write permission 
																		O_WRONLY : write-only 
																	*/
	dup2(output,STDOUT_FILENO);
	close(output);
	return first_params;
}
/*
 *	Function : Output_keep
 *	--------------------------
 * 	Dexetai enan ** params pinaka kai xwrizei to input sto aristero melos
 *	ths enotlhs kai sto deksio. Sthn sunexeia  tha ektelestei h deuterh 
 *	entolh kai tha epistrepsei enan ** first_params me thn prwth entolh.
 *	@param ** params  oloklhrh h entolh
 *	@param num_of_params to megethos tou pinaka **params
  *	@return epistrefei enan double *  char array
 */
char ** Output_prep(char ** params , int num_of_params){
	printf("mphka output\n");
	char **first_params =malloc(sizeof(char*)*MAX_CHAR);
	char **second_params =malloc(sizeof(char*)*MAX_CHAR);
	int i=0,sec=0,first=0,second=0;

		while (i<num_of_params){
		if (strcmp(params[i],">")==0){
			sec=1;
			i++;
		}
		if (sec==0){	
			first_params[i]=malloc(sizeof(char)* MAX_CHAR);	
			first_params[i]=params[i];
			first++;
		}
		if (sec==1){	
			second_params[second]=malloc(sizeof(char)* MAX_CHAR);		
			second_params[second]=params[i];
			second++;

		}
		i++;
	}
	int output = open(second_params[0],O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
																	/*  O_TRUNC : If the file already exists and is a regular file and the open 
																				mode allows writing (i.e., is O_RDWR or O_WRONLY) it will be truncated to 
																				length 0. If the file is a FIFO or terminal device file, the O_TRUNC 
																				flag is ignored. Otherwise the effect of O_TRUNC is
																		 		unspecified.
																		O_CREAT : If the file does not exist it will be created. 
																		S_IRUSR : 00400 user has read permission 
																		S_IRGRP : 00040 group has read permission 
																		S_IWGRP : 00020 group has write permission 
																		S_IWUSR : 00200 user has write permission 
																		O_WRONLY : write-only 
																	*/
	dup2(output,STDOUT_FILENO);
	close(output);
	return first_params;	
}
/*
 *	Function : Input_prep
 *	--------------------------
 * 	Dexetai enan ** params pinaka kai xwrizei to input sto aristero melos
 *	ths enotlhs kai sto deksio. Sthn sunexeia  tha ektelestei h deuterh 
 *	entolh kai tha epistrepsei enan ** first_params me thn prwth entolh.
 *	@param ** params  oloklhrh h entolh
 *	@param num_of_params to megethos tou pinaka **params
 *	@return epistrefei enan double *  char array
 */
char ** Input_prep(char ** params , int num_of_params){
	char **first_params =malloc(sizeof(char*)*MAX_CHAR);
	char **second_params =malloc(sizeof(char*)*MAX_CHAR);
	char **third_params =malloc(sizeof(char*)*MAX_CHAR);
	int i=0,finish_first_param=0,second=0,third=0,sec=0,keep=0;
	while (i<num_of_params){
		if (strcmp(params[i],"<")==0){
			sec++;
			i++;
		}
		if (sec==0){	
			first_params[i]=malloc(sizeof(char)* MAX_CHAR);	
			first_params[i]=params[i];
			
		}
		if (sec==1){	
			second_params[second]=malloc(sizeof(char)* MAX_CHAR);		
			second_params[second]=params[i];
			second++;
		}

		i++;
	}

	while (keep<second){
		if(strcmp(second_params[keep],">")==0){
			sec=3;
			keep++;
		}
		if(sec==3){
			if(second_params[keep]!=NULL){
				third_params[third]=malloc(sizeof(char)* MAX_CHAR);
				third_params[third]=second_params[keep];
				third++;
			}
		}
		keep++;
	} 

	/*int j =0;
	while(j<second){
		printf("%s\n", second_params[j++] );
	} */

	 int input = open(second_params[0],O_RDONLY);	/* read-only mode*/
	 dup2(input,STDIN_FILENO);
	 close(input);
	if(third == 0) { /*  Otan den exoume 3o argument*/
	 	return first_params;
	}
	else{

		/*  O_WRONLY : write-only 
		*	O_CREAT : If the file does not exist it will be created. 
		*/
		int output=open(third_params[0],O_WRONLY | O_CREAT,0666);		
		dup2(output,STDOUT_FILENO);
		close(output);		
		return first_params;
	}
}

/*
 *	Function : Pipe_prep
 *	--------------------------
 * 	Dexetai enan ** params pinaka kai xwrizei to input sto aristero melos
 *	ths enotlhs kai sto deksio. Sthn sunexeia  tha ektelestei h deuterh 
 *	entolh kai tha epistrepsei enan ** first_params me thn prwth entolh.
 *	@param ** params  oloklhrh h entolh
 *	@param num_of_params to megethos tou pinaka **params
 *	@param INPUT flag param h opoia einai 1 otan exoume "<" sto input command
 *	@param OUTPUT flag param h opoia einai 1 otan exoume ">" sto input command
 *	@param APPEND flag param h opoia einai 1 otan exoume ">>" sto input command
 *	@return epistrefei enan double *  char array
 */
void Pipe_prep(char ** params, int num_of_params, int INPUT, int OUTPUT, int APPEND ){
	printf("exw pipe!\n");
	char **first_params =malloc(sizeof(char*)*MAX_CHAR);
	char **second_params =malloc(sizeof(char*)*MAX_CHAR);
	int first=0 , second=0;
	int i =0,sec=0,status,wpid;
	int pipe_fd[2];
	pid_t c_pid; /* paidikh diergasia */

	while (i<num_of_params){
		if (strcmp(params[i],"|")==0){
			sec=1;
			i++;
		}
		if (sec==0){	
			first_params[i]=malloc(sizeof(char)* MAX_CHAR);	
			first_params[i]=params[i];
			first++;
		}
		if (sec==1){	
			second_params[second]=malloc(sizeof(char)* MAX_CHAR);		
			second_params[second]=params[i];
			second++;
		}
		i++;
	}
		int pipe_fork=pipe(pipe_fd);

		/*open a pipe with two fds, [0] for input, [1] for output*/
				if(pipe_fork!=0){
					printf("-Bash : Error failed Pipe \n");
					exit(EXIT_FAILURE);
				}
				if((c_pid=fork())==-1){
					printf("-Bash : Error in fork \n");
					exit(EXIT_FAILURE);
				}else if(c_pid==0) 
				{
					/*
					* 	Redirection flags 
					*/
					if((INPUT==1) && (OUTPUT ==1)){
		      			first_params = Input_prep(first_params,first);
		      		}
		      		else if(OUTPUT == 1) {
			      		first_params = Output_prep (first_params,first);
		      		}
		      		else if (APPEND == 1){
		      			first_params = Append_prep(first_params, first);
				    }

					dup2(pipe_fd[1],1);
					
					close(pipe_fd[0]);
					close(pipe_fd[1]);
														/*Ctrl+s Ctrl+q  */
					wpid = waitpid(c_pid,&status,0); 	/* Waits child-process to finish if not background */
					if (wpid != c_pid){
						perror("-Bash: c_pid error");
					}
					while (!WIFSIGNALED(status) && !WIFEXITED(status));
					execvp(first_params[0],first_params);
					exit(EXIT_SUCCESS);
				}else{

					/*
					* 	Redirection flags 
					*/
					if((INPUT==1) && (OUTPUT ==1)){
		      			second_params = Input_prep(second_params,second);
		      		}
		      		else if(OUTPUT == 1) {
			      		second_params = Output_prep (second_params,second);
		      		}
		      		else if (APPEND == 1){
		      			second_params = Append_prep(second_params, second);
				    }
					dup2(pipe_fd[0],0);
					close(pipe_fd[0]);
					close(pipe_fd[1]);
														/*Ctrl+s Ctrl+q  */
					wpid = waitpid(c_pid,&status,0); 	/* Waits child-process to finish if not background */
					if (wpid != c_pid){
						perror("-Bash: c_pid error");
					}
					while (!WIFSIGNALED(status) && !WIFEXITED(status));
					execvp(second_params[0],second_params);
					exit(EXIT_SUCCESS);

				}
}
/* 
STDIN (0) - Standard input (data fed into the program)
STDOUT (1) - Standard output (data printed by the program, defaults to the terminal)
STDERR (2) - Standard error (for error messages, also defaults to the terminal)

*/

/*
 *	Function : Execute_command
 *	--------------------------
 *	Dexetai mia entolh kai analoga ta flags kanei execute to command h' kalei to pipe to opoio
 *	sthn sunexeia epistrefei to comand wste na ginei execute apo thn sunartish.
 *	@param * comand  to eidos ths entolhs
 *	@param ** params  oloklhrh h entolh
 *	@param num_of_params to megethos tou pinaka **params
 *	@param PIPE flag param h opoia einai 1 otan exoume "|" sto input command
 *	@param INPUT flag param h opoia einai 1 otan exoume "<" sto input command
 *	@param OUTPUT flag param h opoia einai 1 otan exoume ">" sto input command
 *	@param APPEND flag param h opoia einai 1 otan exoume ">>" sto input command
 *	@return epistrefei enan double *  char array
 */

void Execute_command( char * command , char ** params , int num_of_params , 
					int PIPE_ONE , int INPUT, int OUTPUT, int APPEND ){
	int i=0,wpid,status;
	int background_process =0;
	char * path = "/bin/";
	pid_t process_id;
	char * path_command=malloc(sizeof(char)* MAX_CHAR);
	if (strcmp(params[num_of_params-1],"&")==0){ /* Flag if its a background process */
		background_process = 1;
		params[num_of_params-1] = NULL; /* delete the last param because its a "&" */
		num_of_params--;
	}

	while (params[i]!=NULL){
		//printf("Execute_command => params[i] : %s\n",params[i] );

		i++;
	}

							/* 		New Process			 */

	process_id=fork();
	if (process_id==0){
		/* Child */
		if( background_process == 1){
			execve(params[0],params,0);	 /*Background child process */
			exit(EXIT_SUCCESS);
		}
		if(background_process == 0) {
			if(PIPE_ONE==1){
      			Pipe_prep(params,num_of_params,INPUT,OUTPUT,APPEND);
      		}
			if((INPUT==1) && (OUTPUT ==1)){
      			params = Input_prep(params,num_of_params);
      			command = params[0];
      		}
      		else if(OUTPUT == 1) {
	      		params = Output_prep (params,i);
	      		command = params[0];
      		}
      		else if (APPEND == 1){
      			params = Append_prep(params, i);
      			command = params[0];

      		}
			execvp(command,params);
			exit(EXIT_SUCCESS);

		}
	}
	else if (process_id>0) {
		/* Parent*/
		if( background_process == 1){
			printf("Background Process : \n Name of process: %s \n",command);
		}else{
			wpid = waitpid(process_id,&status,0); /* Waits child-process to finish if not background */
			if (wpid != process_id){
				perror("-Bash: Waitpid error");
			}
			while (!WIFSIGNALED(status) && !WIFEXITED(status));
		}
	}else {
		perror("-Bash : Error in fork \n");
		exit(EXIT_FAILURE);
	}

}

void  INThandler(int sig)
{
     char  c;
     signal(sig, SIG_IGN);
     printf("\nDid you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
}

/*
 *	Function : Main
 *	--------------------------
 *	Tupwnei to prompt kai perimenei thn epomenh entolh
 *	@return 0
 */
int main(int argc, char const *argv[])
{
	clear();

	while(TRUE){
		Print_prompt();
		signal(SIGINT, INThandler);
		Read_command();

	}
	return 0;
}