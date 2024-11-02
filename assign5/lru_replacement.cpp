/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"

LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // Initializes the base Replacement class with given pages and frames
}

LRUReplacement::~LRUReplacement()
{
    // Destructor (no dynamic allocation to clear in this case)
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    // Move the accessed page to the front (most recently used)
    page_list.erase(page_map[page_num]);
    page_list.push_front(page_num);
    page_map[page_num] = page_list.begin();
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    // Load the page into the page table and mark as valid
    page_table.set_frame(page_num, frames_in_use.size());
    page_table.set_valid(page_num, true);
    // Add page to the front (most recently used)
    page_list.push_front(page_num);
    page_map[page_num] = page_list.begin();
    frames_in_use.insert(page_num);
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    // Identify the least recently used page (back of the list)
    int victim_page = page_list.back();
    page_list.pop_back();
    page_map.erase(victim_page);
    
    // Invalidate the victim page in the page table
    page_table.set_valid(victim_page, false);
    frames_in_use.erase(victim_page);

    // Load the new page in the freed frame and mark as recently used
    page_table.set_frame(page_num, page_table[victim_page].frame_num);
    page_table.set_valid(page_num, true);
    page_list.push_front(page_num);
    page_map[page_num] = page_list.begin();
    frames_in_use.insert(page_num);

    return victim_page; // Return the replaced page number
}