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
    this->quantum = quantum;
};

SchedulerRR::SchedulerRR(){
    this->quantum = 10;
};

SchedulerRR::~SchedulerRR(){};

void SchedulerRR::init(std::vector<PCB>& process_list){
    this->processes = process_list;
    this->current = 0;
    waiting_times.resize(process_list.size(), 0);
    turnaround_times.resize(process_list.size(), 0);

    //Get burst time for each process
    for(int i = 0; i < process_list.size(); i++)
        remaining_burst_time[i] = process_list[i].burst_time;
};

void SchedulerRR::simulate(){
    int current_time = 0;
    int iterations = 0;

    while(!processes.empty()){
        PCB& pcb = processes[current];
        
        if(remaining_burst_time[current] > 0){
            waiting_times[current] += current_time - pcb.arrival_time;

            current_time += quantum;
            remaining_burst_time[current] -= quantum;

            //Handle negative time (if any)
            if(remaining_burst_time[current] <= 0){
                cout << "Process " << pcb.id << " finished." <<endl;
                remaining_burst_time[current] = 0;
            } else{
                pcb.arrival_time = current_time;
            }

            turnaround_times[current] = current_time - pcb.arrival_time;
            //Update current
            current = (current + 1) % processes.size();
        } else if(iterations < 8){
            current = (current + 1) % processes.size();
            iterations++;
        } else{
            break;
        }
    }
};


void SchedulerRR::print_results(){
    int total_turnaround = 0;
    int total_waiting = 0;
    double avg_turnaround = 0;
    double avg_waiting = 0;

    for(size_t i = 0; i < 8; i++){
        cout << "Process " <<i << " turn-around time = " << turnaround_times[i]
             << ", waiting time = " << waiting_times[i] << endl;

        total_turnaround += turnaround_times[i];
        total_waiting += waiting_times[i];
    }

    avg_turnaround = ((double) total_turnaround) /  8;
    avg_waiting = ((double) total_waiting) / 8;

    cout << "Average turn-around time: " << avg_turnaround << ", Average waiting time = " << avg_waiting << endl;
}

