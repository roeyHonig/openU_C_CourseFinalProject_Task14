#define HASHSIZE 101 // size of hash tables for operations and symbols
typedef int boolean;
#define true 1
#define false 0

boolean errorsFound; // flag indicating if compilation errors were found. If so, no need to output the binary code for the corrput source code FILE.

/*
 * Function:  printLineBeginingAt 
 * --------------------
 * Method to print a line of text begining at char pointer up until the NUL character 
 * 
 * t: char pointer.
 */
void printLineBeginingAt(char *t);

/*
 * Function:  hash 
 * --------------------
 * This is a simple hash functino.  
 * 
 * key: An identifier to allow to get an element out of the hash table.  
 * hSize: The size of the hash table array.
 * 
 * returns: an index of the hash table array.
 */
unsigned int hash(char *key, unsigned int hSize);

/*
 * Function:  isOneOfTheAssemblyLanguageReservedWordsEqualsTo 
 * --------------------
 * This is a simple function to check if a string is one of the assembly language reserved words.  
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isOneOfTheAssemblyLanguageReservedWordsEqualsTo(char *str);