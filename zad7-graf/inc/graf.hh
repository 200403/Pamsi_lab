#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <queue>
#include <conio.h>
#include <string>
#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#define N 25.0 // liczba pol, najlepiej zeby byl to kwadrat
#define SZEROKOSC 650.0

enum kolor { B, C, S};

enum kolorowo {BIALY,CZARNY,CZERWONY,ZIELONY,SZARY, ZOLTY, BRAZOWY,NIEBIESKI};

void Display();

//struktura modelujaca pojedynczy pole na mapie
typedef struct pole{
	GLfloat x1, y1; //wspolrzedne lewego gornego wierzcholka
	GLfloat x2, y2; //wspolrzedne prawego dolnego wierzcholka
	kolorowo kolor;
	pole();
}pole;

//pole lista_pol[int(N*N)]; // lista wszystkich pol



typedef struct wezel_Astar{
	int id;
	wezel_Astar *rodzic;
	int x, y; // wspolrzedne kartezjanskie wezla
	double f, g, h; // -f. kosztu lacznego, g- f. dojscia, h-f. heurystki
	double best_f; // najlepszy dotychczasowy koszt
	bool zablokowany; // czy wezel jest dostepny

	double heurystyka(wezel_Astar cel);
	wezel_Astar();
	/*~wezel_Astar(){
		delete rodzic;
	}*/
}wezel_Astar;


class graf
{
public:
	int V; // wierzcholki
	int E; // krawedzie
	int **M;  // macierz sasiedztwa
	wezel_Astar * wezly;

public:
	graf(){
		V=0;
		E=0;
		M=NULL;
		wezly=NULL;
	}
	~graf();

	void wczytaj_graf_z_pliku(std::string nazwa);
	void wyswietl();
	int * A_star(int koniec, int poczatek);
	int * DFS(int cel, int start);// Depth-first-search
	int * BFS(int cel, int start);// Breadh-first-search
	int * BBS(int cel, int start);// Branch&Bound-search
	void resetuj_wartosci();
};
class Compare{
public:
	bool operator() (wezel_Astar a, wezel_Astar b){
		return a.f > b.f;
	}
};


void generuj_siatke(int w, int s, std::string nazwa);

