#include "Base.h"
 
Base::Base() {
	
}

Base::~Base() {
	
}

void Base::set(int base, int value) {
	this->base = base;
	this->value = value;
	
	this->updateDigits();
}

void Base::updateDigits() {
	int value;
	vector<int> digits;
	
	//Init
	value = this->value;
	
	while(value != 0) {
		digits.push_back(value % this->base);
		value /= this->base;
	}
	
	this->digits = digits;
}

bool Base::isValid() {
	int i;
	
	for(i = 0; i < this->digits.size(); i++)
		if(this->digits[i] != 0 && this->digits[i] != 1)
			return false;
	
	return true;
}

int Base::collisions() {
	int i, j, r;
	
	//Init
	r = 0;
	
	for(i = this->digits.size() - 1; i > 0; i--) {
		r = (r == 0) ? this->digits[i] : r + this->digits[i];
		r *= 2;
	}
	
	if(this->digits.size() > 0)
		r += this->digits[0];
	
	return r;
}

void Base::draw() {
	int i;
	
	cout << this->value << "[base " << this->base << "] = {";
	
	for(i = this->digits.size() - 1; i >= 0; i--) {
		cout << " " << this->digits[i];
	}
	
	cout << " }" << endl;
}