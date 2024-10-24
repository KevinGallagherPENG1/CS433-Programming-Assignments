/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <algorithm>
#include <iostream>
#include <limits.h> // Included for INT_MAX
using namespace std;

// Constructor
SchedulerSJF::SchedulerSJF() {}

// Destructor
SchedulerSJF::~SchedulerSJF() {}

/**
 * @brief Initialize the SJF scheduler with a list of processes.
 * @param processes The list of processes to be scheduled.
 */
void SchedulerSJF::init(vector<PCB>& processes) {
    this->process_list = processes;
    turnaround_times.resize(process_list.size(), 0);
    waiting_times.resize(process_list.size(), 0);
}

/**
 * @brief Simulate the SJF scheduling algorithm.
 *        It selects the process with the shortest burst time first.
 */
void SchedulerSJF::simulate() {
    int current_time = 0;
    vector<bool> completed(process_list.size(), false); // Track completed processes

    // Process all tasks until all are completed
    for (size_t completed_count = 0; completed_count < process_list.size(); ++completed_count) {
        int shortest_job_index = -1;
        int min_burst_time = INT_MAX;

        // Find the process with the shortest burst time that hasn't been completed yet
        for (size_t i = 0; i < process_list.size(); ++i) {
            if (!completed[i] && static_cast<int>(process_list[i].burst_time) < min_burst_time) {
                min_burst_time = process_list[i].burst_time;
                shortest_job_index = i;
            }
        }

        // If found, process it
        if (shortest_job_index != -1) {
            PCB& process = process_list[shortest_job_index];

            // Waiting time is the current time minus the arrival time
            waiting_times[shortest_job_index] = current_time - process.arrival_time;

            // Turnaround time is the waiting time + burst time
            turnaround_times[shortest_job_index] = waiting_times[shortest_job_index] + process.burst_time;

            // Update current time after processing the task
            current_time += process.burst_time;

            // Mark the process as completed
            completed[shortest_job_index] = true;
        }
    }
}

/**
 * @brief Print the results, including individual and average turnaround/waiting times.
 */
void SchedulerSJF::print_results() {
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
