#include "RandomSearch.h"

RandomSearch::RandomSearch() {}

int RandomSearch::losowyWynik(Matrix &a, Matrix &b, GraphNode &c, int it, int maxCzas, int miejsce, string kryterium, bool display)
{
	int *wynik = new int[a.r], pozycja1 = 0, pozycja2 = 0, wartosc = 0, suma = 0, czas = 0, wezel = 0, czasCalkowity = 0;
	int tmpCzas = maxCzas * 60, limit = 1, rot = 0, t_miejsce = 0, punkty = 0;

	srand((unsigned)time(NULL));	// Ziarno losowo�ci

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

	// Ustawienie miejsca pocz�tkowego
	for (int i = 0; i < a.r; i++)
	{
		if (wynik[i] == miejsce)
			rot = i;
	}
	for (int i = 0; i < rot; i++)
	{
		t_miejsce = wynik[0];
		for (int j = 0; j < a.r; j++)
			wynik[j] = wynik[j + 1];
		wynik[a.r - 1] = t_miejsce;
	}

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
	}

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
		cout << "Algorytm random search zako�czy� dzia�anie..." << endl;
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

RandomSearch::~RandomSearch() {}
