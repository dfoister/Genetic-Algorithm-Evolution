#ifndef MATINGPAIR_H
#define MATINGPAIR_H

#include <vector>
#include "Bodies/Organism.h"
#include "Constants.h"

class matingPair {
private:
	Organism* a_;
	Organism* b_;
public:
	matingPair(Organism* a, Organism* b) {
		a_ = a;
		b_ = b;
	};

	~matingPair() {

	};

	Organism* getParentA() const {
		return a_;
	};

	Organism* getParentB() const {
		return b_;
	};
};
#endif