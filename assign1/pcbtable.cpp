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
   table.resize(size);
}

/**
 * @brief Default constructor, will reserve a vector of 100 spaces
 */
PCBTable::PCBTable(){
    table.resize(100);
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
    for(size_t i = 0; i < table.size(); i++)
        delete(table[(int) i]);
    
    //Clear the vector
    table.clear();
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {

    if(idx >= table.size()){
        cout << "Index " << idx << " is out of bounds." <<endl;
        return nullptr;
    }
    
    return(table[idx]);
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB* pcb, unsigned int idx) {
    // Add a PCB pointer to the PCBTable at index idx.
    if(table[idx] != nullptr)
        delete table[idx];
    
    table[idx] = pcb;
}
