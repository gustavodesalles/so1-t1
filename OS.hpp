#include <iostream>
#include <iomanip>
#include <vector>
#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"
#include "Process.hpp"
#include "ProcessVariables.hpp"

/* Improved operating system simulation class.
The OS class represents an operating system simulation and is responsible for managing and executing processes using different scheduling algorithms (such as FCFS, PNP, ETC). 
It reads process parameters from a file, schedules the processes based on their characteristics and scheduling algorithm, and displays the execution timeline with process scheduling details.
It also (at least it should) calculates and prints statistics at the end of execution, including turnaround times, waiting times, and the number of context switches.

*/
class OS
{
private:
    Generic_CPU cpu;
    SchedulerAlgorithm *scheduler;
    std::vector<Process *> waitingQueue;

    // Function to choose a scheduling algorithm based on the input string
    SchedulerAlgorithm *chooseScheduler(const std::string &algorithm)
    {
        if (algorithm == "FCFS")
        {
            return new FCFS_Algorithm(waitingQueue);
        }
        else if (algorithm == "SJF")
        {
            return new SJF_Algorithm(waitingQueue);
        }
        else if (algorithm == "PNP")
        {
            return new PNP_Algorithm(waitingQueue);
        }
        else if (algorithm == "PP")
        {
            return new PP_Algorithm(waitingQueue);
        }
        else
        {
            return new RR_Algorithm(waitingQueue);
        }
    }

    // Function to insert a process into the queue based on its creation time
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

    // Function to print the initial timeline header
    void printInitialTimeline()
    {
        std::cout << "Time ";
        for (int i = 0; i < waitingQueue.size(); ++i)
        {
            std::cout << " P" << i + 1;
        }
        std::cout << '\n';
    }

    // Function to print the timeline for each second
    void printTimeline(int time, const std::vector<std::string> &state)
    {
        std::cout << std::left << std::setw(4) << time << " - ";
        for (int i = 0; i < state.size(); ++i)
        {
            std::cout << state[i] << ' ';
        }
        std::cout << '\n';
    }

    // Function to print statistics at the end of execution
    void printStatistics(int Nprocess, int Ncontext_switch, const std::vector<std::array<int, 2>> &end_data)
    {
        std::cout << "\nTurnaround\n";
        std::cout << "Time:   ";
        float media = 0;
        for (int j = 0; j < Nprocess; ++j)
        {
            media += end_data[j][0];
            std::cout << std::right << std::setw(2) << end_data[j][0] << "  ";
        }
        media /= static_cast<float>(Nprocess);
        std::cout << "| media = " << media << std::endl;

        media = 0;
        std::cout << "Wait\n";
        std::cout << "Time:   ";
        for (int j = 0; j < Nprocess; ++j)
        {
            media += end_data[j][1];
            std::cout << std::right << std::setw(2) << end_data[j][1] << "  ";
        }
        media /= static_cast<float>(Nprocess);
        std::cout << "| media = " << media << std::endl;
        std::cout << "N de trocas de contexto = " << Ncontext_switch << std::endl;
    }

public:
    // Constructor that takes a scheduling algorithm as input
    OS(const std::string &algorithm)
    {
        File inputFile;
        scheduler = chooseScheduler(algorithm);
        std::vector<ProcessVariables *> variables;
        inputFile.readFile(variables);

        for (int i = 0; i < variables.size(); i++)
        {
            Process p(i + 1, *variables[i]);
            insertProcessByCreationTime(p);
        }

        cpu = Generic_CPU();
    }

    // Destructor to clean up memory
    ~OS()
    {
        delete scheduler;
        for (int i = 0; i < waitingQueue.size(); ++i)
        {
            delete waitingQueue[i];
        }
    }

    // Function to start the operating system simulation
    void start()
    {
        printInitialTimeline();
        std::vector<std::string> output(waitingQueue.size(), "  ");
        int prontos = 0;
        int Nprocessos = waitingQueue.size();
        bool running = Nprocessos;
        int time = 0;

        while (running)
        {
            while ((prontos < waitingQueue.size()) && (waitingQueue[prontos]->getCreationTime() == time))
            {
                scheduler->readyProcess(waitingQueue[prontos]);
                prontos++;
            }

            Process *current = scheduler->scheduleNext(waitingQueue);
            scheduler->getState(output);

            if (current != nullptr)
            {
                cpu.setContext(current->getContext());
            }

            running = (current != nullptr) || (prontos == 0);

            if (running)
            {
                printTimeline(time, output);
            }

            time++;
        }

        std::vector<std::array<int, 2>> end_data(Nprocessos, {0, 0});
        scheduler->getFinished(end_data);
        printStatistics(Nprocessos, scheduler->getContextSwitch(), end_data);
    }
};

int main()
{
    // Create an OS instance with the specified scheduling algorithm
    OS os("FCFS");
    os.start(); // Start the OS simulation
    return 0;
}
