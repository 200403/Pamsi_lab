#include "hash.hh"
#include <iostream>
using namespace std;

bool operator < (elem a, elem b){
	return a.klucz<b.klucz;
}

int tab_hash::hash(string klucz){
	/*int suma=0;
	for(unsigned int i=0; i<klucz.size(); i++){
		char j=klucz[i];
		suma+=j;
	}
	return suma % ROZMIAR;*/
	int suma=0;
	int rozmiar=klucz.length();
	for(unsigned int i=0; i<klucz.length(); i++){
		char j=klucz[i];
		suma+=j*(rozmiar-i);
	}
	return suma;

}

void tab_hash::dodaj(string klucz, int wartosc){
	//tworze element
	elem element;
	element.klucz=klucz;
	element.wartosc=wartosc;

	int index = hash(klucz);
	tablica[index].push_back(element);
	//tablica[index].sort();

}

int tab_hash::pobierz(std::string klucz){
	int index=hash(klucz);

	list<elem>::iterator it = tablica[index].begin();
	for(; it !=tablica[index].end() ; it ++ ){
		if(it->klucz == klucz){
			return it->wartosc;
		}
	}


	cout << "brak elementu o zadanym kluczu" << endl;
	return -1;
}

bool tab_hash::usun(std::string klucz){
	int index=hash(klucz);

	list<elem>::iterator it = tablica[index].begin();
	for(; it !=tablica[index].end() ; it ++ ){
		if(it->klucz == klucz){
			tablica[index].erase(it);
			return true;
		}
	}
	return false;
}
void tab_hash::wypisz(){
	cout << "Tablica haszujaca: " << endl;
	list<elem>::iterator it;
	for (int i=0; i<ROZMIAR; i++){
		it = tablica[i].begin();
		cout << "Tab["<<i<<"]:  ";
		for(; it !=tablica[i].end(); it++){
			cout << it->klucz << "-" << it->wartosc <<" ; ";
		}
		cout << endl;
	}
}

