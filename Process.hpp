#include "ProcessVariables.hpp"
#include "Context.hpp"
#include <iostream>
#include <vector>

// This class simulates the attributes and behavior of a process within an operating system simulation.
// It allows to create and manage individual processes, track their states and execution times, and simulate their execution in a controlled environment.

class Process
{
public:
// Initializes the process with an ID and variables
    Process(int id, ProcessVariables &variables) : id(id), variables(variables), start_time(-1), end_time(-1), state(State::NEW), context(New_Context())
    {
    }

    // Getter methods to retrieve process variables
    int getId() const
    {
        return id;
    }

    int getPriority() const
    {
        return variables.getPriority();
    }

    int getStartTime() const
    {
        return start_time;
    }

    int getCreationTime() const
    {
        return variables.getCreationTime();
    }

    int getDuration() const
    {
        return variables.getDuration();
    }

    int getEndTime() const
    {
        return end_time;
    }

    int getTurnaround() const
    {
        return (end_time - start_time);
    }

    // Get the current state of the process as a string
    std::string getState() const
    {
        switch (state)
        {
        case State::NEW:
            return "new";
        case State::READY:
            return "ready";
        case State::RUNNING:
            return "running";
        case State::TERMINATED:
            return "terminated";
        default:
            return "unknown";
        }
    }

    
    // Simulate the running of a process for a given time
    Context running(int time)
    {
        state = context.processing(time); // Update the state using the context
        return context; // Return the updated context
    }

    // Setters for the start and end time of the process
    void setStartTime(int start)
    {
        start_time = start;
    }

    void setEndTime(int end)
    {
        end_time = end;
    }

private:
    // Enum of the possible states of a process
    enum class State
    {
        NEW,
        READY,
        RUNNING,
        TERMINATED
    };

    int id;                         // Identifier for the process
    int start_time;                 // Time whe the process finishes running
    int end_time;                   // Time whe the process starts running
    ProcessVariables &variables;   // Reference to the process variables
    Context context;                // Current state of the process
    State state;                    // Process context for execution
};
