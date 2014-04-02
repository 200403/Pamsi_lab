#include "tester.hh"
#include <iostream>
#include <time.h>
using namespace std;

string wejscie;
void zamienNazwy(int i){
	string nazwa="wejscie", numer, rozszerzenie=".txt";
	ostringstream ss;
	ss << i;
	numer=ss.str();
	wejscie=nazwa+numer+rozszerzenie;
}


int main(){
	Tester test;
	test.otworzPlik("merge.csv");
	test.symulacja();
	test.zamknijPlik();




	/*int tab[7]={10,100,1000,10000,100000,1000000,10000000};
	ofstream plik;
	srand(time(NULL));
	for(int i=5; i<7; i++){
		zamienNazwy(i);
		plik.open(wejscie.c_str(), ios::out);
		plik << tab[i];
		for(int j=0; j<tab[i]; j++ ){
			plik << "\n";
			plik << rand()%1000;
		}
		plik.close();

	}*/
	return 0;

}









