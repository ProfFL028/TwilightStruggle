#include "log.h"
#include <iostream>

using namespace std;
using namespace log;

int main() {
    LogLevel level = LogLevelFactory::getLogLevel(LogLevelFactory::WARN_STR);
    cout << LogLevelFactory::getLogLevel(level) << endl;
    return 0;
}