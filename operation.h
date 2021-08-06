/* Use this wrapper #ifndef encapsulation method to prevent duplicate redefinition errors of operation due to multiple files importing this header  */
#ifndef FILE_OPERATION_SEEN
#define FILE_OPERATION_SEEN
/* --------------------------------------------
 code goes here
 --------------------------------------------
*/
#include "commonHeaders.h"

/*
 * Function:  initAnOperation 
 * --------------------
 * Constructor method to initialize operation structure
 * 
 * name: operation name .his is also the key by which we get operation structure from the OperationsHashTable.
 * type: operation type.
 * funct: operation funct in base 10.
 * code: operation opcode in base 10.
 *
 * returns: pointer to struct operation
 */
struct operation *initAnOperation(char *name, char type, int funct, int code);

/*
 * Function:  setOperation 
 * --------------------
 * Method to set an operation inside the OperationsHashTable.
 * 
 * op: operation structure to store at the OperationsHashTable.
 */
void setOperation(struct operation *op);

/*
 * Function:  initOperationsHashTable 
 * --------------------
 * Method to init the assembly language operations symbols table - OperationsHashTable.
 * 
 */
void initOperationsHashTable();

/*
 * Function:  getOperationWithOpName 
 * --------------------
 * Getter method to retrive an operation structure out of the OperationsHashTable, based on the name of the operation 
 * 
 * name: operation name .
 *
 * returns: pointer to struct operation or NULL if an operation with the desired key (name) doesn't exist 
 */
struct operation *getOperationWithOpName(char *name);

/*
 * Function:  outputOperationsHashTable 
 * --------------------
 * Method to print a short description of all the operations inside the OperationsHashTable. 
 * 
 */
void outputOperationsHashTable();

/* Declare the struct operation which holds 1 record from the Assembly Language Operations Table and is part of a linked List. */
struct operation {
    struct operation *next;
    struct operation *previous; 
    char *opName; /* Example: "Add" */
    char opType; /* Example: 'R' */
    int base10Funct; /* Example: 1 */
    int base10opCode; /* Example: 0 */
};
/* --------------------------------------------
 code ends here
 --------------------------------------------
*/
#endif 



