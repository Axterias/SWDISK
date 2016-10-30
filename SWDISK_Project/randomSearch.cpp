#include "randomSearch.h"

randomSearch::randomSearch() {}

int randomSearch::losowyWynik(Macierz & a, int it, bool display)
{
	int *wynik = new int[a.r], pozycja1 = 0, pozycja2 = 0, wartosc = 0, suma = 0;;

	srand((unsigned)time(NULL));	// Ziarno losowoœci

	for (int i = 0; i < a.r; i++)
		wynik[i] = i;
	for (int i = 0; i < it; i++)
	{
		pozycja1 = rand() % a.r;
		wartosc = wynik[pozycja1];
		pozycja2 = rand() % a.r;
		wynik[pozycja1] = wynik[pozycja2];
		wynik[pozycja2] = wartosc;
	}
	suma = droga(a, wynik);

	// Wyœwietlenie wyników
	if (display) {
		system("CLS");
		cout << "Algorytm random search zakonczyl dzialanie..." << endl;
		cout << endl << "Wyniki:" << endl << endl;
		cout << "Najkrotsza droga (cykl Hamilotna): " << endl << "\t";
		for (int i = 0; i < a.r; i++)
			cout << wynik[i] << " -> ";
		cout << wynik[0] << " ...";
		cout << endl << "Suma wag najkrotszej drogi wynosi: " << suma << endl << endl;
		system("pause");
	}

	delete[] wynik;

	return suma;
}

int randomSearch::droga(Macierz &a, int *tab)
{
	int wynik = 0;
	for (int i = 0; i < a.r - 1; i++)
		wynik += a.m[tab[i]][tab[i + 1]];
	wynik += a.m[tab[a.r - 1]][tab[0]];
	return wynik;
}

randomSearch::~randomSearch() {}
