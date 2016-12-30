#pragma once

#include "Matrix.h"

class Genetic : Matrix {

public:
	Genetic();

	// Algorytm genetyczny
	int algorytmGenetyczny(Matrix &a, Matrix &b, GraphNode &c, int population, int generations, float mutation, int parentsPopulation, int childernPopulation, int swaps, float cross, int maxCzas, int miejsce, string kryterium, bool display);

	// Metoda aktualizuj¹ca œcie¿kê komiwoja¿era i sumuj¹ca populacjê
	int sumowaniePopulacji(Matrix &a, Matrix &b, GraphNode &c, int *populus, int *route, int miejsce, string kryterium);

	// Losowa permutacja tablicy pozycji macierzy S
	void losowaPermutacja(Matrix &a, int *sciezka);

	// Losowanie liczby z przedzia³u od 0 do 1;
	float los(void);

	// Zamiana s¹siedznich pozycji
	void zamiana(int *tab, int x, int y);

	~Genetic();
};
