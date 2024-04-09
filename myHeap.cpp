/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myHeap.cpp
*/

#include "myHeap.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

// Utility function to rebalance heaps
void rebalance(std::priority_queue<int> &maxHeap, std::priority_queue<int, std::vector<int>, std::greater<int>> &minHeap) {
    if (maxHeap.size() < minHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    } else if (maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    }
}

// Utility function to add an element to the heaps
void addToHeap(std::priority_queue<int> &maxHeap, std::priority_queue<int, std::vector<int>, std::greater<int>> &minHeap, int value) {
    if (!maxHeap.empty() && value < maxHeap.top()) {
        maxHeap.push(value);
    } else {
        minHeap.push(value);
    }
    rebalance(maxHeap, minHeap);
}

// Function to pop and return the median from the heaps
int popMedian(std::priority_queue<int> &maxHeap, std::priority_queue<int, std::vector<int>, std::greater<int>> &minHeap) {
    if (maxHeap.empty()) {
        return -1; // Should not happen if used correctly
    }

    int median = maxHeap.top();
    maxHeap.pop();
    rebalance(maxHeap, minHeap);
    return median;
}

void heapMedian(const std::vector<int>* instructions) {
    std::priority_queue<int> maxHeap; // Max heap for elements <= median
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // Min heap for elements > median
    std::vector<int> medians; // Vector to store the medians that are popped

    for (int instruction : *instructions) {
        if (instruction == -1) {
            // Pop median operation
            int median = popMedian(maxHeap, minHeap);
            if (median != -1) { // If the heaps were not empty
                medians.push_back(median);
            }
        } else {
            // Insert operation
            addToHeap(maxHeap, minHeap, instruction);
        }
    }

    // Print out all medians at once to minimize I/O operations
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
