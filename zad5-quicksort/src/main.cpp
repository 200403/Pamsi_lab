#include "tester.hh"
#include <iostream>
#include <time.h>
using namespace std;




int main(){
	Tester test;
	test.otworzPlik("quick_najgorzej.csv");
	test.symulacja();
	test.zamknijPlik();



}









