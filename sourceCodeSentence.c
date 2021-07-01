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
    } else {
        node->head = node;
    }
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
       printLineBeginingAt(tmp->currentTextLine);
    }
}
