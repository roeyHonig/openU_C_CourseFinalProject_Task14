#include "utils.h"
#include "commonHeaders.h"

#define numOfReservedWords 33

char *reservedWords[numOfReservedWords] = {"add", "sub", "and", "or", "nor", "move", "mvhi", "mvlo", "addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt", "bgt", "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call", "stop", ".dd", ".dw", ".db", ".asciz", ".entry", ".extern"};

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

boolean isRTypeKeywordsPresentInFollowingText(char *str) {
      for (int i = 0; i < 8; i++)
        if (strcmp(reservedWords[i], str) == 0) 
            return true;
    return false;
}

boolean isITypeKeywordsPresentInFollowingText(char *str) {
      for (int i = 8; i < 23; i++)
        if (strcmp(reservedWords[i], str) == 0) 
            return true;
    return false;
}

boolean isJTypeKeywordsPresentInFollowingText(char *str) {
    for (int i = 23; i < 27; i++)
        if (strcmp(reservedWords[i], str) == 0) 
            return true;
    return false;
}

boolean isDirectiveTypeKeywordsPresentInFollowingText(char *str) {
    for (int i = 27; i < numOfReservedWords; i++)
        if (strcmp(reservedWords[i], str) == 0) 
            return true;
    return false;
}

boolean isThereLabelInFollowingTextLine(char *str) {
    char *locationOfColon = strstr(str, ":");
    if (locationOfColon == NULL) 
        return false;
    else return true;    
}

boolean getLabelInto(char *label, char* str) {
    char *locationOfColon = strstr(str, ":");
    if (locationOfColon == NULL) {
        return false;
    }   
    // ':' is the 1st 
    if (locationOfColon == str) {
        return false;
    }  
    // too long label, more then 31 characters  
    if (locationOfColon - str > 31) {
        return false;
    }
    for (int i = 0; i < (locationOfColon - str); i++)
    {
        *(label + i) = *(str + i);
    }
    boolean areThereIllegalCharactersInTheLabel = false;
    for (int i = 0; i < (locationOfColon - str); i++)
    {
        if ((*(label + i) >= 'a' && *(label + i) <= 'z') || (*(label + i) >= 'A' && *(label + i) <= 'Z') || (*(label + i) >= '0' && *(label + i) <= '9')) {
            continue;
        } 
        areThereIllegalCharactersInTheLabel = true;
        break;
    }
    if (areThereIllegalCharactersInTheLabel) {
        return false;
    }
    boolean isFirstCharacterInTheLabelNotLetter = !((*label >= 'a' && *label <= 'z') || (*label >= 'A' && *label <= 'Z'));
    if (isFirstCharacterInTheLabelNotLetter) {
        return false;
    }
    return true;
}

char *initAnEmptyStringOfSize(int size) {
    char *pointer = malloc(sizeof(char) * (size + 1));
       for (int k = 0; k < 32; k++)
       {
           *(pointer + k) = '\0';
       }
    return pointer;
}

boolean isDigit(char *ch) {
    if (*ch >= '0' && *ch <= '9')
        return true;
    return false;    
}

boolean isCharacterEquals(char *ch, char eq) {
    if (*ch == eq)
        return true;
    return false;    
}

boolean isCharacterEqualsOrCondition(char *ch, char eq, char eq2) {
    if (isCharacterEquals(ch,eq) || isCharacterEquals(ch,eq2))
        return true;
    return false; 
}

boolean isCharacterNotEquals(char *ch, char eq) {
    return !isCharacterEquals(ch, eq);
}

boolean isCharacterNotEqualsOrCondition(char *ch, char eq, char eq2) {
    return !isCharacterEqualsOrCondition(ch, eq, eq2);
}