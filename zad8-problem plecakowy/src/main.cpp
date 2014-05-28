#include "plecak.hh"
#include <iostream>
#include <cstdio>

using namespace std;

int main(){
	plecak x;
	cout  << endl << endl;
	x.wczytaj_dane_z_pliku("dane.txt");
	x.rozwiaz_problem();
	x.wyswietl();
	x.wypisz_rozwiazanie();
	getchar();
	return 0;
}
