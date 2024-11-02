/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // Initializes the base Replacement class with given pages and frames
}

LIFOReplacement::~LIFOReplacement() {
    // Destructor (no dynamic allocation to clear in this case)
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    // Load page into the page table and mark as valid
    page_table.set_frame(page_num, frames_in_use.size());
    page_table.set_valid(page_num, true);
    // Push page to the stack (LIFO order) and mark as loaded
    page_stack.push(page_num);
    frames_in_use.insert(page_num);
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    // Identify the most recent page (top of the stack)
    int victim_page = page_stack.top();
    page_stack.pop();

    // Invalidate the victim page in the page table
    page_table.set_valid(victim_page, false);
    frames_in_use.erase(victim_page);

    // Add the new page in the freed frame and push to stack
    page_table.set_frame(page_num, page_table[victim_page].frame_num);
    page_table.set_valid(page_num, true);
    page_stack.push(page_num);
    frames_in_use.insert(page_num);

    return victim_page; // Return the replaced page number
}