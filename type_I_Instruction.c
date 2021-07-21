#include "type_I_Instruction.h"

struct type_I_Instruction *initNewType_I_InstructionWith(int rs, int rt, short im, struct operation *aInstruction) {
    struct type_I_Instruction *node = (struct type_I_Instruction*) malloc(1 * sizeof(struct type_I_Instruction));
    node->registerRt = rt;
    node->immed = im;
    node->registerRs = rs;
    node->assemblyInstruction = (struct operation*) malloc(1 * sizeof(struct operation));
    node->assemblyInstruction = aInstruction;
    return node;

}

void outputType_I_Instruction(struct type_I_Instruction *instruction) {
    printf("I Type Name '%s' has rt register %d and rs register %d and an immediate value %d\n", instruction->assemblyInstruction->opName, instruction->registerRt, instruction->registerRs, instruction->immed);
}