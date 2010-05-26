/*
 * sonLibLogging.c
 *
 *  Created on: 24 May 2010
 *      Author: benedictpaten
 */

#include "sonLibGlobalsPrivate.h"

static int32_t ST_LOG_LEVEL = ST_LOGGING_OFF;

void *st_malloc(int32_t i) {
	void *j;
	j = malloc(i);
	if(j == 0) {
		fprintf(stderr, "Malloc failed with a request for: %i bytes\n", i);
		exit(1);
	}
	return j;
}

void *st_calloc(int32_t elementNumber, int32_t elementSize) {
	 void *k;
	 k = calloc(elementNumber, elementSize);
	 if(k == 0) {
		 fprintf(stderr, "Calloc failed with request for %i lots of %i bytes\n", elementNumber, elementSize);
		 exit(1);
	 }
	 return k;
}

void st_setLogLevel(int32_t level) {
	assert(level == ST_LOGGING_OFF || level == ST_LOGGING_INFO || level == ST_LOGGING_DEBUG);
	ST_LOG_LEVEL = level;
}

int32_t st_getLogLevel() {
	return ST_LOG_LEVEL;
}

void st_logInfo(const char *string, ...) {
	if(LOG_LEVEL >= LOGGING_INFO) {
		va_list ap;
		va_start(ap, string);
		vfprintf(stderr, string, ap);
		va_end(ap);
	}
}

void st_logDebug(const char *string, ...) {
	if(LOG_LEVEL >= LOGGING_INFO) {
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
	logDebug("Running command %s\n", cA);
	i = system(cA);
	//vfprintf(stdout, string, ap);
	return i;
}

void st_errAbort(char *format, ...) {
	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	exit(1);
}

void st_errnoAbort(char *format, ...) {
	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
}
