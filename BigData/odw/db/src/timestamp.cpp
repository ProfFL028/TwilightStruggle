#include <timestamp.h>

Timestamp::Timestamp(const long &milliSeconds) {
    this->gmtOffset = milliSeconds;
    this->second = (milliSeconds / SECONDS_IN_MILLS) % MIN_IN_SECONDS;
    this->minute = (milliSeconds / MIN_IN_MILLS) % HOUR_IN_MIN;
    this->hour = (milliSeconds / HOUR_IN_MILLS) % DAY_IN_HOUR;
}
