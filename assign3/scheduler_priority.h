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


#ifndef ASSIGN3_SCHEDULER_PRIORITY_H
#define ASSIGN3_SCHEDULER_PRIORITY_H

#include "scheduler.h"

static int MAX_SIZE = 8;

class SchedulerPriority : public Scheduler {
private:
    // Standard implementation of priority queue from Assignment 1, will base priority on the priority number of the PCB
    PCB queue[10];
    int count = 0;

    void swap(int posA, int posB){
        PCB temp = queue[posA];
        queue[posA] = queue[posB];
        queue[posB] = temp;
    };

    void reheapify(){
        int pos = 0;
        queue[0] = queue[count - 1];
        count--;

        while(pos < count){
            int larger = getLargerChild(pos);

            if(larger == -1 || queue[pos].priority >= queue[larger].priority)
                break;

            swap(pos, larger);
            pos = larger;
        }
    };

    int getLargerChild(int index){
        int LC = (2 * index) + 1;
        int RC = (2 * index) + 2;

        if(LC >= count)
            return -1;

        if(RC >= count)
            return LC;

        if(queue[LC].priority > queue[RC].priority)
            return LC;
        else
            return RC;
    };

    void trickleUp(){
        int x = count - 1;

        while(x > 0){
            int parent = getParent(x);

            //If parent has larger priority, then swap
            if(queue[x].priority > queue[parent].priority){
                swap(x, parent);
                x = parent;
            } else
                break;
        }
    };

    int getParent(int index){
        return ((isEven(index)) ? ((index - 2) / 2) : ((index - 1) / 2));
        /*
        if(isEven(index))
            return((index - 2) / 2);
        else
            return((index - 1) / 2);
            */
    };

    bool isEven(int index){
        return (index % 2 == 0);   
    };

    void addPCB(PCB pcb){
         queue[count++] = pcb;
        trickleUp();
    };

    PCB removePCB(){
        PCB highestPriority = queue[0];
        reheapify();
        return highestPriority;
    }

    int size(){
        return count;
    }

    
public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriority();

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriority() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override{
        //Add PCB to queue based on priority
        for(PCB pcb : process_list){
            queue.addPCB(pcb);
        }
    };

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override{
            
    };


    
    
};


#endif //ASSIGN3_SCHEDULER_PRIORITY_H
