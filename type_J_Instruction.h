#include "operation.h"
#include "commonHeaders.h"

/* 
 * Function:  initNewType_J_InstructionWith 
 * --------------------
 * Constructor method to initialize type_J_Instruction structure
 * 
 * add: an integer between 0 and pow(2,25)-1 representing an address in memory.
 * r: an integer 0 or 1
 * aInstruction: a pointer to a struct operation.
 * 
 * returns: pointer to struct type_I_Instruction
 */
struct type_J_Instruction *initNewType_J_InstructionWith(int add, int r, struct operation *aInstruction);

/* 
 * Function:  outputType_J_Instruction 
 * --------------------
 * outputs to the standared output a short description of the instruction
 * 
 * instruction: a pointer to a J type instruction.
 * 
 * returns: void
 */
void outputType_J_Instruction(struct type_J_Instruction *instruction);

/* Declare the struct type_J_Instruction. */
struct type_J_Instruction {
    // registers are integers between 0-31
    // 25 bit unsigned int. if reg is 1, address is just the number of the register. if reg is 0 address is the number of the address of the label.
    // if the label is external, the number is 0 (25 0's)
    // reg is suppose to be 1 bit 0 or 1
    int address;
    int reg;
    struct operation *assemblyInstruction;
};