#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class GraphNode {

public:
	// Rozmiar tablicy
	int r;
	// Ca³kowita zmienna przechowuj¹ca tablicê
	int *m;
	// Konstruktor bezparametrowy
	GraphNode() : r(0) {};
	// Konstruktor bezargumentowy
	GraphNode(int *m) {};

	// Konstruktor inicjuj¹cy tablicê
	GraphNode(int rozmiar)
	{
		this->r = rozmiar;
		m = new int[r];
	}

	// Konstruktor kopiuj¹cy
	GraphNode(const GraphNode &x)
	{
		this->r = x.r;
		m = new int[r];
		for (int i = 0; i < r; i++)
		{
			m[i] = x.m[i];
		}
	}

	// Odczytuje dane z pliku
	bool odczyt(GraphNode &a);

	// Uzupelnienie macierzy s¹siedztwa losowymi danymi
	bool uzupelnienie(GraphNode &a, int iloscMiast, bool display);

	// Uzupelnienie macierzy danymi z klawiatury
	bool uzupelnienieReczne(GraphNode &a, int iloscMiast);

	// Usuwanie macierzy
	void usuwanie(GraphNode &a);

	// Przeci¹¿ony, zaprzyjaŸniony operator << (wyswietla dane)
	friend ostream& operator<<(ostream &wy, GraphNode &y);

	~GraphNode();
};
