/*
 * kolejka_tab.hh
 *
 *  Created on: 15 mar 2014
 *      Author: Mario
 */

#ifndef KOLEJKA_TAB_HH_
#define KOLEJKA_TAB_HH_

/*!
 * \brief Klasa modelujaca strukture koleki
 * 	Kolejka jest zbudowana w oparciu o liste.
 */
class kolejka_tab{
private:
	int *tab;
	int rozmiar_tab;
	int ilosc_el;
	int *o_ile;

	void powieksz();
	void pomniejsz();

public:

	kolejka_tab(){
			tab= new int[1];
			rozmiar_tab = 1;
			ilosc_el=0;
			o_ile=&rozmiar_tab;//domyslnie zwiekszam rozmiar tablicy podwojnie
							   //w tym celu musze sledzic rozmiar tablicy
			}
		kolejka_tab(int zwieksz){
			tab= new int[1];
			rozmiar_tab = 1;
			ilosc_el=0;
			o_ile=new int(zwieksz);//w tym wypadku podaje konkretna wartosc,
						   	   	   //o ktora bede zwiekszal rozmiar tablicy
		}


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







#endif /* KOLEJKA_TAB_HH_ */
