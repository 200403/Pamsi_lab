#include "tester.hh"
#include <iostream>
#include <time.h>
using namespace std;

string wejscie;
void zamienNazwy(int i){
	string nazwa="dane", numer, rozszerzenie=".txt";
	ostringstream ss;
	ss << i;
	numer=ss.str();
	wejscie=nazwa+numer+rozszerzenie;
}

/*! \brief Funkcja generuje losowy ciag znakow o zadanej dlugosci
 *
 */
void gen_random(char *s, const int len) {
    static const char alphanum[] =
    	"abcdef";
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
}

/*! \brief Funkcja generuje pliki z danymi wejsciowymi
 *
 */
void generator(){

	int tab[7]={10,100,1000,10000,100000,1000000,10000000};
	ofstream plik;
	char  klucz[11];
	srand(time(NULL));
	for(int i=0; i<7; i++){
		zamienNazwy(i);
		plik.open(wejscie.c_str(), ios::out);
		plik << tab[i];
		for(int j=0; j<tab[i]; j++ ){
			gen_random(klucz,10);
			plik << "\n";
			plik << klucz;
		}
		plik.close();
	}
}



int main(){
	Tester test;
	test.otworzPlik("hash.csv");
	test.symulacja();

}









