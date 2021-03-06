/*
 * Copyright (C) 2006-2012 by Benedict Paten (benedictpaten@gmail.com)
 *
 * Released under the MIT license, see LICENSE.txt
 */

/*
 * sonLibLogging.c
 *
 *  Created on: 24 May 2010
 *      Author: benedictpaten
 */

#include "sonLibGlobalsInternal.h"
#include <errno.h>

static enum stLogLevel LOG_LEVEL = critical;

void *st_malloc(size_t i) {
    void *j;
    j = malloc(i);
    if (j == 0) {
        fprintf(stderr, "Malloc failed with a request for: %zu bytes\n", i);
        assert(0);
        exit(1);
    }
    return j;
}

void *st_calloc(int64_t elementNumber, size_t elementSize) {
    void *k;
    k = calloc(elementNumber, elementSize);
    if (k == 0) {
        fprintf(stderr,
                "Calloc failed with request for %lld lots of %zu bytes\n",
                (long long int) elementNumber, elementSize);
        exit(1);
    }
    return k;
}

void st_setLogLevelFromString(const char *string) {
    if (string != NULL) {
        char *string2 = stString_copy(string);
        for (int32_t i = 0; i < strlen(string); i++) {
            string2[i] = tolower(string2[i]);
        }
        if (strcmp(string2, "off") == 0) {
            LOG_LEVEL = off;
        } else if (strcmp(string2, "critical") == 0) {
            LOG_LEVEL = critical;
        } else if (strcmp(string2, "info") == 0) {
            LOG_LEVEL = info;
            st_logInfo("Set log level to INFO\n");
        } else {
            if (strcmp(string2, "debug") != 0) {
                st_errAbort("Unrecognised logging string %s", string);
            }
            LOG_LEVEL = debug;
            st_logInfo("Set log level to DEBUG\n");
        }
        free(string2);
    }
}

void st_setLogLevel(enum stLogLevel level) {
    LOG_LEVEL = level;
}

enum stLogLevel st_getLogLevel(void) {
    return LOG_LEVEL;
}

void st_logCritical(const char *string, ...) {
    if (st_getLogLevel() >= critical) {
        va_list ap;
        va_start(ap, string);
        vfprintf(stderr, string, ap);
        va_end(ap);
    }
}

void st_logInfo(const char *string, ...) {
    if (st_getLogLevel() >= info) {
        va_list ap;
        va_start(ap, string);
        vfprintf(stderr, string, ap);
        va_end(ap);
    }
}

void st_logDebug(const char *string, ...) {
    if (st_getLogLevel() >= debug) {
        va_list ap;
        va_start(ap, string);
        vfprintf(stderr, string, ap);
        va_end(ap);
    }
}

void st_uglyf(const char *string, ...) {
    va_list ap;
    va_start(ap, string);
    vfprintf(stderr, string, ap);
    va_end(ap);
}

int32_t st_system(const char *string, ...) {
    static char cA[100000];
    int32_t i;
    va_list ap;
    va_start(ap, string);
    vsprintf(cA, string, ap);
    va_end(ap);
    assert(strlen(cA) < 100000);
    st_logDebug("Running command %s\n", cA);
    i = system(cA);
    //vfprintf(stdout, string, ap);
    return i;
}

void st_errAbort(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(1);
}

void st_errnoAbort(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, ": %s\n", strerror(errno));
    exit(1);
}
