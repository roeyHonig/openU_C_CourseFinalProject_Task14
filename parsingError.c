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
    case notRecognizableAssemblyLanguageStatement:
        printf("Line #%d doesn't contain any assembly language source code reserved words.\n", lineNumber);
        break; 
    case badLabelFormat:
        printf("Bad format for label on line #%d.\n", lineNumber);
        break; 
    case wrongRegisterNumber:
        printf("Wrong register number on line #%d.\n", lineNumber); 
        break; 
    case immediateOverflow:
        printf("On line #%d, immediate value too big or too small. Should be between %d and %d.\n", lineNumber, INT16_MIN, INT16_MAX); 
        break; 
    case badImmediateFormat:
        printf("Bad format for immediate on line #%d.\n", lineNumber);
        break; 
    case badDirectiveStatementParameterFormat:
        printf("Bad format for parameter on line #%d.\n", lineNumber);
        break; 
    case noParametersInDirectiveStatement:
        printf("No parameter on line #%d.\n", lineNumber);
        break; 
    case parameterOverflow:
        printf("parameter is out of range for directive statement on line #%d.\n", lineNumber);
        break; 
    case badDirectiveStatementAscizFormat:
        printf("Bad format for asciz statement on line #%d.\n", lineNumber);
        break;
    default:
        printf("generic error description");
        break;
    }
}