
#include "dzialanie.hh"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <cmath>
#include <cstdlib>
#include <ctime>


using namespace std;


/*!
	 * \brief metoda wczytuje dane do tablicy znajdujacej sie w zmiennej wejscie.
	 *
	 * 	Format danych w pliku jest nastepujacy:
	 * 	pierwszy wiersz - ilosc elementow, a nastepnie w kolumnie kolejne wartosci tablicy.
	 * 	\param nazwaPliku - nazwa pliku do otwarcia
	 * 	\return void
	 */
void Dzialanie::wczytajDaneWejsciowe(string nazwa){
	ifstream plik;
	plik.open(nazwa.c_str(), ios::in);
	plik >> rozmiar;
		//while( !plik.eof()){
		for(int i=0; i<rozmiar; i++){
			int element;
			plik >> element;
			kontener.dodaj_element(element);
		}
		//assert(rozmiar==kontener.wez_rozmiar());
		plik.close();
}



/*!
	 * \brief Metoda uruchamia pomiar czasu
	 *
	 *  Czas jest mierzony w milisekundach
	 * 	\return czas, w ktorym zostal wlaczony stoper
	 */
LARGE_INTEGER Dzialanie::wlaczStoper(){

	 LARGE_INTEGER start;
	 DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	 QueryPerformanceCounter(&start);
	 SetThreadAffinityMask(GetCurrentThread(), oldmask);
	 return start;
}

/*!
		 * \brief Metoda konczy pomiar czasu
		 *
		 *  Czas jest mierzony w milisekundach
		 * 	\return czas, w ktorym stoper zostal wylaczony
		 */
LARGE_INTEGER Dzialanie::wylaczStoper(){

	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}


int Dzialanie::uruchom(string nazwa){
	LARGE_INTEGER start, end;
	wczytajDaneWejsciowe(nazwa.c_str());
	start=wlaczStoper();
	wykonajAlgorytm();
	end=wylaczStoper();
	return (end.QuadPart-start.QuadPart);
}


void Dzialanie::wykonajAlgorytm(){

	MergeSort(kontener);

}

void Dzialanie::Quicksort( Kontener *tab, int lewy, int prawy)
{
    int i = lewy;
    int j = prawy;
    int x = (*tab)[prawy];
    do
    {
        while( (*tab)[ i ] < x )
             i++;

        while( (*tab)[ j ] > x )
             j--;

        if( i <= j )
        {
            tab->zamien_elementy(i,j);

            i++;
            j--;
        }
    } while( i <= j );

    if( lewy < j ) Quicksort( tab, lewy, j );

    if( prawy > i ) Quicksort( tab, i, prawy);

}



void Dzialanie::uporzadkuj_kopiec(Kontener *kopiec){
	int dlugosc=kopiec->wez_rozmiar()-1; // ilosc elementow w kopcu
	int wysokosc=log(dlugosc)/log(2); // wysokosc kopca
	//aby przeniesc element z najnizszego liscia do korzenia potrzebuje tyle ruchow
	//ile jest poziomow kopca ( wysokosc)
	for(int j=0; j<wysokosc;j++){
		//sprawdzam poczynajac od najnizszej warstwy czy warunek kopca jest spelniony
		for(int i=dlugosc; i>1; i--){
			if((*kopiec)[i] > (*kopiec)[i/2]){
				kopiec->zamien_elementy(i,i/2);
			}
		}
	}
}

Kontener Dzialanie::heap(Kontener tab){
	int rozmiar=tab.wez_rozmiar();
	Kontener kopiec;
	kopiec.dodaj_element(0); //nieuzywany element o indeksie 0
	kopiec=kopiec+tab; //tworze strukture drzewa
	for(int i=rozmiar; i>0;i--){ // wypelniam tablice od konca
		uporzadkuj_kopiec(&kopiec);//porzadkuje kopiec
		tab[i-1]=kopiec[1];//sciagam korzen i dodaje go do tablicy
		kopiec.zamien_elementy(1,i);
		kopiec.usun_z_konca();

	}
	return tab;
}

Kontener Dzialanie::merge(Kontener lewy, Kontener prawy){
	Kontener wynik;

	while((lewy.wez_rozmiar() > 0) || (prawy.wez_rozmiar() > 0)){ // dopoki sa dane w tablicach
		if((lewy.wez_rozmiar()>0) && (prawy.wez_rozmiar()>0) ){ // jesli obydwie tablice maja conajmniej jeden element

			//porownuje pierwsze elementy tablic
			if(lewy[0]<=prawy[0]){//jesli wartosc w lewej jest mniejsza to dodaje ja do tablicy wynikowej
				wynik.dodaj_element(lewy[0]);
				lewy.usun_z_poczatku();
			}
			else{ // w przeciwnym razie wedruje tam pierwszy element z prawej tablicy
				wynik.dodaj_element(prawy[0]);
				prawy.usun_z_poczatku();
			}
		}
		//jesli prawa tablica jest juz pusta to lewa dodaje na koniec tablicy wynikowej
		//pamietajac ze lewa tablica jest juz posortowana
		else if( lewy.wez_rozmiar()>0 ){
			wynik.dodaj_element(lewy[0]);
			lewy.usun_z_poczatku();
		}
		//to samo gdy lewa tablica jest pusta
		else if(prawy.wez_rozmiar()>0){
			wynik.dodaj_element(prawy[0]);
			prawy.usun_z_poczatku();
		}
	}
	return wynik;
}



Kontener Dzialanie::MergeSort(Kontener tab)
{
	if(tab.wez_rozmiar()<=1){ // tablica jednoelementowa jest zawsze posortowana
		return tab;
	}
	Kontener lewy, prawy;
	int srodek=tab.wez_rozmiar()/2; // dziele tablice na 2 podzbiory

	for(int i=0; i<srodek; i++){ // tworze podzbior na lewo od srodka
		lewy.dodaj_element(tab[i]);
	}

	for(int i=srodek; i < (int)tab.wez_rozmiar(); i++){//podzbior na prawo od srodka
			prawy.dodaj_element(tab[i]);
		}

	//wykonuje dzielenie dla coraz mniejszych podzbiorow
	lewy=MergeSort(lewy);
	prawy=MergeSort(prawy);
	//scalam podzielone kawalki w posortowana calosc
	return merge(lewy,prawy);
}
