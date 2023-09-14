#define QUANTUM 2
#include <vector>
#include <string>
#include <algorithm>
#include "Context.hpp"     
#include "ProcessTime.hpp"
#include "Process.hpp"  

// This code is a blueprint for different scheduling algorithms like FCFS (First-Come-First-Serve), SJF (Shortest Job First), Priority Scheduling (Preemptive and Non-Preemptive), and Round Robin. 
// Subclasses inherit from this base class and implement the scheduleNext function according to the specific scheduling strategy they represent.
// TODO: Test algorithms and implement Round-Robin


class SchedulerAlgorithm { // Class for scheduling algorithms
protected:
    int context_switch; // Number of context switches
    ProcessTime timer; // Tracks time
    std::vector<Process *> readyProcesses; // Queue of ready processes
    std::vector<Context *> contextQueue;   // Queue of contexts
    

    virtual void enqueueProcess(Process *p) { // Enqueue a process that is ready.
        readyProcesses.push_back(p);
    }
    
    // Checks if process is ready to execute
    bool isProcessReady(std::vector<Process *> &notReadyProcesses) {
        if (!notReadyProcesses.empty() && notReadyProcesses[0]->getCreationTime() < timer.getTime()) { // TODO: verificar se está correto
            enqueueProcess(notReadyProcesses[0]);
            notReadyProcesses.erase(notReadyProcesses.begin());
            return true;
        }
        return false;
    }

public:
    virtual Process *scheduleNext(std::vector<Process *> &notReadyProcesses) = 0; // Pure virtual function for scheduling the next process
    
    virtual std::vector<std::string> getState(int not_ready_size) {  // Get the current state of processes (override in derived classes)
        int my_size = not_ready_size + readyProcesses.size();
        std::vector<std::string> output(my_size, "  ");
        
        for (const auto &process : readyProcesses) {
            output[process->getId() - 1] = "--";
        }
        return output;
    }
    
    Process *getNextProcess() { // Gets next process to run
        return readyProcesses.empty() ? nullptr : readyProcesses[0];
    }
};

// First-Come-First-Serve scheduling algorithm
class FCFS_Algorithm : public SchedulerAlgorithm {
public:
    FCFS_Algorithm(std::vector<Process *> &processes) {
        readyProcesses = std::vector<Process *>(processes.size(), nullptr);
    }
    
    // Schedule the next process based on FCFS  logic
    Process *scheduleNext(std::vector<Process *> &notReadyProcesses) override {
        if (readyProcesses.empty()) {
            if (isProcessReady(notReadyProcesses)) {
                return getNextProcess();
            }
        }
        return getNextProcess();
    }
};

// Shortest Job First scheduling algorithm
class SJF_Algorithm : public SchedulerAlgorithm {
public:
    SJF_Algorithm(std::vector<Process *> &processes) {
        readyProcesses = std::vector<Process *>(processes.size(), nullptr);
    }
    
    // Schedule the next process based on SJF logic
    Process *scheduleNext(std::vector<Process *> &notReadyProcesses) override {
        if (readyProcesses.empty()) {
            if (isProcessReady(notReadyProcesses)) {
                return getNextProcess();
            }
        }

        // Sort ready processes by duration (shortest job first)
        std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process *a, Process *b) {
            return a->getDuration() < b->getDuration();
        });
        
        return getNextProcess();
    }
};

// Priority Non-Preemptive scheduling algorithm
class PNP_Algorithm : public SchedulerAlgorithm {
public:
    PNP_Algorithm(std::vector<Process *> &processes) {
        readyProcesses = std::vector<Process *>(processes.size(), nullptr);
    }
    
    // Schedule the next process based on Priority Non-Preemptive logic
    Process *scheduleNext(std::vector<Process *> &notReadyProcesses) override {
        if (readyProcesses.empty()) {
            if (isProcessReady(notReadyProcesses)) {
                return getNextProcess();
            }
        }
        
        // Sort ready processes by priority (highest priority first)
        std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process *a, Process *b) {
            return a->getPriority() > b->getPriority();
        });
        
        return getNextProcess();
    }
};


// Priority Preemptive scheduling algorithm
class PP_Algorithm : public SchedulerAlgorithm {
public:
    PP_Algorithm(std::vector<Process *> &processes) {
        readyProcesses = std::vector<Process *>(processes.size(), nullptr);
    }

    // Schedule the next process based on Priority Preemptive logic
    Process *scheduleNext(std::vector<Process *> &notReadyProcesses) override {
        if (readyProcesses.empty()) {
            if (isProcessReady(notReadyProcesses)) {
                return getNextProcess();
            }
        }

        // Sort ready processes by priority (highest priority first)
        std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process *a, Process *b) {
            return a->getPriority() > b->getPriority();
        });
        
        return getNextProcess();
    }
};

// TODO: Implement Round Robin
class RR_Algorithm : public SchedulerAlgorithm {
private:
    int quantum;

public:
    RR_Algorithm(std::vector<Process *> &processes) {
        readyProcesses = std::vector<Process *>(processes.size(), nullptr);
        quantum = QUANTUM;
    }
    
    Process *scheduleNext(std::vector<Process *> &notReadyProcesses) override {
        if (readyProcesses.empty()) {
            if (isProcessReady(notReadyProcesses)) {
                return getNextProcess();
            }
        }
        
        // Implement Round Robin scheduleNext logic here with the quantum
        
        return getNextProcess();
    }
};
