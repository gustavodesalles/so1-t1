#include <iostream>
#include <iomanip>
#include <vector>
#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"
#include "Process.hpp" 
#include "ProcessVariables.hpp" 

// This class represents an operating system simulation.
// It reads process variables from a file, schedules and executes processes using different scheduling algorithms (e.g., FCFS, SJF, PNP, PP, Round Robin), and displays the execution timeline with process scheduling.
// TODO: Write better comments and test

class OS
{
private:
    CPU cpu;
    SchedulingAlgorithm *scheduler; // Pointer to a scheduling algorithm
    std::vector<Process *> waitingQueue; // Queue to hold processes waiting to be scheduled

     // Function to choose a scheduling algorithm based on input string
    SchedulingAlgorithm *chooseScheduler(const std::string &algorithm)
    {
        if (algorithm == "FCFS")
        {
            return new FCFSAlgorithm(waitingQueue);
        }
        else if (algorithm == "SJF")
        {
            return new SJFAlgorithm(waitingQueue);
        }
        else if (algorithm == "PNP")
        {
            return new PNPAlgorithm(waitingQueue);
        }
        else if (algorithm == "PP")
        {
            return new PPAlgorithm(waitingQueue);
        }
        else
        {
            return new RRAlgorithm(waitingQueue);
        }
    }

    // Function to insert a process into the queue based on creation time
    void insertProcessByCreationTime(Process &p)
    {
        int i = 0;
        while (i < waitingQueue.size() && waitingQueue[i]->getCreationTime() < p.getCreationTime())
        {
            ++i;
        }
        waitingQueue.insert(waitingQueue.begin() + i, &p);
    }

    // Function to print process parameters
    void printProcessParameters(const std::vector<ProcessVariables *> &processes)
    {
        for (const auto &p : processes)
        {
            std::cout << *p;
        }
    }

public:
    // Constructor that takes a scheduling algorithm as input
    OS(const std::string &algorithm)
    {
        File inputFile; 
        scheduler = chooseScheduler(algorithm); // Choose and instantiate the specified scheduling algorithm
        std::vector<ProcessVariables *> variables;
        inputFile.readFile(variables); // Read process variables from a file (Obvious comment be obvious)

        for (int i = 0; i < variables.size(); i++)
        {
            Process p(i + 1, *variables[i]); // Create a Process instance
            insertProcessByCreationTime(p); // Insert the process into the queue based on creation time
        }

        cpu = CPU(); // Init the CPU
    }

    // Function to start the OS
    void start()
    {
        std::cout << "Time ";
        for (int i = 0; i < waitingQueue.size(); ++i)
        {
            std::cout << " P" << i + 1;
        }
        std::cout << '\n';
        int time = 0;
        while (!waitingQueue.empty()) // Continue until all processes are done
        {
            std::cout << std::left << std::setw(4) << time << " - ";
            time++;
            Process *current = scheduler->scheduleNext(waitingQueue);  // Get the next scheduled process
            std::vector<std::string> state = scheduler->getState(waitingQueue.size());
            state[current->getID() - 1] = "##"; // Mark the currently executing process

            for (int i = 0; i < state.size(); ++i)
            {
                std::cout << state[i] << ' ';
            }
            std::cout << '\n';
        }
    }
};
