/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "pagetable.h"

// Constrcutor
PageTable::PageTable(int num_pages)
{
    // Initialize the page table with the specified number of pages
    pages.resize(num_pages);
}

// Destructor
PageTable::~PageTable() {
    // Destructor: Clean up any dynamically allocated resources if needed (none here)
}

