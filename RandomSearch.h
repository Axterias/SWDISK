#pragma once

#include "Matrix.h"

class RandomSearch : Matrix {

public:
	RandomSearch();

	// Metoda generuj�ca losowy wynik
	int losowyWynik(Matrix &a, Matrix &b, GraphNode &c, int it, int maxCzas, int miejsce, string kryterium, bool display);

	~RandomSearch();
};
