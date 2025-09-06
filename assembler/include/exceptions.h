#ifndef ASSEMBLER_EXCEPTIONS_H
#define ASSEMBLER_EXCEPTIONS_H

// This file contains ways for showing elaborate exceptions and its trace in order to provide with
// better and more workable exceptions for assembler

// define colors and primary color_generator
#define COLORED_FOREGROUND(r, g, b) "\033[38;2;"#r";"#g";"#b"m"
#define COLORED_BACKGROUND(r, g, b) "\033[48;2;"#r";"#g";"#b"m"
#define DEFAULT_FOREGROUND "\033[39m"
#define DEFAULT_BACKGROUND "\033[49m"

// trace to hold information and sequence of exceptions that led to critical.
// trace is to be done at error or critical level by default.
// TODO: allow trace to be done at warning/debug level too.

enum TraceLevel {
	T_DEBUG = 0b0001,	// just information related to debugging mechanisms
	T_WARNS = 0b0010,	// warning about passed flags and ignored stuff
	T_ERROR = 0b0100,	// exceptions that need be presented in manner
	T_FATAL = 0b1000,	// exceptions that cannot be ignored to move to next
};

/** current implementaion of trace implements message, context, annotations, description and comments.
* specifically these are formatted as follows
* 
* <message> exception occured while parsing line 13; in fib.asm;
*		<context> add rax. rbx		;; this line
*                        ^ <annotations> here
* <comment> instruction register <unexpected> register
* <description> expected `,` but got `.`, perhaps you meant a `,`. 
*/
typedef struct {
	const char* msg;		// message related to trace.
	const char* ctx;		// associated context for trace.
	const char* des;		// descritption about trace.
	const char* com;		// comments made on trace.
	void* _metadata;		// metadata for current trace
} Trace;


#endif