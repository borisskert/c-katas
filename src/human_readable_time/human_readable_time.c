#include <stdio.h>

const unsigned int SECONDS_PER_MINUTE = 60;
const unsigned int MINUTES_PER_HOUR = 60;

/**
 * https://www.codewars.com/kata/52685f7382004e774f0001f7/train/c
 * @param seconds non-negative integer (seconds) as input
 * @param time_string the buffer to write the result into
 * @return the result buffer containing the time in a human-readable format (HH:MM:SS)
 */
char *human_readable_time(unsigned seconds, char *time_string) {
    unsigned secondsPart = seconds % SECONDS_PER_MINUTE;
    unsigned minutes = seconds / SECONDS_PER_MINUTE;
    unsigned minutesPart = minutes % MINUTES_PER_HOUR;
    unsigned hours = minutes / MINUTES_PER_HOUR;

    sprintf(
            time_string,
            "%02d:%02d:%02d",
            hours,
            minutesPart,
            secondsPart
    );

    return time_string;
}
