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

struct Base_Range {
	int b;			// Base
	mpz_t x;		// Start
	mpz_t y;		// End
};

void init(Base_Range &br, int b) {
	br.b = b;
	mpz_init_set_ui(br.x, b);
	mpz_init_set_ui(br.y, b + 1);
}

void init(Base_Range &br, int b, mpz_t x, mpz_t y) {
	br.b = b;
	mpz_init_set(br.x, x);
	mpz_init_set(br.y, y);
}

void next(Base_Range &br) {
	//x = x * b
	mpz_mul_ui(br.x, br.x, br.b);
	
	//y = x + y
	mpz_add(br.y, br.x, br.y);
}

void draw(Base_Range &br) {
	cout << br.b << " "
		<< mpz_get_str(nullptr, 10, br.x) << " "
		<< mpz_get_str(nullptr, 10, br.y) << endl;
}

void draw_size(Base_Range &br) {
	cout << mpz_sizeinbase(br.x, br.b) << " "
		<< mpz_sizeinbase(br.y, br.b) << endl;
}

void clean(Base_Range &br) {
	mpz_clear(br.x);
	mpz_clear(br.y);
}

void f() {
	int i;
	Base_Range br;
	
	//Init
	init(br, 3);
	
	for(i = 0; i < 1000; i++) {
		// Draw
		draw_size(br);
		next(br);
	}
}

int main() {
	f();
}