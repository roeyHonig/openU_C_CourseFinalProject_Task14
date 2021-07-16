
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
struct type_R_Instruction *initNewType_R_InstructionWith(int rt, int rd, int rs, struct operation *aInstruction);

/* Declare the struct type_R_Instruction. */
struct type_R_Instruction {
    // registers are integers between 0-31
    int registerRt;
    int registerRd;
    int registerRs;
    struct operation *assemblyInstruction;
};