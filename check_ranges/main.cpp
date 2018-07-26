#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Base_Algorithem.h"

using namespace std;

int main(int argc, char* argv[]) {
	int i, n;
	vector<int> base_nrs;
	string get_argument;
	
	try {
		// Default
		n = 0;
		base_nrs = {3, 4, 5};
		
		i = 0;
		while(i < argc) {
			string argument = argv[i];
			
			if(argument == "-n") {
				get_argument = "-n";
			}
			else if(get_argument == "-n") {
				n = stoi(argv[i], nullptr, 0);
			}
			else if(argument == "-base") {
				base_nrs = {};
				get_argument = "-base";
			}
			else if(get_argument == "-base") {
				base_nrs.push_back(stoi(argv[i], nullptr, 0));
			}
			
			i++;
		}
		
		// Run Algorithm
		Base_Algorithem ba(base_nrs);
		ba.setN(n);
		ba.scanA();
	}
	catch(exception &e) {
		cout << e.what() << endl;
	}
	
	return 0;
}
