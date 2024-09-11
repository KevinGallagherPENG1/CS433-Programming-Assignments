#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
    count = 0; // Initialize the queue size
    for (int i = 0; i < count; ++i) {
        pcbQueue[i] = NULL;  // Initialize all elements to null
    }
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    // No dynamic memory allocated
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    // When adding a PCB to the queue, you must change its state to READY.
    pcbPtr->state = ProcState::READY;  // Change state to READY
    // Insert PCB based on priority (higher priority first)
    
    pcbQueue[count++] = pcbPtr;
    trickleUp();
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    // When removing a PCB from the queue, you must change its state to RUNNING.

    PCB* highestPriorityPCB = pcbQueue[0];  // Get the PCB with the highest priority
    highestPriorityPCB->state = ProcState::RUNNING;    // Change state to RUNNING

    reheapify();
    return highestPriorityPCB;

}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return count;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    cout << "PCB Queue: " << endl;
    for (int i = 0; i < count; ++i) {
        cout << "ID: " << pcbQueue[i]->id << ", Priority: " << pcbQueue[i]->priority << endl;
    }
}


//Private functions added in readyQueue.h

bool ReadyQueue::isEven(int index){
    return (index % 2 == 0);
}

int ReadyQueue::getParent(int index){
    if(isEven(index))
        return((index - 2) / 2);
    else
        return((index - 1) / 2);
}

void ReadyQueue::trickleUp(){
    int x = count - 1;      //Last index in array

    while(x > 0){
        int parent = getParent(x);

        //If parent has larger priority than pcbQueue[x], swap the two and update x
        if(pcbQueue[x]->priority > pcbQueue[parent]->priority){
            swap(x, parent);
            x = parent;
        } else 
            break;
    }
}

void ReadyQueue::swap(int posA, int posB){
    PCB* temp = pcbQueue[posA];
    pcbQueue[posA] = pcbQueue[posB];
    pcbQueue[posB] = temp; 
}

void ReadyQueue::reheapify(){
    int pos = 0;        //Current position, start at beginning of array
    pcbQueue[0] = pcbQueue[count -1];       //Move last PCB to front
    count--;

    while(pos < count){
        int larger = getLargerChild(pos);         //Gets index of larger child

        if(larger == -1 || pcbQueue[pos]->priority >= pcbQueue[larger]->priority)      //If position is smaller or smaller is nonsense (OOB), break
            break;

        swap(pos, larger);
        pos = larger;          //Update position
    }
}

int ReadyQueue::getLargerChild(int index){
    // Positions of smaller children, left and right children
    int LC = (2 * index) + 1;
    int RC = (2 * index) + 2;

    // If there are no children
    if (LC >= count)
        return -1; // No children

    // If only left child exists
    if (RC >= count)
        return LC;

    // If both children exist, return the one with the higher priority
    if (pcbQueue[LC]->priority > pcbQueue[RC]->priority)
        return LC;
    else
        return RC;
}
