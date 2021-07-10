#include "sourceCodeSentence.h"

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
    while (fgets(line, sizeof(line), input)) 
        {
            char * copy = malloc(strlen(line) + 1); 
            strcpy(copy, line);
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
            copy[maxNumberOfCharacters-1] = '\n'; // Set the last character to be 'new Line' because the last line of source code might not include it.
            nextSentence->currentTextLine = copy;
            // We check by pointer arithmetics the difference between the start of the copy array and the location of the \n characters. If the 1st location is the last character, which we've set ourself, this means this line is too long.
            if ((strchr(copy,'\n') - copy == maxNumberOfCharacters - 1)) {
                nextSentence->error = lineTooLong;   
                nextSentence->currentTextLine[maxNumberOfCharacters-1] = '\n';
                nextSentence->currentTextLine[maxNumberOfCharacters-2] = 'g';
                nextSentence->currentTextLine[maxNumberOfCharacters-3] = 'n';
                nextSentence->currentTextLine[maxNumberOfCharacters-4] = 'o';
                nextSentence->currentTextLine[maxNumberOfCharacters-5] = 'L';
                nextSentence->currentTextLine[maxNumberOfCharacters-6] = ' ';
                nextSentence->currentTextLine[maxNumberOfCharacters-7] = 'o';
                nextSentence->currentTextLine[maxNumberOfCharacters-8] = 'o';
                nextSentence->currentTextLine[maxNumberOfCharacters-9] = 'T';
                nextSentence->currentTextLine[maxNumberOfCharacters-10] = ' ';
                nextSentence->currentTextLine[maxNumberOfCharacters-11] = 'e';
                nextSentence->currentTextLine[maxNumberOfCharacters-12] = 'n';
                nextSentence->currentTextLine[maxNumberOfCharacters-13] = 'i';
                nextSentence->currentTextLine[maxNumberOfCharacters-14] = 'L';
                nextSentence->currentTextLine[maxNumberOfCharacters-15] = '.';
                nextSentence->currentTextLine[maxNumberOfCharacters-16] = '.';
                nextSentence->currentTextLine[maxNumberOfCharacters-17] = '.';
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
                    if (copy[i] != ' ')
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
       tmp = firstSentence;
       firstSentence = firstSentence->next;
       if (tmp->error != NULL) 
            continue;
       boolean isRInstruction = isRTypeKeywordsPresentInFollowingTextLine(tmp->currentTextLine); 
       boolean isIInstruction = isITypeKeywordsPresentInFollowingTextLine(tmp->currentTextLine); 
       boolean isJInstruction = isJTypeKeywordsPresentInFollowingTextLine(tmp->currentTextLine); 
       boolean isDirectiveStatement = isDirectiveTypeKeywordsPresentInFollowingTextLine(tmp->currentTextLine);
       if (isRInstruction) {
           // TODO: parse R instruction
       } else if (isIInstruction) {
           // TODO: parse I instruction
       } else if (isJInstruction) {
           // TODO: parse J instruction
       } else if (isDirectiveStatement) {
           // TODO: parse Directive
       } else {
           tmp->error = notRecognizableAssemblyLanguageStatement;
       }
    }
}