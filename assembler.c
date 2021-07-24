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
        printf("---------------------\n");
        outputSymbolsHashTable();
        nullifySymbolsHashTable();
    }   
    /*
    // example for converstion from decimal to binary
    printf("\n");
    int adress[10] = {0};
    convertDecimalNumberIntoBitBinaryArrayOfSize(17,adress, 10);
    for (int j = 9; j >= 0; j--)
    {
        printf("%d", adress[j]);
    }
    printf("\n");
    */
    return 0;
}
