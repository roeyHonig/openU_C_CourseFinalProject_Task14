#include "assembler.h"
#define binarryArraySize 31
#define decimalNumberUnsignedExample 2147483646

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
    /*
    // example for converstion from decimal to binary
    printf("\n");
    int adress[binarryArraySize] = {0};
    convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(decimalNumberUnsignedExample,adress, binarryArraySize);
    printf("decimal unsugned number %d is in binary unsigned notation of %d bits :\n", decimalNumberUnsignedExample, binarryArraySize);
    for (int j = binarryArraySize-1; j >= 0; j--)
    {
        printf("%d", adress[j]);
    }
    printf("\n");
    // example of representing a x bit signed number in an x+! bits signed complement 2
    printf("same number in binary signed notation of %d bits :\n", binarryArraySize+1);
    printf("\n");
    int adressIn2Complement[binarryArraySize+1] = {0};
    convertUnsignedBinaryNumberArrayOfBitSizeIntoSigned(adress, binarryArraySize, adressIn2Complement);
    for (j = binarryArraySize; j >= 0; j--)
    {
        printf("%d", adressIn2Complement[j]);
    }
    printf("\n");
    // example of negating the num 
    printf("\n");
    negateSignedBitArrayOfSize(adressIn2Complement, binarryArraySize+1);
    printf("the inverse number is:\n");
    for (j = binarryArraySize; j >= 0; j--)
    {
        printf("%d", adressIn2Complement[j]);
    }
    printf("\n");
    // example of computing the maximum and minumum an x amount of bits can represent signed decimal
   int numberOfBits = 24;
   int minNum = (pow(2, numberOfBits) / 2) * -1;
    int maxNum = ((pow(2, numberOfBits) / 2)-1);
    printf("\nmin:%d\nmax:%d\n", minNum, maxNum);
    */
   /*
   // greate way to print a string representing the hexdecimal notation of a decimal number.
   // we will do it byte by byte, so we'll be feedinmg this a decimal number between 0 and 255 at a time
   printf("\n%d is %02X\n",247, 247);
   */


/*

  printf("\n");
  int bitNUmber = 32;
  int sint = -73;
  int unint = sint * -1;
  int roey[bitNUmber];
  convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(unint, roey, bitNUmber);
  int ido[bitNUmber];
  convertUnsignedBinaryNumberArrayOfBitSizeIntoSigned(roey, bitNUmber, ido);
  negateSignedBitArrayOfSize(ido, bitNUmber);
  printf("\n");
  for (int k = bitNUmber-1; k >= 0; k--)
  {
      printf("%d", ido[k]);
  }
  printf("\n");
  
*/
// example to how to represent a signed decimal number in 32 bit array using 2 complement method
/*
printf("\n");
int array[32];
convertSignedNumberInto32Bit2ComplimentAndPlaceInside32BitIntArray(-8197, array);
for (int g = 31; g >= 0; g--)
{
    printf("%d", array[g]);
}
printf("\n");
*/

    return 0;
}
