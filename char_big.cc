#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

unsigned long computeI(const char* str, int i) {
	unsigned long sum = 0L;
	sum += 11881376 * (str[i]-'A');
	sum += 456976 * (str[i+1]-'A');
	sum += 17576 * (str[i+2]-'A');
	sum += 676 * (str[i+3]-'A');
	sum += 1 * (str[i+4]-'A');
	return sum;
}

void get_vector(const string& seq, map<unsigned long, int>* vec) {
	int i = 0;
	int N = 5;
	const char* str = seq.c_str();
	while(true) {
		int lastI = i+N-1;
		if (str[lastI] == '\0') {
			break;
		}
		unsigned long sum = computeI(str, i);
		(*vec)[sum]++;
		i++;
	}
}

double dot(const map<unsigned long, int>& v1,
		   const map<unsigned long, int>& v2) {
			   double sum = 0.0;
			   map<unsigned long,int>::const_iterator iter1 = v1.begin();
			   map<unsigned long,int>::const_iterator iter2 = v2.begin();

			   while(iter1 != v1.end() && iter2 != v2.end()) {
				   if (iter1->first == iter2->first) {
					   sum += (double)iter1->second * iter2->second;
					   iter1++;
					   iter2++;
				   } else if (iter1->first < iter2->first) {
					   iter1++;
					   continue;
				   } else if (iter1->first > iter2->first) {
					   iter2++;
					   continue;
				   }
				   return sum;
			   }
}

double identity_sim(const string& seq1, const string& seq2) {
	map<unsigned long, int> vec1, vec2;
	get_vector(seq1, &vec1);
	get_vector(seq2, &vec2);
	return dot(vec1, vec2);
}

double identity_sim(const map<unsigned long, int>& vec1, const string& seq2) {
	map<unsigned long, int> vec2;
	get_vector(seq2, &vec2);
	return dot(vec1, vec2);
}

double identity_sim(const map<unsigned long, int>& vec1,
					const map<unsigned long, int>& vec2) {
						return dot(vec1, vec2);
}

int main3 (int argc, char* argv[]) {
	ifstream in;    // Create an input file stream.
	in.open(argv[1]);  // Use it to read from a file named data.txt.
	
	vector<map<unsigned long, int>*> all;
	vector<string> allString;
	string str;
	int lineno = 0;
	int N = 5;
	int totalSize = 0;
	while (in) {
		getline(in,str);  // Ignore odd lines
		getline(in,str);  // Use even lines
		// allString.push_back(str);
		map<unsigned long, int>* vec = new map<unsigned long, int>();
		get_vector(str, vec);
		all.push_back(vec);
		lineno++;
		if (lineno % 10000 == 0) {
			cerr << "Loaded " << lineno << " lines." << endl;
		}
	}
	cout << "All string size = " << all.size() << endl;
	int nonzero = 0;
	for (int si = 0; si < all.size(); ++si) {
		cerr << "si:" << si << endl;
		for (int sj = 0; sj < si; ++sj) {
			double sim = identity_sim(*all[si], *all[sj]);
			if (sim != 0.0) {
				nonzero++;
			}
			if (sj > 10000 && sj % 10000 == 0) {
				cerr << "sj:" << sj << " nonzero = " << nonzero << endl;
			}
		}
		cout << "nonzero = " << nonzero << endl;
	}



	return 0;
}
