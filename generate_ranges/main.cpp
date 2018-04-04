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

using namespace std;

/*
	f(3):
		Data:
			x1	y1	x2	y2
			3	4	9	13
			9	13	27	40
			27	40	81	121
			81	121	243	364
			243	364	729	1093
			729	1093	2187	3280
			2187	3280	6561	9841
			6561	9841	19683	29524
			19683	29524	59049	88573
			59049	88573	177147	265720
			177147	265720	531441	797161
			531441	797161	1594323	2391484
		
		Conclusion:
			x2 = 3*x1
			y1 = (x2 - 1) / 2
			y2 = y1 + x2

	f(4):
		Data:
			x1	y1	x2	y2
			4	5	16	21
			16	21	64	85
			64	85	256	341
			256	341	1024	1365
			1024	1365	4096	5461
			4096	5461	16384	21845
			16384	21845	65536	87381
			65536	87381	262144	349525
			262144	349525	1048576	1398101
			1048576	1398101	4194304	5592405
			4194304	5592405	16777216	22369621


		Conclusion:
			x2 = 5*x1
			y1 = (x2 - 1) / 3
			y2 = y1 + x2
	
	f(5):
		Data:
			x1	y1	x2	y2
			5	6	25	31
			25	31	125	156
			125	156	625	781
			625	781	3125	3906
			3125	3906	15625	19531
			15625	19531	78125	97656
			78125	97656	390625	488281
			390625	488281	1953125	2441406
			1953125	2441406	9765625	12207031
			9765625	12207031	48828125	61035156

		Conclusion:
			y1 = (x2 - 1) / 4
			x2 = 5*x1
			y2 = y1 + x2
			
	f(6):
		Data:
			x1	y1	x2	y2
			6	7	36	43
			36	43	216	259
			216	259	1296	1555
			1296	1555	7776	9331
			7776	9331	46656	55987
			46656	55987	279936	335923
			279936	335923	1679616	2015539
			1679616	2015539	10077696	12093235


		Conclusion:
			y1 = (x2 - 1) / 5
			x2 = 6*x1
			y2 = y1 + x2
*/

bool check_base(mpz_t x, int b) {
	int i;
	long long l;
	char s[1000000];
	
	l = mpz_sizeinbase(x, b);
	mpz_get_str(s, b, x);
	
	for(i = 0; i < l; i++)
		if(s[i] != '0' && s[i] != '1')
			return false;
	
	return true;
}

void f_base(int b) {
	mpz_t x;
	int i;
	vector<long long> v1, v2;
	
	//Init
	mpz_init(x);
	
	for(i = 3; i < 100; i++) {
		mpz_set_ui(x, i);
		
		if(check_base(x, b)) {
			cout << i << endl;
		}
	}
}

void f_range_base(int b) {
	int i;
	long long x, y;
	
	//Init
	x = b;
	y = b + 1;
	
	for(i = 0; i < 10; i++) {
		// Debug
		cout << x << " " << y << endl;
		
		// Update
		x = x * b;
		y = x + y;
	}
}

int main() {
	int i;
	
	for(i = 4; i <= 4; i++) {
		f_base(i);
		cout << "--------------" << endl;
	}
}