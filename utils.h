#define HASHSIZE 101 /* size of hash tables for operations and symbols */
typedef int boolean;
#define true 1
#define false 0

boolean errorsFound; /* flag indicating if compilation errors were found. If so, no need to output the binary code for the corrput source code FILE. */

/*
 * Function:  printLineBeginingAt 
 * --------------------
 * Method to print a line of text begining at char pointer up until the NUL character 
 * 
 * t: char pointer.
 */
void printLineBeginingAt(char *t);

/*
 * Function:  hash 
 * --------------------
 * This is a simple hash functino.  
 * 
 * key: An identifier to allow to get an element out of the hash table.  
 * hSize: The size of the hash table array.
 * 
 * returns: an index of the hash table array.
 */
unsigned int hash(char *key, unsigned int hSize);

/*
 * Function:  isOneOfTheAssemblyLanguageReservedWordsEqualsTo 
 * --------------------
 * This is a simple function to check if a string is one of the assembly language reserved words.  
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isOneOfTheAssemblyLanguageReservedWordsEqualsTo(char *str);

/* 
 * Function:  isRTypeKeywordsPresentInFollowingText 
 * --------------------
 * This is a simple function to check if one of the assembly language, R type, reserved words is present in a string.   
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isRTypeKeywordsPresentInFollowingText(char *str);

/* 
 * Function:  isITypeKeywordsPresentInFollowingText 
 * --------------------
 * This is a simple function to check if one of the assembly language, I type, reserved words is present in a string.   
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isITypeKeywordsPresentInFollowingText(char *str);

/* 
 * Function:  isJTypeKeywordsPresentInFollowingText 
 * --------------------
 * This is a simple function to check if one of the assembly language, J type, reserved words is present in a string.   
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isJTypeKeywordsPresentInFollowingText(char *str);

/* 
 * Function:  isDirectiveTypeKeywordsPresentInFollowingText 
 * --------------------
 * This is a simple function to check if one of the assembly language, directive type, reserved words is present in a string.   
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isDirectiveTypeKeywordsPresentInFollowingText(char *str);

/* 
 * Function:  isLabelSupportedForDirectiveTypeKeywords 
 * --------------------
 * This is a simple function to check if one of the assembly language, directive type, reserved words is present in a string and if it is one of the directives which supports labels at the begining of the statement.   
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isLabelSupportedForDirectiveTypeKeywords(char *str);

/* 
 * Function:  isThereLabelInFollowingTextLine 
 * --------------------
 * This is a simple function to check if the character ':' is present in a string.   
 * 
 * str: a string.  
 * 
 * returns: true or false.
 */
boolean isThereLabelInFollowingTextLine(char *str);

/* 
 * Function:  getLabelInto 
 * --------------------
 * This is a function to extract the label from a string.   
 * 
 * label: pointer to a string in which the function will insert the label name.
 * str: a string to look for the label in.  
 * 
 * returns: true if the function was able to extract correct format label or false otherwise, in which case, the label shouldn't be used!.
 */
boolean getLabelInto(char *label, char* str);

/* 
 * Function:  initAnEmptyStringOfSize 
 * --------------------
 * This is a function to init a char array of certain size + 1 space for the nul character.
 * The function sets all the characters to be, initally, the nul character.   
 * 
 * size: the number of characters.
 * 
 * returns: pointer to the start of the array.
 */
char *initAnEmptyStringOfSize(int size);

/* 
 * Function:  initAnEmptyStringOfSizeAndFillWithChacter 
 * --------------------
 * This is a function to init a char array of certain size + 1 space for the nul character.
 * The function sets all the characters to be, initally, a specific character as passed to the function arguments.   
 * 
 * size: the number of characters.
 * ch: this is the character the entire array will be filled with, except the last character, the nul character. 
 * 
 * returns: pointer to the start of the array.
 */
char *initAnEmptyStringOfSizeAndFillWithChacter(int size, char ch);

/* 
 * Function:  isDigit 
 * --------------------
 * This is a function to check if a char is between '0' and '9'.   
 * 
 * ch: a char pointer to check.  
 * 
 * returns: true or false
 */
boolean isDigit(char *ch);

/* 
 * Function:  isAlphabeticCharacter 
 * --------------------
 * This is a function to check if a char is between 'a' and 'z' or between 'A' and 'Z'.   
 * 
 * ch: a char pointer to check.  
 * 
 * returns: true or false
 */
boolean isAlphabeticCharacter(char *ch);

/* 
 * Function:  isNotAlphabeticCharacter 
 * --------------------
 * This is a function to check if a char is NOT between 'a' and 'z' or between 'A' and 'Z'.   
 * 
 * ch: a char pointer to check.  
 * 
 * returns: true or false
 */
boolean isNotAlphabeticCharacter(char *ch);

/* 
 * Function:  isCharacterEquals 
 * --------------------
 * This is a function to check if a char is equal a specific character.   
 * 
 * ch: a char pointer to check.  
 * eq: a char to chaeck against.
 * 
 * returns: true or false
 */
boolean isCharacterEquals(char *ch, char eq);

/* 
 * Function:  isCharacterEqualsOrCondition 
 * --------------------
 * This is a function to check if a char is equal a specific character or a 2nd specific character.   
 * 
 * ch: a char pointer to check.  
 * eq: a char to chaeck against.
 * eq2: a second char to chaeck against.
 * 
 * returns: true or false
 */
boolean isCharacterEqualsOrCondition(char *ch, char eq, char eq2);

/* 
 * Function:  isCharacterNotEquals 
 * --------------------
 * This is a function to check if a char is not equal a specific character.   
 * 
 * ch: a char pointer to check.  
 * eq: a char to chaeck against.
 * 
 * returns: true or false
 */
boolean isCharacterNotEquals(char *ch, char eq);

/* 
 * Function:  isCharacterNotEqualsOrCondition 
 * --------------------
 * This is a function to check if a char is not equal to a specific character or a 2nd specific character.   
 * 
 * ch: a char pointer to check.  
 * eq: a char to chaeck against.
 * eq2: a second char to chaeck against.
 * 
 * returns: true or false
 */
boolean isCharacterNotEqualsOrCondition(char *ch, char eq, char eq2);

/* 
 * Function:  isNotDigit 
 * --------------------
 * This is a function to check if a char is not between '0' and '9'.   
 * 
 * ch: a char pointer to check.  
 * 
 * returns: true or false
 */
boolean isNotDigit(char *ch);

/* 
 * Function:  isCharacterEqualsTrippleOrCondition 
 * --------------------
 * This is a function to check if a char is equal a specific character or a 2nd specific character or a 3rd specific character.   
 * 
 * ch: a char pointer to check.  
 * eq: a char to chaeck against.
 * eq2: a second char to chaeck against.
 * eq3: a third char to check against.
 * 
 * returns: true or false
 */
boolean isCharacterEqualsTrippleOrCondition(char *ch, char eq, char eq2, char eq3);

/* 
 * Function:  isCharacterNotEqualsTrippleOrCondition 
 * --------------------
 * This is a function to check if a char is not equal to a specific character or a 2nd specific character or a 3rd specific character.   
 * 
 * ch: a char pointer to check.  
 * eq: a char to chaeck against.
 * eq2: a second char to chaeck against.
 * eq3: a third char to check against
 * 
 * returns: true or false
 */
boolean isCharacterNotEqualsTrippleOrCondition(char *ch, char eq, char eq2, char eq3);

/* 
 * Function:  isThereOutOfBoundsRegisterNumberInOneOfTheFollowing 
 * --------------------
 * This is a function to check if one of the 3 registers isn't between 0 - 31
 * 
 * reg1: int representing 1st register.
 * reg2: int representing 2nd register.
 * reg3: int representing 3rd register.
 * 
 * returns: true or false
 */
boolean isThereOutOfBoundsRegisterNumberInOneOfTheFollowing(int reg1, int reg2, int reg3);

/* 
 * Function:  parseRegistersAndImmediateForIType 
 * --------------------
 * This is a function to get the numeric values of 2 registers and an immidate value from the source code sentence text. If the instruction doesn't have numeric value but a label name, the label name will be copied
 * 
 * scTextLine: The source code text.
 * name: the name of the instruction.
 * firstRegister: int representing 1st register.
 * secondRegister: int representing 2nd register.
 * immed: short representing immediate value.
 * labelWithinTheInstruction: branching I instructions have a label as the 3rd field of the instruction. The immeduate value is the distance between the label value and the currect instruction value
 * 
 * returns: 0 if valid registers numeric values and immediate or int value corresponding to the appropriate error code, in which case, the values shouldn't be used!!!
 */
int parseRegistersAndImmediateForIType(char *scTextLine, char *name, int *firstRegister, int *secondRegister, short *immed, char* labelWithinTheInstruction);

/* 
 * Function:  parseRegistersOrLabelForJType 
 * --------------------
 * This is a function to parse a J type instruction. It should set the flag for the use of registers or set the label. 
 * 
 * scTextLine: The source code text.
 * name: the name of the instruction.
 * registerFlag: int representing if the instruction is relative to register or label.
 * address - an int representing register number [0:31] or an address in memory of the label [0:(pow(2,25)-1)]
 * labelWithinTheInstruction:  J instructions can have a label. 
 * 
 * returns: 0 if valid registers numeric values or valid label is present. If error is found, returns non zero int value corresponding to the appropriate error code, in which case, the values shouldn't be used!!!
 */
int parseRegistersOrLabelForJType(char *scTextLine, char *name, int *registerFlag, int *address, char* labelWithinTheInstruction);

/* 
 * Function:  convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize 
 * --------------------
 * This is a function to convert a decimal number to its binary notation in the form of an integer array with only 0 and 1. 
 * Make sure to init the array first to all 0 -> int array[] = {0}  
 * 
 * n: int decimal number.
 * a: an  array of integers to be filled with 0 and 1
 * size: int the size of the array  
 * 
 */
void convertUnsignedDecimalNumberIntoBitBinaryArrayOfSize(int n, int *a, int size);

/* 
 * Function:  convertUnsignedBinaryNumberArrayOfBitSize 
 * --------------------
 * This is a function to convert an array of ints, with size of bits, representing an unsigned decimal number to an array of size + 1 bits representing the same number but in a 2 compliment notation.  
 * 
 * a: an  array filled with 0 and 1
 * size: int the size of the array a
 * b: an array larger then array a by 1 most significant bit
 * 
 */
void convertUnsignedBinaryNumberArrayOfBitSizeIntoSigned(int *a, int size, int *b);

/* 
 * Function:  negateSignedBitArrayOfSize 
 * --------------------
 * This is a function to convert an array of ints, representing a signed binary number to an array representing the negation of that number
 * 
 * a: an  array filled with 0 and 1
 * size: int the size of the array a
 * 
 */
void negateSignedBitArrayOfSize(int *a, int size);

/* 
 * Function:  parseParametersOrAsciiStringOrLabelForDirectiveStatement  
 * --------------------
 * This is a function to get parameters of a directive statement, which can be an array of integers, or single ascii string between quatition marks or a simple label
 * 
 * scTextLine: The source code text.
 * name: the name of the instruction.
 * firstPa: a pointer to the start of an integer array which will hold the integers od directive statement type .db, d.h, .dw
 * indexOfParametersArray: The parsing function fills the integer array with numbers based on the parsed statement, so this index keeps track of how many parameters we actually have. Will be needed to accurately init the statement later
 * byteSizeOfEachParameter: 1 byte , 2 bytes or 4 bytes.
 * str: the string in a .asciz statement
 * label: the string in an .extern \ .entry statements 
 * 
 * returns: 0 if successful parsing or int value corresponding to the appropriate error code, in which case, the values shouldn't be used!!!
 */
int parseParametersOrAsciiStringOrLabelForDirectiveStatement(char *scTextLine, char *name, int *firstPa, int *indexOfParametersArray, int *byteSizeOfEachParameter, char *str, char *label);

/* 
 * Function:  convertSignedNumberInto32Bit2ComplimentAndPlaceInside32BitIntArray 
 * --------------------
 * This is a function to convert a signed decimal number into a 32 bit integer array which represents the number in the 2 compliment method
 * 
 * number: an  integer between MIN_OF(uint32_t) and MAX_OF(uint32_t)
 * arr: an int array of 32 size to store the values of the number in 32 bit format.
 * 
 */
void convertSignedNumberInto32Bit2ComplimentAndPlaceInside32BitIntArray(int number, int arr[32]);

/* 
 * Function:  getObjectFileNameForSourceCodeFileName  
 * --------------------
 * This is a function to return the object file name based on the source code file name. If the source code file name is "example.as" the object file will be "example.ob"
 * 
 * name: The source code file name. 
 * 
 * returns: Pointer to a 1st char of the complete object file name 
 */
char *getObjectFileNameForSourceCodeFileName(char *name);

/* 
 * Function:  getExternalFileNameForSourceCodeFileName  
 * --------------------
 * This is a function to return the external file name based on the source code file name. If the source code file name is "example.as" the object file will be "example.ext"
 * 
 * name: The source code file name. 
 * 
 * returns: Pointer to a 1st char of the complete external file name 
 */
char *getExternalFileNameForSourceCodeFileName(char *name);

/*
 * Function:  appendExternalLabelInAddressToTheExternalFileName 
 * --------------------
 * Method to output the external file.
 * 
 * labelName: External variable name.
 * memAddress: Memory address of the jump instruction which originally called the external variable.
 * externalFileName: String representing the external file name.
 */
void appendExternalLabelInAddressToTheExternalFileName(char *labelName ,int memAddress, char *externalFileName);

/* 
 * Function:  getEntryFileNameForSourceCodeFileName  
 * --------------------
 * This is a function to return the entry file name based on the source code file name. If the source code file name is "example.as" the entry file will be "example.ent"
 * 
 * name: The source code file name. 
 * 
 * returns: Pointer to a 1st char of the complete external file name 
 */
char *getEntryFileNameForSourceCodeFileName(char *name);

/*
 * Function:  appendEntryLabelInAddressToTheEntryFileName 
 * --------------------
 * Method to output the entry file.
 * 
 * labelName: Entry variable name.
 * memAddress: Memory address in which the entry is located in the source code.
 * entryFileName: String representing the entry file name.
 */
void appendEntryLabelInAddressToTheEntryFileName(char *labelName ,int memAddress, char *entryFileName);
