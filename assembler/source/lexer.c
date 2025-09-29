#include "lexer.h"

// TODO: fix this for 0b and 0x, maybe introduce a manner to
// TODO: handle numeric value, it always starts a numeric (assuming)

const char LiteralFrntTable[] = {
	'"' ,	// string literal starting with ' symbol
	'#' ,	// decimal representation of number
	'0b',	// binary representation of the number
	'0x',	// hexadecimal representation of the number
	';;',	// comment start symbol, consumes line
};


const char LiteralBackTable[] = {
	'"' ,	// ending of string literal ends with '
	' ' ,	// numeric terminator
	' ' ,	// numeric terminator
	' ' ,	// numeric terminator
	'\n',	// comment is supposed to terminate on new line
};

char* literal_strings_collector(FILE* fd);
char* literal_decnums_collector(FILE* fd);
char* literal_binnums_collector(FILE* fd);
char* literal_hexnums_collector(FILE* fd);
char* literal_comment_collector(FILE* fd);

char* (*LiteralCollectors[])(FILE*) = {
	literal_strings_collector,
	literal_decnums_collector,
	literal_binnums_collector,
	literal_hexnums_collector,
	literal_comment_collector,
};

bool  literal_strings_validator(FILE* fd);
bool  literal_decnums_validator(FILE* fd);
bool  literal_binnums_validator(FILE* fd);
bool  literal_hexnums_validator(FILE* fd);
bool  literal_comment_validator(FILE* fd);

bool (*LiteralValidators[])(FILE*) = {
	literal_strings_validator,
	literal_decnums_validator,
	literal_binnums_validator,
	literal_hexnums_validator,
	literal_comment_validator,
};


char* __generic_collector(FILE* fd){
	unsigned int __begin = ftell(fd);
	unsigned int __found = 0;

	char collected;
	char stop_word = INF_LIT_READ_BACK(TOKEN_STRING) 
		? LiteralBackTable[RSB_READ(TOKEN_STRING)] : EOF;

	while ((collected = fgetchar(fd)) != EOF) {
		if (collected == stop_word)
			break;
		__found++;
	}

	if (collected == EOF)
		return NULL;	// throw trace that current collection has ended due to EOF

	char* __copied = (char*)malloc(__found);
	fseek(fd, __begin, SEEK_SET);
	fread(__copied, sizeof(char), __found, fd);
	return __copied;
}
