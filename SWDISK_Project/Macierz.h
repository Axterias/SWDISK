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
	// r - rozmiar macierzy s�siedztwa
	int r;
	// Ca�kowita zmienna przechowuj�ca macierz
	int **m;
	// Konstruktor bezparametrowy
	Macierz() : r(0) {};
	// Konstruktor bezargumentowy
	Macierz(int **m) {};
	// Konstruktor inicjuj�cy tablice wska�nik�w na tablice
	Macierz(int rozmiar)
	{
		this->r = rozmiar;
		m = new int*[r];
		for (int i = 0; i < r; i++)
			m[i] = new int[r];
	}
	// Konstruktor kopiuj�cy
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
	// Algorytm symulowanego wy�arzania
	int algorytmWyzarzania(Macierz &a, float Tp, float Tk, bool display);
	// Algorytm genetyczny
	int algorytmGenetyczny(Macierz &a, int population, int generations, float mutation, int parentsPopulation, int childernPopulation, int swaps, float cross, bool display);
	// Metoda aktualizuj�ca �cie�k� komiwoja�era i sumuj�ca populacj�
	int sumowaniePopulacji(Macierz &a, int *populus, int *route);
	// Losowanie liczby z przedzia�u od 0 do 1;
	float los(void);
	// Zamiana s�siedznich pozycji
	void zamiana(int *tab, int x, int y);
	// Obliczanie ca�kowitej drogi, kt�ra komiwoja�er musi przeby�
	int droga(Macierz &a, int *tab);
	// Losowa permutacja tablicy pozycji macierzy S
	void losowaPermutacja(Macierz &a, int *sciezka);
	// Obni�anie temperatury wed�ug schematu logarytmicznego
	float schladzanie(int k, float Tp);
	// Obliczanie warto�ci funkcji prawdopodobnie�stwa P
	float prawdopodobienstwo(int s1, int s2, float T);
	// Odczytuje dane z pliku
	bool odczyt(Macierz &a);
	// Uzupelnienie macierzy s�siedztwa losowymi danymi
	bool uzupelnienie(Macierz &a, int iloscMiast, bool sym, bool display = true);
	// Uzupelnienie macierzy danymi z klawiatury
	bool uzupelnienieReczne(Macierz &a, bool  sym);
	// Usuwanie macierzy
	void usuwanie(Macierz &a);
	// Przeci��ony, zaprzyja�niony operator << (wyswietla dane)
	friend ostream& operator<<(ostream &wy, Macierz &y);
	// Bezparametrowy, bezargumentowy destruktor
	~Macierz() {};
};