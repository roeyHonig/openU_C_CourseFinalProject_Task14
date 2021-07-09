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
    char line[1000]; // safe enough buffer size to make sure very long line of text (larger then the alloed max number of characters) won't get divided into multiple source code statements.
    struct sourceCodeSentence *nextSentence = NULL;
    while (fgets(line, sizeof(line), input)) 
        {
            char * copy = malloc(strlen(line) + 1); 
            strcpy(copy, line);
            if (nextSentence == NULL) {
                nextSentence = initNewSourceCodeSentenceAndLinkTo(NULL);
            } else {
                nextSentence = initNewSourceCodeSentenceAndLinkTo(nextSentence);
            }
            nextSentence->currentTextLine = copy;
            // fgets don't strip the terminating \n (New Line), checking its presence would allow to handle lines longer then the alloed max number of characters. We check by pointer arithmetics the difference between the start of the copy array and the location of the \n characters.
            if (strchr(nextSentence->currentTextLine,'\n') != NULL && (strchr(nextSentence->currentTextLine,'\n') - copy) > maxNumberOfCharacters)
                nextSentence->error = lineTooLong;      
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