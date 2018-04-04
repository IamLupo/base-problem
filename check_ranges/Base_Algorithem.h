#ifndef H_BASE_ALGORITHEM
#define H_BASE_ALGORITHEM

#include <vector>
#include "Base_Range.h"

using namespace std;

class Base_Algorithem {
	private:
		int total;		// total bases
		mpz_t t;		// Temp
	
	public:
		vector<Base_Range*> bases;
		
		Base_Algorithem();
		~Base_Algorithem();
		
		bool hasCollision();
		bool hasAnswer();
		
		int getSmallestStart();
		int getBiggestStart();
		
		void updateSmallest();
		
		void scan();
		void scan2(int id, int level);
		
		// Draw
		void draw();
		void drawSize();
};

#endif