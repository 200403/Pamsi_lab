/*
(c) Janusz Ganczarski (Power)
http://www.januszg.hg.pl
JanuszG(ma³peczka)enter.net.pl
*/

#include <stdlib.h>
#include <iostream>
#include "graf.hh"
#include <GL/glu.h>

using namespace std;


graf Graf;
int start, meta;
//uklad wspolrzednych miesci sie w granicach dla 0<x<2, 0>y>-2
float size=SZEROKOSC/2;//size mowi jak trzeba przeskalowac wspolrzedne pol
					   //zeby zmiescily sie w ukladzie
int ilosc_pol= int(N*N);

int * droga; // lista wierzcholkow do zaznaczenia drogi

kolorowo aktualny_kolor=BIALY;
//tablice z kolorami
GLfloat czerwony[3]={1.0, 0.0, 0.0};
GLfloat zielony[3]={0.0, 1.0, 0.0};
GLfloat bialy[3]={1,1,1};
GLfloat czarny[3]={0,0,0};
GLfloat szary[3]={0.6,0.6,0.6};
GLfloat zolty[3]={1,1,0};
GLfloat brazowy[3]={0.6,0.3,0};
GLfloat niebieski[3]={0,0,1};
GLfloat *kolory[8]={bialy,czarny,czerwony, zielony, szary,zolty, brazowy,niebieski};

pole * lista_pol;
// wskaŸnik naciœniêcia lewego przycisku myszki

int button_state = GLUT_UP;

// po³o¿enie kursora myszki

int button_x, button_y;

// sta³e do obs³ugi menu podrêcznego

enum
{
    EXIT, // wyjœcie
    POCZATEK, //pole startowe
    CEL, //pole do ktorego szukamy drogi
    PRZESZKODA, //przeszkoda na drodze
    SPOWOLNIENIE_4, //przeszkoda z ktorej wszystkie wagi maja wartosc 2
    SPOWOLNIENIE_10, //przeszkoda z ktorej wszystkie wagi maja wartosc 2
    ZERUJ, // ustawia pole jako przejezdne
    ASTAR, //rozpoczecie symulacji A*
    DFS, //przeszukiwanie DFS
    BFS, //przeszukiwanie BFS
    RESET, //czysci plansze
    CZYSC, //czysci czewona droge
    FULL_WINDOW, // aspekt obrazu - ca³e okno
    ASPECT_1_1, // aspekt obrazu 1:1
};

// aspekt obrazu

int Aspect = FULL_WINDOW;
// wpó³rzêdne po³o¿enia obserwatora

GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 0;

// wspó³rzêdne punktu w którego kierunku jest zwrócony obserwator,

GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = - 100;

//funkjca inicjujaca wszystkie pola na bialo
//i okreslajaca polozenie kazdego z nich
void initPola(){



    int k=0;
    for (int i=0; i<N; i++){
    	for(int j=0; j<N; j++){

    		lista_pol[k].x1=i*SZEROKOSC/N;
    		lista_pol[k].y1=-j*SZEROKOSC/N;
    		lista_pol[k].x2=(i+1)*SZEROKOSC/N;
    		lista_pol[k].y2=-(j+1)*SZEROKOSC/N;

    		//punkty
    		/*
    		lista_pol[k].x1=(i+1)*SZEROKOSC/N;
    		lista_pol[k].y1=-(j+1)*SZEROKOSC/N;*/
    		lista_pol[k].kolor=SZARY;
    		k++;
    	}
    }
    /*for(k=0; k<ilosc_pol; k++){
    	cout << lista_pol[k].x1 << " "<< lista_pol[k].y1 << " ";
    	cout << lista_pol[k].x2 << " "<< lista_pol[k].y2 << endl;
    }*/

}
// funkcja generuj¹ca scenê 3D
void Display()
{
    // kolor t³a - zawartoœæ bufora koloru
    glClearColor( 1.0, 1.0, 1.0, 1.0 );

    // czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );
    // wybór macierzy modelowania
        glMatrixMode( GL_MODELVIEW );

        // macierz modelowania = macierz jednostkowa
        glLoadIdentity();
        glTranslatef(-1,1,0);
        // ustawienie obserwatora
        //gluLookAt( eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0 );
        glPointSize( 10 );

	//rysowanie wszyskich pol
	for(int k=0; k<ilosc_pol; k++){
		// kolor kwadratu
		glColor3fv(kolory[lista_pol[k].kolor]);

	    // definiowanie polozenia prostokata
	    glRectf(lista_pol[k].x1/size, lista_pol[k].y1/size, lista_pol[k].x2/size, lista_pol[k].y2/size);
		/*glBegin(GL_POINTS);
		glVertex2f(lista_pol[k].x1/size, lista_pol[k].y1/size);
		glEnd();*/
	}
	glColor3f(0,0,0);

	//rysowanie linii oddzielajacych pola
	for(int n=0; n<N+1; n++){
		glLineWidth( 5 );

		glBegin(GL_LINES);
		GLfloat x,y;
		y=0;
		x=n*2/N;
		glVertex2f(x,y);
		y=-2;
		glVertex2f(x,y);
		glEnd();
	}
	for(int n=0; n<N+1; n++){
		glBegin(GL_LINES);
		GLfloat x,y;
		x=0;
		y=-n*2/N;
		glVertex2f(x,y);
		x=2;
		glVertex2f(x,y);
		glEnd();
	}
    // skierowanie poleceñ do wykonania
	glFlush();
    // zamiana buforów koloru
    glutSwapBuffers();
}

// zmiana wielkoœci okna

void Reshape( int width, int height )
{/*
    // obszar renderingu - ca³e okno
    glViewport( 0, 0, width, height );

    // wybór macierzy rzutowania
    glMatrixMode( GL_PROJECTION );

    // macierz rzutowania = macierz jednostkowa
    glLoadIdentity();

    // parametry bry³y obcinania
    if( Aspect == ASPECT_1_1 )
    {
        // wysokoœæ okna wiêksza od wysokoœci okna
        if( width < height && width > 0 )
             glFrustum( - 2.0, 2.0, - 2.0 * height / width, 2.0 * height / width, 1.0, 5.0 );
        else

        // szerokoœæ okna wiêksza lub równa wysokoœci okna
        if( width >= height && height > 0 )
             glFrustum( - 2.0 * width / height, 2.0 * width / height, - 2.0, 2.0, 1.0, 5.0 );

    }
    else
         glFrustum( - 2.0, 2.0, - 2.0, 2.0, 1.0, 5.0 );

    // generowanie sceny 3D*/
    Display();
}


// obs³uga menu podrêcznego

void MenuTrasy(int value){
	switch( value )
	    {
	        // wyjœcie

	    case POCZATEK:
	    	aktualny_kolor=ZIELONY;
	    	break;
	    case CEL:
	    	aktualny_kolor=CZERWONY;
	    	break;
	    }
}
void MenuPrzeszkod( int value){
	switch( value )
	    {

	    case PRZESZKODA:
	    	aktualny_kolor=CZARNY;
	    	break;
	    case SPOWOLNIENIE_4:
	    	aktualny_kolor=BRAZOWY;
	    	break;
	    case SPOWOLNIENIE_10:
	       	aktualny_kolor=NIEBIESKI;
	       	break;
	    case ZERUJ:
	    	aktualny_kolor=SZARY;
	    	break;
	    }
}
void MenuAlgorytmow( int value )
{
    switch( value )
    {

    case ASTAR:

    	droga=Graf.A_star(meta,start);
    	for(int i=1; i<droga[0]; i++){

    		lista_pol[droga[i]].kolor=CZERWONY;
    		glutPostRedisplay();
    	}
    	break;
    case BFS:
    	droga=Graf.BFS(meta, start);
    	for(int i=1; i<droga[0]; i++){
    		lista_pol[droga[i]].kolor=CZERWONY;
    		glutPostRedisplay();
    	}
    	break;
    case DFS:
        droga=Graf.DFS(meta,start);
        for(int i=1; i<droga[0]; i++){
       		lista_pol[droga[i]].kolor=CZERWONY;
       		glutPostRedisplay();
      	}
       	break;
    }
}

void Menu( int value){
	switch(value){
	case EXIT:
		exit(0);
		break;
	case RESET:
		initPola();
		aktualny_kolor=SZARY;
		break;
	case CZYSC:
		initPola();
		Graf.resetuj_wartosci();
		for (int i=0; i<ilosc_pol; i++){
			if(Graf.M[i][i+1]==2 and Graf.M[i][i-1]==2){
				lista_pol[i].kolor=BRAZOWY;
			}
			if(Graf.M[i][i+1]==10 and Graf.M[i][i-1]==10){
				lista_pol[i].kolor=NIEBIESKI;
			}
			if(Graf.wezly[i].zablokowany==true){
				lista_pol[i].kolor=CZARNY;
			}
			if(i==start){
				lista_pol[i].kolor=ZIELONY;
			}
			if(i==meta){
				lista_pol[i].kolor=CZERWONY;
			}
		}

		aktualny_kolor=SZARY;
		break;
	}


}



void MouseButton( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON )
    {
        // zapamiêtanie stanu lewego przycisku myszki
        button_state = state;

        // zapamiêtanie po³o¿enia kursora myszki
        if( state == GLUT_DOWN )
        {
            button_x = x;
            button_y = y;
            int k=0;
            //dopoki nie znajdziemy pola pod kursorem
            while(lista_pol[k].x1>x or lista_pol[k].x2<x or lista_pol[k].y1<-y or lista_pol[k].y2>-y){
            	k++;
            }
            cout << x << " " << y << " " << k<< endl;
            switch(aktualny_kolor){
            case CZARNY:
            	lista_pol[k].kolor=CZARNY;
            	Graf.wezly[k].zablokowany=true;
            	break;

            case ZIELONY:
                lista_pol[k].kolor=ZIELONY;
            	start=Graf.wezly[k].id;
            	cout << "start: "<< start << endl;
                break;

            case CZERWONY:
            	lista_pol[k].kolor=CZERWONY;
            	meta=Graf.wezly[k].id;
            	cout << "meta: " << meta << endl;
            	break;

            case SZARY:
                lista_pol[k].kolor=SZARY;
            	Graf.wezly[k].zablokowany=false;
               	break;
            case BRAZOWY:
                lista_pol[k].kolor=BRAZOWY;
                for(int i=0; i<Graf.V; i++){
                	if(Graf.M[i][k]>0){
                		Graf.M[i][k]=Graf.M[k][i]=2;
                	}
                }
                break;
            case NIEBIESKI:
                lista_pol[k].kolor=NIEBIESKI;
                for(int i=0; i<Graf.V; i++){
                	if(Graf.M[i][k]>0){
                		Graf.M[i][k]=Graf.M[k][i]=10;
                	}
               	}
                break;
             }
        }
            glutPostRedisplay();
    }

}

// obs³uga ruchu kursora myszki

void MouseMotion( int x, int y )
{
    // zmiana koñca po³o¿enia linii
    if( button_state == GLUT_DOWN and (aktualny_kolor==SZARY or aktualny_kolor==CZARNY
    	 or aktualny_kolor==BRAZOWY or aktualny_kolor==NIEBIESKI))
    {
    	int k=0;
    	            //dopoki nie znajdziemy pola pod kursorem
    	            while(lista_pol[k].x1>x or lista_pol[k].x2<x or lista_pol[k].y1<-y or lista_pol[k].y2>-y){
    	            	k++;
    	            }
    	            cout << x << " " << y << " " << k<< endl;
    	            switch(aktualny_kolor){
    	            case CZARNY:
    	            	lista_pol[k].kolor=CZARNY;
    	            	Graf.wezly[k].zablokowany=true;
    	            	break;

    	            case BRAZOWY:
    	                         lista_pol[k].kolor=BRAZOWY;
    	                         for(int i=0; i<Graf.V; i++){
    	                         	if(Graf.M[i][k]>0){
    	                         		Graf.M[i][k]=Graf.M[k][i]=2;
    	                         	}
    	                         }
    	                         break;
    	                     case NIEBIESKI:
    	                         lista_pol[k].kolor=NIEBIESKI;
    	                         for(int i=0; i<Graf.V; i++){
    	                         	if(Graf.M[i][k]>0){
    	                         		Graf.M[i][k]=Graf.M[k][i]=10;
    	                         	}
    	                        	}
    	                         break;

    	            case SZARY:
    	                lista_pol[k].kolor=SZARY;
    	            	Graf.wezly[k].zablokowany=false;
    	               	break;
    	             }
    	            glutPostRedisplay();
    	        }


}


void Keyboard( unsigned char key, int x, int y )
{
    // klawisz +
    if( key == '+' )
         eyez -= 0.1;
    else

    // klawisz -
    if( key == '-' )
         eyez += 0.1;

    cout << eyez << endl;
    // odrysowanie okna
    //Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
    Display();
}
int main( int argc, char * argv[] )
{lista_pol=new pole[ilosc_pol];
    // inicjalizacja biblioteki GLUT
    glutInit( & argc, argv );
    generuj_siatke(N,N,"pola.txt");

    Graf.wczytaj_graf_z_pliku("pola.txt");
    initPola();
    //Graf.wyswietl();

    // inicjalizacja bufora ramki
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

    // rozmiary g³ównego okna programu
    glutInitWindowSize( SZEROKOSC, SZEROKOSC );

    // utworzenie g³ównego okna programu
    glutCreateWindow( "Plansza" );

    // do³¹czenie funkcji generuj¹cej scenê 3D
    glutDisplayFunc( Display );

    // do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
    glutReshapeFunc( Reshape );



    // utworzenie menu podrêcznego
    int menu_trasy=glutCreateMenu( MenuTrasy );

    // dodatnie pozycji do menu podrêcznego
    glutAddMenuEntry( "Poczatek", POCZATEK );
    glutAddMenuEntry( "Cel", CEL);

    int menu_przeszkod= glutCreateMenu( MenuPrzeszkod);

    glutAddMenuEntry( "Dodaj mur", PRZESZKODA );
    glutAddMenuEntry( "Dodaj bagno", SPOWOLNIENIE_4 );
    glutAddMenuEntry( "Dodaj wode", SPOWOLNIENIE_10 );
    glutAddMenuEntry( "Wyczysc pole", ZERUJ );

    int menu_algorytmow= glutCreateMenu( MenuAlgorytmow);
    glutAddMenuEntry( "Przeszukaj A*", ASTAR );
    glutAddMenuEntry( "Przeszukaj BFS", BFS );
    glutAddMenuEntry( "Przeszukaj DFS", DFS );

    glutCreateMenu(Menu);
    glutAddSubMenu("Trasa", menu_trasy);
    glutAddSubMenu("Przeszkody", menu_przeszkod);
    glutAddSubMenu("Algorytmy", menu_algorytmow);
    glutAddMenuEntry( "Reset", RESET );
    glutAddMenuEntry( "czysc", CZYSC );
    glutAddMenuEntry( "Wyjœcie", EXIT );

    // okreœlenie przycisku myszki obs³uguj¹cej menu podrêczne
    glutAttachMenu( GLUT_RIGHT_BUTTON );

    // obs³uga przycisków myszki
    glutMouseFunc( MouseButton );

    // obs³uga ruchu kursora myszki
     glutMotionFunc( MouseMotion );

     // do³¹czenie funkcji obs³ugi klawiatury
     glutKeyboardFunc( Keyboard );

    // wprowadzenie programu do obs³ugi pêtli komunikatów
    glutMainLoop();
    return 0;
}
