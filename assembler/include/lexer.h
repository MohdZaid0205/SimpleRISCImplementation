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
// --------------+--------------------------------------------------------------+
//
// [1]: using LABEL+value or value+value is not same as doing assembly operation
//      as add LABEL, value or add value, value, rather it is to be considerd as 
//      macro for making calculations easier
typedef struct LEXEME_OPERATION{
    unsigned int line_no;               // line number within file OCCURANCE
    unsigned int char_no;               // charcahter number within that LINE
    const char data;                    // data to store (associated symbol)
} LexemeOpr, LexemeOperation;

// LEXEME_LITERAL_TYPE aka LexemeLitType & LexemeLiteralType
// To represent type of literal that has been encountered in process of finding
// LITERALS_TYPE and later this sahll be used to determine default action based
// on type itself
typedef enum LEXEME_LITERAL_TYPE{
    LITERAL_STRING,
    LITERAL_COMMENT,
    LITERAL_NUMERIC,
    LITERAL_NONE,
} LexemeLitType, LexemeLiteralType;

// LEXEME_LITERAL aka LexemeLit & LexemeLiteral
// LEXEME_LITERAL is representation of literal types that has been defined within
// assembly implementation, it is important to note that only some literals have
// been defined, if none of literal type match then it is to be considerd as a 
// a lebel, later this label is to be chaecked against keywords, if current lexem
// -e matches to a keyword then in that case it cannot be a label.
//
// -----------------+-----------------------------------------------------------+
// LITERAL_STRING   | "anything between double quotes is a string" or 's'ingle  |
// LITERAL_COMMENT  | ;; anything appearing after ";" is a comment              |
// LITERAL_NUMBER   | anything starting from NUMERIC char is a number           |
// LITERAL_NONE     | if not matched to anything else it doesnt have type  [1]  |
// -----------------+-----------------------------------------------------------+
//
// [1]: when dealing with any literal that is of NONE type you need to check it
//      against keywords and if it is not a part of keyword then consider it to 
//      a label
typedef struct LEXEME_LITERAL{
    unsigned int line_no;               // line number associated with this
    unsigned inr size_of;               // size of this lexeme in num bytes
    const char* data;                   // data to store (associated char*)
} LexemeLitType, LexemeLiteralType;

#endif
