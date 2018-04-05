#include "Base_Algorithem.h"

Base_Algorithem::Base_Algorithem() {
	int i;
	Base_Range* br;
	
	//Init
	this->total = 3;
	mpz_init(this->t);
	
	for(i = 0; i < this->total; i++) {
		// Create base
		br = new Base_Range();
		
		// Set base
		br->setBase(i + 3);
		
		// Next
		br->next();
		
		// Save base
		this->bases.push_back(br);
	}
}

Base_Algorithem::~Base_Algorithem() {
	int i;
	
	for(i = 0; i < this->total; i++)
		delete this->bases[i];
	
	mpz_clear(this->t);
}

bool Base_Algorithem::hasCollision() {
	int i;
	
	this->getBiggestStart();
	
	// Check end
	for(i = 0; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_end) > 0)
			return false;
	
	return true;
}

bool Base_Algorithem::hasAnswer() {
	int i;
	bool c;
	Base_Range* br;
	
	br = this->bases[0];
	
	// Test 1
	c = true;
	mpz_set(this->t, br->new_start);
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) != 0 and mpz_cmp(this->t, this->bases[i]->new_end) != 0)
			c = false;
	
	if(c)
		return true;
	
	// Test 2
	c = true;
	mpz_set(this->t, br->new_end);
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) != 0 and mpz_cmp(this->t, this->bases[i]->new_end) != 0)
			c = false;
	
	return c;
}

/*
	returns the base id
	Stores start result in "t" variable
*/
int Base_Algorithem::getSmallestStart() {
	int i, id;
	
	//Init
	id = 0;
	mpz_set(this->t, this->bases[0]->new_start);
	
	// Get biggest start
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) > 0) {
			id = i;
			mpz_set(this->t, this->bases[i]->new_start);
		}
	
	return id;
}

/*
	returns the base id
	Stores start result in "t" variable
*/
int Base_Algorithem::getBiggestStart() {
	int i, id;
	
	//Init
	id = 0;
	mpz_set(this->t, this->bases[0]->new_start);
	
	// Get biggest start
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) < 0) {
			id = i;
			mpz_set(this->t, this->bases[i]->new_start);
		}
	
	return id;
}

/*
	returns the base id
	Stores start result in "t" variable
*/
int Base_Algorithem::getSmallestEnd() {
	int i, id;
	
	//Init
	id = 0;
	mpz_set(this->t, this->bases[0]->new_end);
	
	// Get biggest start
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_end) > 0) {
			id = i;
			mpz_set(this->t, this->bases[i]->new_end);
		}
	
	return id;
}

/*
	returns the base id
	Stores start result in "t" variable
*/
int Base_Algorithem::getBiggestEnd() {
	int i, id;
	
	//Init
	id = 0;
	mpz_set(this->t, this->bases[0]->new_end);
	
	// Get biggest start
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_end) < 0) {
			id = i;
			mpz_set(this->t, this->bases[i]->new_end);
		}
	
	return id;
}

void Base_Algorithem::scan() {
	int id, s, l;
	
	l = 10000;
	
	while(true) {
		// Update smallest
		id = this->getSmallestStart();
		this->bases[id]->next();
		
		// Find collision
		while(!this->hasCollision()) {
			// Update smallest
			id = this->getSmallestStart();
			this->bases[id]->next();
		}
		
		// Debug
		//this->draw();
		
		s = mpz_sizeinbase(this->t, 10);
		if(s > l) {
			cout << s << endl;
			l += 10000;
		}
		
		this->scan2();
	}
}

void Base_Algorithem::scan2() {
	int i, id, start, end;
	Base_Range* br;
	Base_Algorithem ba;
	
	// Init
	id = this->getSmallestStart();
	br = this->bases[id];
	
	// Get start
	this->getBiggestStart();
	mpz_sub(this->t, this->t, br->new_start);
	start = mpz_sizeinbase(this->t, br->base) - 2;
	
	// Get end
	this->getSmallestEnd();
	mpz_sub(this->t, this->t, br->new_start);
	end = mpz_sizeinbase(this->t, br->base) - 1;
	
	//cout << start << " " << end << endl;
	
	// Patch new generation
	for(i = 0; i < this->total; i++)
		if(i == id)
			*(ba.bases[i]) << *(this->bases[i]);
		else
			*(ba.bases[i]) = *(this->bases[i]);
	
	for(i = start <= 0 ? 0 : start; i <= end; i++) {
		ba.bases[id]->updateXY(i);
		
		if(ba.hasCollision()) {
			if(ba.hasAnswer()) {
				ba.draw();
				cout << "---------------------------------------" << endl;
			} else {
				ba.scan2();
			}
		}
	}
}

void Base_Algorithem::draw() {
	int i;
	
	for(i = 0; i < this->total; i++)
		this->bases[i]->draw();
}

void Base_Algorithem::drawSize() {
	int i;
	
	for(i = 0; i < this->total; i++)
		this->bases[i]->drawSize();
}
