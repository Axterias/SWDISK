#include "Macierz.h"

int Macierz::algorytmWyzarzania(Macierz &a, float Tp, float Tk, bool display)
{
	bool start = true, weryfikacja = false;	// Pilnuje dzia³anie pêtli while
	int *najlepsza_sciezka = new int[a.r], *sciezka = new int[a.r];	// Przechowuj¹ œcie¿ki
	int koncowy_wynik = 0, najlepszy_wynik = 0, wynik = 0;	// Przechowuj¹ wyniki odleg³oœci
	float T = 0;	// Temperatury: pocz¹tkowa, koñcowa i aktualna
	int iteracja = 1; // Numer iteracji - potrzebne do sch³adzania
	int zamiana1 = 0, zamiana2 = 0;	//Losowe wartoœci, które ulegn¹ zamianie
	float x = 0;	// Zmienna przechowuj¹ca wylosowan¹ wartoœæ z przedzia³u od 0 do 1
	float P = 0;	// Zmienna przechowuj¹ca wynik przyjêtej wartoœci funkcji prawdopodobieñstwa

	srand((unsigned)time(NULL));	// Ziarno losowoœci

	T = Tp;
	losowaPermutacja(a, najlepsza_sciezka);	// Ustawienie pierwszej losowej premutacji
	najlepszy_wynik = droga(a, najlepsza_sciezka);
	for (int i = 0; i < a.r; i++)
		sciezka[i] = najlepsza_sciezka[i];
	wynik = najlepszy_wynik;
	koncowy_wynik = najlepszy_wynik;
	while (start)
	{
		zamiana1 = rand() % a.r;
		zamiana2 = rand() % (a.r - 1);
		if (zamiana2 >= zamiana1)
			++zamiana2;
		zamiana(sciezka, zamiana1, zamiana2);	// Wybranie z s¹siedztwa S*, pewnego rozwi¹zania S'
		wynik = droga(a, sciezka);
		if (wynik <= najlepszy_wynik)	// Jeœli lepsze to zast¹p S*, tak aby S* = S'
		{
			najlepszy_wynik = wynik;
			if (najlepszy_wynik <= koncowy_wynik)
			{
				koncowy_wynik = najlepszy_wynik;
				for (int i = 0; i < a.r; i++)
					najlepsza_sciezka[i] = sciezka[i];
			}
		}
		else
		{
			x = los();
			P = prawdopodobienstwo(wynik, najlepszy_wynik, T);
			if (x < P)	// Jeœli gorsze to badany jest rezultat prawdopodobnego odstêpstwa od œcie¿ki
			{
				najlepszy_wynik = wynik;
				if (najlepszy_wynik <= koncowy_wynik)
				{
					koncowy_wynik = najlepszy_wynik;
					for (int i = 0; i < a.r; i++)
						najlepsza_sciezka[i] = sciezka[i];
				}
			}
		}
		iteracja++;
		if (schladzanie(iteracja, Tp) <= Tk)	// Zmniejszanie temperatury
			start = false;
		else
			T = schladzanie(iteracja, Tp);
	}

	// Wyœwietlenie wyników
	if (display) {
		cout << "Algorytm symulowanego wy¿arzania zakoñczyñ dzia³anie" << endl;
		cout << endl << "Wyniki:" << endl << endl;
		cout << "Iloœæ wykonanych iteracji: " << iteracja << endl;
		cout << "Temperatura przy ostatniej iteracji: " << T << endl;
		cout << "Najkrótsza scie¿ka:" << endl << "\t";
		for (int i = 0; i < a.r; i++)
			cout << najlepsza_sciezka[i] << " -> ";
		cout << najlepsza_sciezka[0] << " ...";
		cout << endl << "Droga do przebycia: " << koncowy_wynik << endl << endl;
		system("pause");
	}

	// Usuwanie tablic
	delete[] najlepsza_sciezka;
	delete[] sciezka;

	return koncowy_wynik;
}

int Macierz::algorytmGenetyczny(Macierz &a, int population, int generations, float mutation, int parentsPopulation, int childernPopulation, int swaps, float cross, bool display)
{
	// Zmienne pomocnicze w obliczeniach
	int temp = 0, tempCP1 = 0, tempCP2 = 0;
	long long tempLong = 0, tempCValue = 0, tempLValue = 0, tempPSum = 0;

	// Tablice pomocnicze w obliczeniach
	int *tmp, *tmpP1, *tmpP2, *tmpC1, *tmpC2, *tmpV;

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
			tmpV[i] = sumowaniePopulacji(a, pop->at(i), route);
			tempPSum += tmpV[i];
		}
		for (int i = 0; i < parentsPopulation; i++)
		{
			tempCValue = 0;
			tempLValue = 0;
			tempLong = los() * tempPSum;
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
		temp = INT_MAX - sumowaniePopulacji(a, pop->front(), route);
		if (temp < result)
		{
			result = temp;
			for (int i = 0; i < a.r; i++)
				final_route[i] = route[i];
		}
	}

	// Wyœwietlenie wyników
	if (display) {
		system("cls");
		cout << "Algorytm genetyczny zakoñczy³ dzia³anie" << endl;
		cout << endl << "Wyniki:" << endl;
		cout << "Najkrotsza sciezka:" << endl << "\t";
		for (int i = 0; i < a.r; i++)
			cout << final_route[i] << " -> ";
		cout << final_route[0] << " ...";
		cout << endl << "Droga do przebycia: " << result << endl << endl;
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

	return result;
}

int Macierz::sumowaniePopulacji(Macierz &a, int *populus, int* route)
{
	int suma = 0, temp = 0;
	for (int i = 0; i < a.r - 1; ++i)
	{
		suma += a.m[populus[i]][populus[i + 1]];
		route[i] = populus[i];
	}
	suma += a.m[populus[a.r - 1]][populus[0]];
	route[a.r - 1] = populus[a.r - 1];
	temp = (INT_MAX - suma);
	return temp;
}

float Macierz::los(void)
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

void Macierz::zamiana(int *tab, int x, int y)
{
	int temp;
	temp = tab[x];
	tab[x] = tab[y];
	tab[y] = temp;
}

int Macierz::droga(Macierz &a, int *tab)
{
	int wynik = 0;
	for (int i = 0; i < a.r - 1; i++)
		wynik += a.m[tab[i]][tab[i + 1]];
	wynik += a.m[tab[a.r - 1]][tab[0]];
	return wynik;
}

void Macierz::losowaPermutacja(Macierz &a, int *sciezka)
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

float Macierz::schladzanie(int k, float Tp)
{
	const double e = 2.71828182846;
	float ln = 0, T = 0;
	ln = (float)(log(k) / log(e));	// ln(k) z w³asnoœci logarytmów
	T = (float)(Tp / ln);	// Sch³adzanie schematem logarytmicznym
	return T;
}

float Macierz::prawdopodobienstwo(int s1, int s2, float T)
{
	const double e = 2.71828182846;
	float prawdopodobienstwo, wykladnik;
	wykladnik = -((s1 - s2) / T);
	prawdopodobienstwo = (float)(pow(e, wykladnik));
	return prawdopodobienstwo;
}

bool Macierz::odczyt(Macierz &a)
{
	// p - zwraca informacjê o utworzeniu macierzy, symetria - wybór tsp lub atsp, werfikacja - sprawdzenie poprawnoœci danych
	// reszta to zmienne pilnuj¹ce koñczenie etapów pobierania danych z pliku
	bool p, symetria, weryfikacja = true, kontrola = true, pobieranie = true, uzupelnianie = true;
	char *cstr, *nast_token = NULL;
	string nazwa_pliku, znak_pom;
	// rozmiar - iloœæ znaków w wierszu, k, j - zmienne interacyjne, check - iloœæ znaków w wierszu bez spacji
	// poczatek - pocz¹tek dynamicznie alokowanej tablicy zmiennych
	int rozmiar, k = 0, j = 0, check, poczatek = 0;
	while (weryfikacja)	// Sprawdzenie poprawnoœæ wpisanych danych
	{
		system("CLS");
		cout << "Proszê podaæ nazwe pliku do odczytu (Nale¿y podaæ w postaci: nazwa_pliku.txt)" << endl;
		cin.sync();
		cin.clear();
		getline(cin, nazwa_pliku);
		ifstream potok;
		potok.open(nazwa_pliku, ios::in);
		if (potok.good())
		{
			weryfikacja = false;
			while (kontrola)	// Sprawdzanie iloœcie miast
			{
				getline(potok, znak_pom);
				rozmiar = znak_pom.length() + 1;
				cstr = new char[rozmiar];
				strcpy_s(cstr, rozmiar, znak_pom.c_str());
				znak_pom = strtok_s(cstr, " ", &nast_token);
				if (znak_pom == "TYPE:")	// Kryterium po którym pozycja rozmiaru jest poznawana
				{
					znak_pom = strtok_s(NULL, " ", &nast_token);
					if (znak_pom == "TSP")
						symetria = true;
					else
						symetria = false;
					kontrola = false;
				}
				nast_token = NULL;
				delete[] cstr;
			}
			kontrola = true;
			while (kontrola)	// Sprawdzanie iloœcie miast
			{
				getline(potok, znak_pom);
				rozmiar = znak_pom.length() + 1;
				cstr = new char[rozmiar];
				strcpy_s(cstr, rozmiar, znak_pom.c_str());
				znak_pom = strtok_s(cstr, " ", &nast_token);
				if (znak_pom == "DIMENSION:")	// Kryterium po którym pozycja rozmiaru jest poznawana
				{
					znak_pom = strtok_s(NULL, " ", &nast_token);
					a.r = atoi(znak_pom.c_str());	// Konwersja string na int
					kontrola = false;
				}
				nast_token = NULL;
				delete[] cstr;
			}
			kontrola = true;
			a.m = new int *[a.r];
			for (int i = 0; i < a.r; i++)
				a.m[i] = new int[a.r];
			while (kontrola)	// Wczytywanie danych do macierzy
			{
				getline(potok, znak_pom);
				rozmiar = znak_pom.length() + 1;
				cstr = new char[rozmiar];
				strcpy_s(cstr, rozmiar, znak_pom.c_str());
				znak_pom = strtok_s(cstr, " ", &nast_token);
				if (znak_pom == "EDGE_WEIGHT_SECTION")	// Kryterium, po którym rozpoczyna siê sekcja odleg³oœci w pliku
				{
					nast_token = NULL;
					delete[] cstr;
					while (uzupelnianie)
					{
						getline(potok, znak_pom);
						rozmiar = znak_pom.length() + 1;
						check = rozmiar;
						for (int i = 0; i < rozmiar; i++)
						{
							if (znak_pom[i] == ' ')	// Odejmowanie spacji od iloœci znaków w wierszu
								check--;
						}
						cstr = new char[rozmiar];
						strcpy_s(cstr, rozmiar, znak_pom.c_str());
						while (pobieranie)
						{
							if (symetria == false)	// Dwie ró¿ne wersje zapisu danych w plikach, wiêc dwie ró¿ne wersje wczytywania
							{
								if (poczatek == 0)
									znak_pom = strtok_s(cstr, " ", &nast_token);	// Pozycja pierwsza
								else
									znak_pom = strtok_s(NULL, " ", &nast_token);	//Ka¿da kolejna pozycja
								a.m[k][j] = atoi(znak_pom.c_str());
								poczatek++;
								j++;
								if (j == a.r)	// Warunki koñcz¹ce wiersz i pobieranie danych
								{
									j = 0;
									k++;
									if (k == a.r)
										uzupelnianie = false;
								}
								check = check - znak_pom.length();
								if (check == 1)
									pobieranie = false;
							}
							else
							{
								if (poczatek == 0)
									znak_pom = strtok_s(cstr, " ", &nast_token);	// Pozycja pierwsza
								else
									znak_pom = strtok_s(NULL, " ", &nast_token);	//Ka¿da kolejna pozycja
								a.m[k][j] = atoi(znak_pom.c_str());
								a.m[j][k] = a.m[k][j];
								poczatek++;
								k++;
								if (k > j)	// Warunki koñcz¹ce wiersz i pobieranie danych
								{
									k = 0;
									j++;
									if (j == a.r)
										uzupelnianie = false;
								}
								check = check - znak_pom.length();
								if (check == 1)
									pobieranie = false;
							}
						}
						poczatek = 0;
						pobieranie = true;
						nast_token = NULL;
						delete[] cstr;
					}
					kontrola = false;
				}
			}
			cout << "Utworzono macierz korzystaj¹c z danych z pliku!" << endl;
			potok.close();
			system("pause");
			p = true;
		}
		else
		{
			cout << "Nie uda³o siê wykonaæ operacji!" << endl;
			cout << "Podano b³êdne dane!" << endl << "Proszê wpisaæ ponownie!" << endl;
			potok.close();
			system("pause");
			p = false;
			cin.sync();
			cin.clear();
		}
	}
	return p;
}

bool Macierz::uzupelnienie(Macierz &a, int iloscMiast, bool sym, bool display)
{
	bool p, weryfikacja = false;
	srand((unsigned)time(NULL));
	int gestosc = 100, check, b, c, war, pom;
	int max_odleglosc = 8;	// Maksymalna losowana odleg³oœæ miêdzy miastami
	if (a.r) {
		a.usuwanie(a);
	}
	a.r = iloscMiast;

	if (sym)	// Symetryczna, a wiec bierzemy po³owe
		gestosc = (int)(gestosc / 2);
	pom = (int)((((a.r * a.r) - a.r) * gestosc) / 100);	// Okreslenie ilosci krawedzi
	a.m = new int *[a.r];
	for (int i = 0; i < a.r; i++)
		a.m[i] = new int[a.r];
	for (int i = 0; i < a.r; i++)	// Uzupelnienie macierzy zerami
	{
		for (int j = 0; j < a.r; j++)
			a.m[i][j] = 0;
	}
	for (int i = 0; i < (a.r - 1); i++)	// Pêtla pilnuj¹ca spójnoœci
	{
		a.m[i][i + 1] = 1;
		check = a.r - 1;
	}
	if (sym)	// sym = true - oznacza ze mamy do czynienia symetryczn¹ macierz¹
	{
		b = 0;
		c = 1;
		war = a.r;
		while (check != pom)	// Losowanie pozycji w macierzy na ktorych zostana umieszczone wagi
		{
			if (c == a.r)	// Na wypadek przekroczenia rozmiaru kolumny (zawsze macierz trójk¹tna górna)
			{
				war--;
				b++;
				c = a.r - war;
			}
			if (b == c && b != a.r && c != a.r)	// Straznik pilnuj¹cy aby przek¹tna by³a zawsze zerem
				c++;
			if (c == a.r && b == (a.r - 1))	// Pilnuje, aby stra¿nik nie wrzuci³ c poza rozmiar wiersza
				b++;						// Zwiêkszenie b w tym przypadku wywo³a kolejny warunek i naprawi to
			if (b == a.r)	// Na wypadek przekroczenia rozmiaru macierzy
			{
				b = 0;
				c = 1;
				war = a.r;
			}
			if (a.m[b][c] == 0)	// Losowanie pozycji krawedzi
				a.m[b][c] = rand() % 2;	// Zakres od 0 do 1
			else
				check--;	//Na wypadek ponownego przegladania macierzy, aby nie liczyc podwojnie
			if (a.m[b][c] == 1)	// Gdy 1 to zwiekszamy ilosc wylosowanych krawedzi
				check++;
			c++;
		}
	}
	else
	{
		b = 0;
		c = 1;
		while (check != pom)	// Losowanie pozycji w macierzy na ktorych zostana umieszczone wagi
		{
			if (b == c && b != a.r && c != a.r)	// Straznik pilnuj¹cy aby przek¹tna by³a zawsze zerem
				c++;
			if (c == a.r)	// Na wypadek przekroczenia rozmiaru kolumny
			{
				b++;
				c = 0;
			}
			if (b == a.r)	// Na wypadek przekroczenia rozmiaru macierzy
			{
				b = 0;
				c = 1;
			}
			if (a.m[b][c] == 0)	// Losowanie pozycji krawedzi
				a.m[b][c] = rand() % 2;
			else
				check--;	// Na wypadek ponownego przegladania macierzy, aby nie liczyc podwojnie
			if (a.m[b][c] == 1)	// Gdy 1 to zwiekszamy ilosc wylosowanych krawedzi
				check++;
			c++;
		}
	}
	if (sym)	// Losowanie wag
	{
		for (int i = 0; i < a.r; i++)
		{
			for (int j = 0; j < a.r; j++)
			{
				if (a.m[i][j] == 1)
					a.m[i][j] = rand() % max_odleglosc + 1;	// Zakres od 1 do max_odleglosc
				a.m[j][i] = a.m[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < a.r; i++)
		{
			for (int j = 0; j < a.r; j++)
			{
				if (a.m[i][j] == 1)
					a.m[i][j] = rand() % max_odleglosc + 1;
			}
		}
	}
	if (display) {
		cout << endl << "\n\tWygenerowano macierz s¹siedztwa po³¹czeñ miêdzy miastami!\n\n" << endl;
		system("pause");
	}
	p = true;
	return p;
}

bool Macierz::uzupelnienieReczne(Macierz &a, bool sym)
{
	bool p, uzup = true, weryfikacja = false;
	string wybor;
	int k = 0, h = 0;
	while (weryfikacja == false)	// Sprawdzenie poprawnoœæ wpisanych danych
	{
		system("CLS");
		cout << "Proszê podaæ iloœæ miast: ";
		cin >> a.r;
		weryfikacja = cin.good();
		if (weryfikacja == false)
		{
			cout << "Podano b³êdne dane!" << endl << "Proszê wpisaæ ponownie!" << endl;
			system("pause");
		}
		cin.sync();
		cin.clear();
	}
	a.m = new int *[a.r];
	for (int i = 0; i < a.r; i++)
		a.m[i] = new int[a.r];
	p = true;
	for (int i = 0; i < a.r; i++)
	{
		for (int j = 0; j < a.r; j++)
			a.m[i][j] = 0;
	}
	while (uzup)
	{
		if (h == k)
			k++;
		weryfikacja = false;
		while (weryfikacja == false)	// Sprawdzenie poprawnoœæ wpisanych danych
		{
			system("CLS");
			cout << a;
			cout << endl << endl << "Proszê wpisaæ wartoœæ w polu [" << h << "," << k << "] macierzy: ";
			cin >> a.m[h][k];
			weryfikacja = cin.good();
			if (weryfikacja == false)
			{
				cout << "Podano b³êdne dane!" << endl << "Proszê wpisaæ ponownie!" << endl;
				system("pause");
			}
			cin.sync();
			cin.clear();
		}
		if (sym)
			a.m[k][h] = a.m[h][k];
		k++;
		if (sym == true && k == a.r)
		{
			h++;
			if (h + 1 == a.r)
				uzup = false;
			else
				k = h + 1;
		}
		else if (sym == false && k == a.r)
		{
			h++;
			k = 0;
		}
		if (k == a.r - 1 && h == a.r - 1)
			uzup = false;
	}
	system("CLS");
	cout << a;
	cout << "Dane wprowadzono prawid³owo" << endl << endl;
	system("pause");
	return p;
}

void Macierz::usuwanie(Macierz &a)
{
	for (int i = 0; i < a.r; i++)
	{
		delete[] a.m[i];
	}
	delete[] a.m;
	a.r = NULL;
}

ostream& operator<<(ostream &wy, Macierz &y)
{
	bool wiersz = true;
	wy << "Odleg³oœci pomiêdzy miastami w macierzy s¹siedztwa z uzupe³nionymi wagami:" << endl << endl << endl;
	wy << "   ";
	if (wiersz)
	{
		for (int i = 0; i < y.r; i++)
			wy << i << " ";
		wy << endl << "  ";
		for (int i = 0; i < y.r * 2; i++)
			wy << "_";
		wy << endl;
		wiersz = false;
	}
	for (int i = 0; i < y.r; i++)
	{
		wy << i << " |";
		for (int j = 0; j < y.r; j++)
		{
			wy << y.m[i][j] << " ";
		}
		wy << endl;
	}
	wy << endl << endl << endl;
	return wy;
}