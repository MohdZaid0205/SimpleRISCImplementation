#include "logging.h"

// premeture macros subjected to change in future
// helper macros to help with repetetive macros and make it easier to use
#define EXIT_PANIC() ERR("%(Panic%): Pogram termitated due to %(explicit panic%)\n");exit(-1);
#define EXIT_FLUSH() fflush(LOG_STREAM_GEN_INTO); fflush(LOG_STREAM_EXC_INTO); exit(-1);
#define LOCATE_THIS_LINE() INF("\t%s:%(%d%)\n", __FILE__, __LINE__)
#define ADD_SEPERATOR(level, stream) lfprintf(level, stream, "\n") 

// exceptions that are used within this project are to be defined within this file
// in order to deal with variants and fallbacks of required exception in case if
// function can be resolved by any decided method, or can be ignored for a while

// [ IDEA ] --------------------------------------------------------------------+
// Exception: function <name> has not been implemented							|
//		~/home/user/.../project/file.c:line										|
//		consider implementing <name> to avoid FUNCTION_NOT_IMPLEMENTED_EXCEPTION|
// if already implemented please remove EXCEPTION from specified line			|		
// -----------------------------------------------------------------------------+

#define FUNCTION_NOT_IMPLEMENTED_EXCEPTION() {EXCEPTION("function %(%s%) has not"	\
	" been implemented\n", {														\
		LOCATE_THIS_LINE();															\
		ERR("\tconsider implementing %s to avoid %(FUNCTION_NOT_IMPLEMENTED_EXCEPTI"\
			"ON%)\n", __func__);													\
		ERR("If already implemented please remove EXCEPTION from specified line\n");\
		ADD_SEPERATOR(LEVEL_ERR, LOG_STREAM_EXC_INTO);								\
		EXIT_FLUSH();																\
	}, __func__)}

