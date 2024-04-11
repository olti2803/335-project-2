/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
main.cpp
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include "myVector.hpp"
#include "myList.hpp"
#include "myHeap.hpp"
#include "myAVLtree.hpp"

int main() {
    std::vector<int> myVec;

    std::string filename = "input3.txt";
    std::ifstream temp (filename);

    std::string line;
    std::string num;

    std::string newline;
    std::string num1;

    int realnum;

    while(std::getline(temp, line)) { //read file line by line
        std::stringstream temp2(line); //parse line
        std::getline(temp2, num, ' '); 

        std::getline(temp2, num1, ' ');  

        if(num == "insert") { //if insert, add to vector
            realnum = stoi(num1);
            myVec.push_back(realnum);
        } else { 
            myVec.push_back(-1);
        }
    }
    
    vectorMedian(&myVec);
    listMedian(&myVec);
    heapMedian(&myVec);
    treeMedian(&myVec);
}