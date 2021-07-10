#include "utils.h"
#include "commonHeaders.h"

#define numOfReservedWords 33

char *reservedWords[numOfReservedWords] = {"add", "sub", "and", "or", "nor", "move", "mvhi", "mvlo", "addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt", "bgt", "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call", "stop", "dd", "dw", "db", "asciz", "entry", "extern"};

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

boolean isOneOfTheAssemblyLanguageReservedWordsEqualsTo(char *str) {
    for (int i = 0; i < numOfReservedWords; i++)
        if (strcmp(reservedWords[i], str) == 0) 
            return true;
    return false;
}

boolean isRTypeKeywordsPresentInFollowingTextLine(char *str) {
    // init array with location of the reserved word sub string inside the str string
    char *locationOfReservedWords[numOfReservedWords] = { NULL };
    // iterate over the reserved words array and find the 1st occurrence, if any, of the reserved word 
    for (int i = 0; i < numOfReservedWords; i++)
        locationOfReservedWords[i] = strstr(str, reservedWords[i]);
    // make sure, we did find at least 1 reserved word!!!
    boolean noReservedWordsFound = true;
    for (i = 0; i < numOfReservedWords; i++)
        if (locationOfReservedWords[i] != NULL) noReservedWordsFound = false;
    if (noReservedWordsFound)
        return false;
    // iterate over the location array to find the 1st reserved word 
    int min = 0;
    for (i = 1; i < numOfReservedWords; i++)
        if (locationOfReservedWords[min] > locationOfReservedWords[i]) 
            min = i;
    if (min < 8) 
        return true;
    else return false;    
}

boolean isITypeKeywordsPresentInFollowingTextLine(char *str) {
    // init array with location of the reserved word sub string inside the str string
    char *locationOfReservedWords[numOfReservedWords] = { NULL };
    // iterate over the reserved words array and find the 1st occurrence, if any, of the reserved word 
    for (int i = 0; i < numOfReservedWords; i++)
        locationOfReservedWords[i] = strstr(str, reservedWords[i]);
    // make sure, we did find at least 1 reserved word!!!
    boolean noReservedWordsFound = true;
    for (i = 0; i < numOfReservedWords; i++)
        if (locationOfReservedWords[i] != NULL) noReservedWordsFound = false;
    if (noReservedWordsFound)
        return false;
    // iterate over the location array to find the 1st reserved word 
    int min = 0;
    for (i = 1; i < numOfReservedWords; i++)
        if (locationOfReservedWords[min] > locationOfReservedWords[i]) 
            min = i;
    if (min > 7 && min < 23) 
        return true;
    else return false;    
}

boolean isJTypeKeywordsPresentInFollowingTextLine(char *str) {
    // init array with location of the reserved word sub string inside the str string
    char *locationOfReservedWords[numOfReservedWords] = { NULL };
    // iterate over the reserved words array and find the 1st occurrence, if any, of the reserved word 
    for (int i = 0; i < numOfReservedWords; i++)
        locationOfReservedWords[i] = strstr(str, reservedWords[i]);
    // make sure, we did find at least 1 reserved word!!!
    boolean noReservedWordsFound = true;
    for (i = 0; i < numOfReservedWords; i++)
        if (locationOfReservedWords[i] != NULL) noReservedWordsFound = false;
    if (noReservedWordsFound)
        return false;
    // iterate over the location array to find the 1st reserved word 
    int min = 0;
    for (i = 1; i < numOfReservedWords; i++)
        if (locationOfReservedWords[min] > locationOfReservedWords[i]) 
            min = i;
    if (min > 22 && min < 27) 
        return true;
    else return false;    
}

boolean isDirectiveTypeKeywordsPresentInFollowingTextLine(char *str) {
    // init array with location of the reserved word sub string inside the str string
    char *locationOfReservedWords[numOfReservedWords] = { NULL };
    // iterate over the reserved words array and find the 1st occurrence, if any, of the reserved word 
    for (int i = 0; i < numOfReservedWords; i++)
        locationOfReservedWords[i] = strstr(str, reservedWords[i]);
    // make sure, we did find at least 1 reserved word!!!
    boolean noReservedWordsFound = true;
    for (i = 0; i < numOfReservedWords; i++)
        if (locationOfReservedWords[i] != NULL) noReservedWordsFound = false;
    if (noReservedWordsFound)
        return false;
    // iterate over the location array to find the 1st reserved word 
    int min = 0;
    for (i = 1; i < numOfReservedWords; i++)
        if (locationOfReservedWords[min] > locationOfReservedWords[i]) 
            min = i;
    if (min > 26) 
        return true;
    else return false;    
}