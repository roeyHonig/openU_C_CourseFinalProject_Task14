#include "symbols.h"
#include "parsingError.h"

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

int setSymbol(struct symbol *sm) {
    unsigned int index = hash(sm->name, HASHSIZE);
    struct symbol *existingElement = ((struct symbol *)symbolHashTable[index]);
    // check if position is free
    if (existingElement == NULL)
    {
        symbolHashTable[index] = sm;
        return noErrorsFound;
    } else {
        // loop over all elements in existing position until you reach the last one
        // Append sm to the last element
        // If any elements name is similar to sm.name and they have the same location (meaning they're both labels or both data variables) we don't append!
        struct symbol *tmp;
        do
        {
            tmp = existingElement;
            if (strcmp(tmp->name, sm->name) == 0 && sm->location == tmp->location)
                return duplicateLabel; // Duplicate record

            if (strcmp(tmp->name, sm->name) == 0 && sm->location == external && tmp->location == instructionStatement)
                return duplicateLabel; // Duplicate record. cann't have external label with same name to label at the begining of directive statement or instruction statement
            if (strcmp(tmp->name, sm->name) == 0 && sm->location == external && tmp->location == directiveStatement)
                return duplicateLabel; // Duplicate record. cann't have external label with same name to label at the begining of directive statement or instruction statement

            if (strcmp(tmp->name, sm->name) == 0 && sm->location == instructionStatement && tmp->location == external)
                return duplicateLabel; // Duplicate record. cann't have external label with same name to label at the begining of directive statement or instruction statement
            if (strcmp(tmp->name, sm->name) == 0 && sm->location == directiveStatement && tmp->location == external)
                return duplicateLabel; // Duplicate record. cann't have external label with same name to label at the begining of directive statement or instruction statement

            if (strcmp(tmp->name, sm->name) == 0 && sm->location == directiveStatement && tmp->location == instructionStatement)
                return duplicateLabel; // Duplicate record. cann't have same label at the begining of directive statement and instruction statement
            if (strcmp(tmp->name, sm->name) == 0 && sm->location == instructionStatement && tmp->location == directiveStatement)
                return duplicateLabel; // Duplicate record. cann't have same label at the begining of directive statement and instruction statement

            if (strcmp(tmp->name, sm->name) == 0 && sm->location == entry && tmp->location == external)
                return duplicateLabel; // Duplicate record, entry labels can't be the same as external labels
            if (strcmp(tmp->name, sm->name) == 0 && sm->location == external && tmp->location == entry)
                return duplicateLabel; // Duplicate record, entry labels can't be the same as external labels

            existingElement = existingElement->next;
        } while (existingElement != NULL);
        tmp->next = (struct symbol*) malloc(1 * sizeof(struct symbol));
        tmp->next = sm;
        sm->previous = (struct symbol*) malloc(1 * sizeof(struct symbol));
        sm->previous = tmp;
        return noErrorsFound;
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

struct symbol *getSymbolWithNameAndLocation(char *symbolName, enum labelLocationInSourceCode location) {
    unsigned int index = hash(symbolName, HASHSIZE);
    struct symbol *existingElement = ((struct symbol *)symbolHashTable[index]);
    if (existingElement != NULL)
    {
        // loop over all elements in existing position until you reach an element with same name or the last one.
        struct symbol *tmp;
        do
        {
            tmp = existingElement;
            if (strcmp(tmp->name, symbolName) == 0 && tmp->location == location)
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
    case instructionStatement:
        loc = "located in a instruction type statement";
        break;
    case entry:
        loc = "located as an entry directive statement";
        break;
    case external:
        loc = "is an external directive statement";
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

void incrementDirectiveTypeSymbolsValueBy(int increment) {
    for (int index = 0; index < HASHSIZE; index++)
    {
        struct symbol *existingElement = ((struct symbol *)symbolHashTable[index]);
        if (existingElement != NULL) {
            struct symbol *tmp;
            do
            {
                tmp = existingElement;
                existingElement = existingElement->next;
                if (tmp->location == directiveStatement) {
                    tmp->value = tmp->value + increment;
                } 
            } while (existingElement != NULL);
        }
    }
}

void updateEntryTypeSymbolsValueBy() {
    for (int index = 0; index < HASHSIZE; index++)
    {
        struct symbol *existingElement = ((struct symbol *)symbolHashTable[index]);
        if (existingElement != NULL) {
            struct symbol *tmp;
            do
            {
                tmp = existingElement;
                existingElement = existingElement->next;
                if (tmp->location == entry) {
                    struct symbol *instructionTypeSymbol = getSymbolWithNameAndLocation(tmp->name, instructionStatement);
                    struct symbol *directiveTypeSymbol = getSymbolWithNameAndLocation(tmp->name, directiveStatement);
                    if (instructionTypeSymbol != NULL) {
                        tmp->value = instructionTypeSymbol->value;
                    } else if (directiveTypeSymbol != NULL) {
                        tmp->value = directiveTypeSymbol->value;
                    } else {
                        return;
                    }
                } 
            } while (existingElement != NULL);
        }
    }

}