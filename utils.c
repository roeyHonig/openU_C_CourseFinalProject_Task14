#include "utils.h"
#include "commonHeaders.h"
#include "parsingError.h"
#define numOfReservedWords 33

boolean parseRegistersForRTypeArithmetic(char *scTextLine, char *name, int *firstRegister, int *secondRegister, int *thirdRegister);
boolean parseRegistersForRTypeCopy(char *scTextLine, char *name, int *firstRegister, int *secondRegister, int *thirdRegister);

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
    for (i = 0; i < (locationOfColon - str); i++)
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

boolean isNotDigit(char *ch) {
    return !isDigit(ch);
}

boolean isCharacterEqualsTrippleOrCondition(char *ch, char eq, char eq2, char eq3) {
    return (isCharacterEqualsOrCondition(ch, eq, eq2) || isCharacterEquals(ch, eq3));
}

boolean isCharacterNotEqualsTrippleOrCondition(char *ch, char eq, char eq2, char eq3) {
    return !isCharacterEqualsTrippleOrCondition(ch, eq, eq2, eq3);
}

boolean isThereOutOfBoundsRegisterNumberInOneOfTheFollowing(int reg1, int reg2, int reg3) {
    return !((reg1 >=0 && reg1 <= 31) && (reg2 >=0 && reg2 <= 31) && (reg3 >=0 && reg3 <= 31));
}

boolean parseRegistersForRType(char *scTextLine, char *name, int *firstRegister, int *secondRegister, int *thirdRegister) {
    if (strcmp(name, "move") == 0 || strcmp(name, "mvhi") == 0 || strcmp(name, "mvlo") == 0) {
        return parseRegistersForRTypeCopy(scTextLine, name, firstRegister, secondRegister, thirdRegister); 
    } else return parseRegistersForRTypeArithmetic(scTextLine, name, firstRegister, secondRegister, thirdRegister);
           
}

boolean parseRegistersForRTypeArithmetic(char *scTextLine, char *name, int *firstRegister, int *secondRegister, int *thirdRegister) {
           // get 1st register
           // scsCh === source code sentence character 
           char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, '$')) {
               return false;
           }
           scsCh++;
           char firstRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               firstRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return false;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               firstRegisterString[1] = *scsCh;
               scsCh++;
           } else if (isCharacterEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               // No need to do anything
           } else {
               return false;
           }
           // a third digit or any other character except these is not allowed!
           if (isCharacterNotEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               return false;
           }

           // get 2nd register
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, ',')) {
               return false;
           }
           scsCh++;
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, '$')) {
               return false;
           }
           scsCh++;
           char secondRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               secondRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return false;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               secondRegisterString[1] = *scsCh;
               scsCh++;
           } else if (isCharacterEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               // No need to do anything
           } else {
               return false;
           }
           // a third digit or any other character except these is not allowed!
           if (isCharacterNotEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               return false;
           }

           // get 3nd register
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, ',')) {
               return false;
           }
           scsCh++;
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, '$')) {
               return false;
           }
           scsCh++;
           char thirdRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               thirdRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return false;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               thirdRegisterString[1] = *scsCh;
               scsCh++;
           } else if (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) {
               // No need to do anything
           } else if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                // No need to do anything
           } else {
               return false;
           }
           // a third digit or any other character except these is not allowed!
           if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
               return false;
           }
           
           while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
           {
               if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t')) {
                    return false;
               }
               scsCh++;
           }
           
          *firstRegister = atoi(firstRegisterString);
          *secondRegister = atoi(secondRegisterString);
          *thirdRegister = atoi(thirdRegisterString);
          if (isThereOutOfBoundsRegisterNumberInOneOfTheFollowing(*firstRegister, *secondRegister, *thirdRegister)) {
              return false;
          }
          return true;
}

boolean parseRegistersForRTypeCopy(char *scTextLine, char *name, int *firstRegister, int *secondRegister, int *thirdRegister) {
           // get 1st register
           // scsCh === source code sentence character 
           char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, '$')) {
               return false;
           }
           scsCh++;
           char firstRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               firstRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return false;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               firstRegisterString[1] = *scsCh;
               scsCh++;
           } else if (isCharacterEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               // No need to do anything
           } else {
               return false;
           }
           // a third digit or any other character except these is not allowed!
           if (isCharacterNotEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               return false;
           }

           // get 2nd register
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, ',')) {
               return false;
           }
           scsCh++;
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, '$')) {
               return false;
           }
           scsCh++;
           char secondRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               secondRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return false;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               secondRegisterString[1] = *scsCh;
               scsCh++;
           } else if (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) {
               // No need to do anything
           } else if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                // No need to do anything
           } else {
               return false;
           }
           // a third digit or any other character except these is not allowed!
           if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
               return false;
           }
           
           while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
           {
               if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t')) {
                    return false;
               }
               scsCh++;
           }
           
          *firstRegister = atoi(firstRegisterString);
          *secondRegister = atoi(secondRegisterString);
          *thirdRegister = 0;
          if (isThereOutOfBoundsRegisterNumberInOneOfTheFollowing(*firstRegister, *secondRegister, *thirdRegister)) {
              return false;
          }
          return true;
}

int parseRegistersAndImmediateForIType(char *scTextLine, char *name, int *firstRegister, int *secondRegister, short *immed) {
    if (strcmp(name, "addi") == 0 || strcmp(name, "subi") == 0 || strcmp(name, "andi") == 0 || strcmp(name, "ori") == 0 || strcmp(name, "nori") == 0) {
        return parseRegistersForITypeArithmetic(scTextLine, name, firstRegister, secondRegister, immed); 
    } else if (strcmp(name, "beq") == 0 || strcmp(name, "bne") == 0 || strcmp(name, "blt") == 0 || strcmp(name, "bgt") == 0) {
        return immediateOverflow;

    } else return immediateOverflow;

}

int parseRegistersForITypeArithmetic(char *scTextLine, char *name, int *firstRegister, int *secondRegister, short *immed) {
           // get 1st register
           // scsCh === source code sentence character 
           char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, '$')) {
               return wrongRegisterNumber;
           }
           scsCh++;
           char firstRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               firstRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return wrongRegisterNumber;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               firstRegisterString[1] = *scsCh;
               scsCh++;
           } else if (isCharacterEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               // No need to do anything
           } else {
               return wrongRegisterNumber;
           }
           // a third digit or any other character except these is not allowed!
           if (isCharacterNotEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               return wrongRegisterNumber;
           }

           // get the immediate 
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, ',')) {
               return wrongRegisterNumber;
           }
           scsCh++;
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEqualsOrCondition(scsCh, '-', '+')) {
               return badImmediateFormat;
           }
           int immediateStringLength = 0;
           scsCh++;
           immediateStringLength++;
           if (isNotDigit(scsCh)) {
               return badImmediateFormat;
           }
           while (isDigit(scsCh)) {
               scsCh++; 
               immediateStringLength++;
           }
           // Any other character except these is not allowed!
           if (isCharacterNotEqualsTrippleOrCondition(scsCh, ' ', '\t', ',')) {
               return badImmediateFormat;
           }
           char immeidateAsString[/*immediateStringLength + 1*/100] = {0};
           for (int j = 0; j < /*immediateStringLength*/99; j++)
           {
               if (j >= immediateStringLength) 
                    break;
               immeidateAsString[j] = *(scsCh-immediateStringLength+j);
           }
           
           // get 3nd register
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, ',')) {
               return wrongRegisterNumber;
           }
           scsCh++;
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, '$')) {
               return wrongRegisterNumber;
           }
           scsCh++;
           char thirdRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               thirdRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return wrongRegisterNumber;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               thirdRegisterString[1] = *scsCh;
               scsCh++;
           } else if (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) {
               // No need to do anything
           } else if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                // No need to do anything
           } else {
               return wrongRegisterNumber;
           }
           // a third digit or any other character except these is not allowed!
           if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
               return wrongRegisterNumber;
           }
           
           while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
           {
               if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t')) {
                    return wrongRegisterNumber;
               }
               scsCh++;
           }
           
          *firstRegister = atoi(firstRegisterString);
          int immediateAsInt = atoi(immeidateAsString);
          *secondRegister = atoi(thirdRegisterString);
          if (isThereOutOfBoundsRegisterNumberInOneOfTheFollowing(*firstRegister, *secondRegister, 1)) {
              return wrongRegisterNumber;
          }
          if (immediateAsInt >= INT16_MIN && immediateAsInt <= INT16_MAX) 
                *immed = (short)immediateAsInt;
          else return immediateOverflow;

          return noErrorsFound;
}