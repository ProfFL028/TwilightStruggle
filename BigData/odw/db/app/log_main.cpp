#include "log.h"
#include <iostream>

#include <ctime>
#include "timestamp.h"
#include <random>
using namespace std;
using namespace log;

int main() {
    LogLevel level = LogLevelFactory::getLogLevel(LogLevelFactory::WARN_STR);
    cout << LogLevelFactory::getLogLevel(level) << endl;


    time_t t = 21245125151l;
    tm tm = *std::localtime(&t);
    Timestamp ts(t);
    if (ts.minute == tm.tm_min) {

    }
    return 0;
}