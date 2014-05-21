/*
 * hash.hh
 *
 *  Created on: 23 kwi 2014
 *      Author: Mario
 */

#ifndef HASH_HH_
#define HASH_HH_
#define ROZMIAR 10000
#include <string>
#include <list>

/*! \brief Struktura modeluj¹ca pare klucz-wartosc
 * */

typedef struct {
	std::string klucz;
	int wartosc;
}elem;

/*! \brief Klasa modelujaca tablice haszujaca z funkcja mieszajaca */
class tab_hash{
private:
	std::list< elem > tablica[ROZMIAR];
	/*!
	 * \brief Funkcja mieszajaca
	 * Dla podanego klucza zostaje wygenerowany indeks tablicy haszujacej
	 * \param klucz-klucz dla ktorego zostanie wygenerowany indeks
	 *	\return indeks dla zadanego klucza
	 */
	int hash(std::string klucz);
public:
	/*! \brief Metoda dodajaca pare klucz-wartosc do tablicy
	 * Dla klucza zostaje wygenerowany indeks tablicy, nastepnie para zostaje dodana pod ten indeks
	 * \param klucz-klucz do dodania
	 * \param wartosc-wartosc do dodania
	 *
	 */
	void dodaj(std::string klucz, int wartosc);
	/*! \brief Metoda pobiera wartosc spod zadanego klucza
	 * Generowany jest indeks tablicy i w liscie spod tego indeksu zostaje wyszukana zadana para
	 * \param klucz - klucz pary ktorej szukamy
	 * \return wartosc spod klucza
	 */
	int pobierz(std::string klucz);
	/*! \brief Metoda usuwa z tablicy pozycje o zadanym kluczu
	 * \param klucz - klucz ktory zostanie usuniety
	 * \return true - gdy klucz zostal usuniety \n
	 * 	false - gdy klucza nie znajeziono
	 */
	bool usun(std::string klucz);
	/*! \brief Metoda pomocnicza, sluzy do wypisania zawartosci tablicy
	 *
	 */
	void wypisz();

};


#endif /* HASH_HH_ */
