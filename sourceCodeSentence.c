#include "sourceCodeSentence.h"
#include "symbols.h"

#define maxNumberOfCharactersForLabel 31
#define maxNumberOfCharactersForInstructionName 7 // reserved word - max 7 characters - ".extern"

void parseRInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord);
void parseIInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord);
void parseJInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord);
void parseDirectiveStatementForTheFollowing(struct sourceCodeSentence *tmp, char *rWord);

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
    node->iInstruction = (struct type_I_Instruction*) malloc(1 * sizeof(struct type_I_Instruction));
    node->iInstruction = NULL;
    node->jInstruction = (struct type_J_Instruction*) malloc(1 * sizeof(struct type_J_Instruction));
    node->jInstruction = NULL;
    node->dStatement = (struct directiveStatement*) malloc(1 * sizeof(struct directiveStatement));
    node->dStatement = NULL;
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
                // the line doesn't have a \n but it does have a \0 ofcourse, so we have to instantate a new copy array, 1 place larger then before, so we can fit all the letters and the \n and the \0
                copy = NULL;
                copy = initAnEmptyStringOfSize(strlen(line)+1);
                strcpy(copy, line);
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
           // TODO: i think i'm not checking for duplicate label names!. should be an error
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
           parseRInstructionForTheFollowing(tmp, rWord);
           if (shouldSetLabel){
               setSymbol(initSymbol(currentLabel, instructionStatement, tmp->currentTextLineNumber == 1 ? 86:116)); // TODO: value should be the counter
           }

       } else if (isIInstruction) {
           parseIInstructionForTheFollowing(tmp, rWord);
           if (shouldSetLabel){
               setSymbol(initSymbol(currentLabel, instructionStatement, 116)); // TODO: value should be the counter
           }
                
       } else if (isJInstruction) {
           parseJInstructionForTheFollowing(tmp, rWord);
           if (shouldSetLabel){
               setSymbol(initSymbol(currentLabel, instructionStatement, 116)); // TODO: value should be the counter
           }

       } else if (isDirectiveStatement) {
           parseDirectiveStatementForTheFollowing(tmp, rWord);           
           boolean isDirectiveStatementSupportsSettingLabel = isLabelSupportedForDirectiveTypeKeywords(rWord);
           if (shouldSetLabel && isDirectiveStatementSupportsSettingLabel){
               setSymbol(initSymbol(currentLabel, directiveStatement, 100)); // TODO: value should be the counter
           }

       } else {
           tmp->error = notRecognizableAssemblyLanguageStatement;
       }
    }
}

void parseRInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord) {
           printf("\n");
           printf("Line#%d, the statement name:%s it is an R type\n", tmp->currentTextLineNumber ,rWord);
           int firstRegister, secondRegister, thirdRegister; 
           boolean errorsFoundDuringParsingRegisters = !parseRegistersForRType(tmp->currentTextLine, rWord, &firstRegister, &secondRegister, &thirdRegister);
           if (errorsFoundDuringParsingRegisters) {
               tmp->error = wrongRegisterNumber;
               return;
           } 
           struct operation *ope = getOperationWithOpName(rWord);
           if (ope == NULL) {
               tmp->error = notRecognizableAssemblyLanguageStatement;
               return;
           }  
           boolean isRTypeCopyInstruction = (strcmp(rWord, "move") == 0 || strcmp(rWord, "mvhi") == 0 || strcmp(rWord, "mvlo") == 0);
           int rs = isRTypeCopyInstruction ? secondRegister : firstRegister;
           int rt = isRTypeCopyInstruction ? 0 : secondRegister;
           int rd = isRTypeCopyInstruction ? firstRegister : thirdRegister; 
           struct type_R_Instruction *r_Instruction = initNewType_R_InstructionWith(rs, rt, rd, ope);
           tmp->rInstruction = r_Instruction;
           outputType_R_Instruction(tmp->rInstruction);
}

void parseIInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord) {
           printf("\n");
           printf("Line#%d, the statement name:%s it is an I type\n", tmp->currentTextLineNumber ,rWord);
           int firstRegister, secondRegister; 
           short immediate;
           char *labelInTheInstruction = initAnEmptyStringOfSizeAndFillWithChacter(maxNumberOfCharactersForLabel,'0');
           tmp->error = parseRegistersAndImmediateForIType(tmp->currentTextLine, rWord, &firstRegister, &secondRegister, &immediate, labelInTheInstruction);
           if (tmp->error != noErrorsFound) {
               return;
           } 
           struct operation *ope = getOperationWithOpName(rWord);
           if (ope == NULL) {
               tmp->error = notRecognizableAssemblyLanguageStatement;
               return;
           } 
           // check if this is an I instruction with a label as the 3rd argument
           if (*labelInTheInstruction != '0') {
               // We need to calculate the immediate based on the distance between label value and the current value of the instruction in the instructino counter
               struct symbol *branchingLabel = getSymbolWithNameAndLocation(labelInTheInstruction, instructionStatement);
               if (branchingLabel == NULL) {
                   immediate = 0; // This is the 1st attemp, so maybe the label will be present in the table after the assembler will read the all code.
               } else {
                   immediate = branchingLabel->value - 108; // TODO: this should be the current counter 
               }
           } 
           struct type_I_Instruction *i_Instruction = initNewType_I_InstructionWith(firstRegister, secondRegister, immediate, ope);
           tmp->iInstruction = i_Instruction;
           outputType_I_Instruction(tmp->iInstruction);
}

void parseJInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord) {
           printf("\n");
           printf("Line#%d, the statement name:%s it is an J type\n", tmp->currentTextLineNumber ,rWord);
           int registerFlag; 
           int address;
           char *labelInTheInstruction = initAnEmptyStringOfSizeAndFillWithChacter(maxNumberOfCharactersForLabel,'0');
           tmp->error = parseRegistersOrLabelForJType(tmp->currentTextLine, rWord, &registerFlag, &address, labelInTheInstruction);
           if (tmp->error != noErrorsFound) {
               return;
           } 
           struct operation *ope = getOperationWithOpName(rWord);
           if (ope == NULL) {
               tmp->error = notRecognizableAssemblyLanguageStatement;
               return;
           } 
           // check if this is a J instruction with a label
           if (*labelInTheInstruction != '0') {
               struct symbol *branchingLabel = getSymbolWithNameAndLocation(labelInTheInstruction, instructionStatement);
               struct symbol *internalLabel = getSymbolWithNameAndLocation(labelInTheInstruction, directiveStatement);
               // TODO we need to add more enum to represent external for example
               if (branchingLabel != NULL) {
                   address = branchingLabel->value;
               } else if (internalLabel != NULL) {
                   address = internalLabel->value;
               } else {
                   address = 0;
               }
               // todo: we need to make sure the external exsists, because if nothing is present we need to show an error but only if this is the 2nd pass
               /*
               if (no symbol was found) {
                    tmp->error = no matching label;
                    return;
                } 
               
               */
           } 
           struct type_J_Instruction *j_Instruction = initNewType_J_InstructionWith(address, registerFlag, ope);
           tmp->jInstruction = j_Instruction;
           outputType_J_Instruction(tmp->jInstruction);
}

void parseDirectiveStatementForTheFollowing(struct sourceCodeSentence *tmp, char *rWord) {
    printf("\n");
    printf("Line#%d, the statement name:%s it is an Directive type\n", tmp->currentTextLineNumber ,rWord);
    char *parsedString = initAnEmptyStringOfSizeAndFillWithChacter(maxNumberOfCharacters, '\0');
    char *labelInTheDirective = initAnEmptyStringOfSizeAndFillWithChacter(maxNumberOfCharacters, '\0');
    int parameters[maxNumberOfCharacters];
    int parametersArrayIndex = -1; // this will have to change by the parsing functino
    int byteSizeOfParameter = 0; // this will have to change by the parsing function
    tmp->error = parseParametersOrAsciiStringOrLabelForDirectiveStatement(tmp->currentTextLine, rWord, parameters, &parametersArrayIndex, &byteSizeOfParameter, parsedString, labelInTheDirective);
    if (tmp->error != noErrorsFound) {
        return;
    }
    if (strcmp(rWord, ".db") == 0 || strcmp(rWord, ".dh") == 0 || strcmp(rWord, ".dw") == 0) {
        struct directiveStatementParameter *p = initNewDirectiveStatementParameterWithNumberByteSizeAndLinkTo(parameters[0], byteSizeOfParameter, NULL);
        struct directiveStatementParameter *tmpParameter;
        for (int i = 1; i <= parametersArrayIndex; i++)
        {
            tmpParameter = p;
            p = initNewDirectiveStatementParameterWithNumberByteSizeAndLinkTo(parameters[i], byteSizeOfParameter, tmpParameter);
        }
        struct directiveStatement *d_Statement = initNewDirectiveStatementWithHeadParameterAndNameAndStringAndLabel(p->head, rWord, NULL, NULL);
        tmp->dStatement = d_Statement;
    } else if (strcmp(rWord, ".asciz") == 0) {
        struct directiveStatement *d_Statement = initNewDirectiveStatementWithHeadParameterAndNameAndStringAndLabel(NULL, rWord, parsedString, NULL);
        tmp->dStatement = d_Statement;
    } else {
        struct directiveStatement *d_Statement = initNewDirectiveStatementWithHeadParameterAndNameAndStringAndLabel(NULL, rWord, NULL, labelInTheDirective);
        tmp->dStatement = d_Statement;
    }
    outputDirectiveStatement(tmp->dStatement);
}