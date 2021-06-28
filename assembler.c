#include "assembler.h"

int main()
{
    // enter your code here...
    printf("\nHello Assembler\n"); 
    struct sourceCodeSentence *firstSentence = initNewSourceCodeSentenceAndLinkTo(NULL);
    struct sourceCodeSentence *secondSentence = initNewSourceCodeSentenceAndLinkTo(firstSentence);
    char l1[] = "This is the first line of code";
    char l2[] = "This is the second line of code";
    firstSentence->currentTextLine = l1;
    secondSentence->currentTextLine = l2;
    outputSourceCodeSentencesBeginingAt(firstSentence);
    freeSourceCodeSentenceLinkedListBeginingAt(firstSentence);
    
    return 0;
}