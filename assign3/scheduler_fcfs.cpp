/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"
#include <algorithm>
#include <iostream>
using namespace std;

// Constructor
SchedulerFCFS::SchedulerFCFS() {}

// Destructor
SchedulerFCFS::~SchedulerFCFS() {}

/**
 * @brief Initialize the FCFS scheduler with a list of processes.
 * @param process_list The list of processes to be scheduled.
 */
void SchedulerFCFS::init(vector<PCB>& processes) {
    this->process_list = processes;
    turnaround_times.resize(process_list.size(), 0);
    waiting_times.resize(process_list.size(), 0);
}

/**
 * @brief Simulate the FCFS scheduling algorithm.
 *        It processes the tasks in the order they arrive.
 */
void SchedulerFCFS::simulate() {
    int current_time = 0;

    // Process each PCB (Process Control Block) in order
    for (size_t i = 0; i < process_list.size(); ++i) {
        PCB& process = process_list[i];

        // Waiting time is the current time minus the arrival time
        waiting_times[i] = current_time - process.arrival_time;

        // Turnaround time is the waiting time + burst time
        turnaround_times[i] = waiting_times[i] + process.burst_time;

        // Update current time after processing the task
        current_time += process.burst_time;
    }
}

/**
 * @brief Print the results, including individual and average turnaround/waiting times.
 */
void SchedulerFCFS::print_results() {
    int total_turnaround = 0;
    int total_waiting = 0;

    for (size_t i = 0; i < process_list.size(); ++i) {
        cout << "Process " << process_list[i].id 
                  << " turn-around time = " << turnaround_times[i]
                  << ", waiting time = " << waiting_times[i] << endl;
        
        total_turnaround += turnaround_times[i];
        total_waiting += waiting_times[i];
    }

    // Calculate and print average times
    double avg_turnaround = static_cast<double>(total_turnaround) / process_list.size();
    double avg_waiting = static_cast<double>(total_waiting) / process_list.size();

    cout << "Average turn-around time = " << avg_turnaround 
              << ", Average waiting time = " << avg_waiting << endl;
}
