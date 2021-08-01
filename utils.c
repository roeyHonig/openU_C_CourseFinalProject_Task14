#include "utils.h"
#include "commonHeaders.h"
#include "parsingError.h"
#define numOfReservedWords 33

boolean parseRegistersForRTypeArithmetic(char *scTextLine, char *name, int *firstRegister, int *secondRegister, int *thirdRegister);
boolean parseRegistersForRTypeCopy(char *scTextLine, char *name, int *firstRegister, int *secondRegister, int *thirdRegister);
int parseParametersForDirectiveStatementOfTypeD(char *scTextLine, char *name, int *firstPa, int *indexOfParametersArray, int *byteSizeOfEachParameter);
int parseParametersForDirectiveStatementOfTypeAnsii(char *scTextLine, char *name, char *str);
int parseParametersForDirectiveStatementOfTypeEnteryOrExtern(char *scTextLine, char *name, char *label);

char *reservedWords[numOfReservedWords] = {"add", "sub", "and", "or", "nor", "move", "mvhi", "mvlo", "addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt", "bgt", "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call", "stop", ".dh", ".dw", ".db", ".asciz", ".entry", ".extern"};

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

boolean isLabelSupportedForDirectiveTypeKeywords(char *str) {
    if (strcmp(reservedWords[27], str) == 0) 
        return true;
    if (strcmp(reservedWords[28], str) == 0) 
        return true;
    if (strcmp(reservedWords[29], str) == 0) 
        return true;
    if (strcmp(reservedWords[30], str) == 0) 
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
       for (int k = 0; k < size + 1; k++)
       {
           *(pointer + k) = '\0';
       }
    return pointer;
}

char *initAnEmptyStringOfSizeAndFillWithChacter(int size, char ch) {
    char *pointer = malloc(sizeof(char) * (size + 1));
       for (int k = 0; k < size; k++)
       {
           *(pointer + k) = ch;
       }
       *(pointer + size) = '\0';
    return pointer;
}

boolean isDigit(char *ch) {
    if (*ch >= '0' && *ch <= '9')
        return true;
    return false;    
}

boolean isAlphabeticCharacter(char *ch) {
    if ((*ch >= 'a' && *ch <= 'z') || (*ch >= 'A' && *ch <= 'Z'))
        return true;
    return false;    

}

boolean isNotAlphabeticCharacter(char *ch) {
    return !isAlphabeticCharacter(ch);
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

int parseRegistersAndImmediateForIType(char *scTextLine, char *name, int *firstRegister, int *secondRegister, short *immed, char* labelWithinTheInstruction) {
    if (strcmp(name, "addi") == 0 || strcmp(name, "subi") == 0 || strcmp(name, "andi") == 0 || strcmp(name, "ori") == 0 || strcmp(name, "nori") == 0) {
        return parseRegistersForITypeArithmetic(scTextLine, name, firstRegister, secondRegister, immed); 
    } else if (strcmp(name, "beq") == 0 || strcmp(name, "bne") == 0 || strcmp(name, "blt") == 0 || strcmp(name, "bgt") == 0) {
        return parseRegistersForITypeBranching(scTextLine, name, firstRegister, secondRegister, immed, labelWithinTheInstruction);
    } else return parseRegistersForITypeArithmetic(scTextLine, name, firstRegister, secondRegister, immed);

}
// This is also valid for I Type loading and saving in memory
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
           if (isCharacterNotEqualsOrCondition(scsCh, '-', '+') && isNotDigit(scsCh)) {
               return badImmediateFormat;
           }
           int immediateStringLength = 0;
           if (isCharacterEqualsOrCondition(scsCh, '-', '+')) {
                scsCh++;
                immediateStringLength++;
           }
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

int parseRegistersForITypeBranching(char *scTextLine, char *name, int *firstRegister, int *secondRegister, short *immed, char *labelWithinTheInstruction) {
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

           // get 2nd register
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
           char secondRegisterString[3] = {0};
           // did we reached 1st digit?
           if (isDigit(scsCh)) {
               secondRegisterString[0] = *scsCh;
               scsCh++;
           } else {
               return wrongRegisterNumber;
           }
           // did we reached 2nd digit?
           if (isDigit(scsCh)) {
               secondRegisterString[1] = *scsCh;
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

           // get The label
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isCharacterNotEquals(scsCh, ',')) {
               return wrongRegisterNumber;
           }
           scsCh++;
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isNotAlphabeticCharacter(scsCh)) {
               return badLabelFormat;
           }
           int labelIndex = 0;
           while (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
           {
               if (isNotDigit(scsCh) && isNotAlphabeticCharacter(scsCh)) {
                   // label can't have characters except digits and letters;
                   return badLabelFormat;
               }
               if (*(labelWithinTheInstruction+labelIndex) == '\0') {
                   // label in the instruction is too long
                   return badLabelFormat;
               }
               *(labelWithinTheInstruction+labelIndex) = *scsCh;
               scsCh++;
               labelIndex++;
           }
           // fill in the rest of the label array with '\0'
           while (*(labelWithinTheInstruction+labelIndex) != '\0')
           {
               *(labelWithinTheInstruction+labelIndex) = '\0';
               labelIndex++;
           }

           // Any other character except these is not allowed!
           if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
               return badLabelFormat;
           }
           scsCh++;
           while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
           {
               if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t')) {
                    return badLabelFormat;
               }
               scsCh++;
           }
           
          *firstRegister = atoi(firstRegisterString);
          *secondRegister = atoi(secondRegisterString);
          if (isThereOutOfBoundsRegisterNumberInOneOfTheFollowing(*firstRegister, *secondRegister, 1)) {
              return wrongRegisterNumber;
          }
          return noErrorsFound;

}

void convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(int n, int *a, int size) {
    for(int i=0;n>0, i < size;i++)    
    {    
        *(a+i) = n%2;    
        n=n/2;    
    }    
    return;  
}

void convertUnsignedBinaryNumberArrayOfBitSizeIntoSigned(int *a, int size, int *b) {
    for(int i=0;i < size;i++)    
    {    
        b[i] = a[i];    
    } 
    b[size] = 0;   
    return;  
}

void negateSignedBitArrayOfSize(int *a, int size) {
    for (int i = 0; i < size; i++)
    {
        if (a[i] == 1)
            a[i] = 0;
        else a[i] = 1; 
    }
    for (int j = 0; j < size; j++)
    {
        if (a[j] == 0) {
            a[j] = 1;
            break;
        } else a[j] = 0; 
    }
    
}

int parseRegistersOrLabelForJType(char *scTextLine, char *name, int *registerFlag, int *address, char* labelWithinTheInstruction) {
           char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) {               
               scsCh++; 
           }
           if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                   if (strcmp(name, "stop") == 0) {
                       // stop instruction is simple to code
                       *registerFlag = 0;
                       *address = 0;
                        return noErrorsFound;
                   } else {
                       // only stop instruction should have no arguments
                       return notRecognizableAssemblyLanguageStatement;
                   }
               }
           if (strcmp(name, "stop") == 0) {
               return notRecognizableAssemblyLanguageStatement;
           } else if (isCharacterEquals(scsCh, '$')) {
                return parseRegistersForJType(scTextLine, name, registerFlag, address, labelWithinTheInstruction);
            } else {
                return parseLabelForJType(scTextLine, name, registerFlag, address, labelWithinTheInstruction);
            }
}

int parseRegistersForJType(char *scTextLine, char *name, int *registerFlag, int *address, char* labelWithinTheInstruction) {
            if (strcmp(name, "jmp") != 0) {
                // only jmp instruction can use register
                return notRecognizableAssemblyLanguageStatement;
            }
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

          *address = atoi(firstRegisterString);
          if (isThereOutOfBoundsRegisterNumberInOneOfTheFollowing(*address, 1, 1)) {
              return wrongRegisterNumber;
          }
          *registerFlag = 1;
          return noErrorsFound;
}

int parseLabelForJType(char *scTextLine, char *name, int *registerFlag, int *address, char* labelWithinTheInstruction) {
           // scsCh === source code sentence character 
           char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
           // get The label
           while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
                scsCh++; 
           if (isNotAlphabeticCharacter(scsCh)) {
               return badLabelFormat;
           }
           int labelIndex = 0;
           while (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
           {
               if (isNotDigit(scsCh) && isNotAlphabeticCharacter(scsCh)) {
                   // label can't have characters except digits and letters;
                   return badLabelFormat;
               }
               if (*(labelWithinTheInstruction+labelIndex) == '\0') {
                   // label in the instruction is too long
                   return badLabelFormat;
               }
               *(labelWithinTheInstruction+labelIndex) = *scsCh;
               scsCh++;
               labelIndex++;
           }
           // fill in the rest of the label array with '\0'
           while (*(labelWithinTheInstruction+labelIndex) != '\0')
           {
               *(labelWithinTheInstruction+labelIndex) = '\0';
               labelIndex++;
           }

           // Any other character except these is not allowed!
           if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
               return badLabelFormat;
           }
           scsCh++;
           while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
           {
               if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t')) {
                    return badLabelFormat;
               }
               scsCh++;
           }
           
          *registerFlag = 0;
          return noErrorsFound;
            
}

int parseParametersOrAsciiStringOrLabelForDirectiveStatement(char *scTextLine, char *name, int *firstPa, int *indexOfParametersArray, int *byteSizeOfEachParameter, char *str, char *label) {
    if (strcmp(name, ".db") == 0 || strcmp(name, ".dh") == 0 || strcmp(name, ".dw") == 0) {
        return parseParametersForDirectiveStatementOfTypeD(scTextLine, name, firstPa, indexOfParametersArray, byteSizeOfEachParameter); 
    } else if (strcmp(name, ".asciz") == 0) {
        return parseParametersForDirectiveStatementOfTypeAnsii(scTextLine, name, str);
    } else return parseParametersForDirectiveStatementOfTypeEnteryOrExtern(scTextLine, name, label);

}

int parseParametersForDirectiveStatementOfTypeD(char *scTextLine, char *name, int *firstPa, int *indexOfParametersArray, int *byteSizeOfEachParameter) {
    if (strcmp(name, ".db") == 0) {
        *byteSizeOfEachParameter = 1;
    } else if (strcmp(name, ".dh") == 0) {
        *byteSizeOfEachParameter = 2;
    } else {
        *byteSizeOfEachParameter = 4;
    }
    // scsCh === source code sentence character 
    char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
    if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                return noParametersInDirectiveStatement;
    }
    boolean moreParametersToExtract = true;
    char *parametersAsString[maxNumberOfCharacters];
    int extractingParmeterLoopIndex = -1;

    do
    {
        extractingParmeterLoopIndex++;
        while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) {
            scsCh++; 
            if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                return noParametersInDirectiveStatement;
            }
        }
        if (extractingParmeterLoopIndex > 0) {
            // 1st parameter don't need to have a ',' before it
            if (isCharacterNotEquals(scsCh, ',')) {
                return badDirectiveStatementParameterFormat;
            }
            scsCh++;
        }        
        while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) 
            scsCh++; 
        if (isCharacterNotEqualsOrCondition(scsCh, '-', '+') && isNotDigit(scsCh)) {
            return badDirectiveStatementParameterFormat;
        }
        int immediateStringLength = 0;
        if (isCharacterEqualsOrCondition(scsCh, '-', '+')) {
            scsCh++;
            immediateStringLength++;
        }
        if (isNotDigit(scsCh)) {
            return badDirectiveStatementParameterFormat;
        }
        while (isDigit(scsCh)) {
            scsCh++; 
            immediateStringLength++;
        }
        // Any other character except these is not allowed!
        if (isCharacterNotEqualsTrippleOrCondition(scsCh, ' ', '\t', ',') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
            return badDirectiveStatementParameterFormat;
        }
        char *currentParameterAsString = initAnEmptyStringOfSizeAndFillWithChacter(maxNumberOfCharacters, '\0');
        for (int j = 0; j < maxNumberOfCharacters; j++)
        {
            if (j >= immediateStringLength) 
                break;
            *(currentParameterAsString+j) = *(scsCh-immediateStringLength+j);
        }
        parametersAsString[extractingParmeterLoopIndex] = currentParameterAsString;
        // check if this was the last parmeter
        char *tmp = scsCh;
        boolean seemsWeHave1MoreParameterToExtract = false;
        while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
        {
            if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t')) {
                if (isCharacterEquals(scsCh, ',')) {
                    // seems we have 1 more parameter
                    scsCh = tmp;
                    //printf("we got here");
                    //printf("before %c and current %c", *(scsCh-1), *scsCh);
                    seemsWeHave1MoreParameterToExtract = true;
                    break;
                }
                return badDirectiveStatementParameterFormat;
            }
            scsCh++;
        }
        moreParametersToExtract = seemsWeHave1MoreParameterToExtract;
    } while (moreParametersToExtract);

    for (int k = 0; k <= extractingParmeterLoopIndex; k++)
    {
        *(firstPa+k) = atoi(parametersAsString[k]);
        *indexOfParametersArray = k;
        int numberOfBits = 8 * (*byteSizeOfEachParameter);
        int minNum = (pow(2, numberOfBits) / 2) * -1;
        int maxNum = ((pow(2, numberOfBits) / 2)-1);
        if ((*(firstPa+k)) <  minNum || (*(firstPa+k)) >  maxNum) {
            return parameterOverflow;

        }
    }
    return noErrorsFound;
}

int parseParametersForDirectiveStatementOfTypeAnsii(char *scTextLine, char *name, char *str) {
    // scsCh === source code sentence character 
    char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
    int iteratingIndex = -1;
    if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                return noParametersInDirectiveStatement;
    }
    while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) {
        scsCh++; 
        if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
            return noParametersInDirectiveStatement;
        }
    }
    if (isCharacterNotEquals(scsCh, '\"')) {
        return badDirectiveStatementAscizFormat;
    }
    scsCh++;
    iteratingIndex++;
    if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
        // No 2nd "
        return badDirectiveStatementAscizFormat;
    }
    while (isCharacterNotEquals(scsCh, '\"'))
    {
        *(str+iteratingIndex) = *scsCh;
        scsCh++;
        iteratingIndex++;
    }
    while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
    {
        scsCh++;
        if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
            // after the closing " , no other character is allowed
            return badDirectiveStatementAscizFormat;
        }
    }
    return noErrorsFound;
}

int parseParametersForDirectiveStatementOfTypeEnteryOrExtern(char *scTextLine, char *name, char *label) {
    // scsCh === source code sentence character
    char *scsCh = (strstr(scTextLine, name) + strlen(name)); // init to 1st character after the name
    int iteratingIndex = -1;
    if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
                return noParametersInDirectiveStatement;
    }
    while (isCharacterEqualsOrCondition(scsCh, ' ', '\t')) {
        scsCh++; 
        if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
            return noParametersInDirectiveStatement;
        }
    }
    iteratingIndex++;
    if (isCharacterEqualsOrCondition(scsCh, '\n', '\0')) {
        // No label
        return noParametersInDirectiveStatement;
    }
    while (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
    {
        *(label+iteratingIndex) = *scsCh;
        scsCh++;
        iteratingIndex++;
    }
    while (isCharacterNotEqualsOrCondition(scsCh, '\n', '\0'))
    {
        scsCh++;
        if (isCharacterNotEqualsOrCondition(scsCh, ' ', '\t') && isCharacterNotEqualsOrCondition(scsCh, '\n', '\0')) {
            // after the label, no other character is allowed
            return badDirectiveStatementLabelFormat;
        }
    }
    // validate the label
    // too long label, more then 31 charcters
    int k = 0;
    while (isCharacterNotEqualsOrCondition(label+k, '\n', '\0'))
    {
        k++;
        if (k >= 31) {
            return badDirectiveStatementLabelFormat;
        }
    }
    k = 0;
    // first letter doesn't start with letter
    boolean isFirstCharacterInTheLabelNotLetter = !((*label >= 'a' && *label <= 'z') || (*label >= 'A' && *label <= 'Z'));
    if (isFirstCharacterInTheLabelNotLetter) {
        return badDirectiveStatementLabelFormat;
    }
    boolean areThereIllegalCharactersInTheLabel = false;
    while (isCharacterNotEqualsOrCondition(label+k, '\n', '\0'))
    {
        if ((*(label + k) >= 'a' && *(label + k) <= 'z') || (*(label + k) >= 'A' && *(label + k) <= 'Z') || (*(label + k) >= '0' && *(label + k) <= '9')) {
            k++;
            continue;
        } 
        areThereIllegalCharactersInTheLabel = true;
        break;
    }
    if (areThereIllegalCharactersInTheLabel) {
        return badDirectiveStatementLabelFormat;
    }
    return noErrorsFound;
}