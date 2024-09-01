/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Kevin Gallagher, Nicholas Everekyan
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   table.reserve(size);
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
    //For every pointer in table, delete it. Should deallocate all memory correctly
    for(PCB * point : table)
        delete point;
    
    //Clear vector just to be sure
    table.clear();
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    if(idx > table.size())
        return NULL;
    else{
        PCB * point = table[idx];
        return point;
    }
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // Add a PCB pointer to the PCBTable at index idx.
    table.insert(table.begin() + idx, pcb);
}
