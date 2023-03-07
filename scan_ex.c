#include <stdio.h>

#include "scan_ex.h"

int scan_operation() 
{

    int int_to_compare;

    printf_s("Enter number to check for even or odd: ");

    if (!scanf_s("%d", &int_to_compare))
    {
        printf_s("ENTERED VALUE SHOULD BE AN INTEGER !!!\n");
        return 1;
    };

    printf_s(int_to_compare % 2 == 0 ? "VALUE \"%i\" is odd\n" : "VALUE \"%i\" is even\n", int_to_compare);

    return 0;

    /* HAVE NO IDEA WHY THIS IS INFINITE LOOPPING .-. */
    // while (1)
    // {
    //     int int_to_compare;

    //     printf_s("Enter number to check for even or odd: ");

    //     if (!scanf_s("%i[^\n]", &int_to_compare))
    //     {
    //         printf_s("ENTERED VALUE SHOULD BE AN INTEGER !!!\n");
    //         continue;
    //     };

    //     printf_s(int_to_compare % 2 == 0 ? "VALUE \"%i\" is odd\n" : "VALUE \"%i\" is even\n", int_to_compare);
    //     break;
    // }
}