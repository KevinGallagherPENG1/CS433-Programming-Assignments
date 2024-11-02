/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // Initializes the base Replacement class with given pages and frames
}

FIFOReplacement::~FIFOReplacement() {
    // Destructor (no dynamic allocation to clear in this case)
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // Add page to the page table and mark it as valid
    page_table.set_frame(page_num, frames_in_use.size());
    page_table.set_valid(page_num, true);
    // Add the page to the queue (FIFO order) and mark as loaded in frames
    page_queue.push(page_num);
    frames_in_use.insert(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // Identify the oldest page (front of queue)
    int victim_page = page_queue.front();
    page_queue.pop();
    
    // Invalidate the victim page in the page table
    page_table.set_valid(victim_page, false);
    frames_in_use.erase(victim_page);

    // Add the new page in the freed frame and update the queue
    page_table.set_frame(page_num, page_table[victim_page].frame_num);
    page_table.set_valid(page_num, true);
    page_queue.push(page_num);
    frames_in_use.insert(page_num);

    return victim_page; // Return the replaced page number
}