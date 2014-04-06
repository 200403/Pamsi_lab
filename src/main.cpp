#include "slownik.hh"
#include <iostream>
#include <time.h>
using namespace std;




int main(){
	Tablica_asocjacyjna<int> tab;
	tab.dodaj("abc",1);
	tab.dodaj("aba",2);
	tab.dodaj("axc",6);
	tab.dodaj("bbc",5);
	tab.dodaj("aaa",2);
	int i;
	// test operatora indeksowania
	i=tab["aaa"];
	cout << "wartosc pod 'aaa': " << i << endl;
	tab["aaa"]=10;
	i=tab["aaa"];
	cout << "wartosc pod 'aaa': " << i<< endl;


}









