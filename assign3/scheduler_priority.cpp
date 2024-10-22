/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority.h"

// TODO: add implementation of SchedulerPriority constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerPriority::SchedulerPriority(){};

SchedulerPriority::~SchedulerPriority(){};

void SchedulerPriority::init(std::vector<PCB>& processes){
    this->process_list = processes;
    turnaround_times.resize(8, 0);
    waiting_times.resize(8, 0);
    id_order.resize(8, 0);

    //Add each process to the queue (based off of priority)
    for(PCB process : processes)
        queue.addPCB(process);
}

void SchedulerPriority::simulate(){
    int current_time = 0;
    int i = 0;

    for(int i = 0; i < 8; i++){
        PCB process = queue.removePCB();
        
        //Get wait time and turnaround time for process
        //Also add process id to id_order for correct order of execution
        id_order[i] = process.id;
        waiting_times[i] = current_time - process.arrival_time;
        turnaround_times[i] = waiting_times[i] + process.burst_time;
        current_time += process.burst_time;
    }
}

void SchedulerPriority::print_results(){
    int total_turnaround = 0;
    int total_waiting = 0;
    double avg_turnaround = 0;
    double avg_waiting = 0;

    for(size_t i = 0; i < 8; i++){
        cout << "Process " <<id_order[i] << " turn-around time = " << turnaround_times[i]
             << ", waiting time = " << waiting_times[i] << endl;

        total_turnaround += turnaround_times[i];
        total_waiting += waiting_times[i];
    }

    avg_turnaround = ((double) total_turnaround) /  8;
    avg_waiting = ((double) total_waiting) / 8;

    cout << "Average turn-around time: " << avg_turnaround << ", Average waiting time = " << avg_waiting << endl;
}