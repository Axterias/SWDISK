#pragma once

#include "Macierz.h"

class randomSearch {

public:
	randomSearch();

	// Metoda generuj�ca losowy wynik
	int losowyWynik(Macierz &a, int it, bool display);

	// Obliczanie ca�kowitej drogi, kt�ra komiwoja�er musi przeby�
	int droga(Macierz &a, int *tab);

	~randomSearch();
};