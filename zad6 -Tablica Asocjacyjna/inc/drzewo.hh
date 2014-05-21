/*
 * drzewo.hh
 *
 *  Created on: 10 kwi 2014
 *      Author: Mario
 */

#ifndef DRZEWO_HH_
#define DRZEWO_HH_
#include <vector>
#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>




using namespace std;

enum jakie_dziecko{ LEWY, PRAWY,KORZEN};



/*!
 * \brief Klasa modeluje pare klucz-wartosc, ktora jest podstawowym elementem tablicy asocjacyjnej
 * 	Zarówno typ Klucz jak i Wartosc musz¹ miec konstruktory parametryczne, ktore inicjuja ich wartosci.
 */
template <typename Wartosc> struct wezel{
	jakie_dziecko dziecko;
	string klucz;
	Wartosc dane;
	wezel *rodzic, *lewy, *prawy;

};

template < typename Wartosc> class Tab_asocjacyjna{
private:

	struct wezel<Wartosc> *korzen;
	int ilosc;
	/*! \brief Metoda znajduje najmniejsza wartosc klucza w poddrzewie ktorego korzeniem jest zadany wezel
	 * \param w - wezel, od ktorego zaczynamy szukac
	 * \return najmniejszy wezel w danym poddrzewie
	 */
	struct wezel<Wartosc>*  znajdzNajmniejszy(struct wezel<Wartosc>* w){
			if (w == NULL)
				return NULL;
			else{
				while(w->lewy != NULL){
					w=w->lewy;
				}
			}
			return w;
		}

	/*! \brief Metoda znajduje nastepnika danego wezla
	 * Nastepnik to element, ktory jest wartosc klucza jest kolejna wartoscia zaraz po kluczu z wezla zadanego
	 * \param w - wezel, od ktorego zaczynamy szukac
	 * \return nastepnik wezla zadanego
	 */
	struct wezel<Wartosc> * znajdzNastepnika(struct wezel<Wartosc> * w){
		struct wezel<Wartosc> *temp;
		if(w==NULL)
			return NULL;
		else if(w->prawy != NULL)
			return znajdzNajmniejszy(w->prawy);
		else{
			temp=w->rodzic;
			while(temp!=NULL and w == temp->prawy){
				w=temp;
				temp=w->rodzic;
			}
		}
		return temp;
	}

public:
	/*! \brief Meteoda dodaje pare klucz-warotsc do tablicy
	 * \param klucz
	 * \param wartosc
	 * 	 */
	Tab_asocjacyjna(){
		korzen=new struct wezel<Wartosc>;
		korzen->rodzic=NULL;
		korzen->lewy=NULL;
		korzen->prawy=NULL;
		korzen->dziecko=KORZEN;
		ilosc=0;
	}
	/*!
	 * \brief Metoda dodaje pare klucz-wartosc do drzewa
	 * 	W przypadku gdy dany klucz juz istnieje to wartosc, ktora jest z nim skojarzona zostaje zastapiona ta\n
	 * 	podana w argumencie "wartosc"
	 *
	 * 	\param [in] klucz-nazwa klucza
	 * 	\param [in] wartosc-wartosc do zapisania
	 */
	bool dodaj(std::string klucz,Wartosc wartosc);

	/*!
	 * \brief Metoda pobiera wartosc przypisana pod zadanym kluczem.
	 *
	 *  \param [in] klucz- nazwa klucza, ktorego szukamy
	 *  \return wartosc spod zadanego klucza
	 */
	Wartosc pobierz(std::string klucz) const;

	/*! \brief Metoda zmienia wartosc pod danym kluczem na ta zadana
	 *
	 */
	void zmien(string klucz,Wartosc wartosc){
		dodaj(klucz,wartosc);
	}


	/*!
	 *  \brief Metoda usuwa pozycje zawierajaca podany klucz.
	 *  \param [in] klucz-klucz do usuniecia
	 */
	bool usun(string klucz);

	/*! \brief Metoda zwraca informacje czy drzewo jest puste
	 * \return true gdy puste \n
	 * false gdy nie puste
	 */
	const bool czy_pusta(){
		return	korzen->lewy == NULL && korzen->prawy==NULL;
	}

	/*! \brief Metoda zwraca ilosc elementow na dzrzewie
	 * \return ilosc elementow
	 */
	const int rozmiar(){
		return ilosc;
	}

	/*! \brief Metoda pomocnicza, ktora wypisuje zawartosc drzewa
	 * 	Powstala w celach testowych
	 */
	void wypisz(string klucz){
		if(ilosc>0){
			struct wezel<Wartosc> *w=korzen; //wezel, w ktorym sie aktualnie znajdujemy
			while(true){
			if(w->klucz == klucz){
				break;
				}
			else if(w->klucz > klucz){
				w=w->lewy;
				}
			else{
				w=w->prawy;
				}
			}

			string nazwa= w->klucz;
			cout << "rodzic: " << nazwa << endl;
			if(w->lewy !=NULL){
			nazwa= w->lewy->klucz;
			cout << "lewy: " << nazwa << endl;}
			if(w->prawy !=NULL){
			nazwa= w->prawy->klucz;
			cout << "prawy: " << nazwa << endl;}

		}
	}
};


template < typename Wartosc >
bool Tab_asocjacyjna<Wartosc>::dodaj(string klucz, Wartosc wartosc){


	if(ilosc==0){ // gdy tablica jest pusta
		korzen->klucz=klucz;
		korzen->dane=wartosc;
		ilosc++;
	}
	else{
		struct wezel<Wartosc> *w=korzen; //wezel, w ktorym sie aktualnie znajdujemy
		while(true){
			if(w->klucz == klucz){
				w->dane=wartosc;
				break;
			}
			if(w->klucz > klucz){
				if(w->lewy == NULL){
					w->lewy=new struct wezel<Wartosc>;
					w->lewy->rodzic=w;
					w->lewy->lewy=NULL;
					w->lewy->prawy=NULL;
					w->lewy->klucz=klucz;
					w->lewy->dane=wartosc;
					w->lewy->dziecko=LEWY;
					ilosc++;
					break;
				}
				else
					w=w->lewy;
			}
			else if(w->klucz < klucz){
				if(w->prawy == NULL){
					w->prawy=new struct wezel<Wartosc>;
					w->prawy->rodzic=w;
					w->prawy->lewy=NULL;
					w->prawy->prawy=NULL;
					w->prawy->klucz=klucz;
					w->prawy->dane=wartosc;
					w->prawy->dziecko=PRAWY;
					ilosc++;
					break;
				}
				else
					w=w->prawy;
			}
		}
	}
	return true;
}

template <typename Wartosc>
Wartosc Tab_asocjacyjna<Wartosc>::pobierz(string klucz) const{
	//BRAK PRZYPADKU GDY KLUCZ NIE ISTNIEJE!!!!
	if(ilosc>0){
		struct wezel<Wartosc> *w=korzen; //wezel, w ktorym sie aktualnie znajdujemy
		while(true){
			if(w->klucz == klucz){
				return w->dane;
			}
			if(w->klucz > klucz){
				w=w->lewy;
			}
			else{
				w=w->prawy;
			}
		}
	}
}

template <typename Wartosc>
bool Tab_asocjacyjna<Wartosc>::usun(std::string klucz){
	if(ilosc>0){
		struct wezel<Wartosc> *w; //wezel, w ktorym sie aktualnie znajdujemy
		struct wezel<Wartosc> *usuwany =korzen;
		while(usuwany != NULL){
			if(usuwany->klucz == klucz){

				w=usuwany->rodzic;

				break;
			}
			if(usuwany->klucz > klucz){
				usuwany=usuwany->lewy;
			}
			else{
				usuwany=usuwany->prawy;
			}
		}
		//gdy usuwany element jest lisciem
		if(usuwany->lewy == NULL and usuwany->prawy == NULL){
			if(usuwany->dziecko == LEWY)
				w->lewy=NULL;
			else
				w->prawy=NULL;
			delete usuwany;
			ilosc--;
			return true;
		}
		//gdy usuwany element ma tylko lewe dziecko
		else if (usuwany->prawy == NULL){
			if(usuwany->dziecko == LEWY)
				w->lewy=usuwany->lewy;
			else
				w->prawy=usuwany->lewy;
			delete usuwany;
			ilosc--;
			return true;
		}
		//gdy usuwany element ma tylko prawe dziecko
		else if (usuwany->lewy == NULL){
			if(usuwany->dziecko == LEWY)
				w->lewy=usuwany->prawy;
			else
				w->prawy=usuwany->prawy;
			delete usuwany;
			ilosc--;
			return true;
		}
		else{
			w=znajdzNastepnika(usuwany);
			//zastepuje nastepnika jego prawym dzieckiem
			if(w->dziecko == LEWY)
				w->rodzic->lewy=w->prawy;
			else
				w->rodzic->prawy=w->prawy;

			//zastepuje usuwany element nastepnikiem
			if(usuwany == korzen)
				korzen=w;
			else if(usuwany->dziecko == LEWY)
				usuwany->rodzic->lewy=w;
			else
				usuwany->rodzic->prawy=w;
			w->lewy=usuwany->lewy;
			w->prawy=usuwany->prawy;
			w->rodzic=usuwany->rodzic;
			w->lewy->rodzic=w;
			w->prawy->rodzic=w;
			delete usuwany;
			ilosc--;
			return true;
		}
	}
	return false;
}



#endif /* DRZEWO_HH_ */
