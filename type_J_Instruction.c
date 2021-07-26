#include "type_J_Instruction.h"

struct type_J_Instruction *initNewType_J_InstructionWith(int add, int r, struct operation *aInstruction) {
    struct type_J_Instruction *node = (struct type_J_Instruction*) malloc(1 * sizeof(struct type_J_Instruction));
    node->address = add;
    node->reg = r;
    node->assemblyInstruction = (struct operation*) malloc(1 * sizeof(struct operation));
    node->assemblyInstruction = aInstruction;
    return node;

}

void outputType_J_Instruction(struct type_J_Instruction *instruction) {
    printf("J Type Name '%s' %s %d\n", instruction->assemblyInstruction->opName,
    (instruction->reg == 0) ? "is referenced to label with address" : "is reference to register #",
    instruction->address);
}