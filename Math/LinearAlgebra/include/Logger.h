#ifndef LINEARALGEBRA_LOGGER_H
#define LINEARALGEBRA_LOGGER_H

enum LoggerLevel {
    info = 0, warning = 1, error = 2, fetal = 4
};

class Logger {
public:
    static void info();
public:
    static LoggerLevel level;
};


#endif //LINEARALGEBRA_LOGGER_H
