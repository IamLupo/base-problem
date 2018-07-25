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
	int n, first_base, last_base;
	
	try {
		// Default values
		n = 0;
		first_base = 3;
		last_base = 5;
		
		if(argc >= 2) {
			n = stoi(argv[1], nullptr, 0);
		}
		
		if(argc >= 4) {
			first_base = stoi(argv[2], nullptr, 0);
			last_base = stoi(argv[3], nullptr, 0);
		}
		
		Base_Algorithem ba(first_base, last_base - first_base + 1);
		ba.setN(n);
		ba.scanA();
	}
	catch(exception &e) {
		cout << e.what() << endl;
	}
	
	return 0;
}
