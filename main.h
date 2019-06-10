/*
 * Author:  Atzamis Iosif 
 * Purpose: C Shell Implementation
 * E-mail: csd3094@csd.uoc.gr
 * Language:  C
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>


/*
 *	Function : Print_prompt
 *	--------------------------
 *	Tupwnei to prompt  
 *	 
 */
void Print_prompt();
/*
 *	Function : Read_command
 *	--------------------------
 *	Dexetai eisodo apo to plhktrologio kai sthn sunexeia parsarei to input
 *	gia na dei ti uparxei kai bazei flags analoga me to input tou xrhsth
 *
 *	 
 */
void Read_command();

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

void Execute_command( char * command , char ** params , int num_of_params, 
						int PIPE_ONE,
						int INPUT,
						int OUTPUT, 
						int APPEND 
					);
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
void Pipe_prep(	char ** params, int num_of_params, 
				int INPUT, 
				int OUTPUT, 
				int APPEND 
			);
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
char ** Input_prep(char **params, int num_of_params);
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
char ** Output_prep(char ** params , int num_of_params);
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
char ** Append_prep(char ** params , int num_of_params);



void  INThandler(int sig);
