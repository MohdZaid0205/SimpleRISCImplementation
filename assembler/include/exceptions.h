#include "logging.h"

// premeture macros subjected to change in future
// helper macros to help with repetetive macros and make it easier to use
#define LOCATE_THIS_LINE() DBG("\t%s:%(%d%)\n", __FILE__, __LINE__)

// exceptions that are used within this project are to be defined within this file
// in order to deal with variants and fallbacks of required exception in case if
// function can be resolved by any decided method, or can be ignored for a while

// [ IDEA ] --------------------------------------------------------------------+
// Exception: function <name> has not been implemented							|
//		~/home/user/.../project/file.c:<line>									|
//		consider implementing <name> to avoid <EXCEPTION_NAME>                  |
// if already implemented please remove EXCEPTION from specified line			|		
// -----------------------------------------------------------------------------+
void FUNCTION_NOT_IMPLEMENTED_EXCEPTION(
        const char* fun, const char* file, int line
);
#define FNI_ARGUMENTS __func__, __FILE__, __LINE__

// [ IDEA ] --------------------------------------------------------------------+
// Exception: found invalid flag while trying to parse argument <flag>          |
//      found flag <flag> but no such flag(s) present <EXCEPTION_NAME>          |
// remove specified flag or use -h || --help to find suitable flags             |
// -----------------------------------------------------------------------------+
void ARGPARSE_FLAG_NOT_RECOGNIZED_EXCEPTION(const char* flag);

// [ IDEA ] --------------------------------------------------------------------+
// Exception: found unrecognized file extension for file:<file>                 |
//      assembler supports only .s or .asm as file extension for source         |
//      found a invalid source extension <src>:<EXCEPTION_NAME>                 |
// consider renaming file with .s/.asm or provide a valid source file           |
// -----------------------------------------------------------------------------+
void ARGPARSE_FILE_NOT_RECOGNIZED_EXCEPTION(const char* file);
