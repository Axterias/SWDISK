#pragma once

#include "stdafx.h"
#include "Matrix.h"
#include "GraphNode.h"
#include "BruteForce.h"
#include "RandomSearch.h"
#include "SimulatedAnnealing.h"
#include "Genetic.h"
#include <Windows.h>
#include <conio.h>
#include <sstream>

using namespace std;

class Menu
{

private:
	Matrix m, t_droga, t_czas;
	GraphNode g, t_wezel;
	bool wykonujPetle, komi_ist, sym;
	int tmp, startPodrozy, czasPodrozy, ppt, maxCzasPodrozy, punktPoczatkowy;
	LARGE_INTEGER time;
	string const kryteria[3] = { "Droga","Czas","Punkty" };

public:

	Menu::Menu() {
		komi_ist = false;
		startPodrozy = 0;
		czasPodrozy = 0;
		ppt = 0;
		maxCzasPodrozy = 72;
		punktPoczatkowy = 0;
	}

	float Menu::getFloat(string Message) {
		float result;
		while (true) {
			cout << Message << endl;
			cin >> result;
			if (cin.good())
				return result;
			cout << "Podano b��dne dane!" << endl << "Prosz� wpisa� ponownie!" << endl;
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
			cout << "Podano b��dne dane!" << endl << "Prosz� wpisa� ponownie!" << endl;
			cout << "Liczba musi mie�ci� si� w zakresie (" << min << "," << max << ">" << endl;
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
			cout << "Podano b��dne dane!" << endl << "Prosz� wpisa� ponownie!" << endl;
			cout << "Liczba musi mie�ci� si� w zakresie <" << min << "," << max << ">" << endl;
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
			cout << "B��dna decyzja. Prosz� spr�bowa� jescze raz...";
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

	void Menu::gotoxy(const short int x, const short int y)	// Funkcja, kt�ra przestawia kursor konsoli w dowolne miejsce
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
			cout << "Nie mo�na u�y� tej opcji, poniewa� nie wczytano danych!" << endl << endl;
			cout << "Czy chcesz wylosowa� te dane teraz? [y/n]";
			cin >> decision;
			if (decision == "y")
				return menuLosuj();
			system("pause");
			return false;
		}
	}

	int Menu::menuSelectMacierz() {
		string positions[] = { "Macierz symetryczna", "Macierz asymetryczna", "Powr�t" };
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
			cout << "Z�a decyzja, prosz� spr�bowa� ponownie";
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
			if (komi_ist) {
				m.usuwanie(t_droga);
				m.usuwanie(t_czas);
				g.usuwanie(t_wezel);
			}
			tmp = getInt("Podaj ilo�� miast: ", 2, 99999999);
			komi_ist = m.uzupelnienie(t_droga, tmp, sym, false, true);
			m.uzupelnienie(t_czas, tmp, sym, true, true);
			g.uzupelnienie(t_wezel, tmp, true);
			break;
		case 1:
			sym = false;
			system("cls");
			if (komi_ist) {
				m.usuwanie(t_droga);
				m.usuwanie(t_czas);
				g.usuwanie(t_wezel);
			}
			tmp = getInt("Podaj ilo�� miast: ", 2, 99999999);
			komi_ist = m.uzupelnienie(t_droga, tmp, sym, false, true);
			m.uzupelnienie(t_czas, tmp, sym, true, true);
			g.uzupelnienie(t_wezel, tmp, true);
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
			system("cls");
			if (komi_ist) {
				m.usuwanie(t_droga);
				m.usuwanie(t_czas);
				g.usuwanie(t_wezel);
			}
			tmp = getInt("Podaj ilo�� miast: ", 2, 99999999);
			komi_ist = m.uzupelnienieReczne(t_droga, tmp, sym, false);
			m.uzupelnienieReczne(t_czas, tmp, sym, true);
			g.uzupelnienieReczne(t_wezel, tmp);
			break;
		case 1:
			sym = false;
			system("cls");
			if (komi_ist) {
				m.usuwanie(t_droga);
				m.usuwanie(t_czas);
				g.usuwanie(t_wezel);
			}
			tmp = getInt("Podaj ilo�� miast: ", 2, 99999999);
			komi_ist = m.uzupelnienieReczne(t_droga, tmp, sym, false);
			m.uzupelnienieReczne(t_czas, tmp, sym, true);
			g.uzupelnienieReczne(t_wezel, tmp);
			break;
		case -1:
			return;
			break;
		}
	}

	void Menu::ustawCzasPodrozy() {
		string positions[] = { "Zmie� czas trwania wycieczki","Zmie� miejsce rozpocz�cia wycieczki", "Powr�t" };
		string footer = "\tCzas trwania wycieczki : " + to_string(maxCzasPodrozy) + " [h]\n\tMiejsce rozpocz�cia wycieczki: " + to_string(punktPoczatkowy);
		switch (displayMenu(positions, 3, footer)) {
		case 0:
			system("cls");
			maxCzasPodrozy = getInt("Podaj nowy czas trwania wycieczki: ", 2, 99999999);
			ustawCzasPodrozy();
			break;
		case 1:
			if (isDataReady()) {
				system("cls");
				punktPoczatkowy = getInt("Podaj miejsce rozpocz�cia wycieczki: ", 0, t_droga.r - 1);
			}
			ustawCzasPodrozy();
			break;
		case 2:
			break;
		}
	}

	void Menu::zmienKryterium() {
		string positions[] = { "Droga", "Czas", "Punkty", "Powr�t" };
		switch (displayMenu(positions, 4, "\tObecnie wybrane kryterium: " + kryteria[ppt])) {
		case 0:
			ppt = 0;
			zmienKryterium();
			break;
		case 1:
			ppt = 1;
			zmienKryterium();
			break;
		case 2:
			ppt = 2;
			zmienKryterium();
			break;
		case 3:
			break;
		}
	}

	void Menu::displayMainMenu() {
		int decision = -1;
		Menu menu;
		SimulatedAnnealing *algorytmSimulatedAnnealing;
		Genetic *algorytmGenetic;
		BruteForce *algorytmBrute;
		RandomSearch *algorytmRandom;

		string footer = "   Zadanie :\tProjekt z SWDiSK\tTemat: \tSystem planowania wypraw motocyklowych po Europie \n   Autorzy : \tMateusz Walczak, Maciej Tymicki, Micha� Ryng, Wojciech Matysiak";
		string names[12];
		names[0] = "Algorytm symulowanego wy�arzania";
		names[1] = "Algorytm genetyczny";
		names[2] = "Algorytm brute force";
		names[3] = "Algorytm random search";
		names[4] = "Testy seryjne";
		names[5] = "Losowanie danych";
		names[6] = "Wczytaj z pliku";
		names[7] = "Wczytaj z klawiatury";
		names[8] = "Wy�wietl dane";
		names[9] = "Zmie� kryterium";
		names[10] = "Czas trwania wycieczki i miejsce";
		names[11] = "Koniec";

		while (decision != 11) {
			decision = menu.displayMenu(names, 12, footer);
			switch (decision) {
			case 0:  // Algorytm symulowanego wyzarzania
				if (isDataReady()) {
					system("cls");
					algorytmSimulatedAnnealing = new SimulatedAnnealing;
					if (ppt == 0 || ppt == 2) {
						algorytmSimulatedAnnealing->algorytmWyzarzania(t_droga, t_czas, t_wezel, getFloat("Prosz� poda� temperatur� pocz�tkow�: "),
							getFloat("Prosz� poda� temperatur� koncow�: "), maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
					else if (ppt == 1) {
						algorytmSimulatedAnnealing->algorytmWyzarzania(t_czas, t_droga, t_wezel, getFloat("Prosz� poda� temperatur� pocz�tkow�: "),
							getFloat("Prosz� poda� temperatur� koncow�: "), maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
				}
				break;
			case 1:  // Algorytm genetyczny
				if (isDataReady()) {
					system("cls");
					algorytmGenetic = new Genetic;
					if (ppt == 0 || ppt == 2) {
						algorytmGenetic->algorytmGenetyczny(t_droga, t_czas, t_wezel, getInt("Prosz� poda� liczb� rozwi�za� wchodz�cych w sk�ad populacji pocz�tkowej: ", 1, 999999),
							getInt("Prosz� poda� ilo�� pokole�: ", 1, 999999),
							getFloatRange("Prosz� poda� prawdopodobie�stwo zaj�cia mutacji: ", 0, 1),
							getInt("Prosz� poda� populacj� rodzic�w: ", 1, 999999),
							getInt("Prosz� poda� populacj� potomk�w: ", 1, 999999),
							getInt("Prosz� poda� ilo�� zamian w mutacji: ", 1, 999999),
							getFloatRange("Prosz� poda� prawdopodobie�stwo zaj�cia krzy�owania: ", 0, 1), maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
					else if (ppt == 1) {
						algorytmGenetic->algorytmGenetyczny(t_czas, t_droga, t_wezel, getInt("Prosz� poda� liczb� rozwi�za� wchodz�cych w sk�ad populacji pocz�tkowej: ", 1, 999999),
							getInt("Prosz� poda� ilo�� pokole�: ", 1, 999999),
							getFloatRange("Prosz� poda� prawdopodobie�stwo zaj�cia mutacji: ", 0, 1),
							getInt("Prosz� poda� populacj� rodzic�w: ", 1, 999999),
							getInt("Prosz� poda� populacj� potomk�w: ", 1, 999999),
							getInt("Prosz� poda� ilo�� zamian w mutacji: ", 1, 999999),
							getFloatRange("Prosz� poda� prawdopodobie�stwo zaj�cia krzy�owania: ", 0, 1), maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
				}
				break;
			case 2:	// Algorytm brute force
				if (isDataReady()) {
					system("cls");
					algorytmBrute = new BruteForce;
					if (ppt == 0 || ppt == 2) {
						algorytmBrute->przegladZupelny(t_droga, t_czas, t_wezel, maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
					else if (ppt == 1) {
						algorytmBrute->przegladZupelny(t_czas, t_droga, t_wezel, maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
				}
				break;
			case 3: // Algorytm random search
				if (isDataReady()) {
					system("cls");
					algorytmRandom = new RandomSearch;
					if (ppt == 0 || ppt == 2) {
						algorytmRandom->losowyWynik(t_droga, t_czas, t_wezel, getInt("Prosz� poda� ilo�� przetasowa�: ", 0, 999999), maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
					else if (ppt == 1) {
						algorytmRandom->losowyWynik(t_czas, t_droga, t_wezel, getInt("Prosz� poda� ilo�� przetasowa�: ", 0, 999999), maxCzasPodrozy, punktPoczatkowy, kryteria[ppt], true);
					}
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
				if (komi_ist) {
					m.usuwanie(t_droga);
					m.usuwanie(t_czas);
					g.usuwanie(t_wezel);
				}
				komi_ist = m.odczyt(t_droga, false);
				m.odczyt(t_czas, true);
				g.odczyt(t_wezel);
				break;
			case 7: // Wczytaj z klawiatury
				wczytajzKlawiatury();
				break;
			case 8: // Wy�wietl dane
				if (isDataReady()) {
					system("cls");
					cout << "Odleg�o�ci pomi�dzy miastami w macierzy s�siedztwa z uzupe�nionymi wagami (w metrach):" << endl << endl << endl;
					cout << t_droga;
					cout << "Czas podr�y pomi�dzy miastami w macierzy s�siedztwa z uzupe�nionymi wagami (w minutach):" << endl << endl << endl;
					cout << t_czas;
					cout << "Czas potrzebny na odwiedziny miasta (w godzinach):" << endl << endl << endl;
					cout << t_wezel;
					system("pause");
					cin.ignore();
				}
				break;
			case 9: // Zmiana dominuj�cego kryterium
				zmienKryterium();
				break;
			case 10:
				ustawCzasPodrozy();
				break;
			case 11: // Koniec
				return;
				break;
			}
		}
	}

	void Menu::seriesMenu() {
		int series, repeats, startCity, endCity, generations = 0, population = 0, parentsPopulation = 0, childernPopulation = 0, swaps = 0, shuffling = 0;
		float tp = 0.0, tk = 0.0, mutation = 0.0, cross = 0.0;
		bool sym, useAnnealing, useGenetic, useBrute, useRandom;

		series = getInt("Prosz� poda� ilo�� serii: ", 1, 9999);
		repeats = getInt("Prosz� poda� ilo�� powtorze�: ", 1, 9999);
		startCity = getInt("Prosz� poda� pocz�tkow� ilo�� miast: ", 2, 999999);
		endCity = getInt("Prosz� poda� ko�cow� ilo�� miast: ", startCity, 99999);
		sym = getBool("Czy macierz ma by� symetryczna?");

		useAnnealing = getBool("Czy uwzgl�dni� algorytm symulowanego wyrza�ania? ");
		if (useAnnealing)
		{
			tp = getFloat("Prosz� poda� temperatur� pocz�tkow� dla algorytmu symulowanego wyrza�ania: ");
			tk = getFloat("Prosz� poda� temperatur� ko�cow� dla algorytmu symulowanego wyrza�ania: ");
		}

		useGenetic = getBool("Czy uwzgl�dni� algorytm genetyczny? ");
		if (useGenetic)
		{
			population = getInt("Prosz� poda� liczb� rozwi�za� wchodz�cych w sk�ad populacji pocz�tkowej: ", 1, 999999);
			generations = getInt("Prosz� poda� ilo�� pokole�: ", 1, 999999);
			mutation = getFloatRange("Prosz� poda� prawdopodobie�stwo zaj�cia mutacji: ", 0, 1);
			parentsPopulation = getInt("Prosz� poda� populacj� rodzic�w: ", 1, 999999);
			childernPopulation = getInt("Prosz� poda� populacj� potomk�w: ", 1, 999999);
			swaps = getInt("Prosz� poda� ilo�� zamian w mutacji: ", 1, 999999);
			cross = getFloatRange("Prosz� poda� prawdopodobie�stwo zaj�cia krzy�owania: ", 0, 1);
		}

		useBrute = getBool("Czy uwzgl�dni� algorytm brute force? ");

		useRandom = getBool("Czy uwzgl�dni� algorytm random search? ");
		if (useRandom) {
			shuffling = getInt("Prosz� poda� ilo�� przetasowa�: ", 0, 999999);
		}

		seriesControler(series, repeats, startCity, endCity, sym, useAnnealing, useGenetic, tp, tk, generations, population, parentsPopulation, childernPopulation, mutation, swaps, cross, useBrute, useRandom, shuffling);
	}

	void Menu::seriesControler(int series, int repeats, int minCitys, int maxCitys, bool sym, bool useAnnealing, bool useGenetic, float tp, float tk, int generations, int population, int parentsPopulation, int childernPopulation, float mutation, int swaps, float cross, bool useBrute, bool useRandom, int shuffling) {
		SimulatedAnnealing *algorytmSimulatedAnnealing;
		Genetic *algorytmGenetic;
		BruteForce *algorytmBrute;
		RandomSearch *algorytmRandom;
		int result;
		long double tmpTime;
		stringstream csvData;
		string fileName;

		csvData << "seria;powtorzenie;ilosc miast;algorytm;wynik;czas;kryterium" << endl;

		int cities = minCitys;
		for (int s = 0; s < series; s++) {
			m.uzupelnienie(t_droga, cities, sym, false, false);
			m.uzupelnienie(t_czas, cities, sym, true, false);
			g.uzupelnienie(t_wezel, cities, false);
			cout << "Seria " << s + 1 << " (ilosc miast " << cities << "):" << endl;
			cities += (maxCitys - minCitys) / (series - 1);
			for (int r = 0; r < repeats; r++) {
				cout << r + 1 << "." << endl;

				if (useAnnealing) {
					algorytmSimulatedAnnealing = new SimulatedAnnealing;
					startTimer();
					result = algorytmSimulatedAnnealing->algorytmWyzarzania(t_droga, t_czas, t_wezel, tp, tk, maxCzasPodrozy, punktPoczatkowy, kryteria[0], false);
					tmpTime = endTimer();
					cout << "Algorytm symulowanego wyrza�ania uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym symulowanego wyrza�ania;" << result << ";" << tmpTime << ";" << kryteria[0] << endl;
				}

				if (useAnnealing) {
					algorytmSimulatedAnnealing = new SimulatedAnnealing;
					startTimer();
					result = algorytmSimulatedAnnealing->algorytmWyzarzania(t_czas, t_droga, t_wezel, tp, tk, maxCzasPodrozy, punktPoczatkowy, kryteria[1], false);
					tmpTime = endTimer();
					cout << "Algorytm symulowanego wyrza�ania uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym symulowanego wyrza�ania;" << result << ";" << tmpTime << ";" << kryteria[1] << endl;
				}

				if (useAnnealing) {
					algorytmSimulatedAnnealing = new SimulatedAnnealing;
					startTimer();
					result = algorytmSimulatedAnnealing->algorytmWyzarzania(t_droga, t_czas, t_wezel, tp, tk, maxCzasPodrozy, punktPoczatkowy, kryteria[2], false);
					tmpTime = endTimer();
					cout << "Algorytm symulowanego wyrza�ania uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym symulowanego wyrza�ania;" << result << ";" << tmpTime << ";" << kryteria[2] << endl;
				}

				if (useGenetic) {
					algorytmGenetic = new Genetic;
					startTimer();
					result = algorytmGenetic->algorytmGenetyczny(t_droga, t_czas, t_wezel, population, generations, mutation, parentsPopulation, childernPopulation, swaps, cross, maxCzasPodrozy, punktPoczatkowy, kryteria[0], false);
					tmpTime = endTimer();
					cout << "Algorytm genetyczny uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym genetyczny;" << result << ";" << tmpTime << ";" << kryteria[0] << endl;
				}

				if (useGenetic) {
					algorytmGenetic = new Genetic;
					startTimer();
					result = algorytmGenetic->algorytmGenetyczny(t_czas, t_droga, t_wezel, population, generations, mutation, parentsPopulation, childernPopulation, swaps, cross, maxCzasPodrozy, punktPoczatkowy, kryteria[1], false);
					tmpTime = endTimer();
					cout << "Algorytm genetyczny uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym genetyczny;" << result << ";" << tmpTime << ";" << kryteria[1] << endl;
				}

				if (useGenetic) {
					algorytmGenetic = new Genetic;
					startTimer();
					result = algorytmGenetic->algorytmGenetyczny(t_droga, t_czas, t_wezel, population, generations, mutation, parentsPopulation, childernPopulation, swaps, cross, maxCzasPodrozy, punktPoczatkowy, kryteria[2], false);
					tmpTime = endTimer();
					cout << "Algorytm genetyczny uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "algorym genetyczny;" << result << ";" << tmpTime << ";" << kryteria[2] << endl;
				}

				if (useBrute) {
					algorytmBrute = new BruteForce;
					startTimer();
					result = algorytmBrute->przegladZupelny(t_droga, t_czas, t_wezel, maxCzasPodrozy, punktPoczatkowy, kryteria[0], false);
					tmpTime = endTimer();
					cout << "Algorytm brute force uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "brute force;" << result << ";" << tmpTime << ";" << kryteria[0] << endl;
				}

				if (useBrute) {
					algorytmBrute = new BruteForce;
					startTimer();
					result = algorytmBrute->przegladZupelny(t_czas, t_droga, t_wezel, maxCzasPodrozy, punktPoczatkowy, kryteria[1], false);
					tmpTime = endTimer();
					cout << "Algorytm brute force uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "brute force;" << result << ";" << tmpTime << ";" << kryteria[1] << endl;
				}

				if (useBrute) {
					algorytmBrute = new BruteForce;
					startTimer();
					result = algorytmBrute->przegladZupelny(t_droga, t_czas, t_wezel, maxCzasPodrozy, punktPoczatkowy, kryteria[2], false);
					tmpTime = endTimer();
					cout << "Algorytm brute force uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "brute force;" << result << ";" << tmpTime << ";" << kryteria[2] << endl;
				}

				if (useRandom) {
					algorytmRandom = new RandomSearch;
					startTimer();
					result = algorytmRandom->losowyWynik(t_droga, t_czas, t_wezel, shuffling, maxCzasPodrozy, punktPoczatkowy, kryteria[0], false);
					tmpTime = endTimer();
					cout << "Algorytm random search uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "random search;" << result << ";" << tmpTime << ";" << kryteria[0] << endl;
				}

				if (useRandom) {
					algorytmRandom = new RandomSearch;
					startTimer();
					result = algorytmRandom->losowyWynik(t_czas, t_droga, t_wezel, shuffling, maxCzasPodrozy, punktPoczatkowy, kryteria[1], false);
					tmpTime = endTimer();
					cout << "Algorytm random search uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "random search;" << result << ";" << tmpTime << ";" << kryteria[1] << endl;
				}

				if (useRandom) {
					algorytmRandom = new RandomSearch;
					startTimer();
					result = algorytmRandom->losowyWynik(t_droga, t_czas, t_wezel, shuffling, maxCzasPodrozy, punktPoczatkowy, kryteria[2], false);
					tmpTime = endTimer();
					cout << "Algorytm random search uzyska� wynik " << result << " w czasie : " << tmpTime << endl;
					csvData << s + 1 << ";" << r + 1 << ";" << cities << ";" << "random search;" << result << ";" << tmpTime << ";" << kryteria[2] << endl;
				}
			}
		}

		if (getBool("Czy zapisa� dane do pliku?")) {
			cout << "Prosz� poda� nazw� pliku (bez rozszerzenia): ";
			cin >> fileName;
			fileName += ".csv";

			// Fizyczny zapis do pliku
			ofstream fileStram;
			fileStram.open(fileName, ios::out);
			fileStram << csvData.rdbuf();
			fileStram.close();

			cout << "Dane zosta�y zapisane..." << endl;
		}
	}

	int displayMenu(string names[], int numberOfElements, string footer) {
		int wybor1, wybor2;
		while (1)	// Menu w p�tli
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
				gotoxy(1, wybor1 * 2 + 1);	// Pisanie wska�nika
				cout << static_cast<char>('\u003E');	// Rodzaj wska�nika, np. 1 w nawiasie to emotikona
				wybor2 = wybor1;	// Czytanie klawiatury
				switch (_getch())
				{
				case 13:	// "Enter" akceptuje wyb�r
					return wybor1;
					break;
				case 224:	// Podw�jny bufor, dla strza�ek
					switch (_getch())
					{
					case 72:	// Strza�ka w g�r�
						if (0 < wybor1)	// Zmiana po�o�enia
							wybor1--;
						else
							wybor1 = numberOfElements - 1;	// Na wypadek przekroczenia rozmiaru menu
						break;
					case 80:	// Strza�ka w d�
						if (wybor1 < numberOfElements - 1)	// Zmiana po�o�enia
							wybor1++;
						else
							wybor1 = 0;	// Na wypadek przekroczenia rozmiaru menu
						break;
					}
					break;
				}
				gotoxy(1, wybor2 * 2 + 1);	//czyszczenie strza�ki wyboru
				cout << " ";
			}
		}
	}

};
