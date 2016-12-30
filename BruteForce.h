#pragma once

#include "Matrix.h"

class BruteForce : Matrix {

public:
	BruteForce();

	// Metoda tworz¹ca wszystkie mo¿liwe permutacje i zapisuj¹ca najkorzystniejsz¹ drogê wraz z sum¹ wag
	int analizaPer(Matrix &a, Matrix &b, GraphNode &c, int droga[], int pozycja[], int wynik[], int y, int &suma, string kryterium, int tmpCzas);

	// Algorytm przegl¹du zupe³nego
	int przegladZupelny(Matrix &a, Matrix &b, GraphNode &c, int maxCzas, int miejsce, string kryterium, bool display);

	~BruteForce();
};
