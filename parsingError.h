#include "commonHeaders.h"
#define maxNumberOfCharacters 81 

/* a comment in the assembly language source code is not technically an error but we use it to flag the assembler to ignore this line */
enum parsingError {noErrorsFound = 0, lineTooLong, useOfReservedWord, comment, illegalUseOfSemiColon, notRecognizableAssemblyLanguageStatement, badLabelFormat, wrongRegisterNumber, immediateOverflow, badImmediateFormat, badDirectiveStatementParameterFormat, noParametersInDirectiveStatement, parameterOverflow, badDirectiveStatementAscizFormat, badDirectiveStatementLabelFormat, duplicateLabel, missingLabel};
 

/* 
 * Function:  printErrorDescriptionFor 
 * --------------------
 * Method to print a short description of a parsing error.
 * 
 * lineNumber: the line# on which the error ocurred.
 * error: a pasing error.
 */
void printErrorDescriptionFor(int lineNumber, enum parsingError error);
