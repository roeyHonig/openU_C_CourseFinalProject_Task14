#include "commonHeaders.h"
#include "parsingError.h"
#include "type_R_Instruction.h"
#include "type_I_Instruction.h"
#include "type_J_Instruction.h"
#include "directiveStatement.h"

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
 * Method to output the source code sentences, 1 after the other following the first sentence.
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

/* 
 * Function:  outputSourceCodeSentencesErrorsBeginingAt 
 * --------------------
 * Method to output the simple description of the error in each source code sentences, 1 after the other.
 * 
 * firstSentence: the initial sourceCodeSentence which will be checked (and output) for error.
 * If firstSentence->previous is NULL (The 1st element of the list) the entire list is outputted.
 */
void outputSourceCodeSentencesErrorsBeginingAt(struct sourceCodeSentence *firstSentence);

/* 
 * Function:  parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter 
 * --------------------
 * Method to parse the source code sentences, 1 after the other following the first sentence.
 * 
 * firstSentence: the initial sourceCodeSentence which will be output.
 * If firstSentence->previous is NULL (The 1st element of the list) the entire list is parsed.
 * instructionCounter: integer representing the 1st available space in memory for the code output
 * pass: integer representing which pass of parsing the source code this is
 */
void parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(struct sourceCodeSentence *firstSentence, int instructionCounter, int pass);

/* 
 * Function:  getCurrentInstructionCounter 
 * --------------------
 * Getter method to get the current instructions counter.
 * 
 * retruns: integer representing the current instructions counter 
 */
int getCurrentInstructionCounter();

/* 
 * Function:  errorsFoundDuringCompilation 
 * --------------------
 * Method to iterate over the linked list of sentences to find if any errors were reported.
 * 
 * * firstSentence: the initial sourceCodeSentence which will be examine.
 * 
 * retruns: integer 1 for true and 0 for false
 */
int errorsFoundDuringCompilation(struct sourceCodeSentence *firstSentence);

/* 
 * Function:  outputCodeAndDataImageBeginingAtMemorryAddress 
 * --------------------
 * Method to output to the screen the content of the object file.
 * 
 * memAddress: the initial memory address of the code and data image.
 * 
 */
void outputCodeAndDataImageBeginingAtMemorryAddress(int memAddress);

/* 
 * Function:  outputCodeAndDataImageBeginingAtMemorryAddress 
 * --------------------
 * Method to output the object file.
 * 
 * memAddress: the initial memory address of the code and data image.
 * objectFileName: String representing the object file name, such as "example.ob"
 * 
 */
void outputCodeAndDataImageBeginingAtMemorryAddressIntoAnObjectFileName(int memAddress, char *objectFileName);

/* Declare the struct sourceCodeSentence which holds 1 line of assembly language source code text. */
struct sourceCodeSentence {
    char *currentTextLine;
    int currentTextLineNumber;
    struct sourceCodeSentence *head;
    struct sourceCodeSentence *next;
    struct sourceCodeSentence *previous; 
    enum parsingError error;
    struct type_R_Instruction *rInstruction;
    struct type_I_Instruction *iInstruction;
    struct type_J_Instruction *jInstruction;
    struct directiveStatement *dStatement;
};
