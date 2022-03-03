
#ifndef DATABASE_TIMESTAMP_H
#define DATABASE_TIMESTAMP_H

class Timestamp {
public:
    /**
     * milliSeconds refers to milli seconds elapsed from 1970-01-01 00:00:00.
     * can be get from by `time_t t = time_t(nullptr)`
     * @param milliSeconds
     */
    Timestamp(const long& milliSeconds=0);
    virtual ~Timestamp() = default;

public:
    long gmtOffset;
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
    int weekday;
    int yearDay;

public:
    constexpr const static int SECONDS_IN_MILLS = 1000;
    constexpr const static int MIN_IN_SECONDS = 60;
    constexpr const static int MIN_IN_MILLS = MIN_IN_SECONDS * SECONDS_IN_MILLS;
    constexpr const static int HOUR_IN_MIN = 60;
    constexpr const static int HOUR_IN_SECONDS = HOUR_IN_MIN * MIN_IN_SECONDS;
    constexpr const static int HOUR_IN_MILLS = HOUR_IN_SECONDS * SECONDS_IN_MILLS;
    constexpr const static int DAY_IN_HOUR = 24;
    constexpr const static int DAY_IN_MIN = DAY_IN_HOUR * HOUR_IN_MIN;
    constexpr const static int DAY_IN_SECONDS = DAY_IN_MIN * MIN_IN_SECONDS;
    constexpr const static int DAY_IN_MILLS = DAY_IN_SECONDS * SECONDS_IN_MILLS;
};

#endif //DATABASE_TIMESTAMP_H
