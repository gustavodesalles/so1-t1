#include <iostream>
#include <fstream>
#include <vector>
#include <memory> // For smart pointers
#include "ProcessVariables.hpp" // Assuming this header provides the ProcessVariables class

class FileManager {
private:
    std::ifstream fileStream; // Input file stream to read data from a file

public:
    FileManager(const std::string& filename = "entrada.txt") {
        fileStream.open(filename); // Attempt to open the specified file
        if (!fileStream.is_open()) {
            std::cerr << "Error opening the file: " << filename << "\n";
            // TODO: Maybe consider throwing an exception here to handle the error
        }
    }

    ~FileManager() {
        if (fileStream.is_open()) {
            fileStream.close(); // Close the file stream if it's open
        }
    }

    // Read parameters of processes to be scheduled from the file and store them in a vector of smart pointers.
    void readProcessParameters(std::vector<std::unique_ptr<ProcessVariables>>& waitingQueue) {
        int creationTime, duration, priority;

        if (!fileStream.is_open()) {
            std::cerr << "File is not open!\n"; // Handle the case where the file is not open
            return; // Return early on error
        }

        int processId = 0;
        while (fileStream >> creationTime >> duration >> priority) {
            processId++;
            int index = 0;

            // Sort the processes by creation time in the waitingQueue
            while (index < waitingQueue.size() && waitingQueue[index]->getCreationTime() < creationTime) {
                index++;
            }

            // Create a unique_ptr for ProcessVariables using std::make_unique
            std::unique_ptr<ProcessVariables> processParams = std::make_unique<ProcessVariables>(creationTime, duration, priority);

            // Insert the processParams into the waitingQueue and move ownership
            waitingQueue.insert(waitingQueue.begin() + index, std::move(processParams));
        }
    }
};

int main() {
    std::vector<std::unique_ptr<ProcessVariables>> waitingQueue; // Use std::unique_ptr for ownership
    FileManager inputFile;

    // Read process parameters from the file and store them in waitingQueue
    inputFile.readProcessParameters(waitingQueue);

    // Print the ProcessVariables objects stored in waitingQueue
    for (const auto& processParams : waitingQueue) {
        std::cout << *processParams << "\n";
    }

    return 0;
}
