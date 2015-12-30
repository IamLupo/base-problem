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
Algorithem 1: Valid number range
	Data:
		f(3):
			[0] [1093]
			[2187] [3280]
			[6561] [9841]
			[19683] [29524]
			[59049] [88573]
			...

		f(4):
			[0] [5461]
			[16384] [21845]
			[65536] [87381]
			[262144] [349525]
			[1048576] [1398101]
			...
		
		f(5):
			[0] [19531]
			[78125] [97656]
			[390625] [488281]
			[1953125] [2441406]
			[9765625] [12207031]
			...
			
	Explain:
		f(base):
			[a] [b]
			[c] [d]

		init:
			n = base - 1
			a = 0
			b = Algo3(base)
			
		Next:
			c = (b * n) + 1
			d = b + c

			a = c
			b = d

Algorithem 2: Number position
	Data:
		f(3):
			[0]    [126]
			[127]  [254]
			[255]  [510]
			[511]  [1022]
			[1023] [2046]
			...

		f(4):
			[0]    [126]
			[127]  [254]
			[255]  [510]
			[511]  [1022]
			[1023] [2046]
			...

	Explain:
		f(base):
			[a] [b]
			[c] [d]

		init:
			n = base - 1
			a = 0
			b = 0
			
		Loop:
			a and b is known we can generate c and d

			c1 = b1 + 1
			c2 = (b2 * n) + 1
			d1 = c1 * 2
			d2 = b2 + c2

			a = c
			b = d

Algorithem 3:
	Data:
		f(3):	1093
		f(4):	5461
		f(5):	19531
		f(6):	55987
		
	Explain:
		f(base):
			return (x^8 - x) / (x^2 - x)
*/

//Temp
static mpz_t c;
static mpz_t d;

struct Range {
	int n;
	mpz_t a;
	mpz_t b;
};

void algo3(int base, mpz_t solution) {
	mpz_t a, b;
	
	//Init
	mpz_init_set_ui(a, base);
	mpz_init_set_ui(b, base);
	
	//(x^8 - x)
	mpz_pow_ui(a, a, 8);
	mpz_sub_ui(a, a, base);
	
	//(x^2 - x)
	mpz_pow_ui(b, b, 2);
	mpz_sub_ui(b, b, base);
	
	mpz_div(solution, a, b);
}

void algo2(int base) {
	int i, n;
	char c_a[1000], c_b[1000];
	mpz_t a, b, c, d;
	
	//Init
	mpz_init_set_ui(a, 0);
	mpz_init_set_ui(b, 126);
	mpz_init(c);
	mpz_init(d);
	
	//Generate
	n = base - 1;
	
	//Draw
	mpz_get_str(c_a, 10, a);
	mpz_get_str(c_b, 10, b);
	printf("[%s] [%s]\n", c_a, c_b);
	
	for(i = 0; i < 5; i++) {
		//c = b + 1
		mpz_add_ui(c, b, 1);
		
		//d = c * 2
		mpz_mul_ui(d, c, 2);
		
		//a = c
		mpz_set(a, c);
		//b = d
		mpz_set(b, d);
		
		//Draw
		mpz_get_str(c_a, 10, a);
		mpz_get_str(c_b, 10, b);
		printf("[%s] [%s]\n", c_a, c_b);
	}
}

void algo1_init(struct Range* r, int base) {
	//Init
	mpz_init_set_ui(r->a, 0);
	mpz_init(r->b);
	
	//Generate
	r->n = base - 1;
	algo3(base, r->b);
}

void algo1_next(struct Range* r) {
	//c = (b * n) + 1
	mpz_mul_ui(c, r->b, r->n);
	mpz_add_ui(c, c, 1);
	
	//d = b + c
	mpz_add(d, r->b, c);
	
	//a = c
	mpz_set(r->a, c);
	//b = d
	mpz_set(r->b, d);
}

void algo1_draw(struct Range* r) {
	char c_a[1000], c_b[1000];
	
	mpz_get_str(c_a, 10, r->a);
	mpz_get_str(c_b, 10, r->b);
	printf("[%s] [%s]\n", c_a, c_b);
}

void algo1(int base) {
	int i, n, count;
	char c_a[1000], c_b[1000];
	mpz_t a, b, c, d;
	
	//Init
	mpz_init_set_ui(a, 0);
	mpz_init(b);
	mpz_init(c);
	mpz_init(d);
	count = 0;
	
	//Generate
	n = base - 1;
	algo3(base, b);
	
	//Draw
	mpz_get_str(c_a, 10, a);
	mpz_get_str(c_b, 10, b);
	printf("[%s] [%s]\n", c_a, c_b);
	
	for(i = 0; i < 10; i++) {
		//c = (b * n) + 1
		mpz_mul_ui(c, b, n);
		mpz_add_ui(c, c, 1);
		
		//d = b + c
		mpz_add(d, b, c);
		
		//a = c
		mpz_set(a, c);
		//b = d
		mpz_set(b, d);
		
		//Draw
		mpz_get_str(c_a, 10, a);
		mpz_get_str(c_b, 10, b);
		printf("[%s] [%s]\n", c_a, c_b);
		
		/*
		if(count % 10000 == 0)
			printf("digits: %ld\n", mpz_sizeinbase(d, 10));
		
		count++;
		*/
	}
}

void collapsedRanges(int base) {
	int i, j, r_length, count, collsion;
	struct Range *r;
	bool check, check_collision;
	mpz_t smallest, biggest;
	
	//Init
	count = 0;
	collsion = 0;
	
	//Generate Range
	r_length = base - 3;
	r = malloc(4 * sizeof(struct Range));
	
	for(i = 0; i < r_length; i++)
		algo1_init(&r[i], 3 + i);
	algo1_init(&r[r_length], base);
	
	//Loop
	for(i = 0; i < 1000000; i++) {
		check = true;
		check_collision = true;
		
		for(j = 0; j < r_length; j++) {
			if(mpz_cmp(r[j].b, r[r_length].a) < 0) {
				algo1_next(&r[j]);
				check = false;
				j = r_length;
			}
			
			if(mpz_cmp(r[j].a, r[r_length].b) > 0)
				check_collision = false;
		}
		
		if(check) {
			if(check_collision) {
				mpz_init_set(biggest, r[r_length].a);
				mpz_init_set(smallest, r[r_length].b);
				
				for(j = 0; j < r_length; j++) {
					if(mpz_cmp(biggest, r[j].a) < 0)
						mpz_set(biggest, r[j].a);
					
					if(mpz_cmp(smallest, r[j].b) > 0)
						mpz_set(smallest, r[j].b);
				}
				
				mpz_sub(smallest, smallest, biggest);
				//printf("smallest digits: %ld\n", mpz_sizeinbase(r[r_length].b, 10));
				
				collsion++;
			}
			algo1_next(&r[r_length]);
		}
		
		//Draw
		if(count % 100000 == 0)
			printf("digits: %ld\n", mpz_sizeinbase(r[r_length].b, 10));
		
		count++;
	}
	
	printf("collsions: %d\n", collsion);
}

int main() {
	//Init
	mpz_init(c);
	mpz_init(d);
	
	collapsedRanges(6);
	
	//Clean
	mpz_clear(c);
	mpz_clear(d);
}