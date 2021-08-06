#include "assembler.h"
#define binarryArraySize 31
#define decimalNumberUnsignedExample 2147483646

int main(int argc, char *argv[])
{
    /* enter your code here... */
    initOperationsHashTable();
    outputOperationsHashTable();
    /* Loop ove command line arguments */
    int i;
    for (i = 1; i < argc; i++)
    {
        errorsFound = false;
        FILE *ifp = fopen(argv[i], "r");
        struct sourceCodeSentence *firstSentence = readAssemblySourceCode(ifp);
        outputSourceCodeSentencesBeginingAt(firstSentence);
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, 100, 1);
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, 100, 2);
        fclose(ifp);
        printf("\n\n");
        printf("These are the errors found:\n");
        outputSourceCodeSentencesErrorsBeginingAt(firstSentence);
        printf("---------------------\n");
        outputSymbolsHashTable();
        nullifySymbolsHashTable();
    }   
    return 0;
}
