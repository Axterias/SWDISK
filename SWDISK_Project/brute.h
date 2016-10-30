#pragma once

#include "Macierz.h"

class brute {

public:
	brute();

	// Metoda tworz�ca wszystkie mo�liwe permutacje i zapisuj�ca najkorzystniejsz� drog� wraz z sum� wag
	void analizaPer(Macierz &a, int droga[], int pozycja[], int wynik[], int y, int &suma);

	// Algorytm przegl�du zupe�nego
	int przegladZupelny(Macierz &a, bool display);

	~brute();
};