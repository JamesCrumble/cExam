#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <windows.h>

#include "binominal_coef_ex.h"

#define TRIANGLED_COEF true

int binominal_coef_ex() {
    uint64_t k, C, input_value;

    printf_s("ENTER NUMBER FOR BINOMINAL SEQUANCE: ");
    if (!scanf_s("%llu", &input_value)) {
        printf_s("ENTERED VALUE SHOULD BE AN INTEGER\n");
        return 1;
    }
    assert(input_value >= 0);

    for (uint64_t i = TRIANGLED_COEF ? 0 : input_value; i <= input_value; i++) {
        printf_s("|");

        k = 0;
        C = 1;

        do {
            printf_s(" %d |", C);
            C = C * (i - k) / (k + 1);
            k++;
        } while (k <= i);

        printf_s("\n");
    }

    return 0;
}