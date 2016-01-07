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
Algorithem 1: Number Generation
	Data:
		f(3, 1):	2
		f(3, 2):	5
		f(3, 5):	14
		f(3, 14):	41
		f(3, 41):	122
		
		f(4, 1):	3
		f(4, 3):	11
		f(4, 11):	43
		f(4, 43):	171
		f(4, 171):	683
		
		f(5, 1):	4
		f(5, 4):	19
		f(5, 19):	94
		f(5, 94):	469
		f(5, 469):	2344
			
	Explain:
		f(base, start):
			(base * start) - 1
			
Algorithem 2: Pattern
	Data:
		f(4):
			x = 1 3 1 11 1 3 1
			
			x (n * 3 + 1)
			x (n * 3 + 1)
			x 43 x (n * 3 + 1)
			x 43 x 171 x 43 x (n * 3 + 1)
			x 43 x 171 x 43 x 683 x 43 x 171 x 43 x (n * 3 + 1)
			
			
		f(5):
			x = 1 4 1 19 1 4 1
	
			x (n * 4 + 1)
			x (n * 4 + 1)
			x 94 x (n * 4 + 1)
			x 94 x 469 x 94 x (n * 4 + 1)
			
	Explain:
		v = main value
		
		x = values list
		xl = x length
		
		a = take list
		t = progress
		dir = direction (up/down)
		
		Init:
			x[0] = Algo1(base, 1)
			x[1] = Algo1(base, 2)
			
Algorithem 3:
	Data:
		f(1): 010
		f(2): 0102010
		f(3): 010201030102010
		f(4): 0102010301020104010201030102010
		
	Explain:
		f(x) = f(x - 1) + "x" + f(x - 1)
		
Algorithem 3 Small:
	Data:
		f(1, 0): 0
		f(1, 1): 1
		f(1, 2): 0
		
		f(2, 0): 0
		f(2, 1): 1
		f(2, 2): 0
		f(2, 3): 2
		f(2, 4): 0
		f(2, 5): 1
		f(2, 6): 0
		
		f(3, 0): 0
		f(3, 1): 1
		f(3, 2): 0
		f(3, 3): 2
		f(3, 4): 0
		f(3, 5): 1
		f(3, 6): 0
		f(3, 7): 3
		f(3, 8): 0
		f(3, 9): 1
		f(3, 10): 0
		f(3, 11): 2
		f(3, 12): 0
		f(3, 13): 1
		f(3, 14): 0
		
		f(4, 0): 0
		f(4, 1): 1
		f(4, 2): 0
		f(4, 3): 2
		f(4, 4): 0
		f(4, 5): 1
		f(4, 6): 0
		f(4, 7): 3
		f(4, 8): 0
		f(4, 9): 1
		f(4, 10): 0
		f(4, 11): 2
		f(4, 12): 0
		f(4, 13): 1
		f(4, 14): 0
		f(4, 15): 4
		f(4, 16): 0
		f(4, 17): 1
		f(4, 18): 0
		f(4, 19): 2
		f(4, 20): 0
		f(4, 21): 1
		f(4, 22): 0
		f(4, 23): 3
		f(4, 24): 0
		f(4, 25): 1
		f(4, 26): 0
		f(4, 27): 2
		f(4, 28): 0
		f(4, 29): 1
		f(4, 30): 0
		
	Explain:
		f(x, y):
			z = 0
			for x
				z = (z + 1) * 2
			
			return f2(x, y, z)
		
		f2(x, y, z):
			if(x == 0 || y == 0)
				return 0
			
			z /= 2
			if(y == z)
				return x
			else
				return f(x - 1, (y > z) ? y - z : y, z)
*/

//Temp
static mpz_t c;
static mpz_t d;

struct Pattern {
	int base;
	mpz_t v;
	
	mpz_t* x;
	long long xl;
	
	bool a;
	bool dir;
};

void algo1(int base, mpz_t start) {
	//(base * start) - 1
	mpz_mul_ui(start, start, base);
	mpz_sub_ui(start, start, 1);
}

void algo2_init(struct Pattern* pat, int base) {
	pat->base = base;
	mpz_init_set_ui(pat->v, base);
	
	//Generate x
	pat->xl = 2;
	pat->x = malloc(pat->xl * sizeof(mpz_t));
	mpz_init_set_ui(pat->x[0], 1);
	algo1(base, pat->x[0]);
	mpz_init_set(pat->x[1], pat->x[0]);
	algo1(base, pat->x[1]);
	
}

void algo2_next(struct Pattern* pat) {
	if(pat->a) {
		mpz_add_ui(pat->v, pat->v, 1);
		pat->a = false;
	} else {
		
		pat->a = true;
	}
}

int algo3(int x, long long y) {
	int i, z;
	
	z = 0;
	
	for(i = 0; i < x; i++)
		z = (z + 1) * 2;
	
	return algo3_2(x, y, z);
}

int algo3_2(int x, long long y, long long z) {
	if(x == 0 || y == 0)
		return 0;
	
	z /= 2;
	
	if(y == z)
		return x;
	else
		return algo3_2(x - 1, (y > z) ? y - z - 1 : y, z);
}

int main() {
	/*
	long long i, z;
	
	z = 0;
	
	for(i = 0; i < 20; i++) {
		z = (z + 1) * 2;
	}
	
	for(i = 0; i < z + 1; i++) {
		printf("%d", algo3(20, i));
	}
	*/
	
	int i;
	char buffer[1000];
	struct Pattern pat;
	
	//Init
	mpz_init(c);
	mpz_init(d);
	algo2_init(&pat, 5);
	
	//Draw
	mpz_get_str(buffer, 10, pat.v);
	printf("value: %s\n", buffer);
	
	mpz_get_str(buffer, 10, pat.x[0]);
	printf("pat.x[0]: %s\n", buffer);
	
	mpz_get_str(buffer, 10, pat.x[1]);
	printf("pat.x[1]: %s\n", buffer);
	
	for(i = 0; i < 2; i++) {
		algo2_next(&pat);
		
		//Draw
		mpz_get_str(buffer, 10, pat.v);
		printf("value: %s\n", buffer);
	}
	
	//Clean
	mpz_clear(c);
	mpz_clear(d);
}