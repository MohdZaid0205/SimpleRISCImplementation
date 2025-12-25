#ifndef ASSEMBLER_LEXER_H
#define ASSEMBLER_LEXER_H

// [ INFO ] --------------------------------------------------------------------+
// lexer for assembler to directly operate on a FILE* while seperating const	| 
// char* into their own small lexemes, essentially there are 4 types of lexemes	|
// as prev implementeation of LEXER_H (classifications) CFL_XXX					|
//																				|
// * PUNCTUATION: single charachter that has associated meaning with it.		|
// * OPERATIONS : single or multicharachter symbols with associated opration.	|
// * LITERAL	: literal types such as string, int or identifiers.				|
// * KEYWORDS	: set of words reserved by assembler to identify operations.	|
// -----------------------------------------------------------------------------+

// enum ASSEMBLER_LEXEME_TYPE containing possible types of lexeme that can be 
// constructed using ASSEMBLER_LEXER_H lexer aimed to seperate charachters.
typedef enum ASSEMBLER_LEXEME_TYPE {
	LEXEME_PUN,							// LEXEME type found to be PUNCTUATION
	LEXEME_OPR,							// LEXEME type found to be OPERATION
	LEXEME_LIT,							// LEXEME type found to be LITERAL
	LEXEME_KEY,							// LEXEME type found to be KEYWORD
} LexemeType;

// [ IDEA ] --------------------------------------------------------------------+
// So we first define all structures that store corresponding lexeme and then	|
// use those structures and directly cast them to required types that we		|
// require such as:																|
//		LEXEME_TOKEN.type	: is typeof(ASSEMBLER_LEXEME_TYPE)					|
//		LEXEME_TOKEN.as.pun : is typeof(<pun-type>)								|
//		LEXEME_TOKEN.as.opr : is typeof(<opr-type>)								|
//		LEXEME_TOKEN.as.lit : is typeof(<lit-type>)								|
//		LEXEME_TOKEN.as.key : is typeof(<key-type>)								|
// *(this idea is subjected to change)											|
// -----------------------------------------------------------------------------+

// LEXEME_PNCTUATION is representation of any punctuataion
typedef struct LEXEME_PUNCTUATION{
    unsigned int line_no;
    unsigned int char_no;
    const char data;
} LexemePun, LexemePunctuation;

#endif
