#ifndef H_BASE_RANGE
#define H_BASE_RANGE

#include <iostream>
#include "gmp.h"

class Base_Range {
	private:
		mpz_t start;		// Start
		mpz_t end;			// End
		
		mpz_t x;			// x
		mpz_t y;			// y
		
	public:
		int base;			// Base
		
		mpz_t new_start;	// new Start
		mpz_t new_end;		// new End
	
		Base_Range();
		~Base_Range();
		
		Base_Range& operator=(const Base_Range& br);
		Base_Range& operator<<(const Base_Range& br);
		
		void setBase(int base);
		void updateXY(long long n);
		bool isDone();
		bool isInRange(mpz_t pos);
		void next();
		
		//Draw
		void draw();
		void drawSize();
};

#endif