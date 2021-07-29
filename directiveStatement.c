#import "directiveStatement.h"

struct directiveStatement *initNewDirectiveStatementWithHeadParameterAndNameAndStringAndLabel(struct directiveStatementParameter *headParameter, char *na, char *strInDirective, char *labInDirective) {
    struct directiveStatement *node = (struct directiveStatement*) malloc(1 * sizeof(struct directiveStatement));
    node->name = na;
    node->parameter = headParameter;
    node->stringInDirective = strInDirective;
    node->labelInDirective = labInDirective;
    return node;
}

void outputDirectiveStatement(struct directiveStatement *statement) {
    // ".dh", ".dw", ".db"
    if (strcmp(statement->name, ".dh") == 0 || strcmp(statement->name, ".dw") == 0 || strcmp(statement->name, ".db") == 0) {
        printf("Directive Statement Name %s has the following %d byte size parameters: ", statement->name, statement->parameter->byteSize);
        struct directiveStatementParameter* tmp;
        struct directiveStatementParameter* first = statement->parameter;
        while (first != NULL)
        {
            tmp = first;
            first = first->next;
            printf("%d ", tmp->number);
        }
        printf("\n");
    }
}