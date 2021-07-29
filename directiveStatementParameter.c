#include "directiveStatementParameter.h"

struct directiveStatementParameter *initNewDirectiveStatementParameterWithNumberByteSizeAndLinkTo(int num, int bSize, struct directiveStatementParameter *previousParameter) {
    struct directiveStatementParameter *node = (struct directiveStatementParameter*) malloc(1 * sizeof(struct directiveStatementParameter));
    node->number = num;
    node->byteSize = bSize;
    node->next = NULL;
    node->previous = previousParameter;
    if (previousParameter != NULL) {
        previousParameter->next = (struct directiveStatementParameter*) malloc(1 * sizeof(struct directiveStatementParameter));
        previousParameter->next = node;
        node->head = previousParameter->head;
    } else {
        node->head = node;
    }
    return node;
}