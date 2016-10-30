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

class Macierz
{
public:
	// r - rozmiar macierzy s¹siedztwa
	int r;
	// Ca³kowita zmienna przechowuj¹ca macierz
	int **m;
	// Konstruktor bezparametrowy
	Macierz() : r(0) {};
	// Konstruktor bezargumentowy
	Macierz(int **m) {};
	// Konstruktor inicjuj¹cy tablice wskaŸników na tablice
	Macierz(int rozmiar)
	{
		this->r = rozmiar;
		m = new int*[r];
		for (int i = 0; i < r; i++)
			m[i] = new int[r];
	}
	// Konstruktor kopiuj¹cy
	Macierz(const Macierz &x)
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
	// Algorytm symulowanego wy¿arzania
	int algorytmWyzarzania(Macierz &a, float Tp, float Tk, bool display);
	// Algorytm genetyczny
	int algorytmGenetyczny(Macierz &a, int population, int generations, float mutation, int parentsPopulation, int childernPopulation, int swaps, float cross, bool display);
	// Metoda aktualizuj¹ca œcie¿kê komiwoja¿era i sumuj¹ca populacjê
	int sumowaniePopulacji(Macierz &a, int *populus, int *route);
	// Losowanie liczby z przedzia³u od 0 do 1;
	float los(void);
	// Zamiana s¹siedznich pozycji
	void zamiana(int *tab, int x, int y);
	// Obliczanie ca³kowitej drogi, która komiwoja¿er musi przebyæ
	int droga(Macierz &a, int *tab);
	// Losowa permutacja tablicy pozycji macierzy S
	void losowaPermutacja(Macierz &a, int *sciezka);
	// Obni¿anie temperatury wed³ug schematu logarytmicznego
	float schladzanie(int k, float Tp);
	// Obliczanie wartoœci funkcji prawdopodobnieñstwa P
	float prawdopodobienstwo(int s1, int s2, float T);
	// Odczytuje dane z pliku
	bool odczyt(Macierz &a);
	// Uzupelnienie macierzy s¹siedztwa losowymi danymi
	bool uzupelnienie(Macierz &a, int iloscMiast, bool sym, bool display = true);
	// Uzupelnienie macierzy danymi z klawiatury
	bool uzupelnienieReczne(Macierz &a, bool  sym);
	// Usuwanie macierzy
	void usuwanie(Macierz &a);
	// Przeci¹¿ony, zaprzyjaŸniony operator << (wyswietla dane)
	friend ostream& operator<<(ostream &wy, Macierz &y);
	// Bezparametrowy, bezargumentowy destruktor
	~Macierz() {};
};