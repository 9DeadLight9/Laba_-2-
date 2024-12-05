#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int start_time = -1;
    int finish_time = -1;
};


std::vector<Process> generateProcesses(int num_processes) {
    std::vector<Process> processes;
    srand(time(0));
    for (int i = 0; i < num_processes; ++i) {
        processes.push_back({
            i + 1,
            rand() % 10,        
            rand() % 10 + 1,   
            rand() % 5 + 1,     
            0                   
            });
        processes.back().remaining_time = processes.back().burst_time;
    }
    return processes;
}


void roundRobin(std::vector<Process> processes, int quantum) {
    std::cout << "\nRound Robin Simulation\n";
    int time = 0;
    std::queue<Process*> ready_queue;

    while (true) {
        for (auto& process : processes) {
            if (process.arrival_time <= time && process.remaining_time > 0) {
                ready_queue.push(&process);
            }
        }

        if (ready_queue.empty()) {
            if (std::all_of(processes.begin(), processes.end(),
                [](const Process& p) { return p.remaining_time == 0; })) {
                break;
            }
            ++time;
            continue;
        }

        Process* current = ready_queue.front();
        ready_queue.pop();
        int exec_time = std::min(current->remaining_time, quantum);
        time += exec_time;
        current->remaining_time -= exec_time;

        std::cout << "Process ID: " << current->id
            << ", Remaining Time: " << current->remaining_time
            << ", Current Time: " << time << "\n";
    }
}

void fcfs(std::vector<Process> processes) {
    std::cout << "\nFCFS Simulation\n";
    std::sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.arrival_time < b.arrival_time;
        });

    int time = 0;
    for (auto& process : processes) {
        if (time < process.arrival_time) {
            time = process.arrival_time;
        }
        process.start_time = time;
        time += process.burst_time;
        process.finish_time = time;

        std::cout << "Process ID: " << process.id
            << ", Start Time: " << process.start_time
            << ", Finish Time: " << process.finish_time
            << ", Waiting Time: " << process.start_time - process.arrival_time
            << "\n";
    }
}

void priorityScheduling(std::vector<Process> processes) {
    std::cout << "\nPriority Scheduling Simulation\n";
    std::sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.priority < b.priority;
        });

    int time = 0;
    for (auto& process : processes) {
        if (time < process.arrival_time) {
            time = process.arrival_time;
        }
        process.start_time = time;
        time += process.burst_time;
        process.finish_time = time;

        std::cout << "Process ID: " << process.id
            << ", Priority: " << process.priority
            << ", Start Time: " << process.start_time
            << ", Finish Time: " << process.finish_time
            << "\n";
    }
}

// Головна функція
int main() {
    int num_processes = 5;
    int quantum = 3;

    std::vector<Process> processes = generateProcesses(num_processes);

    std::cout << "Generated Processes:\n";
    for (const auto& process : processes) {
        std::cout << "ID: " << process.id
            << ", Arrival Time: " << process.arrival_time
            << ", Burst Time: " << process.burst_time
            << ", Priority: " << process.priority << "\n";
    }

    roundRobin(processes, quantum);
    fcfs(processes);
    priorityScheduling(processes);

    return 0;
}
