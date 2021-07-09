#define maxNumberOfCharacters 81 // TODO: bring back to 81 max number of characters in a single line of assembly language source code text

enum parsingError {noErrorsFound = 0, lineTooLong, useOfReservedWord};

/* 
 * Function:  printErrorDescriptionFor 
 * --------------------
 * Method to print a short description of a parsing error.
 * 
 * lineNumber: the line# on which the error ocurred.
 * error: a pasing error.
 */
void printErrorDescriptionFor(int lineNumber, enum parsingError error);
