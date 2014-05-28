#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "plecak.hh"

using namespace std;

plecak::plecak(): ilosc(0), waga(0), K(NULL), elementy(NULL){};
plecak::~plecak(){

	delete [] elementy;
	for(int i=0; i<ilosc+1;i++){
		delete [] K[i];
	}
	delete [] K;
}

bool plecak::wczytaj_dane_z_pliku(string nazwa){
	ifstream plik;
	plik.open(nazwa.c_str(), ios::in);
	plik >> waga >> ilosc;
	//wagi = new int[ilosc+1];
	//ceny = new int[ilosc+1];
	elementy = new przedmiot[ilosc+1];
	for(int i=1; i<ilosc+1; i++){
		plik >> elementy[i].waga;
		plik >> elementy[i].cena;
		elementy[i].id=i;
	}
	plik.close();
	return true;
}

int plecak::rozwiaz_problem(){
	//inicjuje tablice rozwiazan
	K = new int *[ilosc+1];
	for(int i=0; i<ilosc+1; i++){
		K[i] = new int[waga+1];
	}
	for(int i=0; i<ilosc+1; i++){
		for(int j=0; j<waga+1; j++){
			K[i][j]=0;
		}
	}
	//rozwiazanie dla ilosci elementow = 0
	for(int i=0; i<ilosc+1; i++){
		K[i][0]=0;
	}
	//rozwiazanie dla wagi = 0
	for(int i=0; i<waga+1; i++){
		K[0][i]=0;
	}

	for(int i=1; i<ilosc+1; i++){
		for(int j=1; j<waga+1; j++){
			if(j >=elementy[i].waga)
				K[i][j]= max( K[i-1][j-elementy[i].waga]+elementy[i].cena, K[i-1][j]);
			else
				K[i][j]=K[i-1][j];
		}
	}
	return K[ilosc][waga];
}


void plecak::wypisz_rozwiazanie(){
	int n = ilosc;
	int w = waga;
	int suma_wag=0;
	cout << endl <<  endl << "Przedmioty wlozone do plecaka:" << endl << endl;
	cout << setw(17) << "Waga" << setw(5) << "Cena" << endl;
	//dopuki nie doszlismy do poczatku tablicy
	while(K[n][w] > 0){
		//jezeli nie wlozylismy przedmiotu do plecaka
		if( K[n][w] == K[n-1][w])
			n=n-1;

		if( K[n][w] == K[n-1][w-elementy[n].waga]+elementy[n].cena ){
			cout << "Przedmiot " << elementy[n].id << ":";
			cout << setw(5) << elementy[n].waga;
			cout << setw(5) << elementy[n].cena << endl;
			suma_wag+=elementy[n].waga;
			w=w-elementy[n].waga;
			n=n-1;
		}
	}
	cout<< endl << setw(12) <<"Suma:" << setw(5) << suma_wag << setw(5) << K[ilosc][waga] << endl;
}

void plecak::wyswietl(){
	cout << "Max waga: " << waga << endl;
	cout << "Ilosc: " << ilosc << endl << endl;
	cout << setw(9) << "Waga" << setw(5) << "Cena" << endl;
	for(int i=1; i<ilosc+1; i++){
		cout <<setw(2) << elementy[i].id << ": ";
		cout << setw(5) <<elementy[i].waga << setw(5)<< elementy[i].cena << endl;
	}
	cout << endl;
	cout << "Tablica rozwiazania: " << endl;
	for(int i=0; i<ilosc+1; i++){
		for(int j=0; j<waga+1; j++){
			cout <<setw(2) << K[i][j] <<" ";
		}
		cout << endl;
	}
}
