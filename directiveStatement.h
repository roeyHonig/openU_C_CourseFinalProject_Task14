#include "commonHeaders.h"
#include "directiveStatementParameter.h"

/*
 * Function:  initNewDirectiveStatementWithHeadParameterAndNameAndStringAndLabel 
 * --------------------
 * Constructor method to initialize directiveStatement structure
 * 
 * headParameter: 1st parameter if this is ".dh", ".dw", ".db" statement.
 * na: name, for example ".dh"
 * strInDirective: asci string for ".asciz" statement.
 * labelInDirective: for ".entry", ".extern"
 *
 * returns: pointer to struct directiveStatement
 */
struct directiveStatement *initNewDirectiveStatementWithHeadParameterAndNameAndStringAndLabel(struct directiveStatementParameter *headParameter, char *na, char *strInDirective, char *labInDirective);

/* 
 * Function:  outputDirectiveStatement 
 * --------------------
 * outputs to the standared output a short description of the statement
 * 
 * statement: a pointer to a directive statement.
 * 
 * returns: void
 */
void outputDirectiveStatement(struct directiveStatement *statement);

/* Declare the struct directiveStatement. */
struct directiveStatement {
    char *name; // ".dh", ".dw", ".db", ".asciz", ".entry", ".extern"
    struct directiveStatementParameter *parameter; // for ".dh", ".dw", ".db" we have a linked list of parameters which are integer numbers
    char *stringInDirective; // for ".asciz"
    char *labelInDirective;  // for ".entry", ".extern"
};