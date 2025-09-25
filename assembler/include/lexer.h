#ifndef ASSEMBLER_LEXER_H
#define ASSEMBLER_LEXER_H

#include "pch.h"

// defining type classifications for lexemes, each lexeme is to collect its data and be reurned with its properties
// and rules that it must satisfy in order to be considered as tokenizable.

// This lexer module aims to make it easier to define lexeme and data associated with it all in same enum.
// so each type in the base token classifer will be 32 bits long and contain all rules and associated data to itself.
// This behaviour of holding data are governed according to the rules

#define TOKEN(name, clf, inf, rsa, rsb, rsc) name = (clf) | (inf) | (rsa) | (rsb) | (rsc)

// 0bCC00_0000_0000_0000_0000_0000_0000
//   ^^--> first two bits of 32 is used to classify token into broader, similar but distinguishable supported types
#define CLF_MASK 0b11000000000000000000000000000000
#define CLF_PUN  0b00000000000000000000000000000000
#define CLF_OPR  0b01000000000000000000000000000000
#define CLF_LIT  0b10000000000000000000000000000000
#define CLF_KWD  0b11000000000000000000000000000000
// it is important to note that these in itself also define their own ruleset.

#define RSX 000 // representation for empty bits
#define RSA 001	// representation for storage bits
#define RSB 010 // representation for storage bits
#define RSC 100 // representation for storage bits

// -------------------------------------------------------------------------------------------------+ 
#define RSA_READ(x) (x & (0xff << 16)) >> 16	// shift 16 bits to read rsa                        |
#define RSA_MAKE(x) (x << 16) & (0xff << 16)    // shift 16 bits to write rsa                       |
#define RSB_READ(x) (x & (0xff << 8)) >> 8		// shift 08 bits to read rsb                        |
#define RSB_MAKE(x) (x << 8) & (0xff << 8)		// shift 08 bits to write rsb                       |
#define RSC_READ(x) x & 0xff					// shift 00 bits to read rsc        __  (**)  __    |
#define RSC_MAKE(x) x & 0xff					// shift 00 bits to write rsc         \__||__/      |
// -------------------------------------------------------------------------------------------------+

// Punctuations
// 0b00VV_0000_         [BBBB_BBBB]
//     ^^     [AAAA_AAAA]         [CCCC_CCCC] 
//     ||     A B or C can also be used simultaneously, for complexly long puctuations.
//     ++---> to tell which of the byte holds the value for punctuation in case of conflict.
#define INF_PUN_MASK      0b00111111000000000000000000000000
#define INF_PUN_MASK_SIZE 0b00110000000000000000000000000000
#define INF_PUN_MASK_CONT 0b00001110000000000000000000000000
#define INF_PUN_MASK_IMPR 0b00000001000000000000000000000000
#define INF_PUN_READ_SIZE(s) ((INF_PUN_MASK_SIZE & s) >> 28)
#define INF_PUN_MAKE_SIZE(s) ((s << 28) & INF_PUN_MASK_SIZE)
#define INF_PUN_READ_CONT(c) ((INF_PUN_MASK_CONT & c) >> 25)
#define INF_PUN_MAKE_CONT(c) ((c << 25) & INF_PUN_MASK_CONT)
#define INF_PUN_READ_IMPR(i) ((INF_PUN_MASK_IMPR & i) >> 24)
#define INF_PUN_MAKE_IMPR(i) ((i << 24) & INF_PUN_MASK_IMPR)

// Operations
// 0b01TX_0000_         [BBBB_BBBB]
//     ^^     [AAAA_AAAA]         [...._....]
//     ||     A and B marked memory holds the first and second symbols respectively.
//     |+---> to mark size of symbols that are allowed in sequence.
//     +----> to mark type of operation, info like if it has left and right both or just single side.
#define INF_OPR_MASK      0b00110000000000000000000000000000
#define INF_OPR_MASK_TYPE 0b00100000000000000000000000000000
#define INF_OPR_MASK_CONT 0b00010000000000000000000000000000
#define INF_OPR_READ_TYPE(t) ((INF_OPR_MASK_TYPE & t) >> 29)
#define INF_OPR_MAKE_TYPE(t) ((t << 29) & INF_OPR_MASK_TYPE)
#define INF_OPR_READ_CONT(c) ((INF_OPR_MASK_CONT & c) >> 28)
#define INF_OPR_MAKE_CONT(c) ((c << 28) & INF_OPR_MASK_CONT)

// Literals
// 0b10FB_0000_         [BBBB_BBBB]
//     ^^     [AAAA_AAAA]         [CCCC_CCCC]
//     ||     A and B contains index to symbols F and B repectively
//     ||     C holds array index of literal handler in literal function table.
//     |+ --> if back symbol is present.
//     + ---> if front symbol is present.
#define INF_LIT_MASK      0b00110000000000000000000000000000
#define INF_LIT_MASK_FRNT 0b00100000000000000000000000000000
#define INF_LIT_MASK_BACK 0b00010000000000000000000000000000
#define INF_LIT_READ_FRNT(s) ((INF_LIT_MASK_FRNT & s) >> 29)
#define INF_LIT_MAKE_FRNT(s) ((s << 29) & INF_LIT_MASK_FRNT)
#define INF_LIT_READ_BACK(s) ((INF_LIT_MASK_BACK & s) >> 28)
#define INF_LIT_MAKE_BACK(s) ((s << 28) & INF_LIT_MASK_BACK)

// Keywords
// 0b11CS_0000_[AAAA_AAAA_BBBB_BBBB_CCCC_CCCC]
//     ^^     ABC holds complete index of keyword in keyword table.
//     |+ --> if spackes are allowed.
//     + ---> if it is case sensitive.
#define INF_KWD_MASK      0b00110000000000000000000000000000
#define INF_KWD_MASK_CASE 0b00100000000000000000000000000000
#define INF_KWD_MASK_SPCE 0b00010000000000000000000000000000
#define INF_KWD_READ_CASE(s) ((INF_KWD_MASK_CASE & s) >> 29)
#define INF_KWD_MAKE_CASE(s) ((s << 29) & INF_KWD_MASK_CASE)
#define INF_KWD_READ_SPCE(s) ((INF_KWD_MASK_SPCE & s) >> 28)
#define INF_KWD_MAKE_SPCE(s) ((s << 28) & INF_KWD_MASK_SPCE)

// TODO: implement proper supposrt for table referncing, maybe repurpose RAX, RBX, RCX
extern const char* LiteralFrntTable[];
extern const char* LiteralBackTable[];
extern char* (*LiteralCollectors[])(FILE*);
extern bool  (*LiteralValidators[])(FILE*);

// following is part defining all the token types that are allowed as per our implementation of assembler.
// all tokens must belong to one of the classification and must satisfy all defined parameters explicitly.
enum Tokens {

#pragma region PUNCTUATIONS
	TOKEN(TOKEN_COMMA   , CLF_PUN, (INF_PUN_MAKE_SIZE(1) | INF_PUN_MAKE_CONT(RSA) | INF_PUN_MAKE_IMPR(1)), RSA_MAKE(','), RSB_MAKE(0), RSC_MAKE(0)),
	TOKEN(TOKEN_COLON   , CLF_PUN, (INF_PUN_MAKE_SIZE(1) | INF_PUN_MAKE_CONT(RSA) | INF_PUN_MAKE_IMPR(1)), RSA_MAKE(':'), RSB_MAKE(0), RSC_MAKE(0)),
	TOKEN(TOKEN_L_ROUND , CLF_PUN, (INF_PUN_MAKE_SIZE(1) | INF_PUN_MAKE_CONT(RSA) | INF_PUN_MAKE_IMPR(1)), RSA_MAKE('('), RSB_MAKE(0), RSC_MAKE(0)),
	TOKEN(TOKEN_R_ROUND , CLF_PUN, (INF_PUN_MAKE_SIZE(1) | INF_PUN_MAKE_CONT(RSA) | INF_PUN_MAKE_IMPR(1)), RSA_MAKE(')'), RSB_MAKE(0), RSC_MAKE(0)),
	TOKEN(TOKEN_L_SQUARE, CLF_PUN, (INF_PUN_MAKE_SIZE(1) | INF_PUN_MAKE_CONT(RSA) | INF_PUN_MAKE_IMPR(1)), RSA_MAKE('['), RSB_MAKE(0), RSC_MAKE(0)),
	TOKEN(TOKEN_R_SQUARE, CLF_PUN, (INF_PUN_MAKE_SIZE(1) | INF_PUN_MAKE_CONT(RSA) | INF_PUN_MAKE_IMPR(1)), RSA_MAKE(']'), RSB_MAKE(0), RSC_MAKE(0)),
#pragma endregion

#pragma region LITERALS
	TOKEN(TOKEN_STRING , CLF_LIT, (INF_LIT_MAKE_FRNT(1) | INF_LIT_MAKE_BACK(1)), RSA_MAKE(0), RSB_MAKE(0), RSC_MAKE(0)),
	TOKEN(TOKEN_DECNUM , CLF_LIT, (INF_LIT_MAKE_FRNT(1) | INF_LIT_MAKE_BACK(1)), RSA_MAKE(1), RSB_MAKE(1), RSC_MAKE(1)),
	TOKEN(TOKEN_BINNUM , CLF_LIT, (INF_LIT_MAKE_FRNT(1) | INF_LIT_MAKE_BACK(1)), RSA_MAKE(2), RSB_MAKE(2), RSC_MAKE(2)),
	TOKEN(TOKEN_HEXNUM , CLF_LIT, (INF_LIT_MAKE_FRNT(1) | INF_LIT_MAKE_BACK(1)), RSA_MAKE(3), RSB_MAKE(3), RSC_MAKE(3)),
	TOKEN(TOKEN_COMMENT, CLF_LIT, (INF_LIT_MAKE_FRNT(1) | INF_LIT_MAKE_BACK(1)), RSA_MAKE(4), RSB_MAKE(4), RSC_MAKE(4)),
#pragma endregion

};

#endif