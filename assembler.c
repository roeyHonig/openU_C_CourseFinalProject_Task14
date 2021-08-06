#include "assembler.h"

int main(int argc, char *argv[])
{
    initOperationsHashTable();
    /* Loop ove command line arguments */
    int i;
    for (i = 1; i < argc; i++)
    {
        FILE *ifp = fopen(argv[i], "r");
        struct sourceCodeSentence *firstSentence = readAssemblySourceCode(ifp);
        fclose(ifp);
        printf("\nCompiling the following assembly source code:\n");
        outputSourceCodeSentencesBeginingAt(firstSentence);
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, 100, 1); /* 1st pass of compiler */
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, 100, 2); /* 2nd pass of compiler */
        errorsFound = errorsFoundDuringCompilation(firstSentence);
        printf("%s", errorsFound ? "\n\nThese are the errors found:\n" : "");
        if (errorsFound) {
            outputSourceCodeSentencesErrorsBeginingAt(firstSentence);
        } else {
            /* output the obhect file */
        }
        printf("----------Symbols Table-----------\n");
        outputSymbolsHashTable();
        nullifySymbolsHashTable();
    }   
    return 0;
}
