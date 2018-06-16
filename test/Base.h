#ifndef H_BASE
#define H_BASE

#include <iostream>
#include <vector>

using namespace std;

class Base {
	private:
		int base;
		long long value;
		vector<int> digits;
		
		void updateDigits();
		
	public:
		Base();
		~Base();
		
		void set(int base, int value);
		bool isValid();
		int collisions();
		
		void draw();
};

#endif