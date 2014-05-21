#include "kolejka_list.hh"
#include <iostream>

using namespace std;


void kolejka_list::enqueue(int element){
	lista.push_front(element);
}

void kolejka_list::dequeue(int *a){
	if(isempty() == true){
		cerr<<"Stos jest pusty. Nie ma czego sciagnac!" << endl;
	}
	else{
		iter=lista.end();
		*a=*iter;
		lista.pop_back();
	}
}

bool kolejka_list::isempty(){
	return lista.empty();
}

int kolejka_list::size(){
	return lista.size();
}

void kolejka_list::wyswietl(){
	cout << "zawartosc stosu:" << endl;
	for(iter=lista.begin(); iter!=lista.end(); iter++){
		cout << *iter << endl;
	}
}
