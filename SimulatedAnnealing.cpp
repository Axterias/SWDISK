#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing() {}

int SimulatedAnnealing::algorytmWyzarzania(Matrix &a, Matrix &b, GraphNode &c, float Tp, float Tk, int maxCzas, int miejsce, string kryterium, bool display)
{
	bool start = true, weryfikacja = false;	// Pilnuje dzia�anie p�tli while
	int *najlepsza_sciezka = new int[a.r], *sciezka = new int[a.r];	// Przechowuj� �cie�ki
	int koncowy_wynik = 0, najlepszy_wynik = 0, wynik = 0;	// Przechowuj� wyniki odleg�o�ci
	float T = 0;	// Temperatury: pocz�tkowa, ko�cowa i aktualna
	int iteracja = 1; // Numer iteracji - potrzebne do sch�adzania
	int zamiana1 = 0, zamiana2 = 0;	//Losowe warto�ci, kt�re ulegn� zamianie
	float x = 0;	// Zmienna przechowuj�ca wylosowan� warto�� z przedzia�u od 0 do 1
	float P = 0;	// Zmienna przechowuj�ca wynik przyj�tej warto�ci funkcji prawdopodobie�stwa
	int czas = 0, wezel = 0, czasCalkowity = 0, tmpCzas = maxCzas * 60, limit = 1, rot = 0, t_miejsce = 0, punkty = 0;	// Zmienne pomocnicze

	srand((unsigned)time(NULL));	// Ziarno losowo�ci

	T = Tp;
	losowaPermutacja(a, najlepsza_sciezka);	// Ustawienie pierwszej losowej premutacji

	// Ustawienie miejsca pocz�tkowego
	for (int i = 0; i < a.r; i++)
	{
		if (najlepsza_sciezka[i] == miejsce)
			rot = i;
	}
	for (int i = 0; i < rot; i++)
	{
		t_miejsce = najlepsza_sciezka[0];
		for (int j = 0; j < a.r; j++)
			najlepsza_sciezka[j] = najlepsza_sciezka[j + 1];
		najlepsza_sciezka[a.r - 1] = t_miejsce;
	}

	najlepszy_wynik = droga(a, najlepsza_sciezka, a.r);	// Pierwsza inicjalizacja z maksymalnym limitem
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
		zamiana(sciezka, zamiana1, zamiana2);	// Wybranie z s�siedztwa S*, pewnego rozwi�zania S'

		// Ponowne ustawienie miejsca pocz�tkowego
		for (int i = 0; i < a.r; i++)
		{
			if (sciezka[i] == miejsce)
				rot = i;
		}
		for (int i = 0; i < rot; i++)
		{
			t_miejsce = sciezka[0];
			for (int j = 0; j < a.r; j++)
				sciezka[j] = sciezka[j + 1];
			sciezka[a.r - 1] = t_miejsce;
		}

		if (kryterium == "Punkty")
			wynik = drogaPunkty(a, b, c, sciezka, a.r, kryterium);	// Maksymalny limit, dla zachowania sp�jno�ci
		else
			wynik = droga(a, sciezka, a.r);

		if (wynik <= najlepszy_wynik)	// Je�li lepsze to zast�p S*, tak aby S* = S'
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
			if (x < P)	// Je�li gorsze to badany jest rezultat prawdopodobnego odst�pstwa od �cie�ki
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

	if (kryterium == "Droga" || kryterium == "Punkty") {
		for (int i = 0; i < a.r - 1; i++) {
			if (czasCalkowity < tmpCzas) {
				czas += b.m[najlepsza_sciezka[i]][najlepsza_sciezka[i + 1]];
				czas += b.m[najlepsza_sciezka[limit - 1]][najlepsza_sciezka[0]];
				wezel += c.m[najlepsza_sciezka[i]];
				czasCalkowity = czas + wezel * 60;
				limit++;
			}
		}
	}
	else if (kryterium == "Czas") {
		for (int i = 0; i < a.r - 1; i++) {
			if (czasCalkowity < tmpCzas) {
				czas += a.m[najlepsza_sciezka[i]][najlepsza_sciezka[i + 1]];
				czas += a.m[najlepsza_sciezka[limit - 1]][najlepsza_sciezka[0]];
				wezel += c.m[najlepsza_sciezka[i]];
				czasCalkowity = czas + wezel * 60;
				limit++;
			}
		}
	}

	if (kryterium == "Droga" || kryterium == "Punkty") {
		koncowy_wynik = droga(a, najlepsza_sciezka, limit);
		czas = droga(b, najlepsza_sciezka, limit);
	}
	else if (kryterium == "Czas") {
		koncowy_wynik = droga(b, najlepsza_sciezka, limit);
		czas = droga(a, najlepsza_sciezka, limit);
	}

	wezel = drogaTab(c, najlepsza_sciezka, limit - 1);
	czasCalkowity = czas + wezel * 60;
	punkty = wartoscWszystkichWierzcholkow(a, b, c, najlepsza_sciezka, kryterium, limit);

	// Wy�wietlenie wynik�w
	if (display) {
		cout << "Algorytm symulowanego wy�arzania zako�czy� dzia�anie..." << endl;
		cout << endl << "Wyniki:" << endl << endl;
		cout << "Ilo�� wykonanych iteracji: " << iteracja << endl;
		cout << "Temperatura przy ostatniej iteracji: " << T << endl;
		cout << "Najkr�tsza droga:" << endl << "\t";
		for (int i = 0; i < limit; i++)
			cout << najlepsza_sciezka[i] << " -> ";
		cout << najlepsza_sciezka[0] << " ...";
		cout << endl << endl << "Czas trwania wycieczki: " << maxCzas << " [h] = " << tmpCzas << " [min] | Bufor: +/- 4 [h]";
		cout << endl << "Odwiedzonych zostanie " << limit << " miast." << endl << "Dominuj�ce kryterium: " << kryterium;
		if (kryterium == "Droga") {
			cout << endl << "Ca�kowita odleg�o��: " << koncowy_wynik << " [m]" << endl;
			cout << endl << "Ca�kowity czas podr�y mi�dzy miastami: " << czas << " [min]";
			cout << endl << "Ca�kowity czas podr�y sp�dzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca�kowity czas podr�y + powr�t: " << czasCalkowity << " [min]";
			cout << endl << "Warto�� �cie�ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Czas") {
			cout << endl << "Ca�kowity czas podr�y mi�dzy miastami w minutach: " << czas << " [min]" << endl;
			cout << endl << "Ca�kowita odleg�o�� w metrach: " << koncowy_wynik << " [m]";
			cout << endl << "Ca�kowity czas podr�y sp�dzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca�kowity czas podr�y + powr�t: " << czasCalkowity << " [min]";
			cout << endl << "Warto�� �cie�ki w punktach: " << punkty << endl << endl;
		}
		else if (kryterium == "Punkty") {
			cout << endl << "Warto�� �cie�ki w punktach: " << punkty << endl;
			cout << endl << "Ca�kowita odleg�o��: " << koncowy_wynik << " [m]";
			cout << endl << "Ca�kowity czas podr�y mi�dzy miastami: " << czas << " [min]";
			cout << endl << "Ca�kowity czas podr�y sp�dzony w miastach: " << wezel << " [h]";
			cout << endl << "Ca�kowity czas podr�y + powr�t: " << czasCalkowity << " [min]" << endl << endl;
		}
		system("pause");
	}

	// Usuwanie tablic
	delete[] najlepsza_sciezka;
	delete[] sciezka;

	if (kryterium == "Droga")
		return koncowy_wynik;
	else if (kryterium == "Czas")
		return czas;
	else if (kryterium == "Punkty")
		return punkty;
	else
		return 0;
}

float SimulatedAnnealing::los(void)
{
	// Losowy generator niedeterministycznych liczb losowych
	random_device rd;

	// Generator liczb pseudolosowych
	minstd_rand gen(rd());

	// Losowa dystrybucja liczb rozk�adu jednostajnego z przedzia�u (0,1)
	uniform_real_distribution <float> dis(0, 1);

	float a = dis(gen);
	return a;
}

void SimulatedAnnealing::zamiana(int *tab, int x, int y)
{
	int temp;
	temp = tab[x];
	tab[x] = tab[y];
	tab[y] = temp;
}

void SimulatedAnnealing::losowaPermutacja(Matrix &a, int *sciezka)
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

float SimulatedAnnealing::schladzanie(int k, float Tp)
{
	const double e = 2.71828182846;
	float ln = 0, T = 0;
	ln = (float)(log(k) / log(e));	// ln(k) z w�asno�ci logarytm�w
	T = (float)(Tp / ln);	// Sch�adzanie schematem logarytmicznym
	return T;
}

float SimulatedAnnealing::prawdopodobienstwo(int s1, int s2, float T)
{
	const double e = 2.71828182846;
	float prawdopodobienstwo, wykladnik;
	wykladnik = -((s1 - s2) / T);
	prawdopodobienstwo = (float)(pow(e, wykladnik));
	return prawdopodobienstwo;
}

SimulatedAnnealing::~SimulatedAnnealing() {}
