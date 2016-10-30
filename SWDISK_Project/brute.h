#pragma once

#include "Macierz.h"

class brute {

public:
	brute();

	// Metoda tworz¹ca wszystkie mo¿liwe permutacje i zapisuj¹ca najkorzystniejsz¹ drogê wraz z sum¹ wag
	void analizaPer(Macierz &a, int droga[], int pozycja[], int wynik[], int y, int &suma);

	// Algorytm przegl¹du zupe³nego
	int przegladZupelny(Macierz &a, bool display);

	~brute();
};