/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

// TODO: add implementation of SchedulerRR constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerRR::SchedulerRR(int time_quantum){
    this->quantum = time_quantum;
};

SchedulerRR::SchedulerRR(){
    this->quantum = 10;
};

SchedulerRR::~SchedulerRR(){};

void SchedulerRR::init(std::vector<PCB>& process_list){
    this->processes = process_list;
    waiting_times.resize(process_list.size(), 0);
    turnaround_times.resize(process_list.size(), 0);
    remaining_burst_time.resize(process_list.size(), 0);

    //Get burst time for each process
    for(size_t i = 0; i < process_list.size(); i++){
        remaining_burst_time[i] = process_list[i].burst_time;
    }
};

void SchedulerRR::simulate(){
    unsigned int current_time = 0;
    int completed = 0;
    int current = 0;
    bool completed_process[processes.size()];

    for(size_t i = 0; i < processes.size(); i++){
        completed_process[i] = false;
    }

    while(completed != processes.size()){
        PCB& pcb = processes[current];
        int exec_time = quantum;

        //If there is still remaining burst time for the current process:
        //  Update remaining burst time
        //  Update current_time 
        if(remaining_burst_time[current] > 0 && !completed_process[current]){
            //Simulated execution
            remaining_burst_time[current] = remaining_burst_time[current] - quantum;

            //Handle negative time shit
            if(remaining_burst_time[current] <= 0){
                current_time += remaining_burst_time[current];
                exec_time += remaining_burst_time[current];
                remaining_burst_time[current] = 0;
                completed++;                    //VERY IMPORTANT! ONLY FLAG TO MAKE SURE THIS ISNT AN INFINITE LOOP MESS
                completed_process[current] = true;
            }

            //Update current_time
            current_time += quantum;

            cout << "Running process T" << current << " for " << exec_time <<" time units." <<endl;
            
            //Update waiting times and throughput times
            turnaround_times[current] = current_time;           //Will continually update until the process completes, in which case it has updated for the last time to the correct turnaround time (hopefully I swear to the gods above that if it doesnt, Ill make this damn program regret it even saw the light of day.
            waiting_times[current] = turnaround_times[current] - pcb.burst_time;            //See above.
            
            
            
        }

        //Update current
        current = (current + 1) % processes.size();
    }
};


void SchedulerRR::print_results(){
    int total_turnaround = 0;
    int total_waiting = 0;
    double avg_turnaround = 0;
    double avg_waiting = 0;

    for(size_t i = 0; i < processes.size(); i++){
        cout << "Process " <<i << " turn-around time = " << turnaround_times[i]
             << ", waiting time = " << waiting_times[i] << endl;

        total_turnaround += turnaround_times[i];
        total_waiting += waiting_times[i];
    }

    avg_turnaround = ((double) total_turnaround) /  processes.size();
    avg_waiting = ((double) total_waiting) / processes.size();

    cout << "Average turn-around time: " << avg_turnaround << ", Average waiting time = " << avg_waiting << endl;
}