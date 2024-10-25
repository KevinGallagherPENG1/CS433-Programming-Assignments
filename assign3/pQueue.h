/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
#pragma once

#include "pcb.h"
using namespace std;

const int MAX_SIZE = 50;

/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */
class pQueue {
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