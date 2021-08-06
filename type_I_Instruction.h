#include "operation.h"
#include "commonHeaders.h"

/* 
 * Function:  initNewType_I_InstructionWith 
 * --------------------
 * Constructor method to initialize type_I_Instruction structure
 * 
 * rt: an integer between 0 and 31 representing the rt register.
 * im: an integer between INT16_MIN and INT16_MAX representing an immidate value.
 * rs: an integer between 0 and 31 representing the rs register.
 * aInstruction: a pointer to a struct operation.
 * 
 * returns: pointer to struct type_I_Instruction
 */
struct type_I_Instruction *initNewType_I_InstructionWith(int rs, int rt, short im, struct operation *aInstruction);

/* 
 * Function:  outputType_I_Instruction 
 * --------------------
 * outputs to the standared output a short description of the instruction
 * 
 * instruction: a pointer to a I type instruction.
 * 
 * returns: void
 */
void outputType_I_Instruction(struct type_I_Instruction *instruction);

/* Declare the struct type_I_Instruction. */
struct type_I_Instruction {
    /* registers are integers between 0-31 */
    /* immediate are signed numeric values between INT16_MAX and INT16_MIN */
    int registerRt;
    short immed;
    int registerRs;
    struct operation *assemblyInstruction;
    int binary32BitCode[32];
};