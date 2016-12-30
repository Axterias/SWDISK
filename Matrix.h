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
	// r - rozmiar macierzy s�siedztwa
	int r;
	// Ca�kowita zmienna przechowuj�ca macierz
	int **m;
	// Konstruktor bezparametrowy
	Matrix() : r(0) {};
	// Konstruktor bezargumentowy
	Matrix(int **m) {};

	// Konstruktor inicjuj�cy tablice wska�nik�w na tablice
	Matrix(int rozmiar)
	{
		this->r = rozmiar;
		m = new int*[r];
		for (int i = 0; i < r; i++)
			m[i] = new int[r];
	}

	// Konstruktor kopiuj�cy
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

	// Uzupe�nienie macierzy s�siedztwa losowymi danymi
	bool uzupelnienie(Matrix &a, int iloscMiast, bool sym, bool czas, bool display);

	// Uzupe�nienie macierzy danymi z klawiatury
	bool uzupelnienieReczne(Matrix &a, int iloscMiast, bool  sym, bool czas);

	// Usuwanie macierzy
	void usuwanie(Matrix &a);

	// Przeci��ony, zaprzyja�niony operator << (wyswietla dane)
	friend ostream& operator<<(ostream &wy, Matrix &y);

	// Obliczanie ca�kowitej drogi, kt�r� komiwoja�er musi przeby�
	int droga(Matrix &a, int *tab, int limit);

	// Obliczanie punktacji drogi, kt�r� komiwoja�er musi przeby�
	int drogaPunkty(Matrix &a, Matrix &b, GraphNode &c, int *tab, int limit, string kryterium);

	// Obliczanie czasu sp�dzonego w wierzcho�ku grafu
	int drogaTab(GraphNode &a, int *tab, int limit);

	// Obliczanie warto�ci wszystkich wierzcho�k�w
	int wartoscWszystkichWierzcholkow(Matrix &a, Matrix &b, GraphNode &c, int *tab, string kryterium, int limit);

	// Bezparametrowy, bezargumentowy destruktor
	~Matrix();
};
