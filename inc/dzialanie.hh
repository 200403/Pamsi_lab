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
	Kontener wejscie, temp, wynik;

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
	void wczytajWynik(string nazwa);

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
	int uruchom();

	/*!
	 * \brief Metoda zwracajaca rozmiar problemu
	 *
	 * \return rozmiar tablicy
	 */
	unsigned int wez_rozmiar(){
		return wejscie.wez_rozmiar();
	}
};
