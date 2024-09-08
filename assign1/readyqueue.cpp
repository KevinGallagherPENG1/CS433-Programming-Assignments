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
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    //TODO: add your code to release dynamically allocate memory
    // No dynamic memory allocated???
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
    int i;
    for (i = count - 1; i >= 0; --i) {
        if (pcbQueue[i]->priority > pcbPtr->priority) {
            pcbQueue[i + 1] = pcbQueue[i];  // Shift elements to make space
        } else {
            break;
        }
    }
    pcbQueue[i + 1] = pcbPtr;  // Insert PCB at the correct position
    count++;  // Increment count
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    // When removing a PCB from the queue, you must change its state to RUNNING.
    if (count == 0) {
        return NULL;  // Return null if the queue is empty
    }
    PCB* highestPriorityPCB = pcbQueue[0];  // Get the PCB with the highest priority
    highestPriorityPCB->state = ProcState::RUNNING;    // Change state to RUNNING
    // Shift remaining elements in the queue
    for (int i = 1; i < count; ++i) {
        pcbQueue[i - 1] = pcbQueue[i];
    }
    count--;  // Decrement count
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
