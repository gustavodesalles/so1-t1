#ifndef PROCESS_VARIABLE_HPP
#define PROCESS_VARIABLE_HPP

// This class stores information about a process, including its creation time, duration, and priority.
// It also provides methods to access and modify these attributes and allows for convenient printing of ProcessVariables objects.

#include <iostream>

class ProcessVariables {
public:
    // Constructor with member initializer list
    ProcessVariables(int c, int d, int p) : creation_time(c), duration(d), priority(p) {}

    // Getter methods
    int getPriority() const {
        return priority;
    }
   
    int getCreationTime() const {
        return creation_time;
    }

    int getDuration() const {
        return duration;
    }

    // Setter method to update the priority
    void setPriority(int newPriority) {
        priority = newPriority;
    }

    // Overloaded << operator for easier printing
    friend std::ostream& operator<<(std::ostream& os, const ProcessVariables& params) {
        os << "Creation time = " << params.creation_time << " Duration = " << params.duration << " Priority = " << params.priority;
        return os;
    }

private:
    int creation_time;
    int duration;  // Duration is measured in seconds
    int priority;
};

#endif  // PROCESS_VARIABLE_HPP


