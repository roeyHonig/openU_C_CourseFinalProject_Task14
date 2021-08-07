#include "assembler.h"
#define initialMemmoryAddressForStoringOutputCodeAndDataImage 100

int main(int argc, char *argv[])
{
    initOperationsHashTable();
    /* Loop over command line arguments to process source code text files */
    int i;
    for (i = 1; i < argc; i++)
    {
        /* Open and read the next source code file */
        char *sourceCodeFileName = argv[i];
        FILE *ifp = fopen(sourceCodeFileName, "r");
        struct sourceCodeSentence *firstSentence = readAssemblySourceCode(ifp);
        fclose(ifp);
        /* Prepere the output files names. The external file is auto generated so it will be removed if errors are found */
        char *objectFileName = getObjectFileNameForSourceCodeFileName(sourceCodeFileName);
        char *externalFileName = getExternalFileNameForSourceCodeFileName(sourceCodeFileName);
        char *entryFileName = getEntryFileNameForSourceCodeFileName(sourceCodeFileName);
        /* Try to compile the source code */
        printf("\nCompiling the following assembly source code:\n");
        outputSourceCodeSentencesBeginingAt(firstSentence);
        /* 1st pass of compiler */
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, initialMemmoryAddressForStoringOutputCodeAndDataImage, 1, externalFileName); 
        /* 2nd pass of compiler */
        parseSourceCodeSentencesBeginingAtWithInitialInstructionCounter(firstSentence, initialMemmoryAddressForStoringOutputCodeAndDataImage, 2, externalFileName);
        /* Check for errors */
        errorsFound = errorsFoundDuringCompilation(firstSentence);
        printf("%s", errorsFound ? "\n\nThese are the errors found:\n" : "");
        if (errorsFound) {
            outputSourceCodeSentencesErrorsBeginingAt(firstSentence);
            remove(externalFileName);
        } else {
            outputCodeAndDataImageBeginingAtMemorryAddressIntoAnObjectFileName(initialMemmoryAddressForStoringOutputCodeAndDataImage, objectFileName);
            writeToEntryFileNamed(entryFileName);
        }
        nullifySymbolsHashTable();
    }   
    return 0;
}
