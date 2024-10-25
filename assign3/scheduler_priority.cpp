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
    turnaround_times.resize(processes.size(), 0);
    waiting_times.resize(processes.size(), 0);
    id_order.resize(processes.size(), 0);


    //Add each process to the queue (based off of priority)
    for(PCB process : processes)
        queue.addPCB(process);
}

void SchedulerPriority::simulate(){
    int current_time = 0;


    for(size_t i = 0; i < process_list.size(); i++){
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

    for(size_t i = 0; i < process_list.size(); i++){
        cout << "Process " <<(id_order[i] + 1) << " turn-around time = " << turnaround_times[i]
             << ", waiting time = " << waiting_times[i] << endl;

        total_turnaround += turnaround_times[i];
        total_waiting += waiting_times[i];
    }

    avg_turnaround = ((double) total_turnaround) /  process_list.size();
    avg_waiting = ((double) total_waiting) / process_list.size();

    cout << "Average turn-around time: " << avg_turnaround << ", Average waiting time = " << avg_waiting << endl;
}

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
        trickleUp();
    };

    PCB pQueue::removePCB(){
        PCB highestPriority = queue[0];
        reheapify();
        return highestPriority;
    };

    int pQueue::size(){
        return count;
    };
