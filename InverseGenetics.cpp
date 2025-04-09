/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons, string currentStrand);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();
string getValidProtein(Map<char, Set<string>>& codons);
bool isValid(string& protein, Map<char, Set<string>>& codons);

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
    string protein = getValidProtein(codons);
    listAllRNAStrandsFor(protein, codons, "");
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

string getValidProtein(Map<char, Set<string>>& codons) {
    while (true) {
        string protein = getLine("Enter protein: ");
        if (isValid(protein, codons)) {
            return protein;
        }
        cout << "Enter valid protein" << endl;
    }
}

bool isValid(string& protein, Map<char, Set<string>>& codons) {
    for (char ch : protein) {
        if (!codons.containsKey(ch)) {
            return false;
        }
    }
    return true;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons, string currentStrand) {
    if (protein.empty()) {
        cout << currentStrand << endl;
        return;
    }
    char ch = protein[0];
    for (string codon : codons[ch]) {
        listAllRNAStrandsFor(protein.substr(1), codons, currentStrand + codon);
    }
}