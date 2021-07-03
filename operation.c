#include "operation.h"
// Operations in our assembly language.
// -1 in the funct field (3rd column) is a non relevent value for this specific operation
#define addOperation "add", 'R', 1, 0
#define subOperation "sub", 'R', 2, 0
#define andOperation "and", 'R', 3, 0
#define orOperation "or", 'R', 4, 0
#define norOperation "nor", 'R', 5, 0

#define moveOperation "move", 'R', 1, 1
#define mvhiOperation "mvhi", 'R', 2, 1
#define mvloOperation "mvlo", 'R', 3, 1
#define addiOperation "addi", 'I', -1, 10
#define subiOperation "subi", 'I', -1, 11

#define andiOperation "andi", 'I', -1, 12
#define oriOperation "ori", 'I', -1, 13
#define noriOperation "nori", 'I', -1, 14
#define bneOperation "bne", 'I', -1, 15
#define beqOperation "beq", 'I', -1, 16

#define bltOperation "blt", 'I', -1, 17
#define bgtOperation "bgt", 'I', -1, 18
#define lbOperation "lb", 'I', -1, 19
#define sbOperation "sb", 'I', -1, 20
#define lwOperation "lw", 'I', -1, 21

#define swOperation "sw", 'I', -1, 22
#define lhOperation "lh", 'I', -1, 23
#define shOperation "sh", 'I', -1, 24
#define jmpOperation "jmp", 'J', -1, 30
#define laOperation "la", 'J', -1, 31

#define callOperation "call", 'J', -1, 32
#define stopOperation "stop", 'J', -1, 63

struct operation *operationsHashTable[HASHSIZE] = { NULL };

struct operation *initAnOperation(char *name, char type, int funct, int code) {
    struct operation *node = (struct operation*) malloc(1 * sizeof(struct operation));
    node->opName = name;
    node->opType = type;
    node->base10Funct = funct;
    node->base10opCode = code;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

void setOperation(struct operation *op) {
    unsigned int index = hash(op->opName, HASHSIZE);
    struct operation *existingElement = ((struct operation *)operationsHashTable[index]);
    // check if position is free
    if (existingElement == NULL)
    {
        operationsHashTable[index] = op;
    } else {
        // loop over all elements in existing position until you reach the last one
        // Append op to the last element
        // If any elements opName is similar to op.opName, we don't append!
        struct operation *tmp;
        do
        {
            tmp = existingElement;
            if (strcmp(tmp->opName, op->opName) == 0)
                return; // Duplicate record
            existingElement = existingElement->next;
        } while (existingElement != NULL);
        tmp->next = (struct operation*) malloc(1 * sizeof(struct operation));
        tmp->next = op;
        op->previous = (struct operation*) malloc(1 * sizeof(struct operation));
        op->previous = tmp;
    }
}

void initOperationsHashTable() {
    setOperation(initAnOperation(addOperation));
    setOperation(initAnOperation(subOperation));
    setOperation(initAnOperation(andOperation));
    setOperation(initAnOperation(orOperation));
    setOperation(initAnOperation(norOperation));
    setOperation(initAnOperation(moveOperation));
    setOperation(initAnOperation(mvhiOperation));
    setOperation(initAnOperation(mvloOperation));
    setOperation(initAnOperation(addiOperation));
    setOperation(initAnOperation(subiOperation));
    setOperation(initAnOperation(andiOperation));
    setOperation(initAnOperation(oriOperation));
    setOperation(initAnOperation(noriOperation));
    setOperation(initAnOperation(bneOperation));
    setOperation(initAnOperation(beqOperation));
    setOperation(initAnOperation(bltOperation));
    setOperation(initAnOperation(bgtOperation));
    setOperation(initAnOperation(lbOperation));
    setOperation(initAnOperation(sbOperation));
    setOperation(initAnOperation(lwOperation));
    setOperation(initAnOperation(swOperation));
    setOperation(initAnOperation(lhOperation));
    setOperation(initAnOperation(shOperation));
    setOperation(initAnOperation(jmpOperation));
    setOperation(initAnOperation(laOperation));
    setOperation(initAnOperation(callOperation));
    setOperation(initAnOperation(stopOperation));

}

struct operation *getOperationWithOpName(char *name) {
    unsigned int index = hash(name, HASHSIZE);
    struct operation *existingElement = ((struct operation *)operationsHashTable[index]);
    if (existingElement != NULL)
    {
        // loop over all elements in existing position until you reach an element with same name or the last one.
        struct operation *tmp;
        do
        {
            tmp = existingElement;
            if (strcmp(tmp->opName, name) == 0)
                return tmp;
            existingElement = existingElement->next;
        } while (existingElement != NULL);
        return NULL;
    } else {
        return NULL;
    }

}

char *toString(struct operation *op) {
    if (op != NULL && op->base10Funct > 0) 
        printf("This is an Assembly language operation with Name: %s, Type: %c, functCode: %d and opCode: %d\n", op->opName, op->opType, op->base10Funct, op->base10opCode);
    if (op != NULL && op->base10Funct <= 0) 
        printf("This is an Assembly language operation with Name: %s, Type: %c and opCode: %d\n", op->opName, op->opType, op->base10opCode);    
}

void outputOperationsHashTable() {
    for (int index = 0; index < HASHSIZE; index++)
    {
        struct operation *existingElement = ((struct operation *)operationsHashTable[index]);
        if (existingElement != NULL) {
            struct operation *tmp;
            do
            {
                tmp = existingElement;
                toString(tmp);
                existingElement = existingElement->next;
            } while (existingElement != NULL);
        }
    }
    
    
}