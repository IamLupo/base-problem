#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "gmp.h"
#include "Base.h"

using namespace std;

void f() {
	int i, j;
	Base b3, b4, b5;
	
	for(j = 0; j <= 10; j++) {
		for(i = pow(3, i); i <= (pow(3, i + 1) - 1) / 2; i++) {
			b3.set(3, i);
			
			if(b3.isValid()) {
				
				b4.set(4, i);
				if(b4.isValid()) {
					// Debug
					//cout << "f(" << i << ") = " << b3.collisions() << ", " << b4.collisions();
					cout << b3.collisions() << "	" << b4.collisions() << endl;
					/*
					b5.set(5, i);	
					if(b5.isValid()) {
						// Debug
						//cout << ", " << b5.collisions();
					}
					*/
					//cout << endl;
				}
			}
		}
	}
}

int main() {
	f();
	
	return 0;
}