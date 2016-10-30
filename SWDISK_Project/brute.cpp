#include "brute.h"

brute::brute() {}

void brute::analizaPer(Macierz & a, int droga[], int pozycja[], int wynik[], int y, int & suma)
{
	int pom = 0, m, n;	// Zmienne pomocnicze
	if (y < a.r)
	{
		for (int i = y; i < a.r; i++)
		{
			pom = pozycja[y];	// Zamiana warto�ci na pozycjach
			pozycja[y] = pozycja[i];
			pozycja[i] = pom;
			analizaPer(a, droga, pozycja, wynik, y + 1, suma);	// Wywo�anie rekurencyjne
			pom = pozycja[y];	// Przywr�cenie stanu wyj�ciowego po powrocie z rekurencji
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
			m = droga[i];	// Pierwsza wsp�rz�dna pozycji w macierzy
			if (i == a.r - 1)	// Na wypadek przekroczenia rozmiaru tablicy
				n = 0;
			else
				n = droga[i + 1];	// Druga wsp�rz�dna pozycji w macierzy
			pom += a.m[m][n];	// Sumowanie wag	tymczasowo najlepszej drogi
		}
		pom += a.m[droga[a.r - 1]][droga[0]];	// Dodanie ostatniej kraw�dzi tymczasowo najlepszej drogi w celu zamkni�cia cyklu Hamiltona
		if (suma > pom)
		{
			suma = pom;	// Zmiana warto�ci referencji najmniejszej sumy wag
			for (int i = 0; i < a.r; i++)
				wynik[i] = droga[i];	// Najlepsza droga znjadzie si� w wynik[]
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
		pozycja[i] = i;	// Ka�dy wierzcho�ek odwiedzony mo�e by� tylko raz, co za tym idzie ka�da pozycja musi mie� inn� warto��
	}
	analizaPer(a, droga, pozycja, wynik, 0, suma);	// Mywo�anie metody rekurencyjnej

	// Wy�wietlenie wynik�w
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
