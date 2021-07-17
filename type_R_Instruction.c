#include "type_R_Instruction.h"

struct type_R_Instruction *initNewType_R_InstructionWith(int rs, int rt, int rd, struct operation *aInstruction) {
    struct type_R_Instruction *node = (struct type_R_Instruction*) malloc(1 * sizeof(struct type_R_Instruction));
    node->registerRt = rt;
    node->registerRd = rd;
    node->registerRs = rs;
    node->assemblyInstruction = (struct operation*) malloc(1 * sizeof(struct operation));
    node->assemblyInstruction = aInstruction;
    return node;
}

void outputType_R_Instruction(struct type_R_Instruction *instruction) {
    printf("R Type Name '%s' has rt register %d and rd register %d and rs register %d\n", instruction->assemblyInstruction->opName, instruction->registerRt, instruction->registerRd, instruction->registerRs);
}
