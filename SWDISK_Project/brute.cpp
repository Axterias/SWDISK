#include "brute.h"

brute::brute() {}

void brute::analizaPer(Macierz & a, int droga[], int pozycja[], int wynik[], int y, int & suma)
{
	int pom = 0, m, n;	// Zmienne pomocnicze
	if (y < a.r)
	{
		for (int i = y; i < a.r; i++)
		{
			pom = pozycja[y];	// Zamiana wartoœci na pozycjach
			pozycja[y] = pozycja[i];
			pozycja[i] = pom;
			analizaPer(a, droga, pozycja, wynik, y + 1, suma);	// Wywo³anie rekurencyjne
			pom = pozycja[y];	// Przywrócenie stanu wyjœciowego po powrocie z rekurencji
			pozycja[y] = pozycja[i];
			pozycja[i] = pom;
		}
	}
	else
	{
		for (int i = 0; i < a.r; i++)
		{
			droga[i] = pozycja[i];	// Skopiowanie tymczasowo najlepszej drogi
		}
		pom = 0;
		for (int i = 0; i < a.r; i++)
		{
			m = droga[i];	// Pierwsza wspó³rzêdna pozycji w macierzy
			if (i == a.r - 1)	// Na wypadek przekroczenia rozmiaru tablicy
				n = 0;
			else
				n = droga[i + 1];	// Druga wspó³rzêdna pozycji w macierzy
			pom += a.m[m][n];	// Sumowanie wag	tymczasowo najlepszej drogi
		}
		pom += a.m[droga[a.r - 1]][droga[0]];	// Dodanie ostatniej krawêdzi tymczasowo najlepszej drogi w celu zamkniêcia cyklu Hamiltona
		if (suma > pom)
		{
			suma = pom;	// Zmiana wartoœci referencji najmniejszej sumy wag
			for (int i = 0; i < a.r; i++)
				wynik[i] = droga[i];	// Najlepsza droga znjadzie siê w wynik[]
		}
	}
}

int brute::przegladZupelny(Macierz & a, bool display)
{
	int *droga = new int[a.r], suma = 1000000;
	int *pozycja = new int[a.r];
	int *wynik = new int[a.r];
	for (int i = 0; i < a.r; i++)
	{
		wynik[i] = 0;
		droga[i] = 0;
		pozycja[i] = i;	// Ka¿dy wierzcho³ek odwiedzony mo¿e byæ tylko raz, co za tym idzie ka¿da pozycja musi mieæ inn¹ wartoœæ
	}
	analizaPer(a, droga, pozycja, wynik, 0, suma);	// Mywo³anie metody rekurencyjnej

	// Wyœwietlenie wyników
	if (display) {
		system("CLS");
		cout << "Przeglad zupelny zakonczyl dzialanie..." << endl;
		cout << endl << "Wyniki:" << endl << endl;
		cout << "Najkrotsza droga (cykl Hamilotna): " << endl << "\t";
		for (int i = 0; i < a.r; i++)
			cout << wynik[i] << " -> ";
		cout << wynik[0] << " ...";
		cout << endl << "Suma wag najkrotszej drogi wynosi: " << suma << endl << endl;
		system("pause");
	}

	delete[] droga;
	delete[] pozycja;
	delete[] wynik;

	return suma;
}

brute::~brute() {}
