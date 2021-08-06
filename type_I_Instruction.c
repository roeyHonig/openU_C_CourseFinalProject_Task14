#include "type_I_Instruction.h"

void setTheBinaryRepresentationOfInstructionI(struct type_I_Instruction *instruction);

struct type_I_Instruction *initNewType_I_InstructionWith(int rs, int rt, short im, struct operation *aInstruction) {
    struct type_I_Instruction *node = (struct type_I_Instruction*) malloc(1 * sizeof(struct type_I_Instruction));
    node->registerRt = rt;
    node->immed = im;
    node->registerRs = rs;
    node->assemblyInstruction = (struct operation*) malloc(1 * sizeof(struct operation));
    node->assemblyInstruction = aInstruction;
    setTheBinaryRepresentationOfInstructionI(node);
    return node;

}

void outputType_I_Instruction(struct type_I_Instruction *instruction) {
    printf("I Type Name '%s' has rt register %d and rs register %d and an immediate value %d\n", instruction->assemblyInstruction->opName, instruction->registerRt, instruction->registerRs, instruction->immed);
    printf("The binary 32 bit representation for this instruction is: ");
    int j;
    for (j = 32-1; j >= 0; j=j-8)
    {
        printf("%d%d%d%d%d%d%d%d ", instruction->binary32BitCode[j],instruction->binary32BitCode[j-1],instruction->binary32BitCode[j-2],instruction->binary32BitCode[j-3],instruction->binary32BitCode[j-4],instruction->binary32BitCode[j-5],instruction->binary32BitCode[j-6],instruction->binary32BitCode[j-7]);
    }
    printf("\n");
}

void setTheBinaryRepresentationOfInstructionI(struct type_I_Instruction *instruction) {
        int i;
        // bit 0 : 15
        int adress[15] = {0};
        int adressIn2Complement[16] = {0};
        if (instruction->immed >= 0) {
            int immedAsInt = instruction->immed;
            convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(immedAsInt,adress, 15);
            convertUnsignedBinaryNumberArrayOfBitSizeIntoSigned(adress, 15, adressIn2Complement);
        } else {
            int immedAsInt = (-1) * instruction->immed;
            convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(immedAsInt,adress, 15);            
            convertUnsignedBinaryNumberArrayOfBitSizeIntoSigned(adress, 15, adressIn2Complement);
            negateSignedBitArrayOfSize(adressIn2Complement, 16);
        }
        for (i = 0; i < 16; i++)
        {
            instruction->binary32BitCode[i] = adressIn2Complement[i];
        } 
        // bit 16 : 20
        int rt[5];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->registerRt,rt, 5);
        for (i =16; i < 21; i++)
        {
            instruction->binary32BitCode[i] = rt[i-16];
        }  
        // bit 21 : 25
        int rs[5];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->registerRs,rs, 5);
        for (i =21; i < 26; i++)
        {
            instruction->binary32BitCode[i] = rs[i-21];
        }  
        // bit 26 : 31
        int opcode[6];
        convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(instruction->assemblyInstruction->base10opCode,opcode, 6);
        for (i =26; i < 32; i++)
        {
            instruction->binary32BitCode[i] = opcode[i-26];
        } 
     
}