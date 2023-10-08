#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "word_tally.h"


// function to be passed in to llFree to delete allocated keys

void deleteKey(LLNode *node, void *userdata){
	if (node->key != NULL) {
		free(node->key);
	}
}

// Delete the contents of all of the word lists This function assumes that both the nodes and the keys within the nodes have been allocated using malloc() and need to be freed.

void deleteWordLists(LLNode **wordListHeads, int maxLen){

	int i;

	for (i = 0; i <= maxLen; i++) {
		if (wordListHeads[i] != NULL) {
			llFree(wordListHeads[i], deleteKey, NULL);
			wordListHeads[i] = NULL;
		}
	}

}

// print out all of the data in a word list
int printData(char * filename, LLNode * wordListHeads[], int maxLen){
	
    LLNode * node;
    int i;
	//wordListHeads[24] = NULL; //set the head to NULL

    printf("All word count data from file '%s':\n", filename);

    for (i = 0; i <= maxLen; i++) {
        node = wordListHeads[i];
        if (node != NULL) {
            printf("Length %d:\n", i);
            while (node != NULL) {
                printf("    '%s' %d\n", node->key, node->value);
                node = node->next;
            }
        }
    }
    return 1;
} 



// TODO: print out only the hapax legomena in a word list
int printHapax(char *filename, LLNode *wordListHeads[], int maxLen, int hapaxLength){
	// Add your code here
	printf("Hapax legomena from file '%s'\n", filename);


	//for when hapaxLenght is -1 (default), 
	if (hapaxLength == -1) {

   		for (int i = 0; i < maxLen; i++) {
       		LLNode *temp = wordListHeads[i];
			//runs while head != NULL
        	while (temp != NULL) {
            	if (temp->value == 1) {
                	printf("%s\n", temp->key); //prints the words
            	}
            	temp = temp->next;
        	}
    	}
	}
	else{

		//words at specific length
    	LLNode *temp = wordListHeads[hapaxLength];

    	while (temp != NULL) {
        	if (temp->value == 1) {
            	printf("%s\n", temp->key); //prints the words (key)
        	}
        	temp = temp->next;
    	}
	}

	return 1;
}

// print out the command line help
void usage(){

	fprintf(stderr, "\n");
	fprintf(stderr, "Find and print the hapax legomena in one or more files.\n");
	fprintf(stderr, "A \"hapax legomenon\" is a word that occurs only once in the file\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "    hapax [<options>] <datafile> [ <datafile> ...]\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-d     : print out all data loaded before printing hapax legomena.\n");
	fprintf(stderr, "-h     : this help.  You are looking at it.\n");
	fprintf(stderr, "-l <N> : only print hapax legomena of length <N>.\n");
	fprintf(stderr, "       : If no -l option is given, all hapax legomena are printed.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Sample command line:\n");
	fprintf(stderr, "    hapax -l 5 smalldata.txt");
	fprintf(stderr, "\n");
	fprintf(stderr, "This example would print all words of length 5 that exist in the\n");
	fprintf(stderr, "file \"smalldata.txt\".\n");
	fprintf(stderr, "\n");

	//exit the program
	exit(1);
}


//Program mainline
//hapax legomena = words that only occurr once in a document
// define the maximum length of word we will look for, and by extension,
// the number of entries that must be in the array of word lists

#define	MAX_WORD_LEN 24

int main(int argc, char ** argv){
	
	/*variables*/
	int shouldPrintData = 0, didProcessing = 0, printHapaxLength = -1;
	int hapaxLen = -1;

	LLNode * wordListHeads[24]; //Array allocation


	//command line arguments for loop that checks for valid command line arguments.
	for (int i = 1; i < argc; i++) {

		if (argv[i][0] == '-') {
			
			if(argv[i][1] == 'd'){
				//printf("\t-d flag detected\n");
				shouldPrintData = 1;
				
			}
			else if(argv[i][1] == 'h'){
				//printf("\t-h flag detected\n");
				usage();
			}
			else if(argv[i][1] == 'l'){

				hapaxLen = atoi(argv[i + 1]);			
				i++;

				printHapaxLength = hapaxLen;

				if(printHapaxLength < 0){

					printf("invalid input\n");
					return 0;
				}

				//printf("\t-l value detected %d \n", hapaxLen);
			}
		
		}
		else{

			// Once you have set up your array of word lists, you
			// should be able to pass them into this function
			if (tallyWordsInFile(argv[i], wordListHeads, MAX_WORD_LEN) == 0) {
				fprintf(stderr, "Error: Processing '%s' failed -- exitting\n", argv[i]);
				return 1;
			}

			didProcessing = 1;

			printf("Tally loaded\n");

			/*
			* conditionally print out all the words loaded, based
			* on the command line option
			*/

			if (shouldPrintData) {
				printf("Data Should be Printed (-d flag found)\n");
				// this should also work once you have allocated the array of lists properly
				printData(argv[i], wordListHeads, MAX_WORD_LEN);

			}

			//print out all the hapax legomena that we have found
			printHapax(argv[i], wordListHeads, MAX_WORD_LEN, hapaxLen);

			// clean up any memory that we have allocated in this loop
			deleteWordLists(wordListHeads, 24);

		}
	}

	if (!didProcessing) {
		fprintf(stderr, "No data processed -- provide the name of" " a file on the command line\n");
		usage();
		return 1;
	}

	//clean up any remaining memory that we have allocated
	deleteWordLists(wordListHeads, 24);

	return 0;
}

