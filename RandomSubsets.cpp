/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
using namespace std;

//constant
const int EQUAL_CHANCE = 0.5;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s);

int main() {
    // program can be tested here
    return 0;
}

/*
* Our main recursive function. I am not modyfing s, 
* cause if I did so , s would be emptied with this
* function as it is passed by reference and this 
* behaviour might not be what user wants, so I create
* copy of sButWithoutFirst set every time
*/
Set<int> randomSubsetOf(Set<int>& s) {
    Set<int> result;
    if (s.isEmpty()) {
        return result;
    }
    bool choose = randomChance(EQUAL_CHANCE);
    if (choose) {
        result.insert(s.first());
    }
    Set<int> sButWithoutFirst = s; // create copy
    sButWithoutFirst.remove(sButWithoutFirst.first());
    return result + randomSubsetOf(sButWithoutFirst);
}