#pragma once

#include "Matrix.h"

class Genetic : Matrix {

public:
	Genetic();

	// Algorytm genetyczny
	int algorytmGenetyczny(Matrix &a, Matrix &b, GraphNode &c, int population, int generations, float mutation, int parentsPopulation, int childernPopulation, int swaps, float cross, int maxCzas, int miejsce, string kryterium, bool display);

	// Metoda aktualizuj�ca �cie�k� komiwoja�era i sumuj�ca populacj�
	int sumowaniePopulacji(Matrix &a, Matrix &b, GraphNode &c, int *populus, int *route, int miejsce, string kryterium);

	// Losowa permutacja tablicy pozycji macierzy S
	void losowaPermutacja(Matrix &a, int *sciezka);

	// Losowanie liczby z przedzia�u od 0 do 1;
	float los(void);

	// Zamiana s�siedznich pozycji
	void zamiana(int *tab, int x, int y);

	~Genetic();
};
