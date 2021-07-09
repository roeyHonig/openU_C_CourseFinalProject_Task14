#include "commonHeaders.h"
enum labelLocationInSourceCode {directiveStatement = 0, instructionStatement};

/* 
 * Function:  initSymbol 
 * --------------------
 * Constructor method to initialize symbol structure
 * 
 * nameOfSymbol: Label name .This is also the key by which we get symbol structure from the symbolsHashTable.
 * locationOfSymbol: enum describing the location type in which the label appeared.  
 * valueOfSymbol: The value of the symbol. An int representing a certain value of the data counter \ instruction counter
 * code: operation opcode in base 10.
 *
 * returns: pointer to struct symbol
 */
struct symbol *initSymbol(char *nameOfSymbol, enum labelLocationInSourceCode locationOfSymbol, int valueOfSymbol);

/* 
 * Function:  setSymbol 
 * --------------------
 * Method to set an symbol inside the symbolsHashTable.
 * 
 * sm: symbol structure to store at the symbolsHashTable.
 */
void setSymbol(struct symbol *sm);

/* 
 * Function:  getSymbolWithName 
 * --------------------
 * Getter method to retrive a symbol structure out of the symbolsHashTable, based on the name of the symbol 
 * 
 * symbolName: symbol name.
 *
 * returns: pointer to struct symbol or NULL if a symbol with the desired key (name) doesn't exist. 
 */
struct symbol *getSymbolWithName(char *symbolName);

/* 
 * Function:  outputSymbolsHashTable 
 * --------------------
 * Method to print a short description of all the symbols inside the symbolsHashTable. 
 */
void outputSymbolsHashTable();

/* 
 * Function:  nullifySymbolsHashTable 
 * --------------------
 * Method to reset the symbolsHashTable and delete any values in it. This is important when processing multiple assembly language source code files.
 */
void nullifySymbolsHashTable();


/* Declare the struct symbol which holds 1 record of a symbol. such as a label and is part of a linked List. */
struct symbol {
    struct symbol *next;
    struct symbol *previous; 
    char *name; // Example: "MAIN"
    enum labelLocationInSourceCode location; // for example - instructionStatement
    int value;  // Based on the location, the value will be the data counter or instruction counter.
};