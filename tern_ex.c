#include <stdio.h>
#include <stdbool.h>

#include "tern_ex.h"

int tern_operation()
{
    int value = true ? 2 : 3;
    printf_s("%i\n", value);
    return 0;
}