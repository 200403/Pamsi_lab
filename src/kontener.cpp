#include "kontener.hh"
#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

/*!
	 * \brief metoda wczytuje dane do tablicy z pliku
	 *
	 * 	Format danych w pliku jest nastepujacy:
	 * 	pierwszy wiersz - ilosc elementow, a nastepnie w kolumnie kolejne wartosci tablicy.
	 * 	\param nazwaPliku - nazwa pliku do otwarcia
	 * 	\return void
	 */
void Kontener::wczytajDane(string nazwaPliku){
	dane.clear();
	ifstream plik;
	plik.open(nazwaPliku.c_str(), ios::in);
	plik >> rozmiar;
	while( !plik.eof()){
		int element;
		plik >> element;
		dane.push_back(element);
	}
	assert(rozmiar==dane.size());
	plik.close();
}



void Kontener::zamien_elementy(unsigned int i, unsigned int j){
	int temp;
	assert(i<=rozmiar-1 && j<=rozmiar-1);
	temp=dane[i];
	dane[i]=dane[j];
	dane[j]=temp;
}

void Kontener::odwroc_kolejnosc(){
	vector <int> temp;
	for(unsigned int i=0; i<rozmiar;i++){
		temp.push_back(dane[rozmiar-1-i]);
	}
	dane=temp;
}

void Kontener::dodaj_element(int e){
	dane.push_back(e);
	rozmiar++;
}

void Kontener::dodaj_elementy(Kontener tab){
	unsigned int i;
	for(i=0; i<tab.rozmiar; i++){
		dane.push_back(tab.dane[i]);
	}
	rozmiar+=i;
}

int & Kontener::operator [](int index){
	return dane[index];
}

Kontener& Kontener::operator + (Kontener tab){
	dodaj_elementy(tab);
	return *this;
}

Kontener& Kontener::operator = (Kontener tab){
	dane=tab.wez_dane();
	rozmiar=tab.wez_rozmiar();
	return *this;
}

bool Kontener::operator == (Kontener tab){
	if (rozmiar!=tab.wez_rozmiar())
		return false;
	else{
		for(unsigned int i=0; i<rozmiar; i++){
			if(dane[i]!=tab[i])
				return false;
		}
	}
	return true;
}

ostream & operator << (ostream& out, Kontener Tab){
	out << "rozmiar: " << Tab.wez_rozmiar() << endl;
		for(unsigned int i=0; i<Tab.wez_rozmiar(); i++){

			out << Tab[i] << endl;
		}
	return out;
}
