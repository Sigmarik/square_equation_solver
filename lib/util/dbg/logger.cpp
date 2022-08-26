#include "logger.h"

#include <string.h>
#include <time.h>

#include "debug.h"

static FILE* logfile = NULL;
static FILE* logdummy = NULL;
static unsigned int log_threshold = 0;

/**
 * @brief Prints out log line prefix (time and tag).
 * 
 * @param tag (optional) prefix tag
 * @param importance (optional) message importance
 */
static void log_prefix(const char* tag = "status", const unsigned int importance = ABSOLUTE_IMPORTANCE);

/**
 * @brief Returns currently opened log file by given importance.
 * 
 * @param importance (optional) importance of the message file will be used for.
 * 
 * @return FILE* log file
 */
static FILE* log_file(const unsigned int importance = ABSOLUTE_IMPORTANCE);

void log_init(const char* filename, const unsigned int threshold, int* error_code) {
    log_threshold = threshold;
    char dummyname[1024] = {};
    strncpy(dummyname, filename, 1023);
    strncat(dummyname, "_dummy.log", 1023 - strlen(dummyname));

    if (!(logdummy = fopen(dummyname, "w"))) {
        if (error_code) *error_code = FILE_ERROR;
        return;
    }


    if ((logfile = fopen(filename, "a"))) {
        log_printf(ABSOLUTE_IMPORTANCE, "open", "Log file %s was opened. Log dummy - %s.\n", filename, dummyname);
        return;
    }

    if (error_code) *error_code = FILE_ERROR;
}

static void log_prefix(const char* tag, const unsigned int importance) {
    if (!log_file()) return;
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime (&rawtime);
    char* pc_timestamp = asctime(timeinfo);
    pc_timestamp[strlen(pc_timestamp) - 1] = '\0';

    fprintf(log_file(importance), "%-20s [%s]:  ", pc_timestamp, tag);
}

void _log_printf(const unsigned int importance, const char* tag, const char* format, ...) {
    va_list args;
    va_start(args, format);

    if (log_file(importance)) {
        log_prefix(tag, importance);
        vfprintf(log_file(importance), format, args);
        fflush(log_file(importance));
    }

    va_end(args);
}

static FILE* log_file(const unsigned int importance) {
    return importance >= log_threshold ? logfile : logdummy;
}

void log_close(int* error_code) {
    if (!log_file()) return;
    log_printf(ABSOLUTE_IMPORTANCE, "close", "Closing log files.\n\n");
    if (!fclose(logfile) || !fclose(logdummy)) {
        if (error_code) *error_code = FILE_ERROR;
    }
}