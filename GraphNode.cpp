#include "GraphNode.h"

bool GraphNode::odczyt(GraphNode &a)
{
	// p - zwraca informacj� o utworzeniu macierzy, werfikacja - sprawdzenie poprawno�ci danych
	// reszta to zmienne pilnuj�ce ko�czenie etap�w pobierania danych z pliku
	bool p, weryfikacja = true, kontrola = true, pobieranie = true, uzupelnianie = true;
	char *cstr, *nast_token = NULL;
	string nazwa_pliku, znak_pom;
	// rozmiar - ilo�� znak�w w wierszu, j - zmienna interacyjna, check - ilo�� znak�w w wierszu bez spacji
	// poczatek - pocz�tek dynamicznie alokowanej tablicy zmiennych
	int rozmiar, j = 0, check, poczatek = 0;
	while (weryfikacja)	// Sprawdzenie poprawno�� wpisanych danych
	{
		system("CLS");
		cout << "Prosz� poda� nazw� pliku do odczytu z czasem odwiedzin miast\n(Nale�y poda� w postaci: nazwa_pliku.txt)" << endl;
		cin.sync();
		cin.clear();
		getline(cin, nazwa_pliku);
		ifstream potok;
		potok.open(nazwa_pliku, ios::in);
		if (potok.good())
		{
			weryfikacja = false;
			kontrola = true;
			while (kontrola)	// Sprawdzanie ilo�cie miast
			{
				getline(potok, znak_pom);
				rozmiar = znak_pom.length() + 1;
				cstr = new char[rozmiar];
				strcpy_s(cstr, rozmiar, znak_pom.c_str());
				znak_pom = strtok_s(cstr, " ", &nast_token);
				if (znak_pom == "DIMENSION:")	// Kryterium po kt�rym pozycja rozmiaru jest poznawana
				{
					znak_pom = strtok_s(NULL, " ", &nast_token);
					a.r = atoi(znak_pom.c_str());	// Konwersja string na int
					kontrola = false;
				}
				nast_token = NULL;
				delete[] cstr;
			}
			kontrola = true;
			a.m = new int[a.r];
			while (kontrola)	// Wczytywanie danych do macierzy
			{
				getline(potok, znak_pom);
				rozmiar = znak_pom.length() + 1;
				cstr = new char[rozmiar];
				strcpy_s(cstr, rozmiar, znak_pom.c_str());
				znak_pom = strtok_s(cstr, " ", &nast_token);
				if (znak_pom == "EDGE_WEIGHT_SECTION")	// Kryterium, po kt�rym rozpoczyna si� sekcja odleg�o�ci w pliku
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
							if (znak_pom[i] == ' ')	// Odejmowanie spacji od ilo�ci znak�w w wierszu
								check--;
						}
						cstr = new char[rozmiar];
						strcpy_s(cstr, rozmiar, znak_pom.c_str());
						while (pobieranie)
						{
							if (poczatek == 0)
								znak_pom = strtok_s(cstr, " ", &nast_token);	// Pozycja pierwsza
							else
								znak_pom = strtok_s(NULL, " ", &nast_token);	//Ka�da kolejna pozycja
							a.m[j] = atoi(znak_pom.c_str());
							poczatek++;
							j++;
							if (j == a.r)	// Warunek ko�cz�cy wiersz i pobieranie danych
								uzupelnianie = false;
							check = check - znak_pom.length();
							if (check == 1)
								pobieranie = false;
						}
						poczatek = 0;
						pobieranie = true;
						nast_token = NULL;
						delete[] cstr;
					}
					kontrola = false;
				}
			}
			cout << "Utworzono tablic� korzystaj�c z danych z pliku!" << endl;
			potok.close();
			system("pause");
			p = true;
		}
		else
		{
			cout << "Nie uda�o si� wykona� operacji!" << endl;
			cout << "Podano b��dne dane!" << endl << "Prosz� wpisa� ponownie!" << endl;
			potok.close();
			system("pause");
			p = false;
			cin.sync();
			cin.clear();
		}
	}
	return p;
}

bool GraphNode::uzupelnienie(GraphNode &a, int iloscMiast, bool display)
{
	bool p, weryfikacja = false;
	srand((unsigned)time(NULL));
	int max_czas = 11;	// Maksymalny losowany czas na odwiedziny miasta
	if (a.r) {
		a.usuwanie(a);
	}
	a.r = iloscMiast;

	a.m = new int[a.r];
	for (int i = 0; i < a.r; i++)	// Uzupelnienie tablicy zerami
		a.m[i] = 0;

	for (int i = 0; i < a.r; i++) // Losowanie wag
	{
		a.m[i] = rand() % max_czas + 4;	// Zakres od 4 do max_czas
	}

	if (display) {
		cout << endl << "\n\tWygenerowano tablic� czasu na odwiedziny w mie�cie!\n\n" << endl;
		system("pause");
	}

	p = true;
	return p;
}

bool GraphNode::uzupelnienieReczne(GraphNode &a, int iloscMiast)
{
	bool p, uzup = true, weryfikacja = false;
	int k = 0;
	if (a.r) {
		a.usuwanie(a);
	}
	a.r = iloscMiast;

	a.m = new int[a.r];
	p = true;
	for (int i = 0; i < a.r; i++)
		a.m[i] = 0;

	while (uzup)
	{
		weryfikacja = false;
		while (weryfikacja == false)	// Sprawdzenie poprawno�� wpisanych danych
		{
			system("CLS");
			cout << "Tablica czasu sp�dzonego w miestach:" << endl << endl;
			cout << a;
			cout << endl << endl << "Prosz� wpisa� warto�� w polu [" << k << "] tablicy: ";
			cin >> a.m[k];
			weryfikacja = cin.good();
			if (weryfikacja == false)
			{
				cout << "Podano b��dne dane!" << endl << "Prosz� wpisa� ponownie!" << endl;
				system("pause");
			}
			cin.sync();
			cin.clear();
		}
	}
	system("CLS");
	cout << "Tablica czasu sp�dzonego w miastach:" << endl << endl;
	cout << a;
	cout << "Dane wprowadzono prawid�owo" << endl << endl;
	system("pause");
	return p;
}

void GraphNode::usuwanie(GraphNode &a)
{
	delete a.m;
	a.r = NULL;
}

ostream& operator<<(ostream &wy, GraphNode &y)
{
	bool wiersz = true;
	wy << "   ";
	for (int i = 0; i < y.r; i++)
		wy << i << " ";
	wy << endl << "  ";
	for (int i = 0; i < y.r * 2; i++)
		wy << "_";
	wy << endl;
	wy << 0 << " |";
	for (int j = 0; j < y.r; j++)
	{
		wy << y.m[j] << " ";
	}
	wy << endl << endl << endl;
	return wy;
}

GraphNode::~GraphNode() {}
