#pragma once

#include "Macierz.h"

class randomSearch {

public:
	randomSearch();

	// Metoda generuj¹ca losowy wynik
	int losowyWynik(Macierz &a, int it, bool display);

	// Obliczanie ca³kowitej drogi, która komiwoja¿er musi przebyæ
	int droga(Macierz &a, int *tab);

	~randomSearch();
};