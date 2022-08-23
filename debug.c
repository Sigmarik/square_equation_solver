#include "debug.h"

#include <stdio.h>

void print_errno() {
    if (errno == 0) return;
    printf("Error code: %d\n", errno);
}