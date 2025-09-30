#include "assembler.h"
#include "exceptions.h"

int main(int argc, char** argv){
    Trace* tr = __create_highlight_trace(
        "Excountered problamatic symbol while parsing for INSTRUCTIONS",
        "addi eax. 0x0f  ;; add 15 to eax, and call syscall",
        "found token `.` instead of `,` perhaps you forgot a COMMA?", 
        "I-Type instruction has format I_NAME REGISTER COMMA IMMIDIATE DECORATIONS",
        "problamatic symbol", ".", "COMMA?", "COMMA"
    );
    __print_highlight_trace(tr);
}