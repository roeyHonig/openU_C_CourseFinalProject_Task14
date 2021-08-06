#include "codeByte.h"

int computeTotalNumberOfBytesFor(struct codeByte *firstByte);

struct codeByte *initNewCodeByteFrom32BitArrayInPositionAndLinkTo(int binaryRepresentation[], int position, struct codeByte *previousCodeByte) {
    struct codeByte *node = (struct codeByte*) malloc(1 * sizeof(struct codeByte));
    node->next = NULL;
    node->previous = previousCodeByte;
    if (previousCodeByte != NULL) {
        previousCodeByte->next = (struct codeByte*) malloc(1 * sizeof(struct codeByte));
        previousCodeByte->next = node;
        node->head = previousCodeByte->head;
    } else {
        node->head = node;
    }
    if (position >= 1 && position <= 4) {
        int startIndex = position * 8 - 8;
        int i;
        for (i = 0; i < 8; i++)
        {
            node->binary8BitCode[i] = binaryRepresentation[startIndex + i];
        }
    }
    return node;
}

void outputcodeBytesBeginingAt(struct codeByte *firstCodeByte) {
    struct codeByte* tmp;
    int posIndex = 0;
   while (firstCodeByte != NULL)
    {
       tmp = firstCodeByte;
       firstCodeByte = firstCodeByte->next;
       int i;
       for (i = 7; i >= 0; i--)
       {
           printf("%d", tmp->binary8BitCode[i]);
       }
       posIndex++;
       if ((posIndex % 4 ) == 0) {
           printf("\n");
       } else {
           printf(" ");
       }  
    }
    firstCodeByte = tmp->head;
}

void outputcodeBytesInHexadecimalBeginingAt(struct codeByte *firstCodeByte) {
    struct codeByte* tmp;
    int posIndex = 0;
   while (firstCodeByte != NULL)
    {
       tmp = firstCodeByte;
       firstCodeByte = firstCodeByte->next;
       int decimalNumber = 0;
       int i;
       for (i = 7; i >= 0; i--)
       {
           decimalNumber = decimalNumber + ((int)(pow(2, i) * tmp->binary8BitCode[i]));
       }
       printf("%02X",decimalNumber);
       posIndex++;
       if ((posIndex % 4 ) == 0) {
           printf("\n");
       } else {
           printf(" ");
       }  
    }
    firstCodeByte = tmp->head;
}

void outputCompleteCodeAndDataBytesInHexadecimalBeginingAtMemoryAddressAndFirstCodeByteAndFirstDataByteint(int memAddress, struct codeByte *firstCodeByte, struct codeByte *firstDataByte) {
    int numberOfCodeBytes = computeTotalNumberOfBytesFor(firstCodeByte);
    int numberOfDataBytes = computeTotalNumberOfBytesFor(firstDataByte);
    printf("\n---object file----\n");
    printf("\t\t%d %d\n",numberOfCodeBytes,  numberOfDataBytes);
    
    struct codeByte* tmp;
    int posIndex = 0;
    boolean newLine = true;
   while (firstCodeByte != NULL)
    {
        if (newLine) {
            printf("%d ", memAddress);
            memAddress = memAddress + 4;
            newLine = false;
        }
        
       tmp = firstCodeByte;
       firstCodeByte = firstCodeByte->next;
       int decimalNumber = 0;
       int i;
       for (i = 7; i >= 0; i--)
       {
           decimalNumber = decimalNumber + ((int)(pow(2, i) * tmp->binary8BitCode[i]));
       }
       printf("%02X",decimalNumber);
       posIndex++;
       if ((posIndex % 4 ) == 0) {
           printf("\n");
           newLine = true;
       } else {
           printf(" ");
       }  
    }
    firstCodeByte = tmp->head;

    struct codeByte* tmpData;
    posIndex = 0;
    newLine = true;
   while (firstDataByte != NULL)
    {
        if (newLine) {
            printf("%d ", memAddress);
            memAddress = memAddress + 4;
            newLine = false;
        }
        
       tmpData = firstDataByte;
       firstDataByte = firstDataByte->next;
       int decimalNumber = 0;
       int i;
       for (i = 7; i >= 0; i--)
       {
           decimalNumber = decimalNumber + ((int)(pow(2, i) * tmpData->binary8BitCode[i]));
       }
       printf("%02X",decimalNumber);
       posIndex++;
       if ((posIndex % 4 ) == 0) {
           printf("\n");
           newLine = true;
       } else {
           printf(" ");
       }  
    }
    firstDataByte = tmp->head;
    

}

int computeTotalNumberOfBytesFor(struct codeByte *firstByte) {
    int numberOfCodeBytes = 0;
    struct codeByte* tmp;
   while (firstByte != NULL)
    {
       tmp = firstByte;
       firstByte = firstByte->next;
       numberOfCodeBytes++;
    }
    firstByte = tmp->head;
    return numberOfCodeBytes;
}