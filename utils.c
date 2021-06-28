#include "utils.h"
#include "commonHeaders.h"

void printLineBeginingAt(char *t) {
   // Base case
   if (*t == '\0') {
       printf("\n");
       return;
   }
   printf("%c", *t);
   printLineBeginingAt(++t);
}