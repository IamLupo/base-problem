#include "Base_Algorithem.h"

Base_Algorithem::Base_Algorithem() {
	int i;
	Base_Range* br;
	
	//Init
	this->total = 4;
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
	
	// Test 1
	c = true;
	mpz_set(this->t, this->bases[0]->new_start);
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) != 0 and mpz_cmp(this->t, this->bases[i]->new_end) != 0)
			c = false;
	
	if(c)
		return true;
	
	// Test 1
	c = true;
	mpz_set(this->t, this->bases[0]->new_end);
	
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
	string new_start;
	
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


void Base_Algorithem::updateSmallest() {
	int base_id;
	
	base_id = this->getSmallestStart();
	
	this->bases[base_id]->next();
}

void Base_Algorithem::scan() {
	int i, j, id;
	long long s, l;
	Base_Algorithem ba;
	
	l = 1000;
	
	while(true) {
		this->updateSmallest();
		
		// Find collision
		while(!this->hasCollision())
			this->updateSmallest();
		
		// Get smallest start
		id = this->getSmallestStart();
		
		// Patch new generation
		for(i = 0; i < this->total; i++)
			if(i == id)
				*(ba.bases[i]) << *(this->bases[i]);
			else
				*(ba.bases[i]) = *(this->bases[i]);
		
		
		s = mpz_sizeinbase(ba.bases[0]->new_start, 10);
		if(s > l) {
			cout << s << endl;
			l += 1000;
		}
		
		//if(s >= 150001)
			ba.scan2(id, 0);
	}
}

void Base_Algorithem::scan2(int id, int level) {
	int i, new_id;
	Base_Range* br;
	Base_Algorithem ba;
	
	//Debug
	//this->draw();
	
	br = this->bases[id];
	
	// Find collision
	while(!this->hasCollision()) {
		if(br->isDone())
			return;
		
		br->next();
	}
	
	// Get smallest start
	new_id = this->getSmallestStart();
	
	// Patch new generation
	for(i = 0; i < this->total; i++)
		if(i == new_id)
			*(ba.bases[i]) << *(this->bases[i]);
		else
			*(ba.bases[i]) = *(this->bases[i]);
	
	if(hasAnswer()) {
		this->draw();
		cout << "---------------------------------------" << endl;
	} else {
		ba.scan2(new_id, level + 1);
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
