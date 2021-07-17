#define HASHSIZE 101 // size of hash tables for operations and symbols
typedef int boolean;
#define true 1
#define false 0

boolean errorsFound; // flag indicating if compilation errors were found. If so, no need to output the binary code for the corrput source code FILE.

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
