#include "sourceCodeSentence.h"
#include "symbols.h"

#define maxNumberOfCharactersForLabel 31
#define maxNumberOfCharactersForInstructionName 7 // reserved word - max 7 characters - ".extern"

struct sourceCodeSentence *initNewSourceCodeSentenceAndLinkTo(struct sourceCodeSentence *previousSentence) {
    struct sourceCodeSentence *node = (struct sourceCodeSentence*) malloc(1 * sizeof(struct sourceCodeSentence));
    node->currentTextLine = (char*)calloc(maxNumberOfCharacters, sizeof(char));
    node->next = NULL;
    node->previous = previousSentence;
    if (previousSentence != NULL) {
        previousSentence->next = (struct sourceCodeSentence*) malloc(1 * sizeof(struct sourceCodeSentence));
        previousSentence->next = node;
        node->head = previousSentence->head;
        node->currentTextLineNumber = previousSentence->currentTextLineNumber + 1;
    } else {
        node->head = node;
        node->currentTextLineNumber = 1;
    }
    node->error = noErrorsFound;
    node->rInstruction = (struct type_R_Instruction*) malloc(1 * sizeof(struct type_R_Instruction));
    node->rInstruction = NULL;
    return node;
}

void freeSourceCodeSentenceLinkedListBeginingAt(struct sourceCodeSentence *firstSentence) {
   struct sourceCodeSentence* tmp;
   while (firstSentence != NULL)
    {
       tmp = firstSentence;
       firstSentence = firstSentence->next;
       free(tmp);
    }
}

void outputSourceCodeSentencesBeginingAt(struct sourceCodeSentence *firstSentence) {
   struct sourceCodeSentence* tmp;
   while (firstSentence != NULL)
    {
       tmp = firstSentence;
       firstSentence = firstSentence->next;
       printf("%d%c  ", tmp->currentTextLineNumber, '.');
       printLineBeginingAt(tmp->currentTextLine);
    }
}

struct sourceCodeSentence *readAssemblySourceCode(FILE *input) {
    char line[maxNumberOfCharacters];  
    boolean currentLineIsTooLong = false;
    struct sourceCodeSentence *nextSentence = NULL;
    /*
    The C library function char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
    */
    while (fgets(line, sizeof(line), input)) 
        {
            char *copy = initAnEmptyStringOfSize(strlen(line));
            if (strlen(line) == 0) {
                // empty line
                *copy = '\n';
                continue;
            }
            strcpy(copy, line);
            
            if (strlen(line) < maxNumberOfCharacters - 1 && strchr(line,'\n') == NULL) {
                // this is the last line with no \n 
                // we need to manually set \n for the last line
                // otherwise it might be flagged as being too long. since it won't have a \n
                *(copy + strlen(line)) = '\n';
            }
            if (currentLineIsTooLong) {
                // If we got here, we've encountered a very long line of text. Larger then the allowed max number of characters
                // fgets will divide the long line to servel lines to always fit our defined array of size max number of character.
                // we need to check if this is the last part of the long Line.
                // If so. we need to keep back to the original execution of initializing a struct sourceCodeSentence during the next line.
                if (strchr(copy,'\n') != NULL) {
                    currentLineIsTooLong = false;   
                }
                continue;
            } 
            if (nextSentence == NULL) {
                nextSentence = initNewSourceCodeSentenceAndLinkTo(NULL);
            } else {
                nextSentence = initNewSourceCodeSentenceAndLinkTo(nextSentence);
            }
            nextSentence->currentTextLine = copy;
            // We check by pointer arithmetics the difference between the start of the copy array and the location of the \n characters. If the 1st location is the last character, which we've set ourself, this means this line is too long.
            if (strchr(copy,'\n') == NULL) {
                nextSentence->error = lineTooLong;   
                *(nextSentence->currentTextLine + strlen(line)) = '\n';
                *(nextSentence->currentTextLine + strlen(line) -1) = 'g';
                *(nextSentence->currentTextLine + strlen(line) -2) = 'n';
                *(nextSentence->currentTextLine + strlen(line) -3) = 'o';
                *(nextSentence->currentTextLine + strlen(line) -4) = 'L';
                *(nextSentence->currentTextLine + strlen(line) -5) = ' ';
                *(nextSentence->currentTextLine + strlen(line) -6) = 'o';
                *(nextSentence->currentTextLine + strlen(line) -7) = 'o';
                *(nextSentence->currentTextLine + strlen(line) -8) = 'T';
                *(nextSentence->currentTextLine + strlen(line) -9) = ' ';
                *(nextSentence->currentTextLine + strlen(line) -10) = 'e';
                *(nextSentence->currentTextLine + strlen(line) -11) = 'n';
                *(nextSentence->currentTextLine + strlen(line) -12) = 'i';
                *(nextSentence->currentTextLine + strlen(line) -13) = 'L';
                *(nextSentence->currentTextLine + strlen(line) -14) = '.';
                *(nextSentence->currentTextLine + strlen(line) -15) = '.';
                *(nextSentence->currentTextLine + strlen(line) -16) = '.';
                currentLineIsTooLong = true;   
                continue;
            } 
            if (strchr(copy,';') != NULL) {
                // A comment is source code sentence in which the 1st non ' ' character is ';'
                // The assembler can safely ignore this line.
                boolean isThisComment = true;
                int i = 0;
                while (i < strchr(copy,';') - copy)
                {
                    if (*(copy + i) != ' ')
                        isThisComment = false;
                    i++;
                }
                if (isThisComment)
                    nextSentence->error = comment;   
                else nextSentence->error = illegalUseOfSemiColon;     
            }   
        }
    return nextSentence->head;      
}

void outputSourceCodeSentencesErrorsBeginingAt(struct sourceCodeSentence *firstSentence) {
   struct sourceCodeSentence* tmp;
   while (firstSentence != NULL)
    {
       tmp = firstSentence;
       firstSentence = firstSentence->next;
       printErrorDescriptionFor(tmp->currentTextLineNumber, tmp->error);
    }
}

void parseSourceCodeSentencesBeginingAt(struct sourceCodeSentence *firstSentence) {
    struct sourceCodeSentence* tmp;
   while (firstSentence != NULL)
    {
       boolean shouldSetLabel = false; 
       char *currentLabel = initAnEmptyStringOfSize(maxNumberOfCharactersForLabel);
       tmp = firstSentence;
       firstSentence = firstSentence->next;
       if (tmp->error != noErrorsFound) 
            continue;

       // get labels
       if (isThereLabelInFollowingTextLine(tmp->currentTextLine)) {
           if (getLabelInto(currentLabel, tmp->currentTextLine)) {
               shouldSetLabel = true;
           } else {
               shouldSetLabel = false;
               tmp->error = badLabelFormat;
           }
       } 
       // if we have a label we should check if it matches a reserved word 
       if (shouldSetLabel && isOneOfTheAssemblyLanguageReservedWordsEqualsTo(currentLabel)){
            tmp->error = useOfReservedWord;
        } 
        if (tmp->error != noErrorsFound) 
            continue; 
        // get instruction name
       char *rWord = initAnEmptyStringOfSize(maxNumberOfCharactersForInstructionName);
       boolean passedFirstNonWhiteCharacter = false;
       int i = (strstr(tmp->currentTextLine, ":") == NULL) ? 0 : strstr(tmp->currentTextLine, ":") - tmp->currentTextLine + 1; 
       int j = 0;
       while (j < maxNumberOfCharactersForInstructionName && *(tmp->currentTextLine + i) != '\n')
       {
           if (!(*(tmp->currentTextLine + i) == ' ' || *(tmp->currentTextLine + i) == '\t') && !passedFirstNonWhiteCharacter) {
               passedFirstNonWhiteCharacter = true;
           }
           if (passedFirstNonWhiteCharacter) {
               if ((*(tmp->currentTextLine + i) == ' ' || *(tmp->currentTextLine + i) == '\t')) {
                    break;
               }
               *(rWord + j) = *(tmp->currentTextLine + i);
               j++;
           }
           i++;
       }
       if (strcmp(rWord, "") == 0) {
            tmp->error = notRecognizableAssemblyLanguageStatement;
       }
       if (tmp->error != noErrorsFound) 
            continue;
       // check which kind of statement this is 
       boolean isRInstruction = isRTypeKeywordsPresentInFollowingText(rWord); 
       boolean isIInstruction = isITypeKeywordsPresentInFollowingText(rWord); 
       boolean isJInstruction = isJTypeKeywordsPresentInFollowingText(rWord); 
       boolean isDirectiveStatement = isDirectiveTypeKeywordsPresentInFollowingText(rWord);

       if (isRInstruction) {
           // TODO: parse R instruction
           printf("\n");
           printf("Line#%d, the statement name:%s it is an R type\n", tmp->currentTextLineNumber ,rWord);
           int firstRegister, secondRegister, thirdRegister; 
           boolean errorsFoundDuringParsingRegisters = !parseRegistersForRType(tmp->currentTextLine, rWord, &firstRegister, &secondRegister, &thirdRegister);
           if (errorsFoundDuringParsingRegisters) {
               tmp->error = wrongRegisterNumber;
               continue;
           } 
           struct operation *ope = getOperationWithOpName(rWord);
           if (ope == NULL) {
               tmp->error = notRecognizableAssemblyLanguageStatement;
               continue;
           }    
           struct type_R_Instruction *r_Instruction = initNewType_R_InstructionWith(firstRegister, secondRegister, thirdRegister, ope);
            tmp->rInstruction = r_Instruction;
            outputType_R_Instruction(tmp->rInstruction);
           if (shouldSetLabel){
               setSymbol(initSymbol(currentLabel, instructionStatement, 100)); // TODO: value should be the counter
           }

       } else if (isIInstruction) {
           // TODO: parse I instruction
           printf("\n");
           printf("Line#%d, the statement name:%s it is an I type\n", tmp->currentTextLineNumber ,rWord);
           if (shouldSetLabel){
               setSymbol(initSymbol(currentLabel, instructionStatement, 100)); // TODO: value should be the counter
           }
                
       } else if (isJInstruction) {
           // TODO: parse J instruction
           printf("\n");
           printf("Line#%d, the statement name:%s it is an J type\n", tmp->currentTextLineNumber ,rWord);
           if (shouldSetLabel){
               setSymbol(initSymbol(currentLabel, instructionStatement, 100)); // TODO: value should be the counter
           }

       } else if (isDirectiveStatement) {
           // TODO: parse Directive
           printf("\n");
           printf("Line#%d, the statement name:%s it is an Directive type\n", tmp->currentTextLineNumber ,rWord);
           if (shouldSetLabel){
               setSymbol(initSymbol(currentLabel, directiveStatement, 100)); // TODO: value should be the counter
           }

       } else {
           tmp->error = notRecognizableAssemblyLanguageStatement;
       }
    }
}