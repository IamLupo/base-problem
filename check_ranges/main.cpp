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

void f() {
	int i;
	long long x;
	Base_Range br_3, br_4, br_5;
	
	br_3.setBase(3);
	br_4.setBase(4);
	br_5.setBase(5);
	
	while(!br_3.isDone()) {
		if(x % 10000 == 0)
			br_3.drawSize();
		
		br_3.next();
		br_4.next();
		br_5.next();
		
		x++;
	}
}

void f2() {
	int i;
	Base_Range br, br2;
	
	br.setBase(3);
	br.next();
	br.next();
	br.next();
	
	br2 = br;
	
	while(!br2.isDone()) {
		br2.draw();
		br2.next();
	}
}

void f3() {
	Base_Algorithem ba;
	
	ba.scan();
}

void f4() {
	int i;
	Base_Algorithem ba;
	
	i = 0;
	
	while(true) {
		ba.updateSmallest();
		
		if(ba.hasCollision()) {
			i++;
			
			ba.drawSize();
			cout << i << endl;
		}
	}
}

int main() {
	f3();
	
	return 0;
}