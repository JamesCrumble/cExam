#include <stdio.h>
#include <stdbool.h>
#include <process.h>
#include <windows.h>

#include "helpers.h"
#include "tern_ex.h"
#include "scan_ex.h"
#include "threading_ex.h"
#include "fib_ex.h"
#include "binominal_coef_ex.h"


int main()
{
    int status_code = 0;

    CALL_FUNC(tern_operation, &status_code);
    CALL_FUNC(scan_operation, &status_code);
    CALL_FUNC(thread_ex_without_mutex, &status_code);
    CALL_FUNC(thread_ex_with_mutex, &status_code);
    CALL_FUNC(fib_ex, &status_code);
    CALL_FUNC(binominal_coef_ex, &status_code);

    printf_s("STATUS CODE => \"%d\"\n", status_code);

    return status_code;
}