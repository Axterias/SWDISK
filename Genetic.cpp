#include "Genetic.h"

Genetic::Genetic() {};

int Genetic::algorytmGenetyczny(Matrix &a, Matrix &b, GraphNode &c, int population, int generations, float mutation, int parentsPopulation, int childernPopulation, int swaps, float cross, int maxCzas, int miejsce, string kryterium, bool display)
{
	// Zmienne pomocnicze w obliczeniach
	int temp = 0, tempCP1 = 0, tempCP2 = 0;
	long long tempLong = 0, tempCValue = 0, tempLValue = 0, tempPSum = 0;
	int tmpCzas = maxCzas * 60, limit = 1, czasCalkowity = 0, punkty = 0;

	// Tablice pomocnicze w obliczeniach
	int *tmp, *tmpP1, *tmpP2, *tmpC1, *tmpC2, *tmpV, czas = 0, wezel = 0;

	// Œcie¿ka komiwoja¿era
	int *route = new int[a.r];
	for (int i = 0; i < a.r; i++)
		route[i] = 0;

	// Najlepsza œcie¿ka komiwoja¿era
	int *final_route = new int[a.r];
	for (int i = 0; i < a.r; i++)
		final_route[i] = 0;

	// Zmienna przechowuj¹ca wynik koñcowy
	int result = INT_MAX;

	// Wektor populacji
	vector<int*>* pop = new vector<int*>();
	pop->reserve(population);
	// Wektor nowej, tymczasowej populacji
	vector<int*>* newPop;
	// Wektor rodziców
	vector<int*>* par = new vector<int*>();
	par->reserve(parentsPopulation);
	// Wektor potomków
	vector<int*>* chi = new vector<int*>();
	chi->reserve(childernPopulation * 2);

	// Losowanie pocz¹tkowej permutacji
	for (int i = 0; i < population; ++i)
	{
		tmp = new int[a.r];
		losowaPermutacja(a, tmp);
		pop->push_back(tmp);
	}

	// Pêtla iteracyjna pokoleñ
	for (int i = 0; i < generations; ++i)
	{
		par->clear();
		tempCValue = 0;
		tempLValue = 0;
		tempPSum = 0;
		tmpV = new int[population];
		for (int i = 0; i < population; i++)
		{
			tmpV[i] = sumowaniePopulacji(a, b, c, pop->at(i), route, miejsce, kryterium);
			tempPSum += tmpV[i];
		}
		for (int i = 0; i < parentsPopulation; i++)
		{
			tempCValue = 0;
			tempLValue = 0;
			tempLong = (long long)los() * tempPSum;
			for (int i = 0; i < population; i++)
			{
				tempCValue += tmpV[i];
				if (tempLValue <= tempLong && tempLong <= tempCValue)
				{
					par->push_back(pop->at(i));
					break;
				}
				tempLValue += tmpV[i];
			}
		}
		delete[] tmpV;

		// Prawdopodobieñstwo zajœcia krzy¿owania
		if (los() < cross)
		{
			// Krzy¿owanie
			for (int i = 0; i < childernPopulation; i++)
			{
				tmpP1 = par->at(rand() % parentsPopulation);
				tmpP2 = par->at(rand() % parentsPopulation);
				tmpC1 = new int[a.r];
				tmpC2 = new int[a.r];
				for (int i = 0; i < a.r; i++)
				{
					tmpC1[i] = tmpP1[i];
					tmpC2[i] = tmpP2[i];
				}

				// Losowanie pozycji krzy¿owania
				tempCP1 = rand() % a.r;
				tempCP2 = rand() % a.r;

				// Zamiana pozycji w procesie krzy¿owania
				if (tempCP1 > tempCP2)
				{
					temp = tempCP2;
					tempCP2 = tempCP1;
					tempCP1 = temp;
				}
				for (int i = tempCP1; i <= tempCP2; ++i)
				{
					temp = tmpC1[i];
					tmpC1[i] = tmpC2[i];
					tmpC2[i] = temp;
				}
				for (int i = tempCP1; i <= tempCP2; ++i)
				{
					for (int j = 0; j < tempCP1; j++)
					{
						if (tmpC1[j] == tmpC1[i])
							tmpC1[j] = tmpC2[i];
						if (tmpC2[j] == tmpC2[i])
							tmpC2[j] = tmpC1[i];
					}
				}

				// Sprawdzenie, czy ulegnie mutacji
				if (los() < mutation && a.r > 1)
				{
					for (int i = 0; i < swaps; ++i)
						zamiana(tmpC1, rand() % a.r, rand() % a.r);
				}
				if (los() < mutation && a.r > 1)
				{
					for (int i = 0; i < swaps; ++i)
						zamiana(tmpC2, rand() % a.r, rand() % a.r);
				}
				chi->push_back(tmpC1);
				chi->push_back(tmpC2);
			}
		}
		newPop = new vector<int*>();
		newPop->reserve(population);

		// Sortowanie populacji i potomków
		sort(pop->begin(), pop->end());
		sort(chi->begin(), chi->end());
		for (int i = 0; i < population; i++)
		{
			// Gdy wektory pop i chi s¹ puste
			if (chi->empty() && !pop->empty())
			{
				newPop->push_back(pop->back());
				pop->pop_back();
				continue;
			}
			if (!chi->empty() && pop->empty())
			{
				newPop->push_back(chi->back());
				chi->pop_back();
				continue;
			}

			// Wybór obiecuj¹cej drogi rozwoju
			if (pop->back() > chi->back())
			{
				newPop->push_back(pop->back());
				pop->pop_back();
			}
			else
			{
				newPop->push_back(chi->back());
				chi->pop_back();
			}
		}

		// Czyszczenie wektorów
		while (!pop->empty())
		{
			delete[] pop->back();
			pop->pop_back();
		}
		while (!chi->empty())
		{
			delete[] chi->back();
			chi->pop_back();
		}
		delete pop;

		// Ustalenie nowej populacji
		pop = newPop;

		// Weryfikacja wyników
		temp = INT_MAX - sumowaniePopulacji(a, b, c, pop->front(), route, miejsce, kryterium);
		if (temp < result)
		{
			result = temp;
			for (int i = 0; i < a.r; i++)
				final_route[i] = route[i];
		}

	}

	if (kryterium == "Droga" || kryterium == "Punkty") {
		for (int i = 0; i < a.r - 1; i++) {
			if (czasCalkowity < tmpCzas) {
				czas += b.m[final_route[i]][final_route[i + 1]];
				czas += b.m[final_route[limit - 1]][final_route[0]];
				wezel += c.m[final_route[i]];
				czasCalkowity = czas + wezel * 60;
				limit++;
			}
		}
	}
	else if (kryterium == "Czas") {
		for (int i = 0; i < a.r - 1; i++) {
			if (czasCalkowity < tmpCzas) {
				czas += a.m[final_route[i]][final_route[i + 1]];
				czas += a.m[final_route[limit - 1]][final_route[0]];
				wezel += c.m[final_route[i]];
				czasCalkowity = czas + wezel * 60;
				limit++;
			}
		}
	}

	if (kryterium == "Droga" || kryterium == "Punkty") {
		result = droga(a, final_route, limit);
		czas = droga(b, final_route, limit);
	}
	else if (kryterium == "Czas") {
		result = droga(b, final_route, limit);
		czas = droga(a, final_route, limit);
	}

	wezel = drogaTab(c, final_route, limit - 1);
	czasCalkowity = czas + wezel * 60;
	punkty = wartoscWszystkichWierzcholkow(a, b, c, final_route, kryterium, limit);

	// Wyœwietlenie wyników
	if (display) {
		system("cls");
		cout << "Algorytm genetyczny zakoñczy³ dzia³anie..." << endl;
		cout << endl << "Wyniki:" << endl;
		cout << "Najkrótsza droga:" << endl << "\t";
		for (int i = 0; i < limit; i++)
			cout << final_route[i] << " -> ";
		cout << final_route[0] << " ...";
		cout << endl << endl << "Czas trwania wycieczki: " << maxCzas << " [h] = " << tmpCzas << " [min] | Bufor: +/- 4 [h]";
		cout << endl << "Odwiedzonych zostanie " << limit << " miast." << endl << "Dominuj¹ce kryterium: " << kryterium;
		if (kryterium == "Droga") {
			cout << endl << "Ca³kowita odleg³oœæ: " << result << " [m]" << endl;
			cout << endl << "Ca³kowity czas podró¿y miêdzy miastami: " << czas << " [min]";
			cout << endl << "Ca³kowity czas podró¿y spêdzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca³kowity czas podró¿y + powrót: " << czasCalkowity << " [min]";
			cout << endl << "Wartoœæ œcie¿ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Czas") {
			cout << endl << "Ca³kowity czas podró¿y miêdzy miastami w minutach: " << czas << " [min]" << endl;
			cout << endl << "Ca³kowita odleg³oœæ w metrach: " << result << " [m]";
			cout << endl << "Ca³kowity czas podró¿y spêdzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca³kowity czas podró¿y + powrót: " << czasCalkowity << " [min]";
			cout << endl << "Wartoœæ œcie¿ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Punkty") {
			cout << endl << "Wartoœæ œcie¿ki w punktach: " << punkty << endl;
			cout << endl << "Ca³kowita odleg³oœæ: " << result << " [m]";
			cout << endl << "Ca³kowity czas podró¿y miêdzy miastami: " << czas << " [min]";
			cout << endl << "Ca³kowity czas podró¿y spêdzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca³kowity czas podró¿y + powrót: " << czasCalkowity << " [min]" << endl << endl;
		}
		system("pause");
	}

	// Usuwanie wektorów i tablic
	while (!pop->empty())
	{
		delete[] pop->back();
		pop->pop_back();
	}
	chi->clear();
	par->clear();
	pop->clear();
	delete par;
	delete pop;
	delete chi;
	delete[] route;
	delete[] final_route;

	if (kryterium == "Droga")
		return result;
	else if (kryterium == "Czas")
		return czas;
	else if (kryterium == "Punkty")
		return punkty;
	else
		return 0;
}

int Genetic::sumowaniePopulacji(Matrix &a, Matrix &b, GraphNode &c, int *populus, int* route, int miejsce, string kryterium)
{
	int suma = 0, temp = 0, rot = 0, t_miejsce = 0;

	// Ustawienie miejsca pocz¹tkowego
	for (int i = 0; i < a.r; i++)
	{
		if (populus[i] == miejsce)
			rot = i;
	}
	for (int i = 0; i < rot; i++)
	{
		t_miejsce = populus[0];
		for (int j = 0; j < a.r; j++)
			populus[j] = populus[j + 1];
		populus[a.r - 1] = t_miejsce;
	}

	for (int i = 0; i < a.r - 1; ++i)
	{
		if (kryterium == "Punkty") {
			if (a.m[populus[i]][populus[i + 1]] != 0)
				suma += (a.m[populus[i]][populus[i + 1]] / b.m[populus[i]][populus[i + 1]]) / 100 + c.m[populus[i]];
			else
				suma += 0;
		}
		else
			suma += a.m[populus[i]][populus[i + 1]];
		route[i] = populus[i];
	}
	if (kryterium == "Punkty")
		suma += (a.m[populus[a.r - 1]][populus[0]] / b.m[populus[a.r - 1]][populus[0]]) / 100 + c.m[a.r - 1];
	else
		suma += a.m[populus[a.r - 1]][populus[0]];
	route[a.r - 1] = populus[a.r - 1];
	temp = (INT_MAX - suma);
	return temp;
}

void Genetic::losowaPermutacja(Matrix &a, int *sciezka)
{
	int *temp = new int[a.r], losowanie;
	for (int i = 0; i < a.r; i++)
		temp[i] = i;
	for (int i = a.r; i > 0; i--)
	{
		losowanie = rand() % i;
		sciezka[i - 1] = temp[losowanie];
		temp[losowanie] = temp[i - 1];
	}
	delete[] temp;
}

float Genetic::los(void)
{
	// Losowy generator niedeterministycznych liczb losowych
	random_device rd;

	// Generator liczb pseudolosowych
	minstd_rand gen(rd());

	// Losowa dystrybucja liczb rozk³adu jednostajnego z przedzia³u (0,1)
	uniform_real_distribution <float> dis(0, 1);

	float a = dis(gen);
	return a;
}

void Genetic::zamiana(int *tab, int x, int y)
{
	int temp;
	temp = tab[x];
	tab[x] = tab[y];
	tab[y] = temp;
}

Genetic::~Genetic() {};
