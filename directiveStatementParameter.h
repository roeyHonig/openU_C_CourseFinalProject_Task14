#include "commonHeaders.h"

/*
 * Function:  initNewDirectiveStatementParameterAndLinkTo 
 * --------------------
 * Constructor method to initialize directiveStatementParameter structure
 * 
 * previousParameter: the bufferNode which our new structure pointer previous field will point to.
 *
 * returns: pointer to struct directiveStatementParameter
 */
struct directiveStatementParameter *initNewDirectiveStatementParameterWithNumberByteSizeAndLinkTo(int num, int bSize, struct directiveStatementParameter *previousParameter);

/* Declare the struct directiveStatementParameter which holds 1 signed integer and is used to instruct the assembler how much data should be reserved and what is the data itself */
struct directiveStatementParameter {
    int number;
    int byteSize; /* 1 byte, 2 bytes (half word) or 4 byte (word) */
    struct directiveStatementParameter *head;
    struct directiveStatementParameter *next;
    struct directiveStatementParameter *previous; 
};