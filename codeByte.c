#include "codeByte.h"

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
        for (int i = 0; i < 8; i++)
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
       for (int i = 7; i >= 0; i--)
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
}

void outputcodeBytesInHexadecimalBeginingAt(struct codeByte *firstCodeByte) {
    struct codeByte* tmp;
    int posIndex = 0;
   while (firstCodeByte != NULL)
    {
       tmp = firstCodeByte;
       firstCodeByte = firstCodeByte->next;
       int decimalNumber = 0;
       for (int i = 7; i >= 0; i--)
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
}