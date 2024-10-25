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
    turnaround_times.resize(process_list.size(), 0);
    waiting_times.resize(process_list.size(), 0);
    id_order.resize(process_list.size(), 0);
    remaining_burst_time.resize(process_list.size(),0);
    priorities.resize(0, 0);
    inOrderPriorities.resize(process_list.size(), 0);
    burst_time.resize(process_list.size(), 0);
    completed_process.resize(process_list.size(), false);


    //Add each process to the queue (based off of priority)
    for(size_t i = 0; i < process_list.size(); i++){
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
    while (iterations < processes.size()) {
        PCB pcb = queue.removePCB();
        remaining_burst_time[iterations] = pcb.burst_time;
        id_order[iterations] = pcb.id; // Store the actual process ID in order
        priorities.push_back(pcb.priority);
        inOrderPriorities[iterations] = pcb.priority;
        burst_time[iterations] = pcb.burst_time;
        iterations++;
    }

    // Run the simulation
    while (completed != processes.size()) {
        int exec_time = quantum;
        int process_id = id_order[current]; // Get the actual process ID

        // Only run if there are no higher-priority processes to interrupt
        if (!checkPriority(priorities, inOrderPriorities[current])) {
            // Process if it has remaining burst time and is not completed
            if (remaining_burst_time[current] > 0 && !completed_process[current]) {
                // Execute process within quantum or remaining burst time
                exec_time = min(quantum, remaining_burst_time[current]);
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

        // Move to the next process
        current = (current + 1) % processes.size();

        // Skip completed processes
        while (completed_process[current] && completed != processes.size()) {
            current = (current + 1) % processes.size();
        }
    }
};

void SchedulerPriorityRR::print_results(){
    int total_turnaround = 0;
    int total_waiting = 0;
    double avg_turnaround = 0;
    double avg_waiting = 0;

    for(size_t i = 0; i < processes.size(); i++) {
        cout << "Process " << (i + 1) << " turn-around time = " << turnaround_times[i]
             << ", waiting time = " << waiting_times[i] << endl;

        total_turnaround += turnaround_times[i];
        total_waiting += waiting_times[i];
    }

    avg_turnaround = static_cast<double>(total_turnaround) / processes.size();
    avg_waiting = static_cast<double>(total_waiting) / processes.size();

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


//FORWARD DECLARATION?
pQueue::pQueue(){
        this->count = 0;
    };

    pQueue::~pQueue(){};

    void pQueue::swap(int posA, int posB){
        PCB temp = queue[posA];
        queue[posA] = queue[posB];
        queue[posB] = temp;
    };

    void pQueue::reheapify(){
        int pos = 0;
        queue[0] = queue[count - 1];
        count--;

        while(pos < count){
            int larger = getLargerChild(pos);

            if(larger == -1 || queue[pos].priority >= queue[larger].priority || (queue[pos].priority == queue[larger].priority && queue[pos].burst_time <= queue[larger].burst_time))
                break;

            swap(pos, larger);
            pos = larger;
        }
    };

    int pQueue::getLargerChild(int index){
        int LC = (2 * index) + 1;
        int RC = (2 * index) + 2;

        if (LC >= count) return -1;
        if (RC >= count) return LC;

        // Choose child with higher priority, or if equal, shorter burst time
        if (queue[LC].priority > queue[RC].priority) {
            return LC;
        } else if (queue[LC].priority < queue[RC].priority) {
            return RC;
        } else {
            // If both have the same priority, choose the one with shorter burst time
            return (queue[LC].burst_time <= queue[RC].burst_time) ? LC : RC;
        }
    };

    void pQueue::trickleUp(){
        int x = count - 1;

        while(x > 0){
            int parent = getParent(x);

            //If parent has larger priority, then swap
            if((queue[x].priority > queue[parent].priority) || (queue[x].priority == queue[parent].priority && queue[x].burst_time < queue[parent].burst_time)){
                swap(x, parent);
                x = parent;
            }else
                break;
        }
    };

    int pQueue::getParent(int index){
        return ((isEven(index)) ? ((index - 2) / 2) : ((index - 1) / 2));
    };

    bool pQueue::isEven(int index){
        return (index % 2 == 0);   
    };

    void pQueue::addPCB(PCB pcb){
        queue[count++] = pcb;
        sortQueue();
    };

    PCB pQueue::removePCB(){
        PCB highestPriority = queue[0];
        queue[0] = queue[--count]; 
        sortQueue(); 
        return highestPriority;
    };

    int pQueue::size(){
        return count;
    };

    void pQueue::sortQueue(){
        std::sort(queue, queue + count, [](const PCB& a, const PCB& b){
            // Sort by priority first, and by burst time if priorities are equal
            if (a.priority != b.priority) {
                return a.priority > b.priority;  // Higher priority first
            }   
            return a.burst_time < b.burst_time;  // Lower burst time first
        });
};