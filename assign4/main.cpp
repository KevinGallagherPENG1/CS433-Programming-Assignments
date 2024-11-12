/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include "buffer.h"

using namespace std;

// global buffer object
Buffer buffer;

// Producer thread function
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // Attempt to insert the item
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer " << item << ": Buffer full, unable to insert item " << endl; // Shouldn't come here
        }
    }
    return nullptr;
}

// Consumer thread function
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // Attempt to remove an item
        if (buffer.remove_item(&item)) {
            cout << "Consumer: Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer: Buffer empty, unable to remove item" << endl;
        }
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    // Check for correct argument count
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <sleep_time> <num_producers> <num_consumers>" << endl;
        return 1;
    }

    // Parse command line arguments
    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    // Initialize producer and consumer thread arrays
    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];

    // Create producer threads
    for (int i = 0; i < num_producers; ++i) {
        int *producer_id = new int(i + 1); // unique ID for each producer
        if (pthread_create(&producers[i], nullptr, producer, producer_id) != 0) {
            cerr << "Error: Failed to create producer thread " << i + 1 << endl;
            return 1;
        }
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; ++i) {
        if (pthread_create(&consumers[i], nullptr, consumer, nullptr) != 0) {
            cerr << "Error: Failed to create consumer thread " << i + 1 << endl;
            return 1;
        }
    }

    // Main thread sleeps for the specified time before exiting
    sleep(sleep_time);

    // Clean up and exit
    cout << "Main thread: Exiting after " << sleep_time << " seconds" << endl;
    return 0;
}
