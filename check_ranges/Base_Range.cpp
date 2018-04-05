#include "Base_Range.h"
 
using namespace std;
 
Base_Range::Base_Range() {
	this->base = 0;
	
	mpz_init_set_ui(this->start, 0);
	mpz_init_set_ui(this->end, 0);
	//mpz_ui_pow_ui(this->end, 10, 1000);
	
	mpz_init_set_ui(this->x, 0);
	mpz_init_set_ui(this->y, 1);
	
	mpz_init_set_ui(this->new_start, 0);
	mpz_init_set_ui(this->new_end, 1);
}

Base_Range::~Base_Range() {
	mpz_clear(this->start);
	mpz_clear(this->end);
	
	mpz_clear(this->x);
	mpz_clear(this->y);
	
	mpz_clear(this->new_start);
	mpz_clear(this->new_end);
}

/*
	Copy over the variables to the other object
*/
Base_Range& Base_Range::operator=(const Base_Range &parent) {
	// Debug
	//cout << "operator=(const Base_Range &parent)" << endl;
	
	this->base = parent.base;
	
	mpz_set(this->start, parent.start);
	mpz_set(this->end, parent.end);
	
	mpz_set(this->x, parent.x);
	mpz_set(this->y, parent.y);
	
	mpz_set(this->new_start, parent.new_start);
	mpz_set(this->new_end, parent.new_end);
	
	return *this;
}

/*
	Patch over the variables to the other object for the next generation
*/
Base_Range& Base_Range::operator<<(const Base_Range &parent) {
	// Debug
	//cout << "operator<<(const Base_Range &parent)" << endl;
	
	this->base = parent.base;
	
	mpz_set(this->start, parent.new_start);
	mpz_set(this->end, parent.new_end);
	
	mpz_set_ui(this->x, 0);
	mpz_set_ui(this->y, 1);
	
	mpz_set(this->new_start, parent.new_start);
	mpz_add_ui(this->new_end, this->start, 1);
	
	return *this;
}

void Base_Range::setBase(int base) {
	this->base = base;
}

void Base_Range::updateXY(long long n) {
	if(n <= 0) {
		mpz_set_ui(this->x, 0);
		mpz_set_ui(this->y, 1);
	} else {
		// x = base^n
		mpz_ui_pow_ui(this->x, this->base, n);
		
		// y = (base^(n + 1) - 1) / (base - 1)
		mpz_mul_ui(this->y, this->x, this->base);
		mpz_sub_ui(this->y, this->y, 1);
		mpz_div_ui(this->y, this->y, this->base - 1);
	}
	
	// update new start and end
	mpz_add(this->new_start, this->start, this->x);
	mpz_add(this->new_end, this->start, this->y);
}

bool Base_Range::isDone() {
	// No end detected
	if(mpz_cmp_ui(this->end, 0) == 0)
		return false;
	
	return (mpz_cmp(this->new_end, this->end) == 1);
}

bool Base_Range::isInRange(mpz_t pos) {
	if(mpz_cmp(this->new_start, pos) < 0 && mpz_cmp(this->new_end, pos) > 0)
		return true;
	
	return false;
}

void Base_Range::next() {
	// Fix
	if(mpz_cmp_ui(this->x, 0) == 0)
		mpz_set_ui(this->x, 1);
	
	//x = x * base
	mpz_mul_ui(this->x, this->x, this->base);
	
	//y = x + y
	mpz_add(this->y, this->x, this->y);
	
	// update new start and end
	mpz_add(this->new_start, this->start, this->x);
	mpz_add(this->new_end, this->start, this->y);
}

// Draw
void Base_Range::draw() {
	string start, end, x, y, new_start, new_end;
	
	// Get start and y
	start = mpz_get_str(nullptr, 10, this->start);
	end = mpz_get_str(nullptr, 10, this->end);
	
	// Get x and y
	x = mpz_get_str(nullptr, 10, this->x);
	y = mpz_get_str(nullptr, 10, this->y);
	
	// Get new start and end
	new_start = mpz_get_str(nullptr, 10, this->new_start);
	new_end = mpz_get_str(nullptr, 10, this->new_end);
	
	// Draw
	cout << "Base_Range[" << this->base << "] = "
		<< "{ " << start << ", " << end << " }"
		<< "{ " << x << ", " << y << " }"
		<< "{ " << new_start << ", " << new_end << " }"
		<< endl;
}

void Base_Range::drawSize() {
	long long start, end, x, y;
	
	// Get start and y
	start = mpz_sizeinbase(this->start, 10);
	end = mpz_sizeinbase(this->end, 10);
	
	// Get x and y
	x = mpz_sizeinbase(this->x, 10);
	y = mpz_sizeinbase(this->y, 10);
	
	// Draw
	cout << "Base_Range[" << this->base << "] = "
		<< "{ " << start << ", " << end << " }"
		<< "{ " << x << ", " << y << " }" << endl;
}