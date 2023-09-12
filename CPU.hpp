#include "Context.hpp"

// Sets up a basic class hierarchy where CPU is an abstract base class with pure virtual functions, and a derived class that provides implementations for these functions. 
// The purpose and behavior of these functions will depend on how they are implemented in the specific derived classes.

class CPU
{
protected:
    Context current_context; // Can only be acessed by derived classes, like "Generic_CPU"

public:
    virtual void change_context_without_preemption(Context new_context) = 0; // Pure virtual function. Switches context to a new context without preempting the current one.
    virtual void change_context_with_preemption(Context new_context) = 0; // Pure virtual function. It preempts or replaces the current context of the CPU with a new context
};

class Generic_CPU : public CPU
{
public:
    Generic_CPU() {} //Oops, almost forgot the constructor

    void change_context_without_preemption(Context new_context) override // Override of the virtual function
    {
        current_context = new_context;
    }

        void change_context_with_preemption(Context new_context) override // Override of the virtual function
    {
        current_context = new_context;
    }
};