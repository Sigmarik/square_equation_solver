#include "debug.h"

#include <stdio.h>
//TODO: Learn about perror()
void print_errno() {
    if (log_file()) {
        log_prefix("exit", TERMINATE_REPORTS);
        fprintf(log_file(TERMINATE_REPORTS), "programm closed with errno = %d.\n", errno);
        log_close();
    }
    if (errno == 0) return;
    printf("Error code: %d\n", errno);
}