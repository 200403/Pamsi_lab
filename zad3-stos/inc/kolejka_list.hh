/*
 * kolejka_list.hh
 *
 *  Created on: 13 mar 2014
 *      Author: Mario
 */

#ifndef KOLEJKA_LIST_HH_
#define KOLEJKA_LIST_HH_
#include <list>






/*!
 * \brief Klasa modelujaca strukture koleki
 * 	Kolejka jest zbudowana w oparciu o liste.
 */
class kolejka_list{
private:
	std::list<int> lista;
	std::list<int>::iterator iter;

public:


	/*!
	 * \brief Metoda dodajaca element na stos
	 * 	Metoda dodaje element na koniec listy.
	 * 	\param element - element, ktory zostanie dodany do stosu
	 */
	void enqueue(int element);

	/*!
		 * \brief Metoda usuwajaca element ze stos
		 * 	Metoda usuwa element znajdujacy sie na koncu listy.
		 * 	Gdy stos jest pusty, wyswietlony zostaje blad mowiacy
		 * 	ze brak danych do sciagniecia.
		 * 	\param a - wskaznik do zmiennej, do ktorej sciagamy wartosc.
		 */
	void dequeue(int *a);

	/*!
		 * \brief Metoda sprawdzajaca czy stos jest pusty.
		 * 	Metoda sprawdza czy stos jest pusty.
		 * 	\return lista.empty();
		 */
	bool isempty();

	/*!
		 * \brief Metoda zwracajaca rozmiar stosu
		 * 	Metoda zwraca rozmiar listy.
		 * 	\return rozmiar stosu.
		 */
	int size();
	void wyswietl();
};





#endif /* KOLEJKA_LIST_HH_ */
