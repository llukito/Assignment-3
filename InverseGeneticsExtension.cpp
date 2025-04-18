/*
 * File: InverseGeneticsExtension.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * Suppose you have an RNA strand that encodes a particular protein.
 * A point mutation is a chance to an RNA strand where one letter is 
 * replaced with a different letter. Write a program that computes the probability 
 * that a single point mutation to that strand will cause the strand to encode a different protein
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
#include <algorithm>
#include <vector>
using namespace std;

//constant
const int CODON_SIZE = 3;

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadsCodonMap();

//function prototypes for valid RNA receiving
string getValidRNAStrand(Map<char, Set<string> >&, string&);
bool isValidRNAStrand(string&, Map<char, Set<string> >&, string&);
bool containsOnlyNucleutides(string&);
bool invalidSize(string&);
bool allCodonsAreValid(string&, Map<char, Set<string> >&, string&);

//function prototypes for valid mutation tracking
void getMutatedRNAStrands(Set<string>&, string&);
void getMutatedProteins(Vector<string>&, Set<string>&, Map<char, Set<string> >&, string&);

//function prototypes for result
void printVector(Vector<string>&);
void outPutResult(string&, double&, Vector<string>&);

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadsCodonMap();
    string startingProtein;
    string strandRNA = getValidRNAStrand(codons, startingProtein);
    Set<string> allMutatedRNAStrands;
    getMutatedRNAStrands(allMutatedRNAStrands, strandRNA);
    Vector<string> allMutatedProteins;
    getMutatedProteins(allMutatedProteins, allMutatedRNAStrands, codons, startingProtein);

    double allPossibleMutations = 3 * strandRNA.size(); // three changes for every strand
    double probability = (double)allMutatedProteins.size() / allPossibleMutations;
    outPutResult(startingProtein, probability, allMutatedProteins);

    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadsCodonMap() {
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

/*
* Makes user enter valid RNA strand.
*/
string getValidRNAStrand(Map<char, Set<string> >& codons, string& startingProtein) {
    while (true) {
        string strand = getLine("Enter RNA strand : ");
        if (isValidRNAStrand(strand, codons, startingProtein)) {
            return strand;
        }
        cout << "Enter valid RNA strand" << endl;
    }
}

/*
* RNA strand should be made of these four nucleotides,
* it should have length devisible by 3(because of codons)
* and every three nucleotides should be forming valid codon
* (Our check is not case sensitive)
*/
bool isValidRNAStrand(string& strand, Map<char, Set<string> >& codons, string& startingProtein) {
    // turn into valid RNA strand form (to upper)
    transform(strand.begin(), strand.end(), strand.begin(), ::toupper);

    if (!containsOnlyNucleutides(strand)) {
        return false;
    }
    if (invalidSize(strand)) {
        return false;
    }
    return allCodonsAreValid(strand, codons, startingProtein);
}

bool containsOnlyNucleutides(string& strand) {
    for (char ch : strand) {
        if (!(ch == 'A' || ch == 'C' || ch == 'U' || ch == 'G')) {
            return false;
        }
    }
    return true;
}

bool invalidSize(string& strand) {
    return strand.size() % CODON_SIZE != 0;
}

/*
* All three nucleotides(codons) should be valid,
* so they should be in values of codons map. Also
* this function fills startingProtein. So we translate
* RNA strand into protein too
*/
bool allCodonsAreValid(string& strand, Map<char, Set<string> >& codons, string& startingProtein) {
    for (int i = 0; i < strand.size() / CODON_SIZE; i++) {
        int startIndex = CODON_SIZE * i;
        int endIndex = CODON_SIZE * (i + 1);
        string codon = strand.substr(startIndex, endIndex - startIndex);
        bool found = false;
        for (char aminoAcid : codons) {
            for (string validCodon : codons[aminoAcid]) {
                if (validCodon == codon) {
                    found = true;
                    startingProtein += aminoAcid;
                    break;
                }
            }
            if (found)break;
        }
        if (!found)return false;
    }
    return true;
}

/*
* This function generates all possible RNA strands with
* point mutation
*/
void getMutatedRNAStrands(Set<string>& allMutatedRNAStrands, string& strandRNA) {
    vector<char> nucleotides = { 'A','U','G','C' };
    for (int i = 0; i < strandRNA.size(); i++) {
        for (char ch : nucleotides) {
            if (ch != strandRNA[i]) {
                char temp = strandRNA[i];
                strandRNA[i] = ch;
                allMutatedRNAStrands += strandRNA;
                strandRNA[i] = temp;
            }
        }
    }
}

/*
* In txt file there were ";". As task never specified what these are,
* let's assume that if protein contains ";", than it is not
* valid protein. So,We fill allMutatedProteins with criterias :
* 1) does not contain ";" 2)differs from startingProtein
* 3) there are only unique mutated proteins stored there
*/
void getMutatedProteins(Vector<string>& allMutatedProteins, Set<string>& allMutatedRNAStrands,
    Map<char, Set<string> >& codons, string& startingProtein) {

    for (string strand : allMutatedRNAStrands) {
        string mutatedProtein;
        if (allCodonsAreValid(strand, codons, mutatedProtein)) {
            if (mutatedProtein.find(";")==string::npos && mutatedProtein != startingProtein
                && find(allMutatedProteins.begin(), allMutatedProteins.end(), mutatedProtein)== allMutatedProteins.end()){
                allMutatedProteins += mutatedProtein;
            }
        }
    }
}

void outPutResult(string& startingProtein, double& probability, Vector<string>& allMutatedProteins) {
    cout << "Starting protein is : " << startingProtein << endl;
    cout << "Probability that point mutation encodes different protein : " << probability << endl;
    cout << "All mutated proteins : " << endl;
    printVector(allMutatedProteins);
}

void printVector(Vector<string>& allMutatedProteins) {
    for (string proton : allMutatedProteins) {
        cout << proton << endl;
    }
}
