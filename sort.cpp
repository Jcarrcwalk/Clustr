#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include "SeqUnit.hpp"

using namespace std;

bool compareSeqUnitLength(SeqUnit i, SeqUnit j){
		return (i.getLength() > j.getLength());
}

int main (int argc, char* argv[]) {
	ifstream in;    // Create an input file stream.
	//in.open(argv[1]);  // Use it to read from a file named data.txt.
	in.open("trivial.txt");
	cout << "Starting Program..." << endl;
	SeqUnit* nextSeqUnit = new SeqUnit();
	vector<SeqUnit> seqList;
	string nextLine;
	string newSequence;
	string newName;
	//read in sequences, and place them into a vector
	if(in){
		getline(in, nextLine);
		newName = nextLine.substr(1,nextLine.size()-1);
	}
	while(in){
		getline(in,nextLine);
		if(nextLine[0] == '>'){
			SeqUnit* nextSeqUnit = new SeqUnit();
			nextSeqUnit->setName(newName);
			nextSeqUnit->setSequence(newSequence); 
			nextSeqUnit->setLength();
			seqList.push_back(*nextSeqUnit);
			newName = nextLine.substr(1,nextLine.size()-1);
			newSequence.clear();
		}
		else{
			newSequence += nextLine;
		}
	}
	nextSeqUnit->setName(newName);
	nextSeqUnit->setSequence(newSequence); 
	nextSeqUnit->setLength();
	seqList.push_back(*nextSeqUnit);
	
	cout << "Sorting Sequences..." << endl;
	//sort the vector by length
	sort(seqList.begin(),seqList.end(), compareSeqUnitLength);

	FILE *outputFile = fopen("Sorted.txt","w");
	
	for (vector<SeqUnit>::iterator i=seqList.begin(); 
			i!=seqList.end();
			++i) {
				string name= i->getName();
				string sequence = i-> getSequence();
				fprintf(outputFile, "%s\n%s\n",name.c_str(), sequence.c_str());
				//cout << name << "\t" << sequence << endl;
	}
	fclose(outputFile);			
	cout << "Sequences Sorted..." << endl;

	return 0;
}