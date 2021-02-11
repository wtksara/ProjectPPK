#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <locale.h>
#include <algorithm>

using namespace std;

//Zmienne globalne u¿ywane w ca³ym programie
int i = 0;
int nr_lini = 1;
int licznik = 0;

// Deklaracja struktury typu lista przechowuj¹cej numer lini, w której wystepuje dane s³owo

struct List { // Element listy
	int numer; // Numer lini, w której wystepuje dane s³owo
	List*next; // WskaŸnik na nastepny element listy
};

// Deklaracja struktury typu drzewo przechowuj¹cej dane s³owo i jego wystepowanie w tekscie

struct wezel { // Element w drzewie
	string slowo; 
	List *glowa_listy = nullptr; // wskaznik na glowe listy 
	List *ogon_listy = nullptr; // wskaznik na ogon listy
	wezel *lewy = nullptr; // wskaznik na lewego syna 
	wezel *prawy = nullptr; // wskaznik na prawego syna 
};

// Deklaracja struktury typu lista przechowuj¹cej wskaznik na korzen(ojca) drzewa i 
struct BTS {
	wezel * korzen;
	int ile_el;
};


void dodajList(wezel *listInfo, int nr_lini) // funkcja , ktora dodaje element na koniec listy
{
	if (listInfo->glowa_listy == nullptr)
	{
		listInfo->glowa_listy = new List; // tworzy nowy element listy
		listInfo->glowa_listy->numer = nr_lini;
		listInfo->glowa_listy->next = nullptr;
		listInfo->ogon_listy = listInfo->glowa_listy;
	}
	else
	{
		listInfo->ogon_listy->next = new List; // wskaznik next wskazuje na nowy element listy
		listInfo->ogon_listy = listInfo->ogon_listy->next;  // przypisuje ogon na nowy element listy
		listInfo->ogon_listy->numer = nr_lini;   // wpisuje do listy numer lini, w ktorej wystapilo dane slowo
		listInfo->ogon_listy->next = nullptr;
	}
}

void pokazList(wezel *listInfo) // funkcja, ktora wyswietla zawartosc listy
{
	 //wskaznik o nazwie kolejny
	List* pomocnik = listInfo->glowa_listy; //kolejny wskazuje na ten sam adres co glowa
	while (pomocnik) //przeszukiwanie listy az do ostatniego elementu, ktory wskazuje na nullptr
	{
		cout << pomocnik->numer;  //wypisywanie numerow lini po przecinku
		pomocnik = pomocnik->next;//przesuwanie sie do kolejnego elementu listy
		if (pomocnik!= nullptr)
			cout << ",";
	} 
	cout << endl;
}

int porownaj_napisy(wezel * korzen, string nazwa) {

	int dlugosc;
	int dlugosc1;
	string s1;
	//przepisanie aktualnie sprawdzanego slowa do tablicy char
	dlugosc = nazwa.length();
	char * tablica;
	tablica = new char[dlugosc]; // dynamiczne alokowanie tablica
	for (int i = 0; i < dlugosc; i++)
	{
		tablica[i] = nazwa[i];
	}
	//przepisanie aktualnego slowa w wezle do tablicy char 
	s1 = korzen->slowo;
	dlugosc1 = s1.length();
	char * tablica1;
	tablica1 = new char[dlugosc1]; // dynamiczne alokowanie tablica1
	for (int i = 0; i < dlugosc1; i++)
	{
		tablica1[i] = s1[i];
	}
	//porownanie dwoch napisów
	if (_stricmp(tablica, tablica1) == 0)
	{
		return 0;
	}
	else if (_stricmp(tablica, tablica1) <= 0)
	{
		return 1; // kiedy wyraz sprawdzany jest pierwszy w kolejnosci alfabetycznej, a nastepnym jest wyraz znajdujacy sie w wezle
	}
	else if (_stricmp(tablica, tablica1) >= 0)
	{
		return 2;  // kiedy wyraz sprawdzany jest nastepny w kolejnosci alfabetycznej, a pierwszym jest wyraz znajdujacy sie w wezle
	}
};

BTS *utworz_drzewo() //funkcja tworzaca wskaznik na nowo utworzone drzewo
{
	BTS * nowe_drzewo;
	nowe_drzewo = new BTS;
	nowe_drzewo->korzen = nullptr;
	return nowe_drzewo;
};

void dodaj_el_do_drzewa(wezel * korzen, string nazwa, int nr_lini) {


	if (porownaj_napisy(korzen, nazwa) == 0)
	{
		dodajList(korzen, nr_lini);
	}
	else if (porownaj_napisy(korzen, nazwa) == 1)
	{
		if (korzen->lewy == nullptr)
		{
			
			wezel * pom;
			pom = new wezel;
			pom->slowo = nazwa;
			korzen->lewy = pom;
			dodajList(pom, nr_lini);
			
		}
		else
			dodaj_el_do_drzewa(korzen->lewy, nazwa, nr_lini);
	}
	else if (porownaj_napisy(korzen, nazwa) == 2)
	{
		if (korzen->prawy == nullptr) 
		{
			wezel * pom;
			pom = new wezel;
			pom->slowo = nazwa;
			korzen->prawy = pom;
			dodajList(pom, nr_lini);
		}
		else
		{
			dodaj_el_do_drzewa(korzen->prawy, nazwa, nr_lini);
		}
	}
};

void buduj_drzewo(BTS * info, string nazwa, int nr_lini)
{
	if (info->korzen == nullptr)
	{
		wezel*pom = new wezel;
		pom->slowo = nazwa; //Zapisywanie slowa w wezle
		pom->lewy = nullptr;
		pom->prawy = nullptr;
		info->korzen = pom;
		dodajList(info->korzen, nr_lini);
	}

	else
	{
		dodaj_el_do_drzewa(info->korzen, nazwa, nr_lini);
	}
}

bool wczytaj_tekst(BTS * info) //funkcja wczytuj¹ca dany tekst

{

	ifstream plik_wejsciowy; //utworzenie obiektu klasy ifstream
	plik_wejsciowy.open("Tekst.txt"); //skojarzenie obiektu plik_wejsciowy z plikiem
	if (!plik_wejsciowy.is_open())	 //sprawdzenie czy plik zosta³ otwarty
	{
		return false;     // je¿eli plik nie zosta³ otwarty poprawnie, zwraca wartoœæ false
	}
	string linia;
	string napis;
	string slowo;
	int dlugosc;
	do {
		getline(plik_wejsciowy, linia); //pobranie lini tekstu
		dlugosc = linia.length();  //sprawdzenie dlugosc lini tekstu
		for (int i = 0; i < dlugosc; i++)
		{
			if ((linia[i] != ':') && (linia[i] != ',') && (linia[i] != '.'))  //usuniecie z lini tekstu znaków interpunkcji i innych potencjalnych bledów uzytkownika
			{
				napis = napis + linia[i]; //zapisanie nowej lini tekstu
			}
		}
		dlugosc = napis.length();
		while (i < dlugosc) //sprawdzanie lini tekstu slowo po slowie 
		{
			if (napis[i] == ' ')
			{
				i++;
			}
			else
			{
				while ((napis[i] != ' ') && (i < dlugosc))
				{
					slowo = slowo + napis[i];
					i++;
				}
				cout << slowo << endl;
				buduj_drzewo(info, slowo, nr_lini);//wywolanie funkcji dodajacej slowo do drzewa, badz zapisujacej numer wystapienia tego slowa
				slowo = "";
				licznik++;
		     }
		}
		nr_lini++;
		cout << endl;
	} while (!plik_wejsciowy.eof()); //wykonuj az do zakonczenia pliku
	cout << " POD SPODEM WYSWIETLA SIE ELEMENTY DRZEWA" << endl;
	cout << endl;
	plik_wejsciowy.close(); //zamknij plik

	return true;
};


//1.Je¿eli drzewo bylo by posegregowane

void drukuj_drzewo(wezel * korzen) //DO EDYCJI zapis w pliku
{
	if (korzen == nullptr)
	{
		return;
	}
	else
	{
		drukuj_drzewo(korzen->lewy);
		cout << korzen->slowo << ": ";
		pokazList(korzen);
	    cout<< endl;
		drukuj_drzewo(korzen->prawy);
	}
};


bool zapisz_tekst(wezel * korzen) //funkcja zapisujaca dane z kolejnosci alfabetycznej z drzewa do pliku
{
	ofstream plik_wyjsciowy; //utworzenie obiektu klasy ofstream
	plik_wyjsciowy.open("Slowa.txt", ios_base::out | ios_base::trunc | ios_base::app) ; //skojarzenie obiektu plik_wyjsciowy z plikiem

	if (!plik_wyjsciowy.is_open())	 //sprawdzenie czy do zapisu plik zosta³ otwarty
	{
		return false;     // je¿eli plik nie zosta³ otwarty poprawnie, zwraca wartoœæ false
	}
	if (korzen == nullptr)
	{ 
		return false;
	}
	else
	{
		zapisz_tekst(korzen->lewy);
		plik_wyjsciowy << korzen->slowo << ": ";
		
		List* pomocnik = korzen->glowa_listy; //kolejny wskazuje na ten sam adres co glowa
		while (pomocnik) //przeszukiwanie listy az do ostatniego elementu, ktory wskazuje na nullptr
		{
			plik_wyjsciowy << pomocnik->numer;  //wypisywanie numerow lini po przecinku
			pomocnik = pomocnik->next;//przesuwanie sie do kolejnego elementu listy
			if (pomocnik != nullptr)
				plik_wyjsciowy << ",";
		}
		plik_wyjsciowy << endl;
		zapisz_tekst(korzen->prawy);
	}
		plik_wyjsciowy.close();
		return true;

};

int main()
{
	BTS*drzewo = utworz_drzewo();

	setlocale(LC_ALL, "polish");
	if (wczytaj_tekst(drzewo) == 0)
		cout << " Nieuda³o siê otworzyæ pliku ";

	drukuj_drzewo(drzewo->korzen);
	zapisz_tekst(drzewo->korzen);
	cout << "Licznik to " << licznik << endl;
	system("pause");
}
