#include <stdio.h>

#include "helpers.h"

#define CALL_FUNC(f, current_status_code) operation_alert(#f, f, current_status_code)

int operation_alert(char *funcName, int (*func)(void), int *current_status_code) {
    printf_s("=== EXECUTING \"%s\" FUNCTION ===\n", funcName);
    int status_code = func();
    if (*current_status_code == 0 && status_code != 0) {
        *current_status_code = status_code;
    }
    printf_s("=== EXECUTED \"%s\" FUNCTION === \n\n", funcName);
    return status_code;
}