
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
	index=0;
	fstream plik;
	plik.open(nazwa.c_str(), ios::in);
	string klucz;
	int wielkosc=0;
	plik >> wielkosc;
	cout << "rozmiar: " <<wielkosc << endl;
	rozmiar=wielkosc;
		for(int i=0; i<rozmiar; i++){
			plik >> klucz;
			//cout << "wczytywany: " << klucz << endl;
			tablica.dodaj(klucz,i);
			dane[i%10]=klucz;
		}

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


int Dzialanie::uruchom(int j){
	LARGE_INTEGER start, end;

	start=wlaczStoper();
	wykonajAlgorytm();
	end=wylaczStoper();
	return (end.QuadPart-start.QuadPart);
}


void Dzialanie::wykonajAlgorytm(){
	tablica.pobierz(dane[index]);
	index++;

}

