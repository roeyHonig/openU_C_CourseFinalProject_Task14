#include "utils.h"
#include "commonHeaders.h"

void printLineBeginingAt(char *t) {
   // Base case
   if (*t == '\0') 
       return;
   printf("%c", *t);
   printLineBeginingAt(++t);
}

unsigned int hash(char *key, unsigned int hSize) {
    unsigned hashval;
    for (hashval = 0; *key != '\0'; key++)
        hashval += *key;
    return hashval % hSize;
    
    
}