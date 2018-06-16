#ifndef H_BASE_ALGORITHEM
#define H_BASE_ALGORITHEM

#include <vector>
#include <ctime>
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
		bool hasAnswerInStart();
		bool hasAnswerInEnd();
		
		int getSmallestStart();
		int getBiggestStart();
		int getSmallestEnd();
		int getBiggestEnd();
		
		void setN(int n);
		
		void scanA();
		void scanB();
		void scan2(mpz_t start, mpz_t end, int id);
		void scan3(int level);
		
		// Draw
		void draw();
		void drawSize();
		void drawBase();
		void drawTime(time_t t);
};

#endif