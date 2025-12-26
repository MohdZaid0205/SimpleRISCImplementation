#include "assembler.h"
#include "argparse.h"

int main(int argc, char** argv){
    
    int i = 1;
    while (i < argc){
        switch (argparse_get_type_for(argv[i])){
            case ARGUMENT_OUT:
                argparse_argument_output(argv[++i]);
                break;
            case ARGUMENT_FMT:
                argparse_argument_format(argv[++i]);
                break;
            case ARGUMENT_MAP:
                argparse_argument_mapping(argv[++i]);
                break;
            case ARGUMENT_HLP:
                argparse_argument_help("HELP ME");
                break;
            case ARGUMENT_INP:
                argparse_argument_input(argv[i]);
                break;
            case ARGUMENT_NONE:
                return -1;
            default:
                DBG("%(Aint No way that happened%)");
                return -100;
        }
        i++;
    }
    return 0;
}
