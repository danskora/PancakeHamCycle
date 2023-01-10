
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <unordered_set>
#include <algorithm> 
#include <chrono>
#include <math.h>
#include <deque>
#include <fstream>

/*
class Link {
public:
    int data;
    Link* next;
    
    Link(int data)
    {
        this->data = data;
        this->next = NULL;
    }


    void append(Link& link) {
        this->next = link;
    }

    void getValue() {
        return data;
    }

    void getNext() {
        return next;
    }
}
*/


// Flip a pancake

char flip_pancake(char original) { //CHEAP
    if (original == '0') {
        return '3';
    }
    else if (original == '1') {
        return '4';
    }
    else if (original == '2') {
        return '5';
    }
    else if (original == '3') {
        return '0';
    }
    else if (original == '4') {
        return '1';
    }
    else {
        return '2';
    }
}

// Flip a stack

std::string flip(std::string stack, int index) {

    std::string res = "";
    for (int i = 0; i < 3; i++) { //CHEAP
        if (i < 3-index) { //CHEAP
            res = flip_pancake(stack.at(i)) + res;
        }
        else {
            res = res + stack.at(i);
        }
    }
    return res;
}


std::string translate(std::string stack) {
    std::string res = "";
    for (int i = 0; i < 3; i++) {
        char current = stack.at(i);
        if (current == '0') {
            res = res + " +1";
        }
        else if (current == '1') {
            res = res + " +2";
        }
        else if (current == '2') {
            res = res + " +3";
        }
        else if (current == '3') {
            res = res + " -1";
        }
        else if (current == '4') {
            res = res + " -2";
        }
        else {
            res = res + " -3";
        }
    }
    return res;
}





// Search graph with new algorithm

// Main
bool checkForPath(std::string current, int previousFlip, std::unordered_set<std::string>& visited, int depth, std::ofstream& outfile) {

    // Figure out if we just found a path
    if (depth == 48) {   // CHEAP
        return current == "012"; //CHEAP
    }

    // Check if this is a valid extension of our path
    if (visited.count(current) == 0) {
        // It is
        int flip1 = (previousFlip + 1) % 3;
        int flip2 = (previousFlip + 2) % 3;

        visited.insert(current);

        if ( checkForPath(flip(current, flip1), flip1, visited, depth + 1, outfile) ) {
            visited.erase(current);
            outfile << depth;
            outfile << ":";
            outfile << translate(current) << std::endl;
            return true;
        }
                   
        if ( checkForPath(flip(current, flip2), flip2, visited, depth + 1, outfile) ) {
            visited.erase(current);
            outfile << depth;
            outfile << ":";
            outfile << translate(current) << std::endl;
            return true;
        }

        visited.erase(current);
        return false;
    }
    else {
        // It is not
        return false;
    }
}









// Main

int main()
{
    std::ofstream outfile("cycle.txt");
    std::unordered_set<std::string> set;
    std::cout << checkForPath("012", 0, set, 0, outfile);
    outfile.close();

    std::ofstream poo("test.txt");

    poo << "my text here!" << std::endl;

    poo.close();
}
