#include "logger.h"

#include <string.h>
#include <time.h>

#include "debug.h"

static FILE* pf_logfile = NULL;
static FILE* pf_logdummy = NULL;
static unsigned int i_log_threshold = 0;

void log_init(const char* pc_filename, const unsigned int i_threshold, int* pi_error_code) {
    i_log_threshold = i_threshold;
    char pc_dummyname[1024] = {};
    strncpy(pc_dummyname, pc_filename, 1023);
    strncat(pc_dummyname, "_dummy.log", 1023 - strlen(pc_dummyname));

    if (!(pf_logdummy = fopen(pc_dummyname, "w"))) {
        if (pi_error_code) *pi_error_code = FILE_ERROR;
        return;
    }

    if ((pf_logfile = fopen(pc_filename, "a"))) {
        log_prefix("open");
        fprintf(log_file(), "Log file %s was opened. Log dummy - %s.\n", pc_filename, pc_dummyname);
        return;
    }

    if (pi_error_code) *pi_error_code = FILE_ERROR;
}

void log_prefix(const char* tag, const unsigned int importance) {
    if (!log_file()) return;
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime (&rawtime);
    char* pc_timestamp = asctime(timeinfo);
    pc_timestamp[strlen(pc_timestamp) - 1] = '\0';

    fprintf(log_file(importance), "%-20s [%s]:  ", pc_timestamp, tag);
}

void log_write(const char* tag, const char* message, const unsigned int importance, int* pi_error_code) {
    if (!log_file()) return;
    log_prefix(tag, importance);
    fprintf(log_file(importance), "%s\n", message);
}

FILE* log_file(const unsigned int importance) {
    return importance >= i_log_threshold ? pf_logfile : pf_logdummy;
}

void log_close(int* pi_error_code) {
    if (!log_file()) return;
    log_write("close", "Closing log files.");
    if (!fclose(pf_logfile) || !fclose(pf_logdummy)) {
        if (pi_error_code) *pi_error_code = FILE_ERROR;
    }
}