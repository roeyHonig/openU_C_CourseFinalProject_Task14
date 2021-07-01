#include "commonHeaders.h"

#define maxNumberOfCharacters 81 // max number of characters in a single line of assembly language source code text
 
/*
 * Function:  initNewSourceCodeSentenceAndLinkTo 
 * --------------------
 * Constructor method to initialize sourceCodeSentence structure
 * 
 * previousSentence: the bufferNode which our new structure pointer previous field will point to.
 *
 * returns: pointer to struct sourceCodeSentence
 */
struct sourceCodeSentence *initNewSourceCodeSentenceAndLinkTo(struct sourceCodeSentence *previousSentence);

/*
 * Function:  freeSourceCodeSentenceLinkedListBeginingAt 
 * --------------------
 * Method to free all linked sourceCodeSentence struct forward from a specific firstSentence.
 * 
 * firstSentence: the initial sourceCodeSentence which will be free in memory.
 * If firstSentence->previous is NULL (The 1st element of the list) the entire list is freed in memory.
 */
void freeSourceCodeSentenceLinkedListBeginingAt(struct sourceCodeSentence *firstSentence);

/*
 * Function:  outputSourceCodeSentencesBeginingAt 
 * --------------------
 * Method to output the source code sentences 1 after the other following the first sentence.
 * 
 * firstSentence: the initial sourceCodeSentence which will be output.
 * If firstSentence->previous is NULL (The 1st element of the list) the entire list is outputted.
 */
void outputSourceCodeSentencesBeginingAt(struct sourceCodeSentence *firstSentence);

/*
 * Function:  readAssemblySourceCode 
 * --------------------
 * Method to create a linked list of sourceCodeSentence from a file of assembly language source code text. 
 * 
 * input: a pointer to a FILE contaning assembly language source code text. 
 * 
 * * returns: pointer to 1st sentence
 */
struct sourceCodeSentence *readAssemblySourceCode(FILE *input);

/* Declare the struct sourceCodeSentence which holds 1 line of assembly language source code text. */
struct sourceCodeSentence {
    char *currentTextLine;
    struct sourceCodeSentence *head;
    struct sourceCodeSentence *next;
    struct sourceCodeSentence *previous; 
};
