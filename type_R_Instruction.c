#include "type_R_Instruction.h"

void setTheBinaryRepresentationOfInstruction(struct type_R_Instruction *instruction);

struct type_R_Instruction *initNewType_R_InstructionWith(int rs, int rt, int rd, struct operation *aInstruction) {
    struct type_R_Instruction *node = (struct type_R_Instruction*) malloc(1 * sizeof(struct type_R_Instruction));
    node->registerRt = rt;
    node->registerRd = rd;
    node->registerRs = rs;
    node->assemblyInstruction = (struct operation*) malloc(1 * sizeof(struct operation));
    node->assemblyInstruction = aInstruction;
    setTheBinaryRepresentationOfInstruction(node);
    return node;
}

void outputType_R_Instruction(struct type_R_Instruction *instruction) {
    printf("R Type Name '%s' has rt register %d and rd register %d and rs register %d\n", instruction->assemblyInstruction->opName, instruction->registerRt, instruction->registerRd, instruction->registerRs);
    printf("The binary 32 bit representation for this instruction is: ");
    int j;
    for (j = 32-1; j >= 0; j=j-8)
    {
        printf("%d%d%d%d%d%d%d%d ", instruction->binary32BitCode[j],instruction->binary32BitCode[j-1],instruction->binary32BitCode[j-2],instruction->binary32BitCode[j-3],instruction->binary32BitCode[j-4],instruction->binary32BitCode[j-5],instruction->binary32BitCode[j-6],instruction->binary32BitCode[j-7]);
    }
    printf("\n");
}

void setTheBinaryRepresentationOfInstruction(struct type_R_Instruction *instruction) {
        /* bit 0 : 5 */
        int i;
        for (i = 0; i < 6; i++)
        {
            instruction->binary32BitCode[i] = 0;
        }
        /* bit 6 : 10 */
        int funct[5];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->assemblyInstruction->base10Funct,funct, 5);
        for (i =6; i < 11; i++)
        {
            instruction->binary32BitCode[i] = funct[i-6];
        }  
        /* bit 11 : 15 */
        int rd[5];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->registerRd,rd, 5);
        for (i =11; i < 16; i++)
        {
            instruction->binary32BitCode[i] = rd[i-11];
        }  
        /* bit 16 : 20 */
        int rt[5];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->registerRt,rt, 5);
        for (i =16; i < 21; i++)
        {
            instruction->binary32BitCode[i] = rt[i-16];
        }  
        /* bit 21 : 25 */
        int rs[5];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->registerRs,rs, 5);
        for (i =21; i < 26; i++)
        {
            instruction->binary32BitCode[i] = rs[i-21];
        }  
        /* bit 26 : 31 */
        int opcode[6];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->assemblyInstruction->base10opCode,opcode, 6);
        for (i =26; i < 32; i++)
        {
            instruction->binary32BitCode[i] = opcode[i-26];
        } 
     
}

