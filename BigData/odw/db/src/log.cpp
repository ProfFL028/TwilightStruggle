#include "log.h"
#include <iostream>

using namespace std;
using namespace log;

LogLevel LogLevelFactory::getLogLevel(const char *lvlStr) {
    if (strcmp(lvlStr, TRACE_STR) == 0) {
        return TRACE;
    }
    if (strcmp(lvlStr, DEBUG_STR) == 0) {
        return DEBUG;
    }
    if (strcmp(lvlStr, INFO_STR) == 0) {
        return INFO;
    }
    if (strcmp(lvlStr, WARN_STR) == 0) {
        return WARN;
    }
    if (strcmp(lvlStr, ERROR_STR) == 0) {
        return ERROR;
    }

    return INFO;
}

const char* LogLevelFactory::getLogLevel(const LogLevel &lvl) {
    if (lvl == INFO) {
        return INFO_STR;
    }
    if (lvl == TRACE) {
        return TRACE_STR;
    }
    if (lvl == DEBUG) {
        return DEBUG_STR;
    }
    if (lvl == WARN) {
        return WARN_STR;
    }
    if (lvl == ERROR) {
        return ERROR_STR;
    }

    return INFO_STR;
}