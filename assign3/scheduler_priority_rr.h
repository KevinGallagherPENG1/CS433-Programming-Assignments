/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.h
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code



// This will be a nonpreemptive priority algorithm that we implement here.
// A larger number from the PCB->priority represents a higher priority


#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include "scheduler.h"
#include "pcb.h"
using namespace std;

const int MAX_SIZE = 10;

class pQueue{ 
private:
    // Private member variables here
    // choose a data structure for the ReadyQueue. No STL class is allowed.
    PCB queue[MAX_SIZE]; // Array to hold PCBs 
    int count;          // Number of elements in the queue

    //Utility functions

    /**
     * @brief Swaps two positions in the pcbQueue array
     * @param posA, posB: Positions to be swapped
     */
    void swap(int posA, int posB);

    /**
     * @brief Reheapifies array after adding / removing
     */
    void reheapify();

    /**
     * @brief Gets position of larger child
     * @param index: Position of parent index
     * @return int: index of larger child
     */
    int getLargerChild(int index);

    /**
     * @brief Trickles up new addition to correct spot in pcbQueue
     */
    void trickleUp();

    /**
     * @brief Gets parent of index
     * @param index: Index of child 
     * @return int: Index of parent
     */
    int getParent(int index);

    /**
     * @brief Helper function to see if index is even or odd
     * @return bool: True if even, false if odd
     */
    bool isEven(int index);

public:
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    pQueue();

    /**
     * @brief Destructor
     */
    ~pQueue();

	// You may add additional member functions, but don't change the definitions of the following four member functions.

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB pcb);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB removePCB();

    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
	int size();

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

};


class SchedulerPriorityRR : public Scheduler {
private:
    pQueue queue;    
    int quantum;                                
    std::vector<PCB> processes;              
    std::vector<int> id_order;                  
    std::vector<int> turnaround_times;          
    std::vector<int> waiting_times;
    std::vector<int> remaining_burst_time;
    std::vector<int> priorities;
    std::vector<int> inOrderPriorities;
    std::vector<int> burst_time;
    std::vector<bool> completed_process;


    bool checkPriority(std::vector<int> priorities, int priorityToCheck);


public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriorityRR() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

};


#endif //ASSIGN3_SCHEDULER_PRIORITY_RR_H
