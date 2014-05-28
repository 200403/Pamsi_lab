#include <string>

/*! \brief Sturktura modelujaca przedmiot
 * 	Przedmiot posiada identyfikator, wage oraz jego cene
 */
typedef struct przedmiot{
	int id; /*! \val identyfikator */
	int waga; /*! \val waga */
	int cena; /*! \val cena */
	przedmiot(): id(0),  waga(0), cena(0){};
}przedmiot;

/*! \brief Klasa modeluje rozwiazanie problemu plecakowego
 * Rozwiazanie oparte jest o programowanie dynamiczne
 *
 */
class plecak{
private:
	int ilosc; /*! \val ilosc przedmiotow */
	int waga; /*! \val maksymalna waga zawartosci plecaka */
	int **K;  /*! \valtablica kosztów dla rozwiazanie dynamicznego */
	przedmiot *elementy; /*! \val lista przedmiotow */



public:
	/*! \brief Konstruktor klasy
	 * Inicjuje wszystkie wartosc zmiennych na 0
	 */
	plecak();

	/*! \brief Dekonstruktor klasy
	 * Usuwa zmienne dynamiczne z pamieci
	 */
	~plecak();

	/*! \brief Metoda wczytujaca dane problemu z pliku
	 * Struktura danych w pliku:
	 *   max_waga ilosc_przedmiotow
	 *
	 *   waga_1 cena_1
	 *   waga_2 cena 2
	 *    ...    ...
	 *
	 *   \param nazwa - nazwa pliku do wczytania
	 *   \return true jesli wczytalo \n
	 *   		 false jest wystapil blad
	 *
	 */
	bool wczytaj_dane_z_pliku(std::string nazwa);

	/*! \brief Metoda rozwiazuje problem plecakowy
	 * Metoda wyznacza tablice rozwiaznia, z ktorej mozna pozniej odczytac
	 * ktore przedmioty nalezy zapakowac do plecaka
	 * \return Wartosc optymalnej ceny zapakowanych przedmiotow
	 */
	int rozwiaz_problem();

	/*! \brief Metoda wypisuje ktore przedmioty zostaly zapakowane
	 * Metoda wypisuje zapakowane przedmioty oraz laczna wage i cene.
	 */
	void wypisz_rozwiazanie();

	/*! \brief Metoda pomocnicza wypisujaca tablice rozwiazania
	 * Metoda wypisuje dane wczytane z pliku oraz tablice rozwiazania
	 * Sluzy ona jednynie weryfikacji rozwiazania
	 */
	void wyswietl();
};
