#include "Base_Algorithem.h"

Base_Algorithem::Base_Algorithem() {
	int i;
	Base_Range* br;
	
	//Init
	this->total = 4;
	mpz_init(this->t);
	
	for(i = 0; i <= this->total; i++) {
		// Create base
		br = new Base_Range();
		
		// Set base
		br->setBase(i + 3);
		
		// Next
		br->next();
		
		// Save base
		bases.push_back(br);
	}
}

Base_Algorithem::~Base_Algorithem() {
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

void Base_Algorithem::updateSmallest() {
	int base_id;
	
	base_id = this->getSmallestStart();
	
	this->bases[base_id]->next();
}

void Base_Algorithem::scan() {
	int i, id;
	Base_Algorithem ba;
	
	// Find collision
	while(!this->hasCollision()) {
		this->updateSmallest();
	}
	
	// Get smallest start
	id = this->getSmallestStart();
	
	// Patch new generation
	for(i = 0; i < this->total; i++)
		if(i == id)
			*(ba.bases[i]) << *(this->bases[i]);
		else
			*(ba.bases[i]) = *(this->bases[i]);
	
	ba.scan2(id);
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
