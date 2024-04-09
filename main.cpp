/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
main.cpp
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "myVector.hpp"
#include "myList.hpp"
#include "myHeap.hpp"
#include "myAVLtree.hpp"

// declarations of median functions
void vectorMedian(const std::vector<int>* instructions);
void listMedian(const std::vector<int>* instructions);
void heapMedian(const std::vector<int>* instructions);
void treeMedian(const std::vector<int>* instructions);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfile>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Could not open file: " << inputFileName << std::endl;
        return 1;
    }

    std::vector<int> instructions;
    std::string line;

    while (getline(inputFile, line)) {
        if (line.substr(0, 6) == "insert") {
            int value = std::stoi(line.substr(7));
            instructions.push_back(value);
        } else if (line == "pop median") {
            instructions.push_back(-1);
        }
    }

    inputFile.close();

    // Pass instructions to each median method
    vectorMedian(&instructions);
    listMedian(&instructions);
    heapMedian(&instructions);
    treeMedian(&instructions);

    return 0;
}