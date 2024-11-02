/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief header file for the buffer class
 * @version 0.1
 */

#ifndef ASSIGN4_BUFFER_H
#define ASSIGN4_BUFFER_H

#include <vector>
#include <pthread.h>
#include <iostream>
#include <cstdlib>

// Define the data type of the buffer items
typedef int buffer_item;

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot exceed the size of the buffer.
 */
class Buffer {
private:
    std::vector<buffer_item> buffer;  // Buffer storage
    int size;                         // Maximum buffer size
    pthread_mutex_t mutex;            // Mutex for buffer synchronization
    pthread_cond_t not_empty;         // Condition variable for buffer not empty
    pthread_cond_t not_full;          // Condition variable for buffer not full

public:
    /**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */
    Buffer(int size = 5);

    /**
     * @brief Destroy the Buffer object
     */
    ~Buffer();

    /**
     * @brief Insert an item into the buffer
     * @param item the item to insert
     * @return true if successful
     * @return false if not successful
     */
    bool insert_item(buffer_item item);

    /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
    bool remove_item(buffer_item *item);

    /**
     * @brief Get the size of the buffer
     * @return the size of the buffer
     */
    int get_size();

    /**
     * @brief Get the number of items in the buffer
     * @return the number of items in the buffer
     */
    int get_count();

    /**
     * @brief Chceck if the buffer is empty
     * @return true if the buffer is empty, else false
     */
    bool is_empty();
    /**
     * @brief Check if the buffer is full
     * @return true if the buffer is full, else false
     */
    bool is_full();

    /**
     * @brief Print the buffer
     */
    void print_buffer();
};
#endif //ASSIGN4_BUFFER_H
