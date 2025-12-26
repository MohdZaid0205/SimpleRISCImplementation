#include "argparse.h"
#include "exceptions.h"

enum ASSEMBLER_ARGUMENT_TYPE argparse_get_type_for(const char* flag){

    if (strcmp("-o", flag) == 0 || strcmp("--output" , flag) == 0)
        return ARGUMENT_OUT;

    if (strcmp("-f", flag) == 0 || strcmp("--format" , flag) == 0)
        return ARGUMENT_FMT;

    if (strcmp("-m", flag) == 0 || strcmp("--mapping", flag) == 0)
        return ARGUMENT_MAP;

    if (strcmp("-h", flag) == 0 || strcmp("--help"   , flag) == 0)
        return ARGUMENT_HLP;

    // if starts with '-' => user has tried to pass a flag but couldnt.
    if (flag[0] == '-') {
        ARGPARSE_ARGUMENT_FLAG_EXCEPTION(flag);
        return ARGUMENT_NONE;
    }

    // CHECK if given flag is file itself as it is the only possiblity.
    int size = strlen(flag);
    if ((flag[size-1] == 's' && flag[size-2] == '.'))
        return ARGUMENT_INP;
    if ((flag[size-1] == 'm' && flag[size-2] == 's' &&
         flag[size-3] == 'a' && flag[size-4] == '.'))
        return ARGUMENT_INP;

    return ARGUMENT_NONE;
}

struct ASSEMBLER_ARGUMENT argparse_argument_input(const char* value){
    FUNCTION_NOT_IMPLEMENTED_EXCEPTION();
}
struct ASSEMBLER_ARGUMENT argparse_argument_output(const char* value){
    FUNCTION_NOT_IMPLEMENTED_EXCEPTION();
}
struct ASSEMBLER_ARGUMENT argparse_argument_format(const char* value){
    FUNCTION_NOT_IMPLEMENTED_EXCEPTION();
}
struct ASSEMBLER_ARGUMENT argparse_argument_mapping(const char* value){
    FUNCTION_NOT_IMPLEMENTED_EXCEPTION();
}
struct ASSEMBLER_ARGUMENT argparse_argument_help(const char* value){
    FUNCTION_NOT_IMPLEMENTED_EXCEPTION();
}
