#ifndef ASSEMBLER_EXCEPTIONS_H
#define ASSEMBLER_EXCEPTIONS_H

#include "pch.h"

// This file contains ways for showing elaborate exceptions and its trace in order to provide with
// better and more workable exceptions for assembler

// some string manipulation stuff
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// define colors and primary color_generator
#define COLORED_FOREGROUND(r, g, b) "\033[38;2;"#r";"#g";"#b"m"
#define COLORED_BACKGROUND(r, g, b) "\033[48;2;"#r";"#g";"#b"m"
#define DEFAULT_FOREGROUND "\033[39m"
#define DEFAULT_BACKGROUND "\033[49m"

// define null paramaeter
#define NOTEXT ""

// trace to hold information and sequence of exceptions that led to critical.
// trace is to be done at error or critical level by default.
// TODO: allow trace to be done at warning/debug level too.

enum TraceLevel {
	T_DEBUG = 0b0001,	// just information related to debugging mechanisms
	T_WARNS = 0b0010,	// warning about passed flags and ignored stuff
	T_ERROR = 0b0100,	// exceptions that need be presented in manner
	T_FATAL = 0b1000,	// exceptions that cannot be ignored to move to next
};

/*
current implementaion of trace implements message, context, annotations, description and comments.
specifically these are formatted as follows

<message> exception occured while parsing line 13; in fib.asm;
	<context> add rax. rbx		;; this line
                       ^ <annotations> here
<comment> instruction register <unexpected> register
<description> expected `,` but got `.`, perhaps you meant a `,`. 
*/
typedef struct {
	char* msg;				// message related to trace.
	char* ctx;				// associated context for trace.
	char* des;				// descritption about trace.
	char* com;				// comments made on trace.
	void* _metadata;		// metadata for current trace
} Trace;

struct _highlight_metadata {
	struct _h__information {
		unsigned int str;	// where to start highlighting.
		unsigned int end;	// where to end highlighting.
	} msg, ctx, des, com;
};

struct _annotated_metadata {
	struct _a__information {
		unsigned int str;	// start for sequence to annotate.
		const char * ann;	// annotation text to the chr.
	} msg, ctx, des, com;
};

// helper function to deal with string and pattern matching
unsigned int __find_string_string(const char* string, const char* in);

// trace creation: produce trace objects in different modes
Trace* __create_formatted_trace(
	const char* msg, const char* ctx, const char* des, const char* com
);

Trace* __create_highlight_trace(
	const char* msg, const char* ctx, const char* des, const char* com,
	const char* m_w, const char* x_w, const char* d_w, const char* c_w
);

Trace* __create_annotated_trace(
	const char* msg, const char* ctx, const char* des, const char* com,
	const char* m_w, const char* x_w, const char* d_w, const char* c_w,
	const char* m_a, const char* x_a, const char* d_a, const char* c_a
);

// trace printing: output traces in chosen formatting
void __print_formatted_trace(Trace* __trace);
void __print_highlight_trace(Trace* __trace);
void __print_annotated_trace(Trace* __trace);


// cleanup: release traces created earlier.
void __remove_formatted_trace(Trace* __trace);
void __remove_highlight_trace(Trace* __trace);
void __remove_annotated_trace(Trace* __trace);

// state machine to work with and deal with exceptions and logging mechanism.
extern Trace*			__e_trace;	// state to store in case of exceptions or fatal occurred.
extern enum TraceLevel  __e_level;	// __e_level of __e_trace or message that is allowed to escape.		



// to directly display required logging mechanism to screen and corresponding handlers.
#define TODO_MES "Not Implemented Exception. Tried to execute line marked as TODO."
#define TODO_CTX "inside: " __FILE__ ":" STR(__LINE__)
#define TODO_DES 
#define TODO_COM "Marked line requires implementation in order to execute at runtime."

#define TODO(what)	__remove_highlight_trace(__e_trace); __e_trace = NULL;	__e_trace =			 \
					__create_highlight_trace(TODO_MES, TODO_CTX, TODO_DES what, TODO_COM,		 \
											"Not Implemented Exception", TODO_CTX, what, NOTEXT);\
					__print_highlight_trace(__e_trace); exit(-1)

#define NOT_IMPLEMENTED_EXCEPTION TODO(__func__)

#endif