#include "logging.h"

// premeture macros subjected to change in future
// helper macros to help with repetetive macros and make it easier to use
#define LOCATE_THIS_LINE() DBG("\t%s:%(%d%)\n", __FILE__, __LINE__)

// exceptions that are used within this project are to be defined within this file
// in order to deal with variants and fallbacks of required exception in case if
// function can be resolved by any decided method, or can be ignored for a while

// [ IDEA ] --------------------------------------------------------------------+
// Exception: function <name> has not been implemented							|
//		~/home/user/.../project/file.c:line										|
//		consider implementing <name> to avoid FUNCTION_NOT_IMPLEMENTED_EXCEPTION|
// if already implemented please remove EXCEPTION from specified line			|		
// -----------------------------------------------------------------------------+

void    FUNCTION_NOT_IMPLEMENTED_FALLBACK();
#define FUNCTION_NOT_IMPLEMENTED_EXCEPTION() {EXCEPTION("function %(%s%) has not"	\
	" been implemented\n", {														\
		LOCATE_THIS_LINE();															\
		ERR("\tconsider implementing %s to avoid %(FUNCTION_NOT_IMPLEMENTED_EXCEPTI"\
			"ON%)\n", __func__);													\
		ERR("If already implemented please remove EXCEPTION from specified line\n");\
        FUNCTION_NOT_IMPLEMENTED_FALLBACK();                                        \
	}, __func__)}

void    ARGPARSE_ARGUMENT_FLAG_FALLBACK();
#define ARGPARSE_ARGUMENT_FLAG_EXCEPTION(flag) {EXCEPTION("Found invalid flag while"\
    " trying to argparse flag %(%s%)\n", {                                          \
        ERR("\tfound flag %(%s%) but no such flag is present raised  %(ARGPARSE_ARG"\
            "UMENT_FLAG_EXCEPTION%)\n", flag);                                      \
        ERR("use flag %(-h%) | %(--help%) to see list of all available flag\n");    \
        ARGPARSE_ARGUMENT_FLAG_FALLBACK();                                          \
    }, flag)}

