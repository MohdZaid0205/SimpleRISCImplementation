#include "lexer.h"

// TODO: fix this for 0b and 0x, maybe introduce a manner to
// TODO: handle numeric value, it always starts a numeric (assuming)

const char* LiteralFrntTable[] = {
	"\"",	// string literal starting with " symbol
	""  ,	// decimal representation of number
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

bool __generic_validator(enum TokenTypes tt, FILE* fd)
{
	unsigned int __begin = ftell(fd);
	unsigned int __found = 0;

	char collected;
	char* frnt_word = INF_LIT_READ_FRNT(tt)
		? LiteralFrntTable[RSA_READ(tt)] : " ";

	unsigned int __length = strlen(frnt_word);
	while ((__found < __length) && (collected = fgetc(fd)) != EOF) {
		if (collected != frnt_word[__found])
			return false;
		__found++;
	}

	bool result = __length == __found;
	if (!result)
		fseek(fd, __begin, SEEK_SET);
	return result;
}


char* __generic_collector(enum TokenTypes tt, FILE* fd)
{
	unsigned int __begin = ftell(fd);
	unsigned int __found = 0;

	char collected;
	char* stop_word = INF_LIT_READ_BACK(tt)
		? LiteralBackTable[RSB_READ(tt)] : EOF;

	if (!__generic_validator(tt, fd))
		return NULL;

	while ((collected = fgetc(fd)) != EOF) {
		if (collected == stop_word[0])
			break;
		__found++;
	}

	if (collected == EOF)
		return NULL;

	char* __copied = (char*)malloc(__found);
	fseek(fd, __begin + 1, SEEK_SET);
	fread(__copied, sizeof(char), __found, fd);
	fseek(fd, __begin + __found + 1, SEEK_SET);
	return __copied;
}

char* literal_strings_collector(FILE* fd) {
	return __generic_collector(TOKEN_STRING, fd);
}

char* literal_decnums_collector(FILE* fd) {

}

char* literal_binnums_collector(FILE* fd) {

}

char* literal_hexnums_collector(FILE* fd) {

}

char* literal_comment_collector(FILE* fd) {
	return __generic_collector(TOKEN_STRING, fd);
}


bool  literal_strings_validator(FILE* fd) {
	return __generic_validator(TOKEN_STRING, fd);
}

bool  literal_decnums_validator(FILE* fd) {
	return __generic_validator(TOKEN_DECNUM, fd);
}

bool  literal_binnums_validator(FILE* fd) {
	return __generic_validator(TOKEN_BINNUM, fd);
}

bool  literal_hexnums_validator(FILE* fd) {
	return __generic_validator(TOKEN_HEXNUM, fd);
}

bool  literal_comment_validator(FILE* fd) {
	return __generic_validator(TOKEN_COMMENT, fd);
}