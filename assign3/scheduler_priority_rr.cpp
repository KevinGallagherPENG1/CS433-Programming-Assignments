/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"

// TODO: add implementation of SchedulerPriorityRR constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum){
    this->quantum = time_quantum;
}

SchedulerPriorityRR::~SchedulerPriorityRR(){};

void SchedulerPriorityRR::init(std::vector<PCB>& process_list){};

void SchedulerPriorityRR::simulate(){};

void SchedulerPriorityRR::print_results(){};
