#include "kolejka_tab.hh"
#include <iostream>

using namespace std;

void kolejka_tab::powieksz(){
	rozmiar_tab=rozmiar_tab + *o_ile;
	int *temp= new int[rozmiar_tab]; // tworze nowa wieksza tablice
	for(int i=0; i<ilosc_el; i++){ // przepisuje dane do nowej
		temp[i]=tab[i];
	}
	delete tab;// stara tablica jest juz nie potrzbna
	tab=temp; // zachaczm wskaznik do nowej tablicy
}

void kolejka_tab::pomniejsz(){
	rozmiar_tab/=2;
	int *temp= new int[rozmiar_tab];
	for(int i=0; i<ilosc_el; i++){ // przepisuje dane do nowej tablice
			temp[i]=tab[i];
		}
	delete tab;// stara tablica jest juz nie potrzbna
	tab=temp; // zachaczm wskaznik do nowej tablicy
}

void kolejka_tab::enqueue(int element){
	if (ilosc_el == rozmiar_tab){ // jesli tablica jest pelna to ja zwiekszamy
		powieksz();
	}
	tab[ilosc_el]=element; // dodaje element na pierwszy nieuzywany index
	ilosc_el++;
}

void kolejka_tab::dequeue(int *a){
	if(isempty() == true){
		cerr<<"kolejka jest pusta. Nie ma czego sciagnac!" << endl;
	}
	else{
		*a=tab[0]; // pobieram element
		int *wsk; // wskaznik na element, ktory trzeba usunac
		wsk=tab; // nalezy zapamietac adres elementu, ktory wyklucze z tablicy
		tab++;  // wykluczam pierwszy element z tablicy, poprzez przesuniecie wskaznika
		delete wsk; // kasujemy zdjety element z pamieci
		ilosc_el--; // ilosc elementow w kolejce zmniejszyla sie
		rozmiar_tab--; // jak rowniez rozmiar tablicy
		if(4*ilosc_el<=rozmiar_tab){
			pomniejsz();
		}
	}
}

bool kolejka_tab::isempty(){
	return ilosc_el == 0;
}

int kolejka_tab::size(){
	return ilosc_el;
}

void kolejka_tab::wyswietl(){
	cout << "zawartosc stosu:" << endl;
	for(int i=0; i<ilosc_el; i++){
		cout << tab[i]<< endl;
	}
	cout << "ilosc el: " << ilosc_el << endl;
	cout << "rozmiar tab: " << rozmiar_tab << endl;
}
