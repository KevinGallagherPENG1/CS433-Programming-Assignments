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
    waiting_times.resize(8, 0);
    turnaround_times.resize(8, 0);
    remaining_burst_time.resize(8, 0);

    //Get burst time for each process
    for(int i = 0; i < 8; i++){
        remaining_burst_time[i] = process_list[i].burst_time;
    }
};

void SchedulerRR::simulate(){
    unsigned int current_time = 0;
    int completed = 0;
    int current = 0;
    bool completed_process[processes.size()];

    for(int i = 0; i < 8; i++){
        completed_process[i] = false;
    }

    while(completed != 8){
        PCB& pcb = processes[current];

        //If there is still remaining burst time for the current process:
        //  Update remaining burst time
        //  Update current_time 
        if(remaining_burst_time[current] > 0 && !completed_process[current]){
            //Simulated execution
            cout << current << " burst time: " << remaining_burst_time[current] << endl;
            remaining_burst_time[current] = remaining_burst_time[current] - quantum;
            cout << current << " burst time: " << remaining_burst_time[current] << endl;

            //Handle negative time shit
            if(remaining_burst_time[current] <= 0){
                current_time += remaining_burst_time[current];
                remaining_burst_time[current] = 0;
                completed++;                    //VERY IMPORTANT! ONLY FLAG TO MAKE SURE THIS ISNT AN INFINITE LOOP MESS
                completed_process[current] = true;
            }

            //Update current_time
            current_time += quantum;

            //Update waiting times and throughput times
            turnaround_times[current] = current_time;           //Will continually update until the process completes, in which case it has updated for the last time to the correct turnaround time (hopefully I swear to the gods above that if it doesnt, Ill make this damn program regret it even saw the light of day.
            waiting_times[current] = turnaround_times[current] - pcb.burst_time;            //See above.
            
        }

        //Update current
        current = (current + 1) % processes.size();
    }

    
    /*
    //Funky code that should work but doesnt fml
    while(completed != processes.size()){
        PCB& pcb = processes[current];
        
        if(remaining_burst_time[current] > 0){
            waiting_times[current] += current_time - pcb.arrival_time;

            current_time += quantum;
            //pcb.burst_time -= quantum;
            remaining_burst_time[current] -= quantum;

            //Handle negative time (if any)
            if(pcb.burst_time <= 0){
                cout << "Process " << pcb.id << " finished." <<endl;
                remaining_burst_time[current] = 0;
                completed++;
            } else{
                pcb.arrival_time = current_time;
            }

            turnaround_times[current] = current_time - pcb.arrival_time;
        }
        //Update current
        current = (current + 1) % processes.size();
    }
    */
    
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


//Helper function to see if any of the processes still have time left
bool SchedulerRR::anyTimeRemaining(std::vector<PCB> processes){
    for(int i = 0; i < processes.size(); i++){
        PCB pcb = processes[i];
        if(pcb.burst_time > 0){
            //intentionally do nothing
            cout << "Checking.";
        }else{
            return false;
        }
    }
    return true;
}