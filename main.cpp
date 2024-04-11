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
    std::vector<int> myVec; //vector to store numbers

    std::string filename = "input3.txt"; //file to read from
    std::ifstream temp (filename);//open file

    std::string line; //line to read from file
    std::string num;//number to read from line

    std::string newline;//line to read from file
    std::string num1;//number to read from line

    int realnum;//number to add to vector

    while(std::getline(temp, line)) { //read file line by line
        std::stringstream temp2(line); //parse line
        std::getline(temp2, num, ' '); 

        std::getline(temp2, num1, ' ');  

        if(num == "insert") { //if insert, add to vector
            realnum = stoi(num1);//convert string to int
            myVec.push_back(realnum);//add to vector
        } else { 
            myVec.push_back(-1);//add -1 to vector
        }
    }
    
    vectorMedian(&myVec);
    listMedian(&myVec);
    heapMedian(&myVec);
    treeMedian(&myVec);
}