/*
 * File: SubsequencesExtension.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * An interesting variation on this problem is the following: 
 * given a collection of strings, what is the smallest string S such 
 * that every string in the collection is a subsequence of S? 
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "vector"
#include <algorithm>
using namespace std;

//constant
const int TOTAL_TESTS = 12;

/*
* Recusively Finds smallest common string of two strings.
* We are passing string with references for
* optimization and they are constants so we 
* unintentionally don't change them
*/
string scs(const string& s1, const string& s2) {
    if (s1.empty()) {
        return s2;
    }
    if (s2.empty()) {
        return s1;
    }
    if (s1[0] == s2[0]) {
        return s1[0] + scs(s1.substr(1), s2.substr(1));
    }
    string str1 = s1[0] + scs(s1.substr(1), s2);
    string str2 = s2[0] + scs(s1, s2.substr(1));
    return str1.size() > str2.size() ? str2 : str1;
}

/*
* This function is being passed vector of strings which will
* be subsequences of string and that string will
* be smallest by size too
*/
string smallestString(vector<string> vec) {
    if (vec.empty())return "";
    string result = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        result = scs(result, vec[i]);
    }
    return result;
}

int main() {
    // program is being tested here
    for (int i = 1; i <= TOTAL_TESTS; i++) {
        switch (i) {
        case 1: {
            string res = smallestString({ "a", "b", "c" });
            sort(res.begin(), res.end()); // we only care about size
            bool b = res == "abc";
            cout << "1 " << b << endl;
            break;
        }
        case 2: {
            string res = smallestString({ "abc", "ac" });
            sort(res.begin(), res.end());
            bool b = res == "abc";
            cout << "2 " << b << endl;
            break;
        }
        case 3: {
            string res = smallestString({ "abc", "bcd" });
            sort(res.begin(), res.end());
            bool b = res == "abcd";
            cout << "3 " << b << endl;
            break;
        }
        case 4: {
            string res = smallestString({ "abc", "bca" });
            sort(res.begin(), res.end());
            bool b = res == "aabc";
            cout << "4 " << b << endl;
            break;
        }
        case 5: {
            string res = smallestString({ "xyz", "yz", "z" });
            sort(res.begin(), res.end());
            bool b = res == "xyz";
            cout << "5 " << b << endl;
            break;
        }
        case 6: {
            string res = smallestString({ "a", "ab", "abc" });
            sort(res.begin(), res.end());
            bool b = res == "abc";
            cout << "6 " << b << endl;
            break;
        }
        case 7: {
            string res = smallestString({ "ab", "bc", "cd" });
            sort(res.begin(), res.end());
            bool b = res == "abcd";
            cout << "7 " << b << endl;
            break;
        }
        case 8: {
            string res = smallestString({ "ace", "bdf" });
            sort(res.begin(), res.end());
            bool b = res == "abcdef";
            cout << "8 " << b << endl;
            break;
        }
        case 9: {
            string res = smallestString({ "ab", "ba" });
            sort(res.begin(), res.end());
            bool b = res == "aab";
            cout << "9 " << b << endl;
            break;
        }
        case 10: {
            string res = smallestString({ "aab", "aba" });
            sort(res.begin(), res.end());
            bool b = res == "aaab";
            cout << "10 " << b << endl;
            break;
        }
        case 11: {
            string res = smallestString({ "abc", "def", "ghi" });
            sort(res.begin(), res.end());
            bool b = res == "abcdefghi";
            cout << "11 " << b << endl;
            break;
        }
        case 12: {
            string res = smallestString({ "abc", "abc", "abc" });
            sort(res.begin(), res.end());
            bool b = res == "abc";
            cout << "12 " << b << endl;
            break;
        }
        default:
            break;
        }
    }

    cout << "end" << endl;
    return 0;
}