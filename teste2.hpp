#include <vector>
#include <algorithm>
#include "Context.hpp"
#include "ProcessTime.hpp"
#include "Process.hpp"

#define QUANTUM 2

// Function to enqueue a process that is ready.
void enqueueProcess(std::vector<Process*>& readyProcesses, Process* p) {
    readyProcesses.push_back(p);
}

// Function to check if a process is ready to execute.
bool isProcessReady(std::vector<Process*>& readyProcesses, std::vector<Process*>& notReadyProcesses, ProcessTime& timer) {
    if (!notReadyProcesses.empty() && notReadyProcesses[0]->getCreationTime() < timer.getTime()) {
        enqueueProcess(readyProcesses, notReadyProcesses[0]);
        notReadyProcesses.erase(notReadyProcesses.begin());
        return true;
    }
    return false;
}

// Function to set the currently executing process
void setCurrentExecutingProcess(Process* process) {
    Context::currentExecutingProcess = process;
}

// Function to get the currently executing process
Process* getCurrentExecutingProcess() {
    return Context::currentExecutingProcess;
}


// Function to sort processes based on start times (FCFS)
void sortFCFS(std::vector<Process>& processes) {
    std::stable_sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.startTime < b.startTime;
    });
}

// Function to sort processes based on durations (SJF)
void sortSJF(std::vector<Process>& processes) {
    sortFCFS(processes);
    std::stable_sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.duration < b.duration;
    });
}

// Function for the First-Come-First-Serve (FCFS) scheduling algorithm.
Process* fcfsScheduleNext(std::vector<Process*>& readyProcesses, std::vector<Process*>& notReadyProcesses, ProcessTime& timer, std::vector<Process>& processes) {
    if (readyProcesses.empty()) {
        if (isProcessReady(readyProcesses, notReadyProcesses, timer)) {
            // Sort the processes based on arrival time (FCFS)
            sortFCFS(processes);

            // Update the readyProcesses vector
            for (Process& p : processes) {
                enqueueProcess(readyProcesses, &p);
            }

            // Return the first process in the updated readyProcesses vector
            return readyProcesses[0];
        }
    }
    return readyProcesses.empty() ? nullptr : readyProcesses[0];
}

// Function for the Shortest Job First (SJF) scheduling algorithm.
// Function for the Shortest Job First (SJF) scheduling algorithm.
Process* sjfScheduleNext(std::vector<Process*>& readyProcesses, std::vector<Process*>& notReadyProcesses, ProcessTime& timer, std::vector<Process>& processes) {
    if (readyProcesses.empty()) {
        if (isProcessReady(readyProcesses, notReadyProcesses, timer)) {
            // Step 2: If there are processes ready, sort them by job duration in ascending order (shortest job first).
            std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
                return a->duration < b->duration;
            });

            // Step 3: Check if the readyProcesses vector is not empty after sorting.
            if (!readyProcesses.empty()) {
                // Step 4: Select the process with the shortest job duration (first process in the sorted vector).
                Process* nextProcess = readyProcesses[0];

                // Step 5: Check if the selected process is different from the currently executing process.
                if (nextProcess != getCurrentExecutingProcess()) {
                    // Step 5.1: Perform a context switch or any necessary actions for preemption by calling setCurrentExecutingProcess.
                    setCurrentExecutingProcess(nextProcess);
                }

                // Step 6: Return the selected process as the next process to execute.
                return nextProcess;
            }
        }
    }
    // Step 1 (alternative): If no process is ready to execute, return nullptr.
    return readyProcesses.empty() ? nullptr : readyProcesses[0];
}

// Function to sort processes based on static priorities (Non-preemptive Priority)
void sortNonPreemptivePriorities(std::vector<Process>& processes) {
    sortFCFS(processes);
    std::stable_sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority > b.priority; // Sort in descending order (higher priority first)
    });
}


// Function for Non-preemptive Priority (PNP) scheduling algorithm.
Process* pnpScheduleNext(std::vector<Process*>& readyProcesses, std::vector<Process*>& notReadyProcesses, ProcessTime& timer, std::vector<Process>& processes) {
    if (readyProcesses.empty()) {
        if (isProcessReady(readyProcesses, notReadyProcesses, timer)) {
            sortNonPreemptivePriorities(processes); // Use the non-preemptive priorities sorting function
            return readyProcesses[0];
        }
    }
    return readyProcesses.empty() ? nullptr : readyProcesses[0];
}

// Function for the Priority Preemptive (PP) scheduling algorithm.
Process* ppScheduleNext(std::vector<Process*>& readyProcesses, std::vector<Process*>& notReadyProcesses, ProcessTime& timer) {
    // Step 1: Check if there are no processes ready to execute in the readyProcesses vector.
    if (readyProcesses.empty()) {
        // Step 1.1: Check if there are processes in the notReadyProcesses vector that are ready based on their creation time.
        if (isProcessReady(readyProcesses, notReadyProcesses, timer)) {
            // Step 2: If there are processes ready, sort them by priority in descending order (highest priority first).
            std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
                return a->priority > b->priority;
            });

            // Step 3: Check if the readyProcesses vector is not empty after sorting.
            if (!readyProcesses.empty()) {
                // Step 4: Select the process with the highest priority (first process in the sorted vector).
                Process* nextProcess = readyProcesses[0];

                // Step 5: Check if the selected process is different from the currently executing process.
                if (nextProcess != getCurrentExecutingProcess()) {
                    // Step 5.1: Perform a context switch or any necessary actions for preemption by calling setCurrentExecutingProcess.
                    setCurrentExecutingProcess(nextProcess);
                }

                // Step 6: Return the selected process as the next process to execute.
                return nextProcess;
            }
        }
    }
    // Step 1 (alternative): If no process is ready to execute, return nullptr.
    return readyProcesses.empty() ? nullptr : readyProcesses[0];
}

void roundRobin(std::vector<Process>& processes, int quantum) {
    sortFCFS(processes);
    Process current = processes[0];
    int time = current.startTime;
    std::cout << "Time ";
    for (int i = 0; i < processes.size(); ++i)
    {
        std::cout << " P" << i + 1;
    }
    std::cout << '\n';
    for (int i = 0; i < time; i++)
    {
        std::cout << i << "-" << i + 1;
        for (int j = 0; j < processes.size(); j++)
        {
            std::cout << "   ";
        }
        std::cout << '\n';
    }

    while (!allProcessesCompleted(processes))
    {
        for (int i = 0; i < quantum; i++)
        {
            current.timeExecuted++;
            printCurrentState(processes, time);
            time++;
            if (current.timeExecuted == current.duration)
            {
                // Change the state of the current process to completed
                break;
            }
            
        }
        if (current.timeExecuted == current.duration) // Check again at the end of the quantum
        {
            // Change the state of the current process to completed
        } else {
            // Change the state of the current process to ready
        }
        // Find the next process in the queue
    }
}


// Function for Round Robin (RR) scheduling algorithm.
Process* rrScheduleNext(std::vector<Process*>& readyProcesses, std::vector<Process*>& notReadyProcesses, ProcessTime& timer, int quantum) {
    if (readyProcesses.empty()) {
        if (isProcessReady(readyProcesses, notReadyProcesses, timer)) {
            // Implement Round Robin scheduleNext logic here with the quantum
            // Consider using a queue or circular data structure for RR
        }
    }
    return readyProcesses.empty() ? nullptr : readyProcesses[0];
}

int main() { 


    Process* nextProcess = fcfsScheduleNext(readyProcesses, notReadyProcesses, timer, processes);

    return 0;
}
