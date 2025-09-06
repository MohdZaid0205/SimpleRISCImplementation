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
	const char* msg;		// message related to trace.
	const char* ctx;		// associated context for trace.
	const char* des;		// descritption about trace.
	const char* com;		// comments made on trace.
	void* _metadata;		// metadata for current trace
} Trace;

struct _highlight_metadata {
	struct _h__information {
		unsigned int str;	// where to start highlighting.
		unsigned int end;	// where to end highlighting.
	} msg, ctx, des, com;
};

unsigned int _h__information_str(const char* message, const char* what);
unsigned int _h__information_end(const char* message, const char* what);

struct _annotated_metadata {
	struct _a__information {
		unsigned int chr;	// start for sequence to annotate.
		const char * ann;	// annotation text to the chr.
	} msg, ctx, des, com;
};

unsigned int _a__information_str(const char* message, const char* what);
unsigned int _a__information_ann(const char* message, unsigned int off);


// trace creation: produce trace objects in different modes
Trace* __create_formatted_trace(
	const char* msg, const char* ctx, const char* des, const char* com
);

Trace*__create_highlight_trace(
	const char* msg, const char* ctx, const char* des, const char* com,
	const char* m_w, const char* x_w, const char* d_w, const char* c_w
);

Trace* __create_annotated_trace(
	const char* msg, const char* ctx, const char* des, const char* com,
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

#endif