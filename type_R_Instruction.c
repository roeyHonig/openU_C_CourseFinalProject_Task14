#include "type_R_Instruction.h"

struct type_R_Instruction *initNewType_R_InstructionWith(int rt, int rd, int rs, struct operation *aInstruction) {
    struct type_R_Instruction *node = (struct type_R_Instruction*) malloc(1 * sizeof(struct type_R_Instruction));
    node->registerRt = rt;
    node->registerRd = rd;
    node->registerRs = rs;
    node->assemblyInstruction = (struct operation*) malloc(1 * sizeof(struct operation));
    node->assemblyInstruction = aInstruction;
    return node;
}
