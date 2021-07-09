#include "symbols.h"

struct symbol *symbolHashTable[HASHSIZE] = { NULL };

struct symbol *initSymbol(char *nameOfSymbol, enum labelLocationInSourceCode locationOfSymbol, int valueOfSymbol) {
    struct symbol *node = (struct symbol*) malloc(1 * sizeof(struct symbol));
    node->name = nameOfSymbol;
    node->location = locationOfSymbol;
    node->value = valueOfSymbol;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

void setSymbol(struct symbol *sm) {
    unsigned int index = hash(sm->name, HASHSIZE);
    struct symbol *existingElement = ((struct symbol *)symbolHashTable[index]);
    // check if position is free
    if (existingElement == NULL)
    {
        symbolHashTable[index] = sm;
    } else {
        // loop over all elements in existing position until you reach the last one
        // Append sm to the last element
        // If any elements name is similar to sm.name we don't append!
        struct symbol *tmp;
        do
        {
            tmp = existingElement;
            if (strcmp(tmp->name, sm->name) == 0)
                return; // Duplicate record
            existingElement = existingElement->next;
        } while (existingElement != NULL);
        tmp->next = (struct symbol*) malloc(1 * sizeof(struct symbol));
        tmp->next = sm;
        sm->previous = (struct symbol*) malloc(1 * sizeof(struct symbol));
        sm->previous = tmp;
    }
}

struct symbol *getSymbolWithName(char *symbolName) {
    unsigned int index = hash(symbolName, HASHSIZE);
    struct symbol *existingElement = ((struct symbol *)symbolHashTable[index]);
    if (existingElement != NULL)
    {
        // loop over all elements in existing position until you reach an element with same name or the last one.
        struct symbol *tmp;
        do
        {
            tmp = existingElement;
            if (strcmp(tmp->name, symbolName) == 0)
                return tmp;
            existingElement = existingElement->next;
        } while (existingElement != NULL);
        return NULL;
    } else {
        return NULL;
    }
}

void symbolToString(struct symbol *sm) {
    char *loc;
    switch (sm->location)
    {
    case directiveStatement:
        loc = "located in a directive type statement";
        break;
    default:
         loc = "located in an instruction type statement";
        break;
    }
    printf("Label name: %s is %s and value: %d \n",sm->name, loc, sm->value);
}

void outputSymbolsHashTable() {
    for (int index = 0; index < HASHSIZE; index++)
    {
        struct symbol *existingElement = ((struct symbol *)symbolHashTable[index]);
        if (existingElement != NULL) {
            struct symbol *tmp;
            do
            {
                tmp = existingElement;
                symbolToString(tmp);
                existingElement = existingElement->next;
            } while (existingElement != NULL);
        }
    }
}

void nullifySymbolsHashTable() {
    for (int index = 0; index < HASHSIZE; index++)
        symbolHashTable[index] = NULL;
}