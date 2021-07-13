#include "assembler.h"

int main(int argc, char *argv[])
{
    // enter your code here... 
    initOperationsHashTable();
    outputOperationsHashTable();
    // Loop ove command line arguments 
    for (int i = 1; i < argc; i++)
    {
        errorsFound = false;
        FILE *ifp = fopen(argv[i], "r");
        struct sourceCodeSentence *firstSentence = readAssemblySourceCode(ifp);
        outputSourceCodeSentencesBeginingAt(firstSentence);
        parseSourceCodeSentencesBeginingAt(firstSentence);
        fclose(ifp);
        printf("\n\n");
        printf("These are the errors found:\n");
        outputSourceCodeSentencesErrorsBeginingAt(firstSentence);
        freeSourceCodeSentenceLinkedListBeginingAt(firstSentence);
        outputSymbolsHashTable();
        nullifySymbolsHashTable();
    }   
    return 0;
}
