#include "exceptions.h"

#define EXIT_ON_FALLBACK(code) exit(code)
#define NONE_ON_FALLBACK() 
#define SHOW_ON_FALLBACK(what) {what}

void FUNCTION_NOT_IMPLEMENTED_EXCEPTION(
        const char* fun, const char* file, int line
){
    EXCEPTION(
        "function %(%s%) has not been implemented\n", {
        DBG("\t%s:%(%d%)\n", file, line);
        ERR("\tconsider implementing %(%s%) to avoid "
            "%(FUNCTION_NOT_IMPLEMENTED_EXCEPTION%)\n",
            file
        );
        ERR("if already implemented please remove exce"
            "ption call from specified function\n"
        );
    }, fun);
    EXIT_ON_FALLBACK(-1);
}

void ARGPARSE_FLAG_NOT_RECOGNIZED_EXCEPTION(const char* flag){
    EXCEPTION(
        "found invalid flag while trying to parse argument %(%s%)\n", {
        ERR("\tflag %(%s%) but no such flag(s) present "
            "%(ARGPARSE_FLAG_NOT_RECOFNIZED_EXCEPTION%)\n",
            flag
        );
        ERR("remove specified flag or use %(-h%)|%(--help%)"
            " for suitable list of available flags\n"
        );
    }, flag);
    EXIT_ON_FALLBACK(-1);
}

void ARGPARSE_FILE_NOT_RECOGNIZED_EXCEPTION(const char* file){
    EXCEPTION(
        "found unrecognized file extension for file %(%s%)\n", {
        INF("\tassembler supports only %(.s%) or %(.asm%) as file extension\n");
        ERR("\tfound an invalid source extension %(%s%):%("
            "ARGPARSE_FILE_NOT_RECOGNIZED_EXCEPTION%)\n", file
        );
        ERR("consider renaming file with %(.s%)/%(.asm%)"
            " or provide a valid source file\n");
    }, file);
    EXIT_ON_FALLBACK(-1);
}
