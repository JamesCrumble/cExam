#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "fib_ex.h"

// difference between do while and default while in first iteration 
// while check condition first, do while iterate first then check condition
#define DO_WHILE true


int fib_ex() {
    uint32_t input_start_int;

    printf_s("ENTER VALUE TO CALC FIB VALUE: ");

    if (!scanf_s("%d", &input_start_int)){
        printf_s("ENTERED VALUE SHOULD BE AN INTEGER\n");
        return 1;
    };

    uint64_t a = 1, b = 1;
    uint64_t steps = 3;

    if (!DO_WHILE) {
        while (steps <= input_start_int) {
            b = a + b;
            a = b - a;

            steps++;
        }
    } else {
        do {
            b = a + b;
            a = b - a;

            steps++;
        } while (steps <= input_start_int);
    }

    printf_s("FIB VALUE IS \"%d\"\n", b);

    return 0;
}
