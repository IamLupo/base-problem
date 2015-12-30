#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "gmp.h"

/*
	Base Problem:
		Known values: 2, 3, 4, 82000, ???
		
		Base 2-3 = 2
			base 2:                10
		
		Base 2-3 = 3
			base 2:                11
			base 3:                10
		
		Base 2-4 = 4
			base 2:               100
			base 3:                11
			base 4:                10
		
		Base 2-5 = 82000
			base 2:	10100000001010000
			base 3:       11011111001
			base 4:         110001100
			base 5:          10111000
		
		Base 2-6: ?? this is the question...
	
	Info:
		3 and 6	= 36
			base 3: 
			base 6: 
		4 and 6	= 1296
		5 and 6	= 5

		3 and 5 = 30
*/

bool check(mpz_t value, int base) {
	int i, j;
	long long length;
	char buffer[1000000];
	mpz_t mod;
	
	mpz_init(mod);
	
	for(i = 3; i < base; i++) {
		mpz_mod_ui(mod, value, i);
		if(mpz_cmp_ui(mod, 0) != 0 && mpz_cmp_ui(mod, 1) != 0)
			return false;
	}
	
	for(i = 3; i < base; i++) {
		length = mpz_sizeinbase(value, i);
		mpz_get_str(buffer, i, value);
		
		for(j = 0; j < length; j++)
			if(buffer[j] != '0' && buffer[j] != '1')
				return false;
	}
	
	return true;
}

void getSmallestBase(int base) {
	char buffer[1000000];
	mpz_t value, i;
	
	mpz_init_set_ui(i, 2);
	mpz_init_set_ui(value, base);
	
	mpz_get_str(buffer, 2, i);
	mpz_set_str(value, buffer, base);

	while(!check(value, base)) {
		mpz_add_ui(i, i, 1);
		mpz_get_str(buffer, 2, i);
		mpz_set_str(value, buffer, base);
		
		if(mpz_get_ui(value) % 1000000 == 0)
			printf("length = %ld\n", mpz_sizeinbase(value, 10));
	}
	
	mpz_get_str(buffer, 10, value);
	printf("base[2-%d] = %s\n", base, buffer);
}

int main() {
	/*
	getSmallestBase(2);
	getSmallestBase(3);
	getSmallestBase(4);
	getSmallestBase(5);
	*/
	getSmallestBase(6);
	
	return 0;
}