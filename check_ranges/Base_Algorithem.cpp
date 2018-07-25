#include "Base_Algorithem.h"

static int highest_level = 0;

Base_Algorithem::Base_Algorithem(int start, int total) {
	int i;
	Base_Range* br;
	
	//Init
	this->total = total;
	mpz_init(this->t);
	
	for(i = 0; i < this->total; i++) {
		// Create base
		br = new Base_Range();
		
		// Set base
		br->setBase(start + i);
		
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

bool Base_Algorithem::hasAnswerInStart() {
	int i;
	
	//Init
	mpz_set(this->t, this->bases[0]->new_start);
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) != 0 and mpz_cmp(this->t, this->bases[i]->new_end) != 0)
			return false;
	
	return true;
}

bool Base_Algorithem::hasAnswerInEnd() {
	int i;
	
	//Init
	mpz_set(this->t, this->bases[0]->new_end);
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) != 0 and mpz_cmp(this->t, this->bases[i]->new_end) != 0)
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
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_start) < 0) {
			id = i;
			mpz_set(this->t, this->bases[i]->new_start);
		}
	
	return id;
}

/*
	returns the base id
	Stores end result in "t" variable
*/
int Base_Algorithem::getSmallestEnd() {
	int i, id;
	
	//Init
	id = 0;
	mpz_set(this->t, this->bases[0]->new_end);
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_end) > 0) {
			id = i;
			mpz_set(this->t, this->bases[i]->new_end);
		}
	
	return id;
}

/*
	returns the base id
	Stores end result in "t" variable
*/
int Base_Algorithem::getBiggestEnd() {
	int i, id;
	
	//Init
	id = 0;
	mpz_set(this->t, this->bases[0]->new_end);
	
	for(i = 1; i < this->total; i++)
		if(mpz_cmp(this->t, this->bases[i]->new_end) < 0) {
			id = i;
			mpz_set(this->t, this->bases[i]->new_end);
		}
	
	return id;
}

void Base_Algorithem::setN(int n) {
	int i;
	long long base_n;
	
	mpz_ui_pow_ui(this->t, 10, n);
	
	for(i = 0; i < this->total; i++) {
		base_n = mpz_sizeinbase(this->t, this->bases[i]->base);
		
		this->bases[i]->updateXY(base_n);
	}
}

void Base_Algorithem::scanA() {
	int id, s, l;
	time_t start_time;
	
	s = 0;
	l = 10000;
	start_time = time(0);
	
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
		
		s = mpz_sizeinbase(this->t, 10);
		if(s > l) {
			this->drawTime(time(0) - start_time);
			cout << " - " << s << endl;
			l = s + 10000;
		}

		this->scan3(0);
	}
}

void Base_Algorithem::scanB() {
	int id, s, l;
	time_t start_time;
	mpz_t start, end;
	Base_Range* br;
	
	//Init
	id = this->total - 1;	// Highest base id
	br = this->bases[id];	// Base Range Object
	mpz_init(start);		// Biggest start
	mpz_init(end);			// Smallest end
	
	s = 0;
	l = 10000;
	start_time = time(0);
	
	while(true) {
		br->next();
		
		mpz_set(start, br->new_start);
		mpz_set(end, br->new_end);
		
		// Debug
		s = mpz_sizeinbase(start, 10);
		if(s > l) {
			cout << time(0) - start_time << " " << s << endl;
			l += 10000;
		}
		
		this->scan2(start, end, id - 1);
	}
	
	mpz_clear(start);
	mpz_clear(end);
}

void Base_Algorithem::scan2(mpz_t start, mpz_t end, int id) {
	int i;
	mpz_t new_start, new_end;
	long long start_size, end_size;
	Base_Range* br;
	
	//Init
	mpz_init(new_start);	// new Biggest start
	mpz_init(new_end);		// new Smallest end
	br = this->bases[id];	// Base Range Object
	
	start_size = mpz_sizeinbase(start, br->base) - 2;
	end_size = mpz_sizeinbase(start, br->base) - 1;
	
	for(i = start_size <= 0 ? 0 : start_size; i <= end_size; i++) {
		br->updateXY(i);
		
		if(br->isInRange(start) || br->isInRange(end)) {
			mpz_set(new_start, start);
			mpz_set(new_end, end);
			
			// Update start and end
			if(mpz_cmp(new_start, br->new_start) < 0)
				mpz_set(new_start, br->new_start);
			
			if(mpz_cmp(new_end, br->new_end) > 0)
				mpz_set(new_end, br->new_end);
			
			if(id - 1 >= 0)
				this->scan2(new_start, new_end, id - 1);
			else
				this->scan3(0);
		}
	}
	
	mpz_clear(new_start);
	mpz_clear(new_end);
}

void Base_Algorithem::scan3(int level) {
	int i, id, start, end;
	Base_Range* br;
	Base_Algorithem ba(this->bases[0]->base, this->total);
	
	if(highest_level < level) {
		highest_level = level;
		
		cout << "level = " << level << endl;
	}
	
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
	
	// Patch new generation
	for(i = 0; i < this->total; i++)
		if(i == id)
			*(ba.bases[i]) << *(this->bases[i]);
		else
			*(ba.bases[i]) = *(this->bases[i]);
	
	for(i = start <= 0 ? 0 : start; i <= end; i++) {
		ba.bases[id]->updateXY(i);
	
		if(ba.hasCollision()) {
			if(ba.hasAnswerInStart() || ba.hasAnswerInEnd()) {
				ba.draw();
				//ba.drawSize();
			} else {
				ba.scan3(level + 1);
			}
		}
	}
}

void Base_Algorithem::draw() {
	int i;
	
	for(i = 0; i < this->total; i++)
		this->bases[i]->draw();
	
	cout << "---------------------------------------" << endl;
}

void Base_Algorithem::drawSize() {
	int i;
	
	for(i = 0; i < this->total; i++)
		this->bases[i]->drawSize();
}

void Base_Algorithem::drawBase() {
	int i;
	
	cout << mpz_get_str(nullptr, 10, this->t);
				
	for(i = 0; i < this->total; i++)
		cout << "	" << mpz_get_str(nullptr, this->bases[i]->base, this->t);
	
	cout << "	" << mpz_get_str(nullptr, 11, this->t);
	
	cout << endl;
}

void Base_Algorithem::drawTime(time_t t) {
	int d, h, m, s;
	
	s = t % 60;
	t /= 60;
	m = t % 60;
	t /= 60;
	h = t % 24;
	t /= 24;
	d = t;
	
	cout << d << " days, " << h << " hours, " << m << " min, " << s << " sec"; 
}