#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <random>
#include <array>

class Context
{
private:
    std::array<long int, 6> registers; // An array to store registers
    long int SP;                       // Stack Pointer
    long int PC;                       // Program Counter
    long int ST;                       // Stack
    float progress;                    // Progress of the context

    // Private function to generate a random long integer value
    long int generateRandomValue()
    {
        // Use C++11 random library for better random number generation
        static std::random_device rd;
        static std::mt19937 generator(rd());
        std::uniform_int_distribution<long int> dis_long(std::numeric_limits<long int>::min(), std::numeric_limits<long int>::max());
        return dis_long(generator);
    }

public:
    // Constructor
    Context()
        : registers{}, SP(generateRandomValue()), PC(generateRandomValue()), ST(generateRandomValue()), progress(static_cast<float>(generateRandomValue()))
    {
        // Initialize registers with random values
        for (int i = 0; i < 6; ++i)
        {
            registers[i] = generateRandomValue();
        }
    }

    // Getter methods for attribute access
    const std::array<long int, 6>& getRegisters() const { return registers; }
    long int getSP() const { return SP; }
    long int getPC() const { return PC; }
    long int getST() const { return ST; }
    float getProgress() const { return progress; }

    // Function to alter registers and other attributes randomly (Way more simplified)
    void processing()
    {
        // Randomly update registers
        for (int i = 0; i < 6; ++i)
        {
            registers[i] = generateRandomValue();
        }

        // Randomly update PC, SP, and ST
        PC = generateRandomValue();
        SP = generateRandomValue();
        ST = generateRandomValue();
    }
};

class New_Context : public Context
{
public:
    // Constructor for the derived class
    New_Context()
        : Context()
    {
    }
};

#endif
