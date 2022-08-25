#include "debug.h"

#include <stdio.h>

void end_program() {
    if (log_file()) {
        _LOG_PRINTF_(TERMINATE_REPORTS, "exit", "Program closed with errno = %d.\n", errno);
        log_close();
    }
    if (errno == 0) return;
    printf("Error code: %d\n", errno);
}