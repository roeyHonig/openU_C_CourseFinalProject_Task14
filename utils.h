#define HASHSIZE 101 // size of hash tables for operations and symbols

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