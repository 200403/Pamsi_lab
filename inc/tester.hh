#include "dzialanie.hh"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*!
 * \brief Klasa Tester
 * 	Klasa modeluje narzedzie do benchmarkowania algorytmu.
 * 	Poprzez wielokrotne wynonywanie algorytmu mozemy wyciagnac sredni czas dzialania,
 * 	co jest dokladniejszym pomiarem.
 */
class Tester{
private:
	ofstream plik;
	int powtorzenia, ilosc;
	string wejscie;
public:

	/*!
	 * \brief konstruktor klasy
	 * Konstruktor inicjuje wartosci:
	 * -powtorzenia (ile razy wykonywac algorytm)
	 * -ilosc (ile mamy zestawow dancyh)
	 * -wejscie (nazwa pliku z danymi wejsciowymi)
	 * -wynik (nazwa pliku z poprawnym wynikiem algorytmu)
	 */
	Tester(){
		powtorzenia=5;
		ilosc=4;
		wejscie="wejscie0.txt";

	}

	/*!
	 * \brief Metoda otwierajaca referencje do pliku CSV
	 */
	void otworzPlik(string nazwa);
	/*!
		 * \brief Metoda otwierajaca referencje do pliku CSV
		 */
	void zamknijPlik();

	/*!
	 * \brief Metoda symulujaca badanie algorytmu
	 * Metoda wykonuje symulacje dzialania algorytmu.
	 * Wykonuje algorytm zadana liczbe razy dla zadanych zestawow danych.
	 * Wyniki zapisuje do pliku CSV o nazwie rezultat.csv
	 * Format zapisu: rozmiar_problemu,ilosc_powtorzen,sredni_czas
	 */
	void symulacja();

	/*!
	 *\brief Metoda aktualizuje nazwe plikow wejsciowych
	 *	Format plikow wejsciowych jest scisle okreslony.
	 *	Dane wejsciowe: wejscie%.txt, gdzie % to numer zestawu
	 *	Dane wynikowe: wynik%.txt, gdzie % to numer zestawu
	 *	Zestawy nalazy numerowac od 0.
	 *	\param numer - % zostaje zamieniony na wartosc 'numer'
	 */
	void zamienNazwy(int numer);

};
