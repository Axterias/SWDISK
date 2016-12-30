#pragma once

#include "Matrix.h"

class SimulatedAnnealing : Matrix {

public:
	SimulatedAnnealing();

	// Algorytm symulowanego wy�arzania
	int algorytmWyzarzania(Matrix &a, Matrix &b, GraphNode &c, float Tp, float Tk, int maxCzas, int miejsce, string kryterium, bool display);

	// Losowanie liczby z przedzia�u od 0 do 1;
	float los(void);

	// Zamiana s�siedznich pozycji
	void zamiana(int *tab, int x, int y);

	// Losowa permutacja tablicy pozycji macierzy S
	void losowaPermutacja(Matrix &a, int *sciezka);

	// Obni�anie temperatury wed�ug schematu logarytmicznego
	float schladzanie(int k, float Tp);

	// Obliczanie warto�ci funkcji prawdopodobnie�stwa P
	float prawdopodobienstwo(int s1, int s2, float T);

	~SimulatedAnnealing();
};
