#ifndef SEQUNIT_H_
#define SEQUNIT_H_

#include <string>

using namespace std;

class SeqUnit{
public:
	string name;
	int length;
	string seq;	
	void setName(string newName);
	void setSequence(string newSeq);
	void setLength();
	int getLength();
	string getName();
	string getSequence();
	
};

#endif