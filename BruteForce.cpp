#include "BruteForce.h"

BruteForce::BruteForce() {}

int BruteForce::analizaPer(Matrix &a, Matrix &b, GraphNode &c, int droga[], int pozycja[], int wynik[], int y, int &suma, string kryterium, int tmpCzas)
{
	int pom = 0, m, n, czasCalkowity = 0, czas = 0, wezel = 0, limitReturn = 0, limit = 1;	// Zmienne pomocnicze
	if (y < a.r)
	{
		for (int i = y; i < a.r; i++)
		{
			pom = pozycja[y];	// Zamiana warto�ci na pozycjach
			pozycja[y] = pozycja[i];
			pozycja[i] = pom;
			limitReturn = analizaPer(a, b, c, droga, pozycja, wynik, y + 1, suma, kryterium, tmpCzas);	// Wywo�anie rekurencyjne
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
			pom += a.m[droga[a.r - 1]][droga[0]];	// Dodanie ostatniej kraw�dzi tymczasowo najlepszej drogi w celu zamkni�cia cyklu Hamiltona
		if (suma > pom)
		{
			suma = pom;	// Zmiana warto�ci referencji najmniejszej sumy wag
			for (int i = 0; i < a.r; i++)
				wynik[i] = droga[i];	// Najlepsza droga znjadzie si� w wynik[]
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
		pozycja[i] = i;	// Ka�dy wierzcho�ek odwiedzony mo�e by� tylko raz, co za tym idzie ka�da pozycja musi mie� inn� warto��
	}

	// Ustawienie miejsca pocz�tkowego
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

	limit = analizaPer(a, b, c, sciezka, pozycja, wynik, 1, suma, kryterium, tmpCzas);	// Mywo�anie metody rekurencyjnej

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

	// Wy�wietlenie wynik�w
	if (display) {
		system("CLS");
		cout << "Przegl�d zupe�ny zako�czy� dzialanie..." << endl;
		cout << endl << "Wyniki:" << endl << endl;
		cout << "Najkr�tsza droga: " << endl << "\t";
		for (int i = 0; i < limit; i++)
			cout << wynik[i] << " -> ";
		cout << wynik[0] << " ...";
		cout << endl << endl << "Czas trwania wycieczki: " << maxCzas << " [h] = " << tmpCzas << " [min] | Bufor: +/- 4 [h]";
		cout << endl << "Odwiedzonych zostanie " << limit << " miast." << endl << "Dominuj�ce kryterium: " << kryterium;
		if (kryterium == "Droga") {
			cout << endl << "Ca�kowita odleg�o��: " << suma << " [m]" << endl;
			cout << endl << "Ca�kowity czas podr�y mi�dzy miastami: " << czas << " [min]";
			cout << endl << "Ca�kowity czas podr�y sp�dzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca�kowity czas podr�y + powr�t: " << czasCalkowity << " [min]";
			cout << endl << "Warto�� �cie�ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Czas") {
			cout << endl << "Ca�kowity czas podr�y mi�dzy miastami w minutach: " << czas << " [min]" << endl;
			cout << endl << "Ca�kowita odleg�o�� w metrach: " << suma << " [m]";
			cout << endl << "Ca�kowity czas podr�y sp�dzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca�kowity czas podr�y + powr�t: " << czasCalkowity << " [min]";
			cout << endl << "Warto�� �cie�ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Punkty") {
			cout << endl << "Warto�� �cie�ki w punktach: " << punkty << endl;
			cout << endl << "Ca�kowita odleg�o��: " << suma << " [m]";
			cout << endl << "Ca�kowity czas podr�y mi�dzy miastami: " << czas << " [min]";
			cout << endl << "Ca�kowity czas podr�y sp�dzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca�kowity czas podr�y + powr�t: " << czasCalkowity << " [min]" << endl << endl;
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
