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
*/

bool check(mpz_t value, int base) {
	int i, j;
	long long length;
	char buffer[1000000];
	
	for(i = 3; i < base; i++) {
		length = mpz_sizeinbase(value, i);
		mpz_get_str(buffer, i, value);
		
		for(j = 0; j < length; j++)
			if(buffer[j] != '0' && buffer[j] != '1')
				return false;
	}
	
	return true;
}

bool check_char(char* str, int base) {
	mpz_t value;
	
	mpz_init_set_str(value, str, 10);
	
	return check(value, base);
}

void next(mpz_t value, mpz_t index, int base) {
	char buffer[1000000];
	
	mpz_add_ui(index, index, 1);
	mpz_get_str(buffer, 2, index);
	mpz_set_str(value, buffer, base);

	while(!check(value, base)) {
		mpz_add_ui(index, index, 1);
		mpz_get_str(buffer, 2, index);
		mpz_set_str(value, buffer, base);
		
		//if(mpz_get_ui(value) % 1000000 == 0)
		//	printf("length = %ld\n", mpz_sizeinbase(value, 10));
	}
}

void getSmallestBase(int base, int loop) {
	int i, j, nr;
	char buffer[1000000];
	mpz_t value, index;
	
	nr = 0;
	mpz_init_set_ui(index, 0);
	mpz_init_set_ui(value, 0);
	
	for(j = 0; j < loop; j++) {
		next(value, index, base);
		
		mpz_get_str(buffer, 10, value);
		printf("%d	%s\n", nr, buffer);
		nr++;
	}
}

int main() {
	getSmallestBase(3, 2000);
	
	//printf("%s\n", check_char("82000", 5) ? "true" : "false");
	
	return 0;
}