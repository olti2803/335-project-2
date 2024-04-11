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
void rebalance(std::priority_queue<int> &maxHeap, std::priority_queue<int, std::vector<int>, std::greater<int>> &minHeap) { //rebalance the heaps
    if (maxHeap.size() < minHeap.size()) {//max heap is smaller
        maxHeap.push(minHeap.top());//push top of min heap to max heap
        minHeap.pop();//pop top of min heap
    } else if (maxHeap.size() > minHeap.size() + 1) {//max heap is larger
        minHeap.push(maxHeap.top());//push top of max heap to min heap
        maxHeap.pop();//pop top of max heap
    }
}

// Utility function to add an element to the heaps
void addToHeap(std::priority_queue<int> &maxHeap, std::priority_queue<int, std::vector<int>, std::greater<int>> &minHeap, int value) {//add value to heaps
    if (!maxHeap.empty() && value < maxHeap.top()) {//value is less than top of max heap
        maxHeap.push(value);//push value to max heap
    } else {//value is greater than or equal to top of max heap
        minHeap.push(value);//push value to min heap
    }
    rebalance(maxHeap, minHeap);//rebalance the heaps
}

// Function to pop and return the median from the heaps
int popMedian(std::priority_queue<int> &maxHeap, std::priority_queue<int, std::vector<int>, std::greater<int>> &minHeap) {//pop median from heaps
    if (maxHeap.empty()) {//max heap is empty
        return -1; // Should not happen if used correctly
    }

    int median = maxHeap.top();//get top of max heap
    maxHeap.pop();//pop top of max heap
    rebalance(maxHeap, minHeap);//rebalance the heaps
    return median;//return median
}

void heapMedian(const std::vector<int>* instructions) {//find median of heap
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
        std::cout << median << " ";//print median
    }
    std::cout << std::endl;//print newline
}
