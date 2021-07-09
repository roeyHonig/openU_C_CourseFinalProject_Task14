#include "parsingError.h"

void printErrorDescriptionFor(int lineNumber, enum parsingError error) {
    switch (error)
    {
    case noErrorsFound:
        break;
    case lineTooLong:
        printf("Line #%d is too long. Must be under %d characters\n", lineNumber, maxNumberOfCharacters);
        break;
    case useOfReservedWord:
        printf("Illegal use of assembly language reserved word on line #%d.\n", lineNumber);
        break;
    case comment:
        break;
    case illegalUseOfSemiColon:
        printf("Illigeal use of ; on line #%d.\n", lineNumber);
        break;
    default:
        printf("generic error description");
        break;
    }
}