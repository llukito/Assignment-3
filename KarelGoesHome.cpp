/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

//constants
const int MIN_VALUE = 1;
const int EXIT_NUM = 0;

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue);
int getValidValue(string text);

int main() {
    while (true) {
        int street = getValidValue("street");
        int avenue = getValidValue("avenue");
        int totalWays = numPathsHome(street, avenue);
        cout << "Total of " << totalWays << " different ways" << endl;

        int choice = getInteger("Enter 0 if you want to exit program: ");
        if (choice == EXIT_NUM)break;
    }
    cout << "You exited program"<<endl;
    return 0;
}

/*
* Makes sure user enters valid street and avenue
* number. We could pass invalid values to our
* main recursive function and it will return 0,
* but it is till better to have this function
*/
int getValidValue(string text) {
    while (true) {
        int n = getInteger("Enter " + text + " number: ");
        if (n >= MIN_VALUE) {
            return n;
        }
        cout << "Enter valid " << text << " number (starting from 1)" << endl;
    }
}

/*
* Our main recursive function
*/
int numPathsHome(int street, int avenue) {
    if (street == 1 && avenue == 1) {
        return 1;
    }
    if (street < 1 || avenue < 1) {
        return 0;
    }
    return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
}
