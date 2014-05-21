#include "stos_list.hh"
#include <iostream>

using namespace std;


void stos_list::push(int element){
	lista.push_back(element);
}

void stos_list::pop(int *a){
	if(isempty() == true){
		cerr<<"Stos jest pusty. Nie ma czego sciagnac!" << endl;
	}
	else{
		iter=lista.end();
		*a=*iter;
		lista.pop_back();
	}
}

bool stos_list::isempty(){
	return lista.empty();
}

int stos_list::size(){
	return lista.size();
}

void stos_list::wyswietl(){
	cout << "zawartosc stosu:" << endl;
	for(iter=lista.begin(); iter!=lista.end(); iter++){
		cout << *iter << endl;
	}
}
