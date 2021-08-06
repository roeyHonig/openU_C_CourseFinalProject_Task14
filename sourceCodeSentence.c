#include "sourceCodeSentence.h"
#include "symbols.h"
#include "codeByte.h"

#define maxNumberOfCharactersForLabel 31
#define maxNumberOfCharactersForInstructionName 7 /* reserved word - max 7 characters - ".extern" */

int ic;
int dc = 0;
struct codeByte *previousCodeByte;
struct codeByte *previousDataByte;

void parseRInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass);
void parseIInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass);
void parseJInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass);
void parseDirectiveStatementForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass);
int computeTheDataCounterIncrementDueToDataOrAscizStatmentIn(struct sourceCodeSentence *sentence);
void appendInstructionCodeBytesFromBinaryRepresantation(int binary32BitRepresentation[]);
void appendDirectiveStatmentDataBytesForSourceCodeSenteneWithFollowingOpperationName(struct sourceCodeSentence *tmp, char *rWord);

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
    firstSentence = tmp->head;
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
                /* empty line */
                *copy = '\n';
                continue;
            }
            strcpy(copy, line);
            
            if (strlen(line) < maxNumberOfCharacters - 1 && strchr(line,'\n') == NULL) {
                /* this is the last line with no \n 
                 we need to manually set \n for the last line
                 otherwise it might be flagged as being too long. since it won't have a \n
                 the line doesn't have a \n but it does have a \0 ofcourse, so we have to instantate a new copy array, 1 place larger then before, so we can fit all the letters and the \n and the \0 */
                copy = NULL;
                copy = initAnEmptyStringOfSize(strlen(line)+1);
                strcpy(copy, line);
                *(copy + strlen(line)) = '\n';
            }
            if (currentLineIsTooLong) {
                /* If we got here, we've encountered a very long line of text. Larger then the allowed max number of characters
                 fgets will divide the long line to servel lines to always fit our defined array of size max number of character.
                 we need to check if this is the last part of the long Line.
                 If so. we need to keep back to the original execution of initializing a struct sourceCodeSentence during the next line. */
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
            /* We check by pointer arithmetics the difference between the start of the copy array and the location of the \n characters. If the 1st location is the last character, which we've set ourself, this means this line is too long. */
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
                /* A comment is source code sentence in which the 1st non ' ' character is ';' */
                /* The assembler can safely ignore this line. */
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
    firstSentence = tmp->head;
}

void parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(struct sourceCodeSentence *firstSentence, int instructionCounter, int pass) {
    extern int ic;
    extern int dc;
    extern struct codeByte *previousCodeByte;
    previousCodeByte = NULL;
    extern struct codeByte *previousDataByte;
    previousDataByte = NULL;
    ic = instructionCounter;
    dc = 0;
    struct sourceCodeSentence* tmp;
   while (firstSentence != NULL)
    {
       boolean shouldSetLabel = false; 
       char *currentLabel = initAnEmptyStringOfSize(maxNumberOfCharactersForLabel);
       tmp = firstSentence;
       firstSentence = firstSentence->next;
       if (tmp->error != noErrorsFound) 
            continue;

       /* get labels */
       if (isThereLabelInFollowingTextLine(tmp->currentTextLine)) {
           if (getLabelInto(currentLabel, tmp->currentTextLine)) {
               shouldSetLabel = true;
           } else {
               shouldSetLabel = false;
               tmp->error = badLabelFormat;
           }
       } 
       /* if we have a label we should check if it matches a reserved word */
       if (shouldSetLabel && isOneOfTheAssemblyLanguageReservedWordsEqualsTo(currentLabel)){
            tmp->error = useOfReservedWord;
        } 
        if (tmp->error != noErrorsFound) 
            continue; 
        /* get instruction name */
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
       /* check which kind of statement this is  */
       boolean isRInstruction = isRTypeKeywordsPresentInFollowingText(rWord); 
       boolean isIInstruction = isITypeKeywordsPresentInFollowingText(rWord); 
       boolean isJInstruction = isJTypeKeywordsPresentInFollowingText(rWord); 
       boolean isDirectiveStatement = isDirectiveTypeKeywordsPresentInFollowingText(rWord);

       if (isRInstruction) {
           parseRInstructionForTheFollowing(tmp, rWord, pass);
           if (shouldSetLabel && tmp->error == noErrorsFound){
               if (pass == 1) {
                   tmp->error = setSymbol(initSymbol(currentLabel, instructionStatement, ic)); 
               }
           }
           if (tmp->error == noErrorsFound) {
               ic = ic + 4;
               if (pass == 2) {
                   appendInstructionCodeBytesFromBinaryRepresantation(tmp->rInstruction->binary32BitCode);
               }
           }
       } else if (isIInstruction) {
           parseIInstructionForTheFollowing(tmp, rWord, pass);
           if (shouldSetLabel && tmp->error == noErrorsFound){
               if (pass == 1) {
                   tmp->error = setSymbol(initSymbol(currentLabel, instructionStatement, ic)); 
               }
           }
           if (tmp->error == noErrorsFound) {
               ic = ic + 4;
               if (pass == 2) {
                   appendInstructionCodeBytesFromBinaryRepresantation(tmp->iInstruction->binary32BitCode);
               }
           }    
       } else if (isJInstruction) {
           parseJInstructionForTheFollowing(tmp, rWord, pass);
           if (shouldSetLabel && tmp->error == noErrorsFound){
               if (pass == 1) {
                   tmp->error = setSymbol(initSymbol(currentLabel, instructionStatement, ic)); 
               }
           }
           if (tmp->error == noErrorsFound) {
               ic = ic + 4;
               if (pass == 2) {
                   appendInstructionCodeBytesFromBinaryRepresantation(tmp->jInstruction->binary32BitCode);
               }
           }
       } else if (isDirectiveStatement) {
           parseDirectiveStatementForTheFollowing(tmp, rWord, pass);           
           boolean isDirectiveStatementSupportsSettingLabel = isLabelSupportedForDirectiveTypeKeywords(rWord);
           if (shouldSetLabel && isDirectiveStatementSupportsSettingLabel && tmp->error == noErrorsFound){
               /* this a data \ asciz directive */
               if (pass == 1) {
                   tmp->error = setSymbol(initSymbol(currentLabel, directiveStatement, dc)); 
               }
           }
           if (tmp->error == noErrorsFound) {
                   dc = dc + computeTheDataCounterIncrementDueToDataOrAscizStatmentIn(tmp); 
                   if (pass == 2) {
                        appendDirectiveStatmentDataBytesForSourceCodeSenteneWithFollowingOpperationName(tmp, rWord);
                    }
            }
           
           if (tmp->error == noErrorsFound && tmp->dStatement->labelInDirective != NULL) {
               /* this an entry or external directive */
               if (strcmp(rWord, ".entry") == 0) {
                   if (pass == 1) {
                       tmp->error = setSymbol(initSymbol(tmp->dStatement->labelInDirective, entry, 1)); /* Dammy Value. Real value will be updated after the 2nd pass by calling 'updateEntryTypeSymbolsValueBy()' */
                   }
                   if (pass == 2) {
                       if (getSymbolWithNameAndLocation(tmp->dStatement->labelInDirective, instructionStatement) == NULL && getSymbolWithNameAndLocation(tmp->dStatement->labelInDirective, directiveStatement) == NULL) {
                           tmp->error = missingLabel;
                       }
                   }
               }
               if (strcmp(rWord, ".extern") == 0) {
                   if (pass == 1) {
                       tmp->error = setSymbol(initSymbol(tmp->dStatement->labelInDirective, external, 0)); 
                   } 
               }
           }
       } else {
           tmp->error = notRecognizableAssemblyLanguageStatement;
       }
    }
    firstSentence = tmp->head;
    if (pass == 1) {
        incrementDirectiveTypeSymbolsValueBy(getCurrentInstructionCounter());
    }
    if (pass ==2) {
        updateEntryTypeSymbolsValueBy();
    }
}

void parseRInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass) {
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
           if (pass == 2) {
               /* outputType_R_Instruction(tmp->rInstruction); */
           }
}

void parseIInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass) {
           extern int ic;
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
           /* check if this is an I instruction with a label as the 3rd argument */
           if (*labelInTheInstruction != '0') {
               /* We need to calculate the immediate based on the distance between label value and the current value of the instruction in the instructino counter */
               struct symbol *branchingLabel = getSymbolWithNameAndLocation(labelInTheInstruction, instructionStatement);
               struct symbol *directiveLabel = getSymbolWithNameAndLocation(labelInTheInstruction, directiveStatement);
                if (branchingLabel != NULL) {
                    immediate = branchingLabel->value - ic;  
                } else if (directiveLabel != NULL) {
                    immediate = directiveLabel->value - ic;  
                } else {
                    if (pass == 2) {
                       tmp->error = missingLabel;
                   } else {
                       immediate = 0; 
                   }
                }
           } 
           struct type_I_Instruction *i_Instruction = initNewType_I_InstructionWith(firstRegister, secondRegister, immediate, ope);
           tmp->iInstruction = i_Instruction;
           if (pass == 2) {
               /* outputType_I_Instruction(tmp->iInstruction); */
           }
}

void parseJInstructionForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass) {
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
           /* check if this is a J instruction with a label */
           if (*labelInTheInstruction != '0') {
               struct symbol *branchingLabel = getSymbolWithNameAndLocation(labelInTheInstruction, instructionStatement);
               struct symbol *externalLabel = getSymbolWithNameAndLocation(labelInTheInstruction, external);
               struct symbol *directiveLabel = getSymbolWithNameAndLocation(labelInTheInstruction, directiveStatement);
               if (branchingLabel != NULL) {
                   address = branchingLabel->value;
               } else if (externalLabel != NULL) {
                   address = externalLabel->value;
               } else if (directiveLabel != NULL) {
                   address = directiveLabel->value;
               } else {
                   if (pass == 2) {
                       tmp->error = missingLabel;
                   } else {
                       address = 0;
                   }
               }
           } 
           struct type_J_Instruction *j_Instruction = initNewType_J_InstructionWith(address, registerFlag, ope);
           tmp->jInstruction = j_Instruction;
           if (pass == 2) {
               /* Type_J_Instruction(tmp->jInstruction); */
           }
}

void parseDirectiveStatementForTheFollowing(struct sourceCodeSentence *tmp, char *rWord, int pass) {
    char *parsedString = initAnEmptyStringOfSizeAndFillWithChacter(maxNumberOfCharacters, '\0');
    char *labelInTheDirective = initAnEmptyStringOfSizeAndFillWithChacter(maxNumberOfCharacters, '\0');
    int parameters[maxNumberOfCharacters];
    int parametersArrayIndex = -1; /* this will have to change by the parsing functino */
    int byteSizeOfParameter = 0; /* this will have to change by the parsing function */
    tmp->error = parseParametersOrAsciiStringOrLabelForDirectiveStatement(tmp->currentTextLine, rWord, parameters, &parametersArrayIndex, &byteSizeOfParameter, parsedString, labelInTheDirective);
    if (tmp->error != noErrorsFound) {
        return;
    }
    if (strcmp(rWord, ".db") == 0 || strcmp(rWord, ".dh") == 0 || strcmp(rWord, ".dw") == 0) {
        struct directiveStatementParameter *p = initNewDirectiveStatementParameterWithNumberByteSizeAndLinkTo(parameters[0], byteSizeOfParameter, NULL);
        struct directiveStatementParameter *tmpParameter;
        int i;
        for (i = 1; i <= parametersArrayIndex; i++)
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
    if (pass == 2) {
        /* outputDirectiveStatement(tmp->dStatement); */
    }
}

int getCurrentInstructionCounter() {
    extern int ic;
    return ic;
}

int computeTheDataCounterIncrementDueToDataOrAscizStatmentIn(struct sourceCodeSentence *sentence) {
    /* data */
    int dataIncrement = 0;
    struct directiveStatementParameter* firstParmater = sentence->dStatement->parameter;
    struct directiveStatementParameter* tmp;
    while (firstParmater != NULL)
    {
        tmp = firstParmater;
        firstParmater = firstParmater->next;
        dataIncrement= dataIncrement + tmp->byteSize;
    }
    /* asciz */
    if (sentence->dStatement->stringInDirective != NULL) {
        dataIncrement = strlen(sentence->dStatement->stringInDirective) + 1;
    }
    return dataIncrement;
}

void appendInstructionCodeBytesFromBinaryRepresantation(int binary32BitRepresentation[]) {
    extern struct codeByte *previousCodeByte;
    previousCodeByte = initNewCodeByteFrom32BitArrayInPositionAndLinkTo(binary32BitRepresentation, 1, previousCodeByte);
    previousCodeByte = initNewCodeByteFrom32BitArrayInPositionAndLinkTo(binary32BitRepresentation, 2, previousCodeByte);
    previousCodeByte = initNewCodeByteFrom32BitArrayInPositionAndLinkTo(binary32BitRepresentation, 3, previousCodeByte);
    previousCodeByte = initNewCodeByteFrom32BitArrayInPositionAndLinkTo(binary32BitRepresentation, 4, previousCodeByte);
}

void appendDirectiveStatmentDataBytesForSourceCodeSenteneWithFollowingOpperationName(struct sourceCodeSentence *tmp, char *rWord) {
    extern struct codeByte *previousDataByte;
    int binary32BitRepresentation[32];
        if (strcmp(rWord, ".asciz") == 0) {
            /* append String bytes */
            int strIndex;
            for (strIndex = 0; strIndex < strlen(tmp->dStatement->stringInDirective); strIndex++)
            {
                convertSignedNumberInto32Bit2ComplimentAndPlaceInside32BitIntArray(*(tmp->dStatement->stringInDirective+strIndex), binary32BitRepresentation);
                previousDataByte = initNewCodeByteFrom32BitArrayInPositionAndLinkTo(binary32BitRepresentation, 1, previousDataByte);
            }
            /* append nul character '\n' */
            convertSignedNumberInto32Bit2ComplimentAndPlaceInside32BitIntArray('\0', binary32BitRepresentation);
            previousDataByte = initNewCodeByteFrom32BitArrayInPositionAndLinkTo(binary32BitRepresentation, 1, previousDataByte);
        } else if (strcmp(rWord, ".db") == 0 || strcmp(rWord, ".dh") == 0 || strcmp(rWord, ".dw") == 0) {
            struct directiveStatementParameter* tmpParameter;
            struct directiveStatementParameter* first = tmp->dStatement->parameter;
            while (first != NULL)
            {
                tmpParameter = first;
                first = first->next;
                int parameterIndex;
                for (parameterIndex = 1; parameterIndex <= tmpParameter->byteSize; parameterIndex++)
                {
                    convertSignedNumberInto32Bit2ComplimentAndPlaceInside32BitIntArray(tmpParameter->number, binary32BitRepresentation);
                    previousDataByte = initNewCodeByteFrom32BitArrayInPositionAndLinkTo(binary32BitRepresentation, parameterIndex, previousDataByte);
                }
            }
            first = tmpParameter->head;
        }
}

int errorsFoundDuringCompilation(struct sourceCodeSentence *firstSentence) {
    struct sourceCodeSentence* tmp;
   while (firstSentence != NULL)
    {
       tmp = firstSentence;
       firstSentence = firstSentence->next;
       if (tmp->error != noErrorsFound && tmp->error != comment) {
           return true;
       }
       
    }
    firstSentence = tmp->head;
    return false;
}

void outputCodeAndDataImageBeginingAtMemorryAddress(int memAddress) {
    extern struct codeByte *previousCodeByte;
    extern struct codeByte *previousDataByte;
    outputCompleteCodeAndDataBytesInHexadecimalBeginingAtMemoryAddressAndFirstCodeByteAndFirstDataByteint(memAddress, previousCodeByte->head, previousDataByte->head);
}

void outputCodeAndDataImageBeginingAtMemorryAddressIntoAnObjectFileName(int memAddress, char *objectFileName) {
    extern struct codeByte *previousCodeByte;
    extern struct codeByte *previousDataByte;
    outputCompleteCodeAndDataBytesInHexadecimalBeginingAtMemoryAddressToObjectFileName(memAddress, previousCodeByte->head, previousDataByte->head, objectFileName);
}