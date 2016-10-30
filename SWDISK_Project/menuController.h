#pragma once

#include "stdafx.h"
#include "Macierz.h"
#include "brute.h"
#include "randomSearch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <sstream>

using namespace std;

class Menu
{
private:
	Macierz m, a;
	bool wykonujPetle, komi_ist, sym;
	LARGE_INTEGER time;

public:

	Menu::Menu() {
		komi_ist = false;
	}

	float Menu::getFloat(string Message) {
		float result;
		while (true) {
			cout << Message << endl;
			cin >> result;
			if (cin.good())
				return result;
			cout << "Podano b³êdne dane!" << endl << "Proszê wpisaæ ponownie!" << endl;
			cin.sync();
			cin.clear();
		}
	}

	float Menu::getFloatRange(string Message, int min, int max) {
		float result;
		while (true) {
			cout << Message << endl;
			cin >> result;
			if (cin.good() && result >= min && result <= max)
				return result;
			cout << "Podano b³êdne dane!" << endl << "Proszê wpisaæ ponownie!" << endl;
			cout << "Liczba musi mieœciæ siê w zakresie (" << min << "," << max << ">" << endl;
			cin.sync();
			cin.clear();
		}
	}

	int Menu::getInt(string Message, int min, int max) {
		int result;
		while (true) {
			cout << Message << endl;
			cin >> result;
			if (cin.good() && result >= min && result <= max)
				return result;
			cout << "Podano b³êdne dane!" << endl << "Proszê wpisaæ ponownie!" << endl;
			cout << "Liczba musi mieœciæ siê w zakresie <" << min << "," << max << ">" << endl;
			cin.sync();
			cin.clear();
		}
	}

	bool Menu::getBool(string Message) {
		bool decision = false;
		string dec;

		while (true) {
			cout << Message << " [y/n] " << endl;
			cin >> dec;
			if (dec == "y" || dec == "Y" || dec == "yes" || dec == "YES" || dec == "t" || dec == "tak" || dec == "Yes" || dec == "T")
				return true;
			if (dec == "n" || dec == "N" || dec == "no" || dec == "NO" || dec == "No" || dec == "nO" || dec == "nie" || dec == "f")
				return false;
			cout << "B³êdna decyzja. Proszê spróbowaæ jescze raz...";
		}
	}

	LARGE_INTEGER Menu::startTimer()
	{
		LARGE_INTEGER start;
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&start);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		time = start;
		return time;
	}

	long double Menu::endTimer()
	{
		LARGE_INTEGER stop;
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&stop);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		return stop.QuadPart - time.QuadPart;
	}

	void Menu::gotoxy(const int x, const int y)	// Funkcja, która przestawia kursor konsoli w dowolne miejsce
	{
		COORD coord = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	bool Menu::isDataReady() {
		string decision;
		if (komi_ist)
			return true;
		else
		{
			system("CLS");
			cout << "Nie mo¿na u¿yæ tej opcji, poniewa¿ nie wczytano danych!" << endl << endl;
			cout << "Czy chcesz wylosowaæ te dane teraz? [y/n]";
			cin >> decision;
			if (decision == "y")
				return menuLosuj();
			system("pause");
			return false;
		}
	}

	int Menu::menuSelectMacierz() {
		string positions[] = { "Macierz symetryczna", "Macierz asymetryczna", "Powrót" };
		switch (displayMenu(positions, 3, "")) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return -1;
			break;
		default:
			system("CLS");
			cout << "Z³a decyzja, proszê spróbowaæ ponownie";
			cin.ignore();
			menuSelectMacierz();
			break;
		}
	}

	bool Menu::menuLosuj() {
		switch (menuSelectMacierz())
		{
		case 0:
			sym = true;
			system("cls");
			komi_ist = m.uzupelnienie(a, getInt("Podaj iloœæ miast: ", 2, 99999999), sym);
			break;
		case 1:
			sym = false;
			system("cls");
			komi_ist = m.uzupelnienie(a, getInt("Podaj iloœæ miast: ", 2, 99999999), sym);
			break;
		case -1:
			return false;
			break;
		}
		return true;
	}

	void Menu::wczytajzKlawiatury() {
		switch (menuSelectMacierz())
		{
		case 0:
			sym = true;
			if (komi_ist)
				m.usuwanie(a);
			komi_ist = m.uzupelnienieReczne(a, sym);
			break;
		case 1:
			sym = false;
			if (komi_ist)
				m.usuwanie(a);
			komi_ist = m.uzupelnienieReczne(a, sym);
			break;
		case -1:
			return;
			break;
		}
	}

	void Menu::displayMainMenu() {
		int decision = -1;
		Menu menu;
		brute *algorytmBrute;
		randomSearch *algorytmRandom;

		string footer = "   Zadanie :\tProjekt z SWDISK \n   Temat: \tSystem planowania wypraw motocyklowych po Europie \n   Autorzy : \tMateusz Walczak, Maciej Tymicki, Micha³ Ryng, Wojciech Matysiak";
		string names[10];
		names[0] = "Algorytm symulowanego wy¿arzania";
		names[1] = "Algorytm genetyczny";
		names[2] = "Algorytm brute force";
		names[3] = "Algorytm random search";
		names[4] = "Testy seryjne";
		names[5] = "Losowanie danych";
		names[6] = "Wczytaj z pliku";
		names[7] = "Wczytaj z klawiatury";
		names[8] = "Wyœwietl dane";
		names[9] = "Koniec";

		while (decision != 9) {
			decision = menu.displayMenu(names, 10, footer);
			switch (decision) {
			case 0:  // Algorytm symulowanego wyzarzania
				if (isDataReady()) {
					system("cls");
					m.algorytmWyzarzania(a, getFloat("Proszê podaæ temperaturê pocz¹tkow¹: "),
						getFloat("Proszê podaæ temperaturê koncow¹: "), true);
				}
				break;
			case 1:  // Algorytm genetyczny
				if (isDataReady()) {
					system("cls");
					m.algorytmGenetyczny(a, getInt("Proszê podaæ liczbê rozwi¹zañ wchodz¹cych w sk³ad populacji pocz¹tkowej: ", 1, 999999),
						getInt("Proszê podaæ iloœæ pokoleñ: ", 1, 999999),
						getFloatRange("Proszê podaæ prawdopodobieñstwo zajœcia mutacji: ", 0, 1),
						getInt("Proszê podaæ populacjê rodziców: ", 1, 999999),
						getInt("Proszê podaæ populacjê potomków: ", 1, 999999),
						getInt("Proszê podaæ iloœæ zamian w mutacji: ", 1, 999999),
						getFloatRange("Proszê podaæ prawdopodobieñstwo zajœcia krzy¿owania: ", 0, 1), true);
				}
				break;
			case 2:	// Algorytm brute force
				if (isDataReady()) {
					system("cls");
					algorytmBrute = new brute;
					algorytmBrute->przegladZupelny(a, true);
				}
				break;
			case 3: // Algorytm random search
				if (isDataReady()) {
					system("cls");
					algorytmRandom = new randomSearch;
					algorytmRandom->losowyWynik(a, getInt("Proszê podaæ iloœæ przetasowañ: ", 0, 999999), true);
				}
				break;
			case 4:	// Testy seryjne
				system("cls");
				seriesMenu();
				system("pause");
				break;
			case 5: // Losowanie danych
				menuLosuj();
				break;
			case 6: // Wczytaj z pliku"
				if (komi_ist)
					m.usuwanie(a);
				komi_ist = m.odczyt(a);
				break;
			case 7: // Wczytaj z klawiatury
				wczytajzKlawiatury();
				break;
			case 8: // Wyœwietl dane
				if (isDataReady()) {
					system("cls");
					cout << a;
					system("pause");
					cin.ignore();
				}
				break;
			case 9: // Koniec
				return;
				break;
				break;
			}
		}
	}

	void Menu::seriesMenu() {
		int series, repeats, startCity, endCity, generations = 0, population = 0, parentsPopulation = 0, childernPopulation = 0, swaps = 0, shuffling = 0;
		float tp = 0.0, tk = 0.0, mutation = 0.0, cross = 0.0;
		bool sym, useAnnealing, useGenetic, useBrute, useRandom;

		series = getInt("Proszê podaæ iloœæ serii: ", 1, 9999);
		repeats = getInt("Proszê podaæ iloœæ powtorzeñ: ", 1, 9999);
		startCity = getInt("Proszê podaæ pocz¹tkow¹ iloœæ miast: ", 2, 999999);
		endCity = getInt("Proszê podaæ koñcow¹ iloœæ miast: ", startCity, 99999);
		sym = getBool("Czy macierz ma byæ symetryczna?");

		useAnnealing = getBool("Czy uwzglêdniæ algorytm symulowanego wyrza¿ania? ");
		if (useAnnealing)
		{
			tp = getFloat("Proszê podaæ temperaturê pocz¹tkow¹ dla algorytmu symulowanego wyrza¿ania: ");
			tk = getFloat("Proszê podaæ temperaturê koñcow¹ dla algorytmu symulowanego wyrza¿ania: ");
		}

		useGenetic = getBool("Czy uwzglêdniæ algorytm genetyczny? ");
		if (useGenetic)
		{
			population = getInt("Proszê podaæ liczbê rozwi¹zañ wchodz¹cych w sk³ad populacji pocz¹tkowej: ", 1, 999999);
			generations = getInt("Proszê podaæ iloœæ pokoleñ: ", 1, 999999);
			mutation = getFloatRange("Proszê podaæ prawdopodobieñstwo zajœcia mutacji: ", 0, 1);
			parentsPopulation = getInt("Proszê podaæ populacjê rodziców: ", 1, 999999);
			childernPopulation = getInt("Proszê podaæ populacjê potomków: ", 1, 999999);
			swaps = getInt("Proszê podaæ iloœæ zamian w mutacji: ", 1, 999999);
			cross = getFloatRange("Proszê podaæ prawdopodobieñstwo zajœcia krzy¿owania: ", 0, 1);
		}

		useBrute = getBool("Czy uwzglêdniæ algorytm brute force? ");

		useRandom = getBool("Czy uwzglêdniæ algorytm random search? ");
		if (useRandom) {
			shuffling = getInt("Proszê podaæ iloœæ przetasowañ: ", 0, 999999);
		}

		seriesControler(series, repeats, startCity, endCity, sym, useAnnealing, useGenetic, tp, tk, generations, population, parentsPopulation, childernPopulation, mutation, swaps, cross, useBrute, useRandom, shuffling);
	}

	void Menu::seriesControler(int series, int repeats, int minCitys, int maxCitys, bool sym, bool useAnnealing, bool useGenetic, float tp, float tk, int generations, int population, int parentsPopulation, int childernPopulation, float mutation, int swaps, float cross, bool useBrute, bool useRandom, int shuffling) {
		brute *algorytmBrute;
		randomSearch *algorytmRandom;
		int result;
		long double tmpTime;
		stringstream csvData;
		string fileName;

		csvData << "seria;powtorzenie;ilosc miast;algorytm;wynik;czas" << endl;

		int cities = minCitys;
		for (int s = 0; s < series; s++) {
			m.uzupelnienie(a, cities, sym, false);
			cout << "Seria " << s + 1 << " (ilosc miast " << cities << "):" << endl;
			cities += (maxCitys - minCitys) / (series - 1);
			for (int r = 0; r < repeats; r++) {
				cout << r + 1 << "." << endl;

				if (useAnnealing) {
					startTimer();
					result = m.algorytmWyzarzania(a, tp, tk, false);
					tmpTime = endTimer();
					cout << "Algorytm symulowanego wyrza¿ania uzyska³ wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym symulowanego wyrza¿ania;" << result << ";" << tmpTime << endl;
				}

				if (useGenetic) {
					startTimer();
					result = m.algorytmGenetyczny(a, population, generations, mutation, parentsPopulation, childernPopulation, swaps, cross, false);
					tmpTime = endTimer();
					cout << "Algorytm genetyczny uzyska³ wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym genetyczny;" << result << ";" << tmpTime << endl;
				}

				if (useBrute) {
					algorytmBrute = new brute;
					startTimer();
					result = algorytmBrute->przegladZupelny(a, false);
					tmpTime = endTimer();
					cout << "Algorytm brute force uzyska³ wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "brute force;" << result << ";" << tmpTime << endl;
				}

				if (useRandom) {
					algorytmRandom = new randomSearch;
					startTimer();
					result = algorytmRandom->losowyWynik(a, shuffling, false);
					tmpTime = endTimer();
					cout << "Algorytm random search uzyska³ wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "random search;" << result << ";" << tmpTime << endl;
				}
			}
		}

		if (getBool("Czy zapisaæ dane do pliku?")) {
			cout << "Proszê podaæ nazwê pliku (bez rozszerzenia): ";
			cin >> fileName;
			fileName += ".csv";

			// Fizyczny zapis do pliku
			ofstream fileStram;
			fileStram.open(fileName, ios::out);
			fileStram << csvData.rdbuf();
			fileStram.close();

			cout << "Dane zosta³y zapisane..." << endl;
		}
	}

	int displayMenu(string names[], int numberOfElements, string footer) {
		int wybor1, wybor2;
		while (1)	// Menu w pêtli
		{
			wybor1 = 0;
			wybor2 = wybor1;
			wykonujPetle = true;
			system("CLS");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);	// Kolor
			gotoxy(3, 1);
			for (int i = 0; i < numberOfElements; i++) {
				gotoxy(3, i * 2 + 1);
				cout << names[i];
			}

			cout << "\n\n\n\n";
			cout << footer;
			while (wykonujPetle)
			{
				gotoxy(1, wybor1 * 2 + 1);	// Pisanie wskaŸnika
				cout << static_cast<char>('\u003E');	// Rodzaj wskaŸnika, np. 1 w nawiasie to emotikona
				wybor2 = wybor1;	// Czytanie klawiatury
				switch (_getch())
				{
				case 13:	// "Enter" akceptuje wybór
					return wybor1;
					break;
				case 224:	// Podwójny bufor, dla strza³ek
					switch (_getch())
					{
					case 72:	// Strza³ka w górê
						if (0 < wybor1)	// Zmiana po³o¿enia
							wybor1--;
						else
							wybor1 = numberOfElements - 1;	// Na wypadek przekroczenia rozmiaru menu
						break;
					case 80:	// Strza³ka w dó³
						if (wybor1 < numberOfElements - 1)	// Zmiana po³o¿enia
							wybor1++;
						else
							wybor1 = 0;	// Na wypadek przekroczenia rozmiaru menu
						break;
					}
					break;
				}
				gotoxy(1, wybor2 * 2 + 1);	//czyszczenie strza³ki wyboru
				cout << " ";
			}
		}
	}
};