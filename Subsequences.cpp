/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    // program can be tested here
    return 0;
}

/*
* We have two base cases. First if subsequence gets empty
* it means it is valid cause it could be only emptied if
* first chars were same of text and subsequences all the way up.
* And second base case is when text size becomes smalller as
* first chars are not the same
*/
bool isSubsequence(string text, string subsequence) {
    if (subsequence.empty()) {
        return true;
    }
    if (text.size() < subsequence.size()) {
        return false;
    }
    if (text[0] == subsequence[0]) {
        return isSubsequence(text.substr(1), subsequence.substr(1));
    }
    return isSubsequence(text.substr(1), subsequence);
}