/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority_rr.h"

// TODO: add implementation of SchedulerPriority constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum){
    this->quantum = time_quantum;
};

SchedulerPriorityRR::~SchedulerPriorityRR(){};

void SchedulerPriorityRR::init(std::vector<PCB>& process_list){
    this->processes = process_list;
    turnaround_times.resize(8, 0);
    waiting_times.resize(8, 0);
    id_order.resize(8, 0);
    remaining_burst_time.resize(8,0);
    priorities.resize(0, 0);
    inOrderPriorities.resize(8, 0);
    burst_time.resize(8, 0);
    completed_process.resize(8, false);


    //Add each process to the queue (based off of priority)
    for(int i = 0; i < 8; i++){
        queue.addPCB(processes[i]);
    }
};

void SchedulerPriorityRR::simulate() {
    unsigned int current_time = 0;
    int completed = 0;
    int current = 0;
    int iterations = 0;
    int total_exec_time = 0;

    // Initialize the process priorities and burst times
    while (iterations < 8) {
        PCB pcb = queue.removePCB();
        remaining_burst_time[iterations] = pcb.burst_time;
        id_order[iterations] = pcb.id; // Store the actual process ID in order
        priorities.push_back(pcb.priority);
        inOrderPriorities[iterations] = pcb.priority;
        burst_time[iterations] = pcb.burst_time;
        iterations++;
    }

    // Run the simulation
    while (completed != 8) {
        int exec_time = quantum;
        int process_id = id_order[current]; // Get the actual process ID

        // Only run if there are no higher-priority processes to interrupt
        if (!checkPriority(priorities, inOrderPriorities[current])) {
            // Process if it has remaining burst time and is not completed
            if (remaining_burst_time[current] > 0 && !completed_process[current]) {
                // Execute process within quantum or remaining burst time
                exec_time = std::min(quantum, remaining_burst_time[current]);
                remaining_burst_time[current] -= exec_time;
                current_time += exec_time;

                cout << "Running process T" << process_id << " for " << exec_time << " time units." << endl;

                // Mark process as completed if burst time is 0 or less
                if (remaining_burst_time[current] <= 0) {
                    completed_process[current] = true;
                    completed++;
                    cout << "Process T" << process_id << " completed." << endl;

                    // Update turnaround and waiting times for the correct process ID
                    turnaround_times[process_id] = current_time;
                    waiting_times[process_id] = turnaround_times[process_id] - burst_time[current];
                }
            }
        }

        // Move to the next process, ensuring fairness in rotation
        current = (current + 1) % processes.size();

        // Ensure no infinite loop by skipping completed processes
        while (completed_process[current] && completed != 8) {
            current = (current + 1) % processes.size();
        }
    }
};

void SchedulerPriorityRR::print_results(){
    int total_turnaround = 0;
    int total_waiting = 0;
    double avg_turnaround = 0;
    double avg_waiting = 0;

    for(size_t i = 0; i < 8; i++) {
        cout << "Process " << (i + 1) << " turn-around time = " << turnaround_times[i]
             << ", waiting time = " << waiting_times[i] << endl;

        total_turnaround += turnaround_times[i];
        total_waiting += waiting_times[i];
    }

    avg_turnaround = static_cast<double>(total_turnaround) / 8;
    avg_waiting = static_cast<double>(total_waiting) / 8;

    cout << "Average turn-around time: " << avg_turnaround << ", Average waiting time = " << avg_waiting << endl;
};


bool SchedulerPriorityRR::checkPriority(std::vector<int> priorities, int priorityToCheck){
     for (int i = 0; i < priorities.size(); ++i) {
        // If there is a higher-priority process, return true
        if (!completed_process[i] && priorities[i] > priorityToCheck) {
            return true;
        }
    }
    return false;
};
