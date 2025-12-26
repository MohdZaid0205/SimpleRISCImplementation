#include "exceptions.h"

#define EXIT_ON_FALLBACK(code) exit(code)
#define NONE_ON_FALLBACK() 
#define SHOW_ON_FALLBACK(what) {what}

void FUNCTION_NOT_IMPLEMENTED_FALLBACK(){
    EXIT_ON_FALLBACK(-1);
}

