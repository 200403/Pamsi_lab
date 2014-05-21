/*
 * stos.hh
 *
 *  Created on: 13 mar 2014
 *      Author: Mario
 */

#ifndef STOS_TAB_HH_
#define STOS_TAB_HH_
#include <iostream>
/*!
 * \brief Klasa modelujaca strukture stosu
 * 	Stos jest zbudowany w oparciu o tablice.
 */
class stos_tab{
private:
	int *tab;
	int rozmiar_tab;
	int ilosc_el;
	int *o_ile;

	/*!
		 * \brief Metoda zwieksza rozmiar tablicy gdy zostanie ona przepelniona.
		 * 	W przypadku gdy tablica jest pelna tworzymy nowa wieksza o 1 tablice.
		 * 	Elementy starej przepisujemy do nowej. Nastepnie stara mozna skasowac.
		 *
		 */
	void powiekszStos();
	void pomniejszStos();
public:

	stos_tab(){
		tab= new int[1];
		rozmiar_tab = 1;
		ilosc_el=0;
		o_ile=&rozmiar_tab;//domyslnie zwiekszam rozmiar tablicy podwojnie
						   //w tym celu musze sledzic rozmiar tablicy
		}
	stos_tab(int zwieksz){
		tab= new int[1];
		rozmiar_tab = 1;
		ilosc_el=0;
		o_ile=new int(zwieksz);//w tym wypadku podaje konkretna wartosc,
		   	   	   	   	   	   //o ktora bede zwiekszal rozmiar tablicy
	}


	/*!
	 * \brief Metoda dodajaca element na stos
	 * 	Metoda dodaje element na koniec tablicy.
	 * 	W przypadku gdy tablica jest pelna zostaje ona powiekszona o 1 element.
	 * 	\param element - element, ktory zostanie dodany do stosu
	 */
	void push(int element);

	/*!
		 * \brief Metoda usuwajaca element ze stos
		 * 	Metoda usuwa element znajdujacy sie na koncu tablicy.
		 * 	Z kazdorazowym pobraniem danych rozmiar tablicy jest zmniejszany o 1.
		 * 	\param a - wskaznik do zmiennej, do ktorej sciagamy wartosc.
		 */
	void pop(int *a);

	/*!
		 * \brief Metoda sprawdzajaca czy stos jest pusty.
		 * 	Metoda sprawdza czy stos jest pusty.
		 * 	Sprawdzenie polega na odczytaniu zmiennej rozmiar, \n
		 * 	ktora pamieta ile jest elementow na stosie
		 * 	\return true - rozmiar == 0 \n
		 * 	false - rozmiar > 0.
		 */
	bool isempty();

	/*!
		 * \brief Metoda zwracajaca rozmiar stosu
		 * 	Metoda zwraca rozmiar stosu.
		 * 	Rozmiar stosu przechowywany jest w zmiennej rozmiar.
		 * 	\return rozmiar stosu.
		 */
	int size();
	void wyswietl();
};


#endif /* STOS_HH_ */
