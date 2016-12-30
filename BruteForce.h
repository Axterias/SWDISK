#pragma once

#include "Matrix.h"

class BruteForce : Matrix {

public:
	BruteForce();

	// Metoda tworz�ca wszystkie mo�liwe permutacje i zapisuj�ca najkorzystniejsz� drog� wraz z sum� wag
	int analizaPer(Matrix &a, Matrix &b, GraphNode &c, int droga[], int pozycja[], int wynik[], int y, int &suma, string kryterium, int tmpCzas);

	// Algorytm przegl�du zupe�nego
	int przegladZupelny(Matrix &a, Matrix &b, GraphNode &c, int maxCzas, int miejsce, string kryterium, bool display);

	~BruteForce();
};
