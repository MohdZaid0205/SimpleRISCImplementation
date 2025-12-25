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

// LEXEME_PUNCTUATION aka LexemePun & LexemePunctuation
// LEXEME_PUNCTUATION is representation of any punctuataion that is allowed inside
// assembly grammar, see GRAMMAR.md for TERMINAL values and symbols, following is
// a list of example punctuations that are found in example assembly files
//
// -----------------------------------------------------------------------------+
// DOT   (.) -> sub-labels like `.label` or with predefined types `.data`       |
// COMMA (,) -> seperators between arguments to instructions, `li a0, 0x01`     |
// ...                                                                          |
// -----------------------------------------------------------------------------+
typedef struct LEXEME_PUNCTUATION{
    unsigned int line_no;               // line number within file OCCURANCE
    unsigned int char_no;               // charcahter number within that LINE
    const char data;                    // data to store (associated char).
} LexemePun, LexemePunctuation;

// LEXEME_OPERATION aka LexemeOpr & LexemeOperation
// LEXEME_OPERATION is representation of operations that is allowed inside assem-
// -bly, what do i call operation? anything arithmatic that has directly been put
// in place inside assembly file, however this is to be used only when dealing
// with addresses and constant expressions in general sense, following is a list
// of example operations according to this project
//
// --------------+--------------------------------------------------------------+
// ADD       (+) | for example we jump relative to label by `LABEL+0x08`        |
// SUBTRACT  (-) |             we mutiply value with a value 0x08*0x0ff         |
// MULTIPLY  (*) | it is however important to note that this is only to be used |
// DIVIDE    (/) | at compile time, not at runtime [1]                          |
// -----------------------------------------------------------------------------+
//
// [1]: using LABEL+value or value+value is not same as doing assembly operation
//      as add LABEL, value or add value, value, rather it is to be considerd as 
//      macro for making calculations easier
typedef struct LEXEME_OPERATION{
    unsigned int line_no;               // line number within file OCCURANCE
    unsigned int char_no;               // charcahter number within that LINE
    const char data;                    // data to store (associated symbol)
} LexemeOpr, LexemeOperation;

#endif
