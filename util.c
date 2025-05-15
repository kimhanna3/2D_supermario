#include "util.h"
#include <time.h>

// Sleep for the specified number of milliseconds
void sleep_ms(size_t ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;                     // Convert milliseconds to seconds
    ts.tv_nsec = (ms % 1000) * 1000000;        // Convert remaining milliseconds to nanoseconds
    nanosleep(&ts, NULL);                      // Sleep for the given timespec duration
}
