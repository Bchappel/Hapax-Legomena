#include <stdio.h>
#include <stdlib.h> // for malloc(), free()
#include <string.h>

#include "word_extractor.h"
#include "word_tally.h"

//A tool to hold the words we care about in an array, a/provide a method for processing the file

// forward declarations
static int updateWordInTallyList(LLNode **wordLists, int maxLen, char *word);


//Here we do all the work, processing the file and determining what to do for each word as we read it.  Once we are done reading, we can then examine our wordsToCheck list and see what their state is
int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen){
	
	struct WordExtractor *wordExtractor = NULL;
	char *aWord = NULL;
	// add any more variables that you need


	// create the extractor and open the file
	wordExtractor = weCreateExtractor(filename, maxLen);

	if (wordExtractor == NULL) {
		fprintf(stderr, "Failed creating extractor for '%s':\n", filename);
		return 0;
	}

	/** TODO: ensure that all of the word list heads are NULL */

	/*sets each of index of heads in wordLists to null*/
	for(int i = 0; i <= maxLen; i++){
		wordLists[i] = NULL;
	}	

	// read each word from the file using the WordExtractor,
	// and for each tally how often it has been used in
	// the appropriate list

	// In the loop, figure out whether we have seen this
	// word before, and do the appropriate thing if we have

	int totalWordCount = 0;

	while (weHasMoreWords(wordExtractor)) {
		aWord = weGetNextWord(wordExtractor);
		totalWordCount++;

		// figure out whether we have seen this word before,
		// and do the appropriate thing if we have
		updateWordInTallyList(wordLists, maxLen, aWord);
	}

	// is there anything else you need to do at the end of the loop?
	printf("Total word count %d\n", totalWordCount);

	// Close the file when we are done
	weDeleteExtractor(wordExtractor);

	return 1;
}


//TODO: Either update the tally in the list, or add it to the list

static int updateWordInTallyList(LLNode ** wordListHeads, int maxLen, char *word){

	int len = strlen(word);

	//find the word in the correct list to see if we have already seen it
	LLNode *temp = llLookupKey(wordListHeads[len], word);

	//use malloc to allocate memory to make a copy of thw word
	char *str = malloc(len + 1);
	strcpy(str, word);

	if (temp != NULL) {
    	//if the word is in the list, update the tally in the node and free memory
    	temp->value = temp->value + 1;
    	free(str);
	} else {
    	//If the word is not found in the list then add it to the list
    	wordListHeads[len] = llPrepend(wordListHeads[len], llNewNode(str, 1));
	}

	// Return success
	return 1;

}

