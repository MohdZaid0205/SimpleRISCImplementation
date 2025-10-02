#include "lexer.h"

//IMPORTANT: [>_] -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=+
// * All following tables and definitions attached must be in pre-		|
// * defined order as indexed in @TokenTypes <TOKEN_XX>.				|
// * if altered with, this implementation will not work properly.		|
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+

const char* LiteralFrntTable[] = {
	"\"",	// string literal starting with " symbol
	" " ,	// decimal representation of number
	"0b",	// binary representation of the number
	"0x",	// hexadecimal representation of the number
	"#" ,	// comment start symbol, consumes line
};

const char* LiteralBackTable[] = {
	"\"",	// ending of string literal ends with "
	" " ,	// numeric terminator
	" " ,	// numeric terminator
	" " ,	// numeric terminator
	"\n",	// comment is supposed to terminate on new line
};

//IDEA: [>_] -----------------------------------------------------------+
// * Literal collector must be defined for all types of literals.		|
// * Note that collector will start from its `frnt` value included and	|
// * it must exit with its `back` value excluded, it is assumed	that	|
// * literal does contain its `frnt` and `back` as result.				|
// ---------------------------------------------------------------------+

//NOTE: add more collectors implementations here, preferably.
char* literal_strings_collector(FILE* fd);
char* literal_decnums_collector(FILE* fd);
char* literal_binnums_collector(FILE* fd);
char* literal_hexnums_collector(FILE* fd);
char* literal_comment_collector(FILE* fd);
//NOTE: include all validator implementations in order below.
//IMPORTANT: in `LiteralCollectors` inclusion must be orderd.

char* (*LiteralCollectors[])(FILE*) = {
	literal_strings_collector,
	literal_decnums_collector,
	literal_binnums_collector,
	literal_hexnums_collector,
	literal_comment_collector,
};

//IDEA: [>_] -----------------------------------------------------------+
// * Literal Validator is used to Validate all the parts that is		|
// * present within previously collected literal, this may also be		|
// * used for checking if collection is properly reasoned with.			|
// ---------------------------------------------------------------------+


//NOTE: add more validator implementations here, preferably.
bool  literal_strings_validator(FILE* fd);
bool  literal_decnums_validator(FILE* fd);
bool  literal_binnums_validator(FILE* fd);
bool  literal_hexnums_validator(FILE* fd);
bool  literal_comment_validator(FILE* fd);

//NOTE: include all validator implementations in order below.
//IMPORTANT: in `LiteralValidators` inclusion must be orderd.

bool (*LiteralValidators[])(FILE*) = {
	literal_strings_validator,
	literal_decnums_validator,
	literal_binnums_validator,
	literal_hexnums_validator,
	literal_comment_validator,
};

// Following is implementation for each of collectors and validators.
#define INIT_FRNTWORD(tt) INF_LIT_READ_FRNT(tt) ? LiteralFrntTable[RSA_READ(tt)] : EOF
#define INIT_BACKWORD(tt) INF_LIT_READ_BACK(tt) ? LiteralBackTable[RSB_READ(tt)] : EOF

char* __generic_collector(enum TokenTypes tt, FILE* fd, bool (*res)(char), bool (*all)(char))
{
	unsigned int __begin = ftell(fd);
	unsigned int __found = 0;

	char collected;
	char* frnt_word = INIT_FRNTWORD(tt);
	char* back_word = INIT_BACKWORD(tt);

	//TODO: iterate thru frnt of the literal.

	while ((collected = fgetc(fd) != EOF))
	{
		if (all(collected))
			__found++;
		if (res(collected))
			break;
	}

	//TODO: iterate thru back of the literal.
}