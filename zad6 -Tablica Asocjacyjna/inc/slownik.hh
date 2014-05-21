/*
 * slownik.hh
 *
 *  Created on: 3 kwi 2014
 *      Author: Mario
 */

#ifndef SLOWNIK_HH_
#define SLOWNIK_HH_
#include <vector>
#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>




using namespace std;




/*!
 * \brief Klasa modeluje pare klucz-wartosc, ktora jest podstawowym elementem tablicy asocjacyjnej
 * 	Zarówno typ Klucz jak i Wartosc musz¹ miec konstruktory parametryczne, ktore inicjuja ich wartosci.
 */
template <typename Wartosc> class Para{
private:

	std::string key;
	Wartosc val;
public:
	/*! \brief Konstruktor inicjujacy wartosci key i val*/
	Para():key(),val(){};
	/*! \brief Konstruktor inicjujacy wartosci key i val*/
	Para(const std::string & key):key(key){};
	/*! \brief Konstruktor inicjujacy wartosci key i val*/
	Para(const std::string & key, const Wartosc & val):key(key),val(val){};

	/*! \brief Metoda zwraca referencje do pola key, dzieki niej mozemy modyfikowac jego wartosc
	 * \return referencja do pola key
	 */
    std::string & klucz() {
       return key;
    }
    /*! \brief Metoda zwraca referencje do pola val, dzieki niej mozemy modyfikowac jego wartosc
    	 * \return referencja do pola val
    	 */
    Wartosc & wartosc() {

       return val;
    }
    /*! \brief Metoda zwraca wartosc pola key, sluzy ona do odczytu tej wartosci
    	 * \return wartosc pola key
    	 */
    const std::string & klucz() const {
       return key;
    }
    /*! \brief Metoda zwraca wartosc pola val, sluzy ona do odczytu tej wartosci
      	 * \return wartosc pola val
      	 */
    const Wartosc & wartosc() const {
       return val;
    }

};


/*!
 * \brief Klasa modeluje pojecie tablicy asocjacyjnej
 * 	Tablica asocjacyjna jest to tablica, w ktorej do wartosci mozemy sie odwolywac poprzez klucze.
 * 	Odwolanie poprez indeks rowniez jest mozliwe.
 */
template < typename Wartosc> class Tablica_asocjacyjna{
private:
	typename std::vector< Para<Wartosc> > Dane;
	bool czy_istnieje;/*! \val zmienna pomocnicza, ktora sluzy do okreslania czy wartosc o podanym kluczu \n
	znajduje sie w zbiorze */

public:
	/*! \brief Meteoda dodaje pare klucz-warotsc do tablicy
	 * \param klucz
	 * \param wartosc
	 * 	 */
	Tablica_asocjacyjna(){
		czy_istnieje=true;
	}
	/*!
	 * \brief Metoda dodaje pare klucz-wartosc do tablicy
	 * 	W przypadku gdy dany klucz juz istnieje to wartosc, ktora jest z nim skojarzona zostaje zastapiona ta\n
	 * 	podana w argumencie "wartosc"
	 * 	Po kazdorazowym dodaniu nowego klucza, tablica jest sortrowana alfabetycznie wzgledem nazw kluczy.
	 * 	Takie rozwiazanie daje mozliwosc przeszukiwania binarnego co powoduje ze dostep do elementu
	 * 	jest w czasie logn.
	 * 	\param [in] klucz-nazwa klucza
	 * 	\param [in] wartosc-wartosc do zapisania
	 */
	void dodaj(std::string klucz,Wartosc wartosc);

	/*!
	 * \brief Metoda pobiera wartosc przypisana pod zadanym kluczem.
	 *
	 *  Jesli klucz nie istnieje to flaga czy_istnieje jest ustawiana na false, w przeciwnym wypadku ma ona wartosc true.
	 *  Po wywolaniu metody "pobierz" mozna sprawdzic stan flagi metoda czy_znalazlo() i jego podstawie okreslic\n
	 *  czy operacja zostala wykonana poprawnie.
	 *  \param [in] klucz- nazwa klucza, ktorego szukamy
	 *  \return wartosc spod zadanego klucza
	 */

	void zmien(string klucz,Wartosc wartosc){
		dodaj(klucz,wartosc);
	}
	Wartosc pobierz(std::string klucz);

	/*!
	 *  \brief Metoda usuwa pozycje zawierajaca podany klucz.
	 *  Gdy klucz istnieje, to jest usuwany, a flaga czy_istnieje ustawiana na wartosc true, przeciwnie flaga ma wartosc false.
	 *  \param [in] klucz-klucz do usuniecia
	 */
	void usun(string klucz);

	/*!
	 * \brief Metoda znajduje pozycje(nazwe klucza), pod ktora znajduje sie podana wartosc
	 * \return gdy wartosc istnieje: nazwa klucza, \n
	 * 		   gdy nie istnieje: pusta zmienna string
	 */
	string znajdz(Wartosc wartosc);

	/*!
	 * \brief Metoda zwraca stan flagi czy_istnieje.
	 * Flaga czy istnieje jest ustawiana za kazdym razem gdy wykonujemy funkcje, ktora przeszukuje tablice po kluczach.
	 * Gdy zadany klucz istnieje to flaga jest ustawiana. Natomiast gdy danego klucza nie ma w zbiorze to flaga jest zerowana
	 * \return true - zadany klucz istnieje w zbiorze \n
	 * 		   false - klucz nie istnieje.
	 */
	const bool czy_znalazlo() const {
		return czy_istnieje;
	}

	const bool czy_pusta(){
		return Dane.is_empty();
	}

	const int rozmiar(){
		return Dane.size();
	}

	 Wartosc operator [] (string klucz) const {
		 Wartosc war=pobierz(klucz);
	       return war;
	    }
	 Wartosc & operator [] (string klucz) {
		 assert(Dane.size()>0);//jesli tablica nie zawiera zadnego elementu
		 	czy_istnieje=false; // domyslnie zakladam ze klucza nie ma w zbiorze
		 	//przeszukiwanie binarne
		 	int poczatek=0;
		 	int koniec=Dane.size()-1;
		 	int srodek=koniec/2;
		 	string temp=Dane[srodek].klucz(); // zmienna przechowuje nazwe klucza z indeksu srodek

		 	do{
		 		temp=Dane[srodek].klucz();
		 		if(temp.compare(klucz) == 0){ // jesli klucz istnieje w zbiorze
		 			czy_istnieje=true;
		 			return  ( Dane[srodek].wartosc() );
		 	    }
		 		else{
		 			if(temp.compare(klucz) < 0){//jesli k jest alfabetycznie dalej od temp
		 				poczatek=srodek;
		 				srodek=(koniec+1-poczatek)/2+poczatek;
		 			}
		 			else if(temp.compare(klucz)>0){ // jesli k jest alfabetycznie blizej niz temp
		 				koniec=srodek;
		 				srodek=(koniec-poczatek)/2;

		 			}
		 		}
		 	}while(koniec-poczatek>0);
	 	    }

};

template < typename Wartosc >
void Tablica_asocjacyjna<Wartosc>::dodaj(std::string klucz, Wartosc wartosc){
	Para<Wartosc> para(klucz,wartosc);
	int licz=0;
	if(Dane.size()==0) {// gdy tablica jest pusta
		cout << "1" << endl;
		Dane.push_back(para);}
	else{
		typename std::vector< Para<Wartosc> >::iterator it,koniec;
		it=Dane.begin();
		koniec=Dane.end();
		koniec--;

		// przypadek gdy musimy dodaj na koniec listy
		//if(para.klucz().compare(koniec->klucz()) > 0){// dodajemy pare na koniec listy
		if(para.klucz() > koniec->klucz() ){
			cout << "na koniec" << endl;
			Dane.push_back(para);}
		//przypadek gdy klucz jest identyczny jak klucz ostatniego elementu listy
		//else if(para.klucz().compare(koniec->klucz()) == 0){
		else if(para.klucz() == koniec->klucz()){
			cout << "podmianka" << endl;
			Dane.end()->wartosc()=wartosc;}
		else{ // w przeciwnym wypadku wstawiamy pare

			while(it!=koniec){

				//if(para.klucz().compare(it->klucz()) < 0){
				if(para.klucz() < it->klucz()){
					cout << "gdzies: "<< licz << endl;
					Dane.insert(it,para);
					cout << "sie zawiesza" << endl;
				}
				//else if(para.klucz().compare(it->klucz()) == 0){
				else if(para.klucz() == it->klucz()){
					cout << "moze cos tutaj" << endl;
					it->wartosc()=wartosc;
				}
				it++;
				licz++;
			}
			cout << "else" << endl;
		}
	}


}

template <typename Wartosc>
Wartosc Tablica_asocjacyjna<Wartosc>::pobierz(std::string k){
	assert(Dane.size()>0);//jesli tablica nie zawiera zadnego elementu
	czy_istnieje=false; // domyslnie zakladam ze kluca nie ma w zbiorze
	//przeszukiwanie binarne
	int poczatek=0;
	int koniec=Dane.size()-1;
	int srodek=koniec/2;
	string temp=Dane[srodek].klucz(); // zmienna przechowuje nazwe klucza z indeksu srodek

	do{
		temp=Dane[srodek].klucz();
		if(temp.compare(k) == 0){ // jesli klucz istnieje w zbiorze
			czy_istnieje=true;
			return  ( Dane[srodek].wartosc() );
	    }
		else{
			if(temp.compare(k) < 0){//jesli k jest alfabetycznie dalej od temp
				poczatek=srodek;
				srodek=(koniec+1-poczatek)/2+poczatek;
			}
			else if(temp.compare(k)>0){ // jesli k jest alfabetycznie blizej niz temp
				koniec=srodek;
				srodek=(koniec-poczatek)/2;

			}
		}
	}while(koniec-poczatek>0);
}

template <typename Wartosc>
void Tablica_asocjacyjna<Wartosc>::usun(std::string k){
	typename std::vector< Para<Wartosc> >::iterator it,end;
	czy_istnieje=false;
	end=Dane.end();
	for (it = Dane.begin(); end != it; ++it) {
		if (0 == (it->klucz().compare(k))) { // do ulepszenia !!
			Dane.erase(it);
			czy_istnieje=true;
	    }
	}
}

template <typename Wartosc>
string Tablica_asocjacyjna<Wartosc>::znajdz(Wartosc wartosc){
	typename std::vector< Para<Wartosc> >::iterator it,end;
		czy_istnieje=false;
		end=Dane.end();
		for (it = Dane.begin(); end != it; ++it) {
			if (it->wartosc() == wartosc){ // typ Wartosc musi miec zdefiniowany operator porownania ==
				czy_istnieje=true;
				return  ( it->klucz() );

		    }
		}
}

#endif /* SLOWNIK_HH_ */
