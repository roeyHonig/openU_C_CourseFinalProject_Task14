#include "commonHeaders.h"

/*
 * Function:  initNewCodeByteFrom32BitArrayInPositionAndLinkTo  
 * --------------------
 * Constructor method to initialize codeByte structure.
 * 
 * binaryRepresentation: Array of 32 integers representing a binary word.
 * position: integer between 1 and 4 to divide the word into byte size.
 * previousCodeByte: codeByte structure which will point to the new instance as his next pointer
 *
 * returns: pointer to struct codeByte
 */
struct codeByte *initNewCodeByteFrom32BitArrayInPositionAndLinkTo(int binaryRepresentation[], int position, struct codeByte *previousCodeByte);

/*
 * Function:  outputcodeBytesBeginingAt
 * --------------------
 * Method to output the binary representation of a codeByte, 1 after the other following the codeByte.
 * 
 * firstCodeByte: the initial codeByte which will be output.
 * If firstCodeByte->previous is NULL (The 1st element of the list) the entire list is outputted.
 */
void outputcodeBytesBeginingAt(struct codeByte *firstCodeByte);

/*
 * Function:  outputcodeBytesInHexadecimalBeginingAt
 * --------------------
 * Method to output the Hexadecimal representation of a codeByte, 1 after the other following the codeByte.
 * 
 * firstCodeByte: the initial codeByte which will be output.
 * If firstCodeByte->previous is NULL (The 1st element of the list) the entire list is outputted.
 */
void outputcodeBytesInHexadecimalBeginingAt(struct codeByte *firstCodeByte);

/* Declare the struct codeByte which represents a 1/4 part of the instruction statement in assembly language. */
struct codeByte {
    struct codeByte *head;
    struct codeByte *next;
    struct codeByte *previous; 
    int binary8BitCode[8];
};