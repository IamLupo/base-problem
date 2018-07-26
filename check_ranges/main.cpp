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
	
	try {
		// Default
		n = 0;
		base_nrs = {3, 4, 5};
		
		i = 0;
		while(i < argc) {
			string argument = argv[i];
			
			if(argument == "-n") {
				n = stoi(argv[i + 1], nullptr, 0);
				
				i++;
			}
			
			if(argument == "-base") {
				base_nrs = {};
				
				i++;
				while(i < argc) {
					cout << stoi(argv[i], nullptr, 0) << endl;
					
					base_nrs.push_back(stoi(argv[i], nullptr, 0));
					
					i++;
				}
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
