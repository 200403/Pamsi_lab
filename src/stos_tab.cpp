#include "stos_tab.hh"
#include <iostream>

using namespace std;

void stos_tab::powiekszStos(){
	rozmiar_tab=rozmiar_tab + *o_ile;
	int *temp= new int[rozmiar_tab]; // tworze nowa wieksza tablice
	for(int i=0; i<ilosc_el; i++){ // przepisuje dane do nowej
		temp[i]=tab[i];
	}
	delete tab;// stara tablica jest juz nie potrzbna
	tab=temp; // zachaczm wskaznik do nowej tablicy
}

void stos_tab::pomniejszStos(){
	rozmiar_tab/=2;
	int *temp= new int[rozmiar_tab];
	for(int i=0; i<ilosc_el; i++){ // przepisuje dane do nowej
			temp[i]=tab[i];
		}
	delete tab;// stara tablica jest juz nie potrzbna
	tab=temp; // zachaczm wskaznik do nowej tablicy
}

void stos_tab::push(int element){
	if (ilosc_el == rozmiar_tab){
		powiekszStos();
	}
	tab[ilosc_el]=element;
	ilosc_el++;
}

void stos_tab::pop(int *a){
	if(isempty() == true){
		cerr<<"Stos jest pusty. Nie ma czego sciagnac!" << endl;
	}
	else{
		*a=tab[ilosc_el-1];
		ilosc_el--;
		if(4*ilosc_el<=rozmiar_tab){
			pomniejszStos();
		}
	}
}

bool stos_tab::isempty(){
	return ilosc_el == 0;
}

int stos_tab::size(){
	return ilosc_el;
}

void stos_tab::wyswietl(){
	cout << "zawartosc stosu:" << endl;
	for(int i=0; i<ilosc_el; i++){
		cout << tab[i]<< endl;
	}
	cout << "ilosc el: " << ilosc_el << endl;
	cout << "rozmiar tab: " << rozmiar_tab << endl;
}
