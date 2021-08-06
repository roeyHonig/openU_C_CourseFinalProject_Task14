#include "assembler.h"
#define initialMemmoryAddressForStoringOutputCodeAndDataImage 100

int main(int argc, char *argv[])
{
    initOperationsHashTable();
    /* Loop over command line arguments to process source code text files */
    int i;
    for (i = 1; i < argc; i++)
    {
        FILE *ifp = fopen(argv[i], "r");
        struct sourceCodeSentence *firstSentence = readAssemblySourceCode(ifp);
        fclose(ifp);
        printf("\nCompiling the following assembly source code:\n");
        outputSourceCodeSentencesBeginingAt(firstSentence);
        /* 1st pass of compiler */
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, initialMemmoryAddressForStoringOutputCodeAndDataImage, 1); 
        /* 2nd pass of compiler */
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, initialMemmoryAddressForStoringOutputCodeAndDataImage, 2); 
        errorsFound = errorsFoundDuringCompilation(firstSentence);
        printf("%s", errorsFound ? "\n\nThese are the errors found:\n" : "");
        if (errorsFound) {
            outputSourceCodeSentencesErrorsBeginingAt(firstSentence);
        } else {
            outputCodeAndDataImageBeginingAtMemorryAddress(initialMemmoryAddressForStoringOutputCodeAndDataImage);
            printf("\n----------Symbols Table-----------\n");
            outputSymbolsHashTable();
        }
        nullifySymbolsHashTable();
    }   
    return 0;
}
