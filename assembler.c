#include "assembler.h"

int main(int argc, char *argv[])
{
    // enter your code here... 
    initOperationsHashTable();
    // Loop ove command line arguments and read the contents of the files
    for (int i = 1; i < argc; i++)
    {
        errorsFound = false;
        FILE *ifp = fopen(argv[i], "r");
        struct sourceCodeSentence *firstSentence = readAssemblySourceCode(ifp);
        outputSourceCodeSentencesBeginingAt(firstSentence);
        fclose(ifp);
        printf("\n\n");
        printf("These are the errors found:\n");
        outputSourceCodeSentencesErrorsBeginingAt(firstSentence);
        freeSourceCodeSentenceLinkedListBeginingAt(firstSentence);
    }   
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