#include "BruteForce.h"

BruteForce::BruteForce() {}

int BruteForce::analizaPer(Matrix &a, Matrix &b, GraphNode &c, int droga[], int pozycja[], int wynik[], int y, int &suma, string kryterium, int tmpCzas)
{
	int pom = 0, m, n, czasCalkowity = 0, czas = 0, wezel = 0, limitReturn = 0, limit = 1;	// Zmienne pomocnicze
	if (y < a.r)
	{
		for (int i = y; i < a.r; i++)
		{
			pom = pozycja[y];	// Zamiana wartoœci na pozycjach
			pozycja[y] = pozycja[i];
			pozycja[i] = pom;
			limitReturn = analizaPer(a, b, c, droga, pozycja, wynik, y + 1, suma, kryterium, tmpCzas);	// Wywo³anie rekurencyjne
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
			if (kryterium == "Punkty") {
				if (a.m[m][n] != 0)
					pom += (a.m[m][n] / b.m[m][n]) / 100 + c.m[m];
				else
					pom += 0;
			}
			else
				pom += a.m[m][n];	// Sumowanie wag tymczasowo najlepszej drogi
		}
		if (kryterium == "Punkty")
			pom += (a.m[a.r - 1][0] / b.m[a.r - 1][0]) / 100 + c.m[a.r - 1];
		else
			pom += a.m[droga[a.r - 1]][droga[0]];	// Dodanie ostatniej krawêdzi tymczasowo najlepszej drogi w celu zamkniêcia cyklu Hamiltona
		if (suma > pom)
		{
			suma = pom;	// Zmiana wartoœci referencji najmniejszej sumy wag
			for (int i = 0; i < a.r; i++)
				wynik[i] = droga[i];	// Najlepsza droga znjadzie siê w wynik[]
		}

		limit = 1;
		if (kryterium == "Droga" || kryterium == "Punkty") {
			for (int i = 0; i < a.r - 1; i++) {
				if (czasCalkowity < tmpCzas) {
					czas += b.m[wynik[i]][wynik[i + 1]];
					czas += b.m[wynik[limit - 1]][wynik[0]];
					wezel += c.m[wynik[i]];
					czasCalkowity = czas + wezel * 60;
					limit++;
				}
			}
			czasCalkowity = 0;
			limitReturn = limit;
		}
		else if (kryterium == "Czas") {
			for (int i = 0; i < a.r - 1; i++) {
				if (czasCalkowity < tmpCzas) {
					czas += a.m[wynik[i]][wynik[i + 1]];
					czas += a.m[wynik[limit - 1]][wynik[0]];
					wezel += c.m[wynik[i]];
					czasCalkowity = czas + wezel * 60;
					limit++;
				}
			}
			czasCalkowity = 0;
			limitReturn = limit;
		}
	}

	return limitReturn;
}

int BruteForce::przegladZupelny(Matrix &a, Matrix &b, GraphNode &c, int maxCzas, int miejsce, string kryterium, bool display)
{
	int *sciezka = new int[a.r], suma = 10000000, czas = 0, wezel = 0, czasCalkowity = 0;
	int *pozycja = new int[a.r];
	int *wynik = new int[a.r];
	int tmpCzas = maxCzas * 60, limit = 1, rot = 0, t_miejsce = 0, punkty = 0;

	for (int i = 0; i < a.r; i++)
	{
		wynik[i] = 0;
		sciezka[i] = 0;
		pozycja[i] = i;	// Ka¿dy wierzcho³ek odwiedzony mo¿e byæ tylko raz, co za tym idzie ka¿da pozycja musi mieæ inn¹ wartoœæ
	}

	// Ustawienie miejsca pocz¹tkowego
	for (int i = 0; i < a.r; i++)
	{
		if (pozycja[i] == miejsce)
			rot = i;
	}
	for (int i = 0; i < rot; i++)
	{
		t_miejsce = pozycja[0];
		for (int j = 0; j < a.r; j++)
			pozycja[j] = pozycja[j + 1];
		pozycja[a.r - 1] = t_miejsce;
	}

	limit = analizaPer(a, b, c, sciezka, pozycja, wynik, 1, suma, kryterium, tmpCzas);	// Mywo³anie metody rekurencyjnej

	if (kryterium == "Droga" || kryterium == "Punkty") {
		suma = droga(a, wynik, limit);
		czas = droga(b, wynik, limit);
	}
	else if (kryterium == "Czas") {
		suma = droga(b, wynik, limit);
		czas = droga(a, wynik, limit);
	}

	wezel = drogaTab(c, wynik, limit - 1);
	czasCalkowity = czas + wezel * 60;
	punkty = wartoscWszystkichWierzcholkow(a, b, c, wynik, kryterium, limit);

	// Wyœwietlenie wyników
	if (display) {
		system("CLS");
		cout << "Przegl¹d zupe³ny zakoñczy³ dzialanie..." << endl;
		cout << endl << "Wyniki:" << endl << endl;
		cout << "Najkrótsza droga: " << endl << "\t";
		for (int i = 0; i < limit; i++)
			cout << wynik[i] << " -> ";
		cout << wynik[0] << " ...";
		cout << endl << endl << "Czas trwania wycieczki: " << maxCzas << " [h] = " << tmpCzas << " [min] | Bufor: +/- 4 [h]";
		cout << endl << "Odwiedzonych zostanie " << limit << " miast." << endl << "Dominuj¹ce kryterium: " << kryterium;
		if (kryterium == "Droga") {
			cout << endl << "Ca³kowita odleg³oœæ: " << suma << " [m]" << endl;
			cout << endl << "Ca³kowity czas podró¿y miêdzy miastami: " << czas << " [min]";
			cout << endl << "Ca³kowity czas podró¿y spêdzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca³kowity czas podró¿y + powrót: " << czasCalkowity << " [min]";
			cout << endl << "Wartoœæ œcie¿ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Czas") {
			cout << endl << "Ca³kowity czas podró¿y miêdzy miastami w minutach: " << czas << " [min]" << endl;
			cout << endl << "Ca³kowita odleg³oœæ w metrach: " << suma << " [m]";
			cout << endl << "Ca³kowity czas podró¿y spêdzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca³kowity czas podró¿y + powrót: " << czasCalkowity << " [min]";
			cout << endl << "Wartoœæ œcie¿ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Punkty") {
			cout << endl << "Wartoœæ œcie¿ki w punktach: " << punkty << endl;
			cout << endl << "Ca³kowita odleg³oœæ: " << suma << " [m]";
			cout << endl << "Ca³kowity czas podró¿y miêdzy miastami: " << czas << " [min]";
			cout << endl << "Ca³kowity czas podró¿y spêdzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca³kowity czas podró¿y + powrót: " << czasCalkowity << " [min]" << endl << endl;
		}
		system("pause");
	}

	delete[] sciezka;
	delete[] pozycja;
	delete[] wynik;

	if (kryterium == "Droga")
		return suma;
	else if (kryterium == "Czas")
		return czas;
	else if (kryterium == "Punkty")
		return punkty;
	else
		return 0;
}

BruteForce::~BruteForce() {}
