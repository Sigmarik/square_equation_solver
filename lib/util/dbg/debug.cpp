#include "debug.h"

#include <stdio.h>

void log_end_program() {
    log_printf(TERMINATE_REPORTS, "exit", "Program closed with errno = %d.\n", errno);
    log_close();
    if (errno == 0) return;
    printf("Error code: %d\n", errno);
    perror("Error: ");
}