#include "type_J_Instruction.h"

void setTheBinaryRepresentationOfInstructionJ(struct type_J_Instruction *instruction);

struct type_J_Instruction *initNewType_J_InstructionWith(int add, int r, struct operation *aInstruction) {
    struct type_J_Instruction *node = (struct type_J_Instruction*) malloc(1 * sizeof(struct type_J_Instruction));
    node->address = add;
    node->reg = r;
    node->assemblyInstruction = (struct operation*) malloc(1 * sizeof(struct operation));
    node->assemblyInstruction = aInstruction;
    setTheBinaryRepresentationOfInstructionJ(node);
    return node;
}

void outputType_J_Instruction(struct type_J_Instruction *instruction) {
    printf("J Type Name '%s' %s %d\n", instruction->assemblyInstruction->opName,
    (instruction->reg == 0) ? "is referenced to label with address" : "is reference to register #",
    instruction->address);
    printf("The binary 32 bit representation for this instruction is: ");
    int j;
    for (j = 32-1; j >= 0; j=j-8)
    {
        printf("%d%d%d%d%d%d%d%d ", instruction->binary32BitCode[j],instruction->binary32BitCode[j-1],instruction->binary32BitCode[j-2],instruction->binary32BitCode[j-3],instruction->binary32BitCode[j-4],instruction->binary32BitCode[j-5],instruction->binary32BitCode[j-6],instruction->binary32BitCode[j-7]);
    }
    printf("\n");
}

void setTheBinaryRepresentationOfInstructionJ(struct type_J_Instruction *instruction) {
    int i;
        // bit 0 : 24
        int adress[25] = {0};
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->address,adress, 25);
        for (i = 0; i < 25; i++)
        {
            instruction->binary32BitCode[i] = adress[i];
        } 
        // bit 25 
        instruction->binary32BitCode[25] = (instruction->reg == 1) ? 1: 0;
        
        // bit 26 : 31
        int opcode[6];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->assemblyInstruction->base10opCode,opcode, 6);
        for (i =26; i < 32; i++)
        {
            instruction->binary32BitCode[i] = opcode[i-26];
        } 
}