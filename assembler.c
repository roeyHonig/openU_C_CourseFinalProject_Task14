#include "assembler.h"

int main(int argc, char *argv[])
{
    // enter your code here... 
    initOperationsHashTable();
    outputOperationsHashTable();
    // Loop ove command line arguments and read the contents of the files
    for (int i = 1; i < argc; i++)
    {
        if (i == 1) {
            setSymbol(initSymbol("testroey", directiveStatement, 5));
            setSymbol(initSymbol("testido", instructionStatement, 10));
            setSymbol(initSymbol("testmayyan", directiveStatement, 15));
        } else {
            // change to someting else
            setSymbol(initSymbol("testEfrat", directiveStatement, 5));
            setSymbol(initSymbol("testLiat", instructionStatement, 10));
            setSymbol(initSymbol("testmaria", directiveStatement, 15));
        }
        outputSymbolsHashTable();
        errorsFound = false;
        FILE *ifp = fopen(argv[i], "r");
        struct sourceCodeSentence *firstSentence = readAssemblySourceCode(ifp);
        outputSourceCodeSentencesBeginingAt(firstSentence);
        fclose(ifp);
        printf("\n\n");
        printf("These are the errors found:\n");
        outputSourceCodeSentencesErrorsBeginingAt(firstSentence);
        freeSourceCodeSentenceLinkedListBeginingAt(firstSentence);
        nullifySymbolsHashTable();
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