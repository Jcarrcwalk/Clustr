#include "SeqUnit.hpp"

using namespace std;

void SeqUnit::setName(string newName){
	name = newName;
}

void SeqUnit::setSequence(string newSeq){
	seq = newSeq;
}

void SeqUnit::setLength(){
	length = seq.size();
}

int SeqUnit::getLength(){
	return length;
}

string SeqUnit::getName(){
	return name;
}

string SeqUnit::getSequence(){
return seq;
}
