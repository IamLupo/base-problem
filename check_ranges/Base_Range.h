#ifndef H_BASE_RANGE
#define H_BASE_RANGE

#include <iostream>
#include "gmp.h"

class Base_Range {
	private:
		int base;			// Base
		
		mpz_t start;		// Start
		mpz_t end;			// End
		
		mpz_t x;			// x
		mpz_t y;			// y
		
	public:
		mpz_t new_start;	// new Start
		mpz_t new_end;		// new End
	
		Base_Range();
		~Base_Range();
		
		Base_Range& operator=(const Base_Range& br);
		Base_Range& operator<<(const Base_Range& br);
		
		void setBase(int base);
		bool isDone();
		void next();
		
		//Draw
		void draw();
		void drawSize();
};

#endif