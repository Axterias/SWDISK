#pragma once

#include "Matrix.h"

class RandomSearch : Matrix {

public:
	RandomSearch();

	// Metoda generująca losowy wynik
	int losowyWynik(Matrix &a, Matrix &b, GraphNode &c, int it, int maxCzas, int miejsce, string kryterium, bool display);

	~RandomSearch();
};
