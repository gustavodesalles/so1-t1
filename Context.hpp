#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <random>

// This class represents a context of a process. 
// It stores various attributes like registers, program counter, stack pointer, and progress. The Context constructor initializes these attributes with random values. 
// The generateRandomValue function generates random long integers for these attributes.

class Context
{
public:

    long int SP;
    long int PC;
    long int ST;
    long int *registers;
    float progress; // Progress of the context.

 
    Context() // Constructor.
    {   
        // Initializes all registers with random values.
        registers = new long int[6]; // Dynamically allocate an array of 6 long integers for registers.

        for (int i = 0; i < 6; ++i)
        {
            registers[i] = generateRandomValue();
        }

        SP = generateRandomValue();
        PC = generateRandomValue();
        ST = generateRandomValue();
        progress = static_cast<float>(generateRandomValue());
    }

    ~Context() // Destructor
    {
        delete[] registers;
    }

    long int generateRandomValue() // Function to generate a random long integer value.
    {
        std::random_device rd; // Provides the random seed for the pseudo-random number generator.
        std::mt19937 generator(rd()); // Creates pseudo-random number generator mt19937 (Mersenne Twister).
        std::uniform_int_distribution<long int> dis_long(std::numeric_limits<long int>::min(), std::numeric_limits<long int>::max()); // Creates distribution to generate numbers in the entire range o `long int`.
        return dis_long(generator); // returbs a `long int` value from the distribution.
    }

    // Function to alter registers randomly and return if the process has finished
    int processing(int progress_time)
    {
        int output = 0;
        progress += 100 * (static_cast<float>(progress_time) / parameter.get_duration()); //TODO: Update progress based on time

        if (progress >= 100.0) // Checks if progress made it to 100.0 or higher
        {
            output = 1;
        }

        // Generate random numbers for all the registers
        for (int i = 0; i < 6; ++i)
        {registers[i] = generateRandomValue();
        }
        PC = generateRandomValue();
        SP = generateRandomValue();
        ST = generateRandomValue();
        return output;
    }
};

class New_Context : public Context
{
public:

    New_Context() : Context() // Calls the base class constructor
    {
    }

};
#endif