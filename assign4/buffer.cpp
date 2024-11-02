/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"

// Constructor: initializes buffer size, mutex, and condition variables
Buffer::Buffer(int size) : size(size) {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);
}

// Destructor: destroys mutex and condition variables
Buffer::~Buffer() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);
}

// Insert item into the buffer
bool Buffer::insert_item(buffer_item item) {
    pthread_mutex_lock(&mutex);

    // Wait if buffer is full
    while (is_full()) {
        pthread_cond_wait(&not_full, &mutex);
    }

    buffer.push_back(item);
    pthread_cond_signal(&not_empty);  // Signal that buffer is not empty
    pthread_mutex_unlock(&mutex);
    return true;
}

// Remove item from the buffer
bool Buffer::remove_item(buffer_item *item) {
    pthread_mutex_lock(&mutex);

    // Wait if buffer is empty
    while (is_empty()) {
        pthread_cond_wait(&not_empty, &mutex);
    }

    *item = buffer.front();
    buffer.erase(buffer.begin());
    pthread_cond_signal(&not_full);  // Signal that buffer is not full
    pthread_mutex_unlock(&mutex);
    return true;
}

// Get the maximum size of the buffer
int Buffer::get_size() {
    return size;
}

// Get the current count of items in the buffer
int Buffer::get_count() {
    pthread_mutex_lock(&mutex);
    int count = buffer.size();
    pthread_mutex_unlock(&mutex);
    return count;
}

// Check if the buffer is empty
bool Buffer::is_empty() {
    return buffer.empty();
}

// Check if the buffer is full
bool Buffer::is_full() {
    return buffer.size() >= size;
}

// Print buffer contents
void Buffer::print_buffer() {
    std::cout << "Buffer: [";
    for (size_t i = 0; i < buffer.size(); ++i) {
        std::cout << buffer[i];
        if (i < buffer.size() - 1) {
            std::cout << " "; // keeps space between the items
        }
    }
    std::cout << "]" << std::endl; // Closes buffer display with no trailing space
}