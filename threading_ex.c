#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "threading_ex.h"

#define THREADS_COUNT 2
#define THREADS_FROM_WINDOWS true

#define INITIAL_INC_VALUE 50000
#define SUCCESS_VALUE_AFTER_THREADS INITIAL_INC_VALUE * (THREADS_COUNT * THREADS_COUNT)

HANDLE mutex = NULL;
unsigned long value = 0;

void inc_with_mutex() 
{
    for (int i = 0; i < INITIAL_INC_VALUE; i++) { 
        WaitForSingleObject(mutex, INFINITE);
        value++;
        ReleaseMutex(mutex);
    }
    ExitThread(0);
}

void inc_without_mutex() { for (int i = 0; i < INITIAL_INC_VALUE; i++) { value++; } ExitThread(0); }

int thread_ex_with_mutex() {
    
    HANDLE events[2];
    unsigned long *first_thread_id;
    unsigned long *second_thread_id;
    
    mutex = CreateMutex(NULL, false, "thread_ex_with_mutex mutex");
    
    if (mutex == NULL) {
        printf_s("CANNOT CREATE MUTEX FOR THREADS");
        return 1;
    }

    printf_s("VALUE BEFORE THREADS => %d\n", value);

    if (!THREADS_FROM_WINDOWS) {
        // NOT USING MUTEX LOGIC FROM <windows.h>
        // events[0] = (HANDLE)_beginthreadex(NULL, 0, inc_with_mutex, NULL, 0, &first_thread_id); 
        // events[1] = (HANDLE)_beginthreadex(NULL, 0, inc_with_mutex, NULL, 0, &second_thread_id);
        
        printf_s("NOT IMPLEMENTED FOR OTHER THREADS CALL EXCEPTS WINDOWS API\n");
        return 1;
    } else {
        events[0] = CreateThread(NULL, 0, inc_with_mutex, NULL, 0, &first_thread_id);
        events[1] = CreateThread(NULL, 0, inc_with_mutex, NULL, 0, &second_thread_id);
    }

    WaitForMultipleObjects(THREADS_COUNT, &events, true, INFINITE); // <windows.h>

    for (int i = 0; i < 2; i++) { 
        if (events[i] != INVALID_HANDLE_VALUE) {
            CloseHandle(events[i]);
        }
    }

    printf_s("FIRST THREAD WITH ID => \"%d\", SECOND THREAD WITH ID => \"%d\" WAS STARTED\n", first_thread_id, second_thread_id);
    printf_s("VALUE AFTER THREADS => %d, SHOULD BE => %d\n", value, SUCCESS_VALUE_AFTER_THREADS);

    return 0;
}

int thread_ex_without_mutex()
{
    // https://learn.microsoft.com/ru-ru/cpp/cpp/cdecl?view=msvc-170
    // _beginthread using __cdecl agreement so cannot await threads

    HANDLE events[2];

    // storage to write thread id
    unsigned long *first_thread_id;
    unsigned long *second_thread_id;

    if (!THREADS_FROM_WINDOWS) {
        // <process.h> (DTK HOW WORK WITH _beginthreadex and mutex on windows)
        events[0] = (HANDLE)_beginthreadex(NULL, 0, inc_without_mutex, NULL, 0, &first_thread_id); 
        events[1] = (HANDLE)_beginthreadex(NULL, 0, inc_without_mutex, NULL, 0, &second_thread_id);
    } else {
        events[0] = CreateThread(NULL, 0, inc_without_mutex, NULL, 0, &first_thread_id);
        events[1] = CreateThread(NULL, 0, inc_without_mutex, NULL, 0, &second_thread_id);
    }

    printf_s("FIRST THREAD WITH ID => \"%d\", SECOND THREAD WITH ID => \"%d\" WAS STARTED\n", first_thread_id, second_thread_id);

    WaitForMultipleObjects(THREADS_COUNT, &events, true, INFINITE); // <windows.h>

    for (int i = 0; i < 2; i++) { 
        if (events[i] != INVALID_HANDLE_VALUE) {
            CloseHandle(events[i]);
        }
    }

    printf_s("VALUE AFTER THREADS => %d, SHOULD BE => %d\n", value, SUCCESS_VALUE_AFTER_THREADS);

    return 0;
}