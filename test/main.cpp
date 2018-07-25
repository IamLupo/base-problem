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
	
	for(i = 1; i <= 100; i++) {
		for(j = pow(3, i); j <= (pow(3, i + 1) - 1) / 2; j++) {
		
			b3.set(3, j);
			b4.set(4, j);
			
			if(b3.isValid() && b4.isValid()) {
				b3.draw();
				//b4.draw();
			}
		}
	}
}

int main() {
	f();
	
	return 0;
}