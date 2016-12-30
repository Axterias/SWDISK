#pragma once

#include "stdafx.h"
#include "GraphNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class Matrix
{
public:
	// r - rozmiar macierzy s¹siedztwa
	int r;
	// Ca³kowita zmienna przechowuj¹ca macierz
	int **m;
	// Konstruktor bezparametrowy
	Matrix() : r(0) {};
	// Konstruktor bezargumentowy
	Matrix(int **m) {};

	// Konstruktor inicjuj¹cy tablice wskaŸników na tablice
	Matrix(int rozmiar)
	{
		this->r = rozmiar;
		m = new int*[r];
		for (int i = 0; i < r; i++)
			m[i] = new int[r];
	}

	// Konstruktor kopiuj¹cy
	Matrix(const Matrix &x)
	{
		this->r = x.r;
		m = new int*[r];
		for (int i = 0; i < r; i++)
			m[i] = new int[r];
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < r; j++)
				m[i][j] = x.m[i][j];
		}
	}

	// Odczytuje dane z pliku
	bool odczyt(Matrix &a, bool czas);

	// Uzupe³nienie macierzy s¹siedztwa losowymi danymi
	bool uzupelnienie(Matrix &a, int iloscMiast, bool sym, bool czas, bool display);

	// Uzupe³nienie macierzy danymi z klawiatury
	bool uzupelnienieReczne(Matrix &a, int iloscMiast, bool  sym, bool czas);

	// Usuwanie macierzy
	void usuwanie(Matrix &a);

	// Przeci¹¿ony, zaprzyjaŸniony operator << (wyswietla dane)
	friend ostream& operator<<(ostream &wy, Matrix &y);

	// Obliczanie ca³kowitej drogi, któr¹ komiwoja¿er musi przebyæ
	int droga(Matrix &a, int *tab, int limit);

	// Obliczanie punktacji drogi, któr¹ komiwoja¿er musi przebyæ
	int drogaPunkty(Matrix &a, Matrix &b, GraphNode &c, int *tab, int limit, string kryterium);

	// Obliczanie czasu spêdzonego w wierzcho³ku grafu
	int drogaTab(GraphNode &a, int *tab, int limit);

	// Obliczanie wartoœci wszystkich wierzcho³ków
	int wartoscWszystkichWierzcholkow(Matrix &a, Matrix &b, GraphNode &c, int *tab, string kryterium, int limit);

	// Bezparametrowy, bezargumentowy destruktor
	~Matrix();
};
