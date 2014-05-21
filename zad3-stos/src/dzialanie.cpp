
#include "dzialanie.hh"
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;


/*!
	 * \brief metoda wczytuje dane do tablicy znajdujacej sie w zmiennej wejscie.
	 *
	 * 	Format danych w pliku jest nastepujacy:
	 * 	pierwszy wiersz - ilosc elementow, a nastepnie w kolumnie kolejne wartosci tablicy.
	 * 	\param nazwaPliku - nazwa pliku do otwarcia
	 * 	\return void
	 */
void Dzialanie::wczytajDaneWejsciowe(string nazwa, stos_tab stos){
	ifstream plik;
	plik.open(nazwa.c_str(), ios::in);
	plik >> rozmiar;
		while( !plik.eof()){
			int element;
			plik >> element;
			stos.push(element);
		}
		assert(rozmiar==stos.size());
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
	stos_tab stos(1);
	start=wlaczStoper();
	wczytajDaneWejsciowe(nazwa.c_str(),stos);
	end=wylaczStoper();
	return (end.QuadPart-start.QuadPart);


}
