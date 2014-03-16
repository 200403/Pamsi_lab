#include <string>
#include <vector>
using namespace std;

/*!
 *\brief Klasa Dane
 *
 *	Klasa posiada 2 pola:
 *	-tablice (vector),
 *	-rozmiar tablicy.
 */
class Kontener{
private:
	vector <int> dane;
	unsigned int rozmiar;

public:

	/*!
	 * \brief Metoda zwracajaca rozmiar tablicy
	 * \return rozmiar tablicy
	 */
	unsigned int wez_rozmiar(){
		return rozmiar;
	}

	/*!
		 * \brief Metoda zwracajaca referencje do tablicy danych
		 * 	Metoda pozwala na dostep do tablicy i jej modyfikacje
		 * \return referencja do tablicy
		 */
	vector <int>& wez_dane(){
		return dane;
	}

	/*!
		 * \brief metoda wczytuje dane do tablicy z pliku
		 *
		 * 	Format danych w pliku jest nastepujacy:
		 * 	pierwszy wiersz - ilosc elementow, a nastepnie w kolumnie kolejne wartosci tablicy.
		 * 	\param nazwaPliku - nazwa pliku do otwarcia
		 * 	\return void
		 */
	void wczytajDane(string nazwaPliku);

	/*!
			 * \brief Metoda zamienia ze soba dwa elementy tablicy
			 * \param i,j - indeksy, ktore zostana zamienione
			 */
	void zamien_elementy(unsigned int i,unsigned int j);

	/*!
			 * \brief Metoda odwraca zawartosc tablicy
			 */
	void odwroc_kolejnosc();

	/*!
			 * \brief Metoda dodaje element na koniec tablicy
			 * \param e - wartosc elementu
			 */
	void dodaj_element(int e);

	/*!
			 * \brief Metoda dodaje na koniec tablicy zawartosc innej tablicy
			 * \param tablica, ktora bedzie dodana na koniec
			 */
	void dodaj_elementy(Kontener tab);

	/*!
			 * \brief Operator indeksujacy tablice
			 * \param index - indeks, ktorego referencja zostanie zwrocona
			 * \return referencja do zadanego indeksu
			 */
	int & operator [](int index);

	/*!
			 * \brief Operator dodawania tablic
			 * 	Operator pozwala na dodanie 2 tablic
			 * 	\param tablica do dodania
			 * \return dwie polaczone tablice
			 */
	Kontener& operator + (Kontener tab);

	/*!
			 * \brief Operator przypisania
			 * 	Operator pozwala na przypisanie do tablicy zawartosci innej tablicy
			 * \param tablica, ktora przypisujemy
			 */
	Kontener& operator = (Kontener tab);

	/*!
			 * \brief Operator porownania 2 tablic
			 *  Operator pozwala na porownanie 2 tablic.
			 *  Sprawdza on czy sa takie same pod wzgledem zawartosci.
			 *  \param tablica, z ktora bedziemy porownywac
			 *  \return true - tablice sa identyczne \n
			 *  false - tablice sa rozne
			 */
	bool operator == (Kontener tab);

	/*!
			 * \brief Operator wwypisywania
			 * 	Metoda pozwala na wypisanie zawartosci tablicy na standardowe wyjscie
			 *
			 */
	friend ostream & operator << (ostream& out, Kontener Tab);

};

