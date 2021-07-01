#include "assembler.h"

int main(int argc, char *argv[])
{
    // enter your code here...
    // Loop ove command line arguments  
    for (int i = 1; i < argc; i++)
    {
        printf("\n");
        FILE *ifp = fopen(argv[i], "r");
        char line[maxNumberOfCharacters];
        struct sourceCodeSentence *nextSentence = NULL;
        while (fgets(line, sizeof(line), ifp)) 
        {
            /* note that fgets don't strip the terminating \n, checking its
            presence would allow to handle lines longer that sizeof(line) */
            char * copy = malloc(strlen(line) + 1); 
            strcpy(copy, line);
            if (nextSentence == NULL) {
                nextSentence = initNewSourceCodeSentenceAndLinkTo(NULL);
            } else {
                nextSentence = initNewSourceCodeSentenceAndLinkTo(nextSentence);
            }
            nextSentence->currentTextLine = copy;
        }
        outputSourceCodeSentencesBeginingAt(nextSentence->head);
        fclose(ifp);
        printf("\n");
    }   
    printf("\n");
    return 0;
}


/*
old version of main 
-------------------------
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
-------------------------
*/