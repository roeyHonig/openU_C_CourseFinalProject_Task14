final:
	gcc assembler.c sourceCodeSentence.c utils.c operation.c parsingError.c symbols.c type_R_Instruction.c type_I_Instruction.c type_J_Instruction.c -Wall -ansi -pedantic  -o assembler