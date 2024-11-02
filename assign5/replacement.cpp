/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "replacement.h"

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
    : page_table(num_pages), num_frames(num_frames) {
    // Initialize the base Replacement class with given pages and frames
}

// Destructor
Replacement::~Replacement()
{
    // Destructor (no dynamic memory to clear in this case)
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write) {
    // Check if the page is already in frames
    if (frames_in_use.find(page_num) != frames_in_use.end()) {
        touch_page(page_num); // Update page's access status
        return false; // No page fault
    }

    // Page fault occurs
    page_faults++;

    // Load page if there's free frame, otherwise replace a page
    if (frames_in_use.size() < num_frames) {
        load_page(page_num);
    } else {
        page_replacements++;
        replace_page(page_num);
    }

    return true; // Page fault occurred
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
    std::cout << "Number of references: \t\t" << page_faults + page_replacements << std::endl;
    std::cout << "Number of page faults: \t\t" << page_faults << std::endl;
    std::cout << "Number of page replacements: \t" << page_replacements << std::endl;
}