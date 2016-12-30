#include "Matrix.h"

bool Matrix::odczyt(Matrix &a, bool czas)
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
		if (czas)
			cout << "Proszê podaæ nazwê pliku do odczytu z czasem podró¿y miêdzy miastami\n(Nale¿y podaæ w postaci: nazwa_pliku.txt)" << endl;
		else
			cout << "Proszê podaæ nazwê pliku do odczytu z odleg³oœciami pomiêdzy miastami\n(Nale¿y podaæ w postaci: nazwa_pliku.txt)" << endl;
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

bool Matrix::uzupelnienie(Matrix &a, int iloscMiast, bool sym, bool czas, bool display)
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
	if (czas) {
		for (int i = 0; i < a.r; i++)	// Zwiêkszenie wartoœci razy 8, dla czasu (rezultat -> minuty)
		{
			for (int j = 0; j < a.r; j++)
				a.m[i][j] *= 8;
		}
	}
	else
	{
		for (int i = 0; i < a.r; i++)	// Zwiêkszenie wartoœci razy 13855, dla odleg³oœci (rezultat -> km)
		{
			for (int j = 0; j < a.r; j++)
				a.m[i][j] *= 13855;
		}
	}
	if (display) {
		if (czas)
			cout << endl << "\n\tWygenerowano macierz czasu podró¿y miêdzy miastami!\n\n" << endl;
		else
			cout << endl << "\n\tWygenerowano macierz s¹siedztwa po³¹czeñ miêdzy miastami!\n\n" << endl;
		system("pause");
	}
	p = true;
	return p;
}

bool Matrix::uzupelnienieReczne(Matrix &a, int iloscMiast, bool sym, bool czas)
{
	bool p, uzup = true, weryfikacja = false;
	int k = 0, h = 0;
	if (a.r) {
		a.usuwanie(a);
	}
	a.r = iloscMiast;

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
			if (czas)
				cout << "Macierz czasu podró¿y miêdzy miastami:" << endl << endl;
			else
				cout << "Macierz odleg³oœci miêdzy miastami:" << endl << endl;
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
	if (czas)
		cout << "Macierz czasu podró¿y miêdzy miastami:" << endl << endl;
	else
		cout << "Macierz odleg³oœci miêdzy miastami:" << endl << endl;
	cout << a;
	cout << "Dane wprowadzono prawid³owo" << endl << endl;
	system("pause");
	return p;
}

void Matrix::usuwanie(Matrix &a)
{
	for (int i = 0; i < a.r; i++)
	{
		delete[] a.m[i];
	}
	delete[] a.m;
	a.r = NULL;
}

ostream& operator<<(ostream &wy, Matrix &y)
{
	bool wiersz = true;
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

int Matrix::droga(Matrix &a, int *tab, int limit)
{
	int wynik = 0;
	for (int i = 0; i < limit - 1; i++)
		wynik += a.m[tab[i]][tab[i + 1]];
	wynik += a.m[tab[limit - 1]][tab[0]];
	return wynik;
}

int Matrix::drogaPunkty(Matrix &a, Matrix &b, GraphNode &c, int *tab, int limit, string kryterium)
{
	int wynik = 0;
	for (int i = 0; i < a.r; i++) {
		if (kryterium == "Punkty") {
			if (a.m[tab[i]][tab[i]] != 0)
				wynik += (a.m[tab[i]][tab[i + 1]] / b.m[tab[i]][tab[i + 1]]) / 100 + c.m[tab[i]];
			else
				wynik += 0;
		}
		else
			wynik += a.m[tab[i]][tab[i + 1]];
	}
	if (kryterium == "Punkty")
		wynik += (a.m[tab[a.r - 1]][tab[0]] / b.m[tab[a.r - 1]][tab[0]]) / 100 + c.m[tab[a.r - 1]];
	else
		wynik += a.m[tab[a.r - 1]][tab[0]];
	return wynik;
}

int Matrix::drogaTab(GraphNode &a, int *tab, int limit)
{
	int wynik = 0;
	for (int i = 0; i < limit; i++)
		wynik += a.m[tab[i]];
	return wynik;
}

int Matrix::wartoscWszystkichWierzcholkow(Matrix &a, Matrix &b, GraphNode &c, int *tab, string kryterium, int limit)
{
	int wynik = 0;
	if (kryterium == "Droga" || kryterium == "Punkty") {
		for (int i = 0; i < limit - 1; i++)
			wynik += (a.m[tab[i]][tab[i + 1]] / b.m[tab[i]][tab[i + 1]]) / 100 + c.m[tab[i]];
	}
	else if (kryterium == "Czas") {
		for (int i = 0; i < limit - 1; i++)
			wynik += (b.m[tab[i]][tab[i + 1]] / a.m[tab[i]][tab[i + 1]]) / 100 + c.m[tab[i]];	// Zmiana spowodowana podmian¹ macierzy przy wywo³aniu metod nadrzêdnych
	}
	return wynik;
}

Matrix::~Matrix() {}
