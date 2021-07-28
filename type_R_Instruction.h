
#include "operation.h"
#include "commonHeaders.h"
/* 
 * Function:  initNewType_R_InstructionWith 
 * --------------------
 * Constructor method to initialize type_R_Instruction structure
 * 
 * rt: an integer between 0 and 31 representing the rt register.
 * rd: an integer between 0 and 31 representing the rd register.
 * rs: an integer between 0 and 31 representing the rs register.
 * aInstruction: a pointer to a struct operation.
 * 
 * returns: pointer to struct type_R_Instruction
 */
struct type_R_Instruction *initNewType_R_InstructionWith(int rs, int rt, int rd, struct operation *aInstruction);

/* 
 * Function:  outputType_R_Instruction 
 * --------------------
 * outputs to the standared output a short description of the instruction
 * 
 * instruction: a pointer to a R type instruction.
 * 
 * returns: void
 */
void outputType_R_Instruction(struct type_R_Instruction *instruction);

/* Declare the struct type_R_Instruction. */
struct type_R_Instruction {
    // registers are integers between 0-31
    int registerRt;
    int registerRd;
    int registerRs;
    struct operation *assemblyInstruction;
    int binary32BitCode[32];
};