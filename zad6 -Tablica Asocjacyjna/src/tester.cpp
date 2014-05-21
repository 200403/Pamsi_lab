#include "tester.hh"

using namespace std;

void Tester::otworzPlik(string nazwa){
	plik.open(nazwa.c_str(), ios::out);
}

void Tester::zamknijPlik(){
	plik.close();
}

void Tester::symulacja(){

	Dzialanie program;
	for (int j=0; j<ilosc; j++){

		double suma=0;
		program.wczytajDaneWejsciowe(wejscie);
		cout << "wczytane" << endl;
		for(int i=0 ; i<powtorzenia; i++){
				suma+=program.uruchom(j);
		}
		plik << program.wez_rozmiar() << ',' << powtorzenia << ','<< suma/powtorzenia << '\n';
		zamienNazwy(j+1);
	}
}

void Tester::zamienNazwy(int i){
	string nazwa="dane", numer, rozszerzenie=".txt";
	ostringstream ss;
	ss << i;
	numer=ss.str();
	wejscie=nazwa+numer+rozszerzenie;
}

