//
// Created by 方笠 on 2022/3/2.
//

#ifndef DATABASE_LOG_H
#define DATABASE_LOG_H

namespace log {
    enum LogLevel {
        TRACE = 0, DEBUG = 1, INFO = 10, WARN = 20, ERROR = 40
    };

    class LogLevelFactory {
    private:
        LogLevelFactory() = default;

        virtual ~LogLevelFactory() = default;

    public:
        static LogLevel getLogLevel(const char *lvlStr);
        static const char* getLogLevel(const LogLevel& lvl);

        constexpr const static char *TRACE_STR = "TRACE";
        constexpr const static char *DEBUG_STR = "DEBUG";
        constexpr const static char *INFO_STR = "INFO";
        constexpr const static char *WARN_STR = "WARN";
        constexpr const static char *ERROR_STR = "ERROR";
    };
}

#endif //DATABASE_LOG_H
