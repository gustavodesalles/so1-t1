#define CLOCK 1
#include <time.h>
#include <unistd.h>

// It allows you to track time, retrieve the current time, and advance time using the tick method.
// The CLOCK constant defines the time interval in seconds.

class ProcessTime
{
private:
    time_t current_time;  // Use time_t to store the current time

public:ProcessTime()
    {
        current_time = 0;  // Initialize the current time to 0
    }

    ~ProcessTime()
    {
        // Destructor (if needed)
    }

    time_t getTime() const
    {
        return current_time;  // Return the current time (time_t)
    }

    void tick()
    {
        sleep(CLOCK);  // Sleep for the specified time interval (CLOCK seconds)
        current_time += CLOCK;  // Update the current time
    }
};
