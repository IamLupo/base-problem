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
	try {
		Base_Algorithem ba;
		
		if(argc == 2) {
			string nr = argv[1];
			
			ba.setN(stoi(nr.c_str(), nullptr, 0));
		}
		
		ba.scanA();
	}
	catch(exception &e) {
		cout << e.what() << endl;
	}
	
	return 0;
}