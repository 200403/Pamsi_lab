#include "graf.hh"

using namespace std;
extern pole * lista_pol;

pole * lista;

pole::pole(){
	x1=y1=x2=y2=0;
	kolor=SZARY;
}
void generuj_siatke(int w, int s, string nazwa){
	int v=s*w;
	int M[v][v];
	//int **M;
	/**M= new int [v];
	for (int i=0;i<v;i++){
		M[i]=new int[v];
	}*/
	int x, y,p=0;

	for(x=0; x<v; x++){
		for(y=0; y<v; y++){
			M[x][y]=0;
		}
	}

	x=0; y=1;
	for(;x<v and y<v; x++, y++){

		if(p<(s-1)){

			M[x][y]=1;
			p++;
		}
		else{
			p=0;
		}
	}
	x=1; y=0,p=0;
	for(;x<v and y<v; x++, y++){
		if(p<(s-1)){

					M[x][y]=1;
					p++;
				}
				else{
					p=0;
				}
	}
	x=s; y=0;
	for(;x<v and y<v; x++, y++){
		M[x][y]=1;
	}
	x=0; y=s;
	for(;x<v and y<v; x++, y++){
		M[x][y]=1;
	}

	ofstream plik;
	plik.open(nazwa.c_str(), ios::out);
	plik << w*s << " ";
	plik << s*(w-1)+w*(s-1) << " ";
	plik << w << " " << s << "\n";
	for(x=0; x<v; x++){
		plik << "\n";
		for(y=0; y<v; y++){
			plik << M[x][y] << " ";
		}

	}
	plik.close();
	for (int i = 0; i < v; i++)
		{
			delete[] M[i];
		}
		delete[] M;
}
//#########################################
//wezel
wezel_Astar::wezel_Astar(){
	id=0;
	rodzic=NULL;
	x= y= -1;
	f= g= 0;
	h=32000000;
	best_f=32000000;
	zablokowany=false;
}

double wezel_Astar::heurystyka(wezel_Astar cel){
	//jesli przez wezel nie mozna przechodzic to zwrocona wartosc 32000 sprawi,
	//ze koszt przejscia bedzie bardzo wysoki i algorytm zaniecha przechodzenia przez ten wezel
	if(zablokowany==true)
		return 32000;
	else
		//Manhattan
		return abs(x-cel.x)+abs(y-cel.y);
		//return sqrt((x-cel.x)*(x-cel.x)+(y-cel.y)*(y-cel.y));
		//return 0;
}

//#########################################
// GRAF
graf::~graf(){

	for (int i = 0; i < V; i++)
	{
		delete[] M[i];
	}
	delete[] M;
	delete [] wezly;


}

void graf::wczytaj_graf_z_pliku(std::string nazwa){
	ifstream plik;
	int w, s;
		plik.open(nazwa.c_str());
		plik >> V;  // liczba wierzcholkow
		plik >> E;  // liczba krawedzi
		plik >> w >> s; //w-wysokosc, s-szerokosc
		M = new int*[V];
		wezly = new wezel_Astar[V];
		for (int i = 0; i < V; i++)
		{
			M[i] = new int[V];
		}

		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				plik >>M[i][j];
			}
		}
		for(int k=0; k<V; k++){
			wezly[k].x= k/w;
			wezly[k].y= k%(s);
			wezly[k].id= k;
		}

		plik.close();
		cout << "V: " << V << endl;
}

void graf::wyswietl()
{
	for (int i = 0; i < V; i++)
	{
		cout << endl << setw(3) << i << ":";
		for (int j = 0; j < V; j++)
		{
			cout << setw(3) << M[i][j];
		}
	}
	cout << endl;

}

int * graf::A_star(int meta, int start){
	int l_odwiedzonych=0;
	cout << start << " " << meta << endl;
	lista=lista_pol;
	wezel_Astar *temp, x; // do sciagania wezlow z kolejki
	int q; //aktualnie analizowany wezel
	kolor odwiedzone[V];
	int * droga= new int[V];//lista indeksow po ktorych nalezy sie poruszac aby dotrzec z start do mety
	for(int i=0; i<V; i++){
		odwiedzone[i]=B;
	}
	priority_queue<wezel_Astar, vector<wezel_Astar>, Compare> Q;
	Q.push(wezly[start]);
	while( Q.empty()==false ){
		x=Q.top(); // pobieram wezel z najnizszym f
		Q.pop();
		q=x.id;

		for(int i=0; i<V; i++){ // dla kazdego sasiada
			if( M[i][q]>0 and odwiedzone[i]==B and wezly[i].zablokowany==false){ // jesli taki sasiad istnieje
				temp=&(wezly[i]);
				temp->g=wezly[q].g + M[i][q]; // aktualizujemy koszt dojscia z startu
				temp->h=temp->heurystyka(wezly[meta]);//aktualizujemy heurystyke
				temp->f=temp->g + temp->h; // i calkowity koszt

				//########################################
				//DO WYSWIETLANIA
				lista[i].kolor=ZOLTY;
				l_odwiedzonych++;
				//glutPostRedisplay();
				Display();
				//########################################
				//jesli doszlismy do docelowego punktu
				if(i==meta){
					int ilosc=1;
					temp->rodzic=&wezly[q];
					int k=1;
					//cout << "Droga: " << endl;
					while(temp->rodzic != NULL){
						droga[ilosc++]=temp->id;
						//cout  << temp->id <<" -> ";
						if(k%8==0)
							cout << endl;
						k++;
						temp=temp->rodzic;
					}
					//cout << temp->id << endl;
					//cout << "Koszt: " << wezly[meta].g << endl;
					droga[ilosc++]=temp->id;
					droga[0]=ilosc;
					cout << "Liczba odwiedzonych wezlow: " << l_odwiedzonych << endl;
					cout << "Koszt: " << wezly[meta].g << endl;
					return droga;
				}

				if(temp->best_f > temp->f){ // jesli mamy lepszy wynik
					temp->rodzic=&wezly[q];
					temp->best_f=temp->f;
					Q.push(wezly[i]);

				}
			}
		}

		odwiedzone[q]= C;

	}

	return NULL;
}

int * graf::BFS(int meta, int start){
	int l_odwiedzonych=0;
	bool czy_na_kolejce[V];
	lista=lista_pol;
	wezel_Astar *temp, x; // do sciagania wezlow z kolejki
	int q; //aktualnie analizowany wezel
	kolor odwiedzone[V];
	int droga[V/2];//lista indeksow po ktorych nalezy sie poruszac aby dotrzec z start do mety
	for(int i=0; i<V; i++){
		odwiedzone[i]=B;
		czy_na_kolejce[i]=false;
		}

	queue<wezel_Astar> Q;
	Q.push(wezly[start]);
	czy_na_kolejce[start]=true;
	while(!Q.empty()){
		x=Q.front();
		Q.pop();
		q=x.id;
		czy_na_kolejce[q]=false;

		for(int i=0; i<V; i++){


			if(M[i][q]>0){
				if(odwiedzone[i]==B and wezly[i].zablokowany==false ){
					temp=&(wezly[i]);
					temp->g=wezly[q].g + M[i][q]; // aktualizujemy koszt dojscia z startu
					temp->rodzic=&wezly[q];
					Q.push(wezly[i]);
					czy_na_kolejce[i]=true;
					//########################################
					//DO WYSWIETLANIA
					lista[i].kolor=ZOLTY;
					l_odwiedzonych++;
					//glutPostRedisplay();
					Display();
					//########################################
				if(i==meta){// jesli znalezlismy wierzcholek koncowy
					int ilosc=1;
						temp->rodzic=&wezly[q];
						int k=1;
						//cout << "Droga: " << endl;
						while(temp->rodzic != NULL){
							droga[ilosc++]=temp->id;
							//cout  << temp->id <<" -> ";
							if(k%8==0)
								cout << endl;
							k++;
							temp=temp->rodzic;
							}
						droga[ilosc++]=temp->id;
						droga[0]=ilosc;
						cout << "Liczba odwiedzonych wezlow: " << l_odwiedzonych << endl;
						cout << "Koszt: " << wezly[meta].g << endl;
						return droga;
				}
				}
			}
		}
		odwiedzone[q]=C;


	}
	return NULL;
}

int * graf::DFS(int meta, int start){
	int l_odwiedzonych=0;
	lista=lista_pol;
	wezel_Astar *temp, x; // do sciagania wezlow z kolejki
	int q; //aktualnie analizowany wezel
	kolor odwiedzone[V];
	int droga[V];//lista indeksow po ktorych nalezy sie poruszac aby dotrzec z start do mety
	for(int i=0; i<V; i++){
		odwiedzone[i]=B;
		}

	stack<wezel_Astar> S;
	S.push(wezly[start]);

	while( !S.empty() ){//dopoki n ie znalezlismy wszystkich wierzcholkow
		x=S.top();
		S.pop();
		q=x.id;
		for(int i=0; i<V; i++){
		if(M[i][q]>0){//jesli jest polaczenie
			if(odwiedzone[i]==B and wezly[i].zablokowany==false){//jesli wierzcholek nie jest znaleziony
				temp=&(wezly[i]);
				temp->g=wezly[q].g + M[i][q]; // aktualizujemy koszt dojscia z startu
				temp->rodzic=&wezly[q];
				odwiedzone[i]=C;
				S.push(wezly[i]);
				//########################################
				//DO WYSWIETLANIA
				lista[i].kolor=ZOLTY;
				l_odwiedzonych++;
				Display();
				//########################################
				if(i==meta){// jesli znalezlismy wierzcholek koncowy
					int ilosc=1;
						temp->rodzic=&wezly[q];
						int k=1;
						//cout << "Droga: " << endl;
						while(temp->id!=start){
							droga[ilosc++]=temp->id;
							//cout  << temp->id <<" -> ";
							//if(k%8==0)
								//cout << endl;
							k++;
							temp=temp->rodzic;
							}
						droga[ilosc++]=temp->id;
						droga[0]=ilosc;
						cout << "Liczba odwiedzonych wezlow: " << l_odwiedzonych << endl;
						cout << "Koszt: " << wezly[meta].g << endl;
						return droga;
				}
			}
		}


		}
	}

}

void graf::resetuj_wartosci(){
	for(int i=0; i<V; i++){
		wezly[i].rodzic=NULL;

		wezly[i].f= wezly[i].g =0;
		wezly[i].h=0;
		wezly[i].best_f=32000;

	}
}
