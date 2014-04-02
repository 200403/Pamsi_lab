#include "kontener.hh"
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

/*!
 * \brief Klasa modelujaca g³owna czesc programu
 *
 * 	Klasa modeluje glowna czesc porgramu, ktorego zadaniem jest:
 * 	-wczytanie danych
 * 	-zmierzenie czasu dzialania algorytmu
 * 	-sprawdzenie poprawnosci tego algorytmu, majac oczekiwany wynik
 */
class Dzialanie{
private:
	//! Kontener typu Dane na dane wejsciowe
	Kontener kontener;
	int rozmiar;
	int p[100];

public:
	/*!
	 * \brief metoda wczytuje dane do tablicy znajdujacej sie w zmiennej wejscie.
	 *
	 * 	Format danych w pliku jest nastepujacy:
	 * 	pierwszy wiersz - ilosc elementow, a nastepnie w kolumnie kolejne wartosci tablicy.
	 * 	\param nazwaPliku - nazwa pliku do otwarcia
	 * 	\return void
	 */
	void wczytajDaneWejsciowe(string nazwa);


	/*!
	 * \brief Metoda uruchamia pomiar czasu
	 *
	 *  Czas jest mierzony w milisekundach
	 * 	\return czas, w ktorym zostal wlaczony stoper
	 */
	LARGE_INTEGER wlaczStoper();

	/*!
		 * \brief Metoda konczy pomiar czasu
		 *
		 *  Czas jest mierzony w milisekundach
		 * 	\return czas, w ktorym stoper zostal wylaczony
		 */
	LARGE_INTEGER wylaczStoper();

	/*!
		 * \brief Metoda wykonuje algorytm na danych wejsciowych ( tablicy)
		 *
		 * 	Algorytm do wykonania : pomnoz kazdy element razy 2.
		 *
		 * 	\return void
		 */
	void wykonajAlgorytm();

	/*!
		 * \brief Metoda sprawdza poprawnosc algorytmu
		 *
		 *	Wczytywane sa poprawne dane wynikowe, a nastepnie sa one porownywane z tymi
		 *	otrzymanymi przez wykonanie algorytmu
		 *
		 * 	\return 0 - gdy algorytm jest poprawny, -1 - gdy nie.
		 */
	bool sprawdz();

	/*!
			 * \brief Metoda wykonuje jednorazowy test algorytmu
			 * 	Metoda:
			 * 	-wlacza zegar
			 * 	-wykonuje algorytm
			 * 	-wylacza zegar
			 * 	-sprawdza poprawnosc algorytmu
			 * 	return czas wykonywania algorytmu w milisekundach
			 */
	int uruchom(string nazwa);

	/*!
	 * \brief Metoda implementuj¹ca sortowanie szybkie
	 * \param tab - wskaznik na tablice do posortowania
	 * \param lewy - indeks poczatku tablicy
	 * \param prawy - indeks konca tablicy
	 */
	void Quicksort( Kontener *tab, int lewy, int prawy );

	/*!
		 * \brief Metoda implementuj¹ca sortowanie przez kopcowanie
		 * \param tab - tablica do posortowania
		 * \return metoda zwraca posortowana tablice
		 */
	Kontener heap(Kontener tab);

	/*!
		 * \brief Metoda przywraca sturkturê kopca jesli ta zostala zaburzona
		 *
		 * \param kopiec - wskaznik na kopiec do uporzadkowania
		 *
		 *
		 */
	void uporzadkuj_kopiec(Kontener *kopiec);

	/*!
		 * \brief Metoda implementuj¹ca scalanie dwoch tablic
		 * 	Scalanie czyli laczenie dwoch posortowanych tablic w jedna(rowniez posortowana)
		 *
		 * \param lewy - element pierwszy
		 * \param prawy - element drugi
		 * \return metoda zwraca scalony zbior
		 */
	Kontener merge(Kontener lewy, Kontener prawy);

	/*!
		 * \brief Metoda implementuj¹ca sortowanie przez scalanie
		 * \param tab - tablica do posortowania
		 * \return metoda zwraca posortowana tablice
		 */
	Kontener MergeSort(Kontener tab);

	int wez_rozmiar(){
		return rozmiar;
	};

};


