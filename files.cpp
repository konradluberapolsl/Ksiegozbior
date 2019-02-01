#include "files.h"
#include "stru.h"
#include "ui.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Lista_Autorow autorzy;

ksiegozbior ksiegi;

void load()
{

	string imie{}, nazwisko{}, data{}, linia{};
	fstream autors;
	int nr_linii = 1;
	autors.open("autorzy.txt", ios::in );
	if (autors.good() == false)
	{
		cout << "!" << endl;

	}
	while (getline(autors, linia))
	{
		//cout << linia << endl;
		switch (nr_linii)
		{
		case 1: imie = linia; break;
		case 2: nazwisko = linia; break;
		case 3: data = linia;  break;
		}
		if (nr_linii == 3) 
		{ 
			autorzy.dodaj_a(imie, nazwisko, data); 
			nr_linii = 0; 
		}
		nr_linii++;
	}
	autors.close();

	linia = "";
	string tytul{}, wydawnictwo{};
	int id{};
	fstream books;
	nr_linii = 1;
	books.open("ksiazki.txt", ios::in);
	if (books.good() == false)
	{
		cout << "!" << endl;

	}
	while (getline(books, linia))
	{
		//cout << linia << endl;
		switch (nr_linii)
		{
		case 1: id = atoi(linia.c_str()); break;
		case 2: tytul = linia; break;
		case 3: data = linia;  break;
		case 4: wydawnictwo = linia; break;
		}
		if (nr_linii == 4)
		{
			ksiegi.dodaj(id, tytul, data, wydawnictwo);
			nr_linii = 0;
		}
		nr_linii++;
	}
	books.close();
	
	if_book();
}

void if_book()
{
	Ksiazka biezaca = ksiegi.pierwsza;
	while (biezaca != nullptr)
	{
		Autor biezacy = autorzy.pierwszy;
		while (biezacy != nullptr)
		{
			if (biezacy->id == biezaca->id_a)
			{
				biezacy->books = true;
			}
			biezacy = biezacy->kolejny;
		}
		biezaca = biezaca->kolejna;
	}
}

void print()
{		
	if_book();
	autorzy.drukuj_la(3,2);
}

void add(string i, string n, string d)
{
	autorzy.dodaj_a(i, n, d);
}

void Lista_Autorow::save_a()
{
	Autor biezacy = pierwszy;
	fstream autors;
	autors.open("autorzy.txt", ios::trunc | ios::out );
	if (autors.good() == false)
	{
		cout << "Dostep do pliku zostal zabroniony!" << endl;
	}
	while (biezacy != nullptr)
	{
		autors << biezacy->imie << endl;
		autors << biezacy->nazwisko << endl;
		autors << biezacy->data << endl;

		biezacy = biezacy->kolejny;
	}
	autors.close();
}

void ksiegozbior::save_b()
{
	Ksiazka biezaca = pierwsza;
	fstream books;
	books.open("ksiazki.txt", ios::trunc | ios::out);
	if (books.good() == false)
	{
		cout << "Dostep do pliku zostal zabroniony!" << endl;
	}
	while (biezaca != nullptr)
	{
		
		ostringstream ss;
		ss << biezaca->id_a;
		string id = ss.str();

		books << id << endl;
		books << biezaca->tytul << endl;
		books << biezaca->data<< endl;
		books << biezaca->wydawnictwo << endl;

		biezaca = biezaca->kolejna;
	}
	books.close();
}

void drukuj_k(int x, int y)
{
	int i = 1;
	int c = y;
	int z=1;
	string imie{}, nazwisko{};
	
	Ksiazka biezaca = ksiegi.pierwsza;

	while (biezaca != nullptr)
	{
		imie = "";
		nazwisko = "";
		Autor biezacy = autorzy.pierwszy;
		while (biezacy != nullptr)
		{
			if (biezacy->id == biezaca->id_a)
			{
				imie = biezacy->imie;
				nazwisko = biezacy->nazwisko;
			}

			biezacy = biezacy->kolejny;
			

		}
		Gotoxy(0, c);
		cout << i << ". ";
		Gotoxy(x, c);
		cout << biezaca->tytul;
		Gotoxy(x, c + 1);
		cout<< imie << " " <<nazwisko;
		Gotoxy(x, c + 2);
		cout << biezaca->data;
		Gotoxy(x, c + 3);
		cout << biezaca->wydawnictwo;
		c += 5;
		cout << endl;
		biezaca = biezaca->kolejna;
		i++;
	}

}

void save()
{
	autorzy.save_a();
	ksiegi.save_b();
}

void a_del(int nr)
{
	if_book();
	autorzy.usun(nr);
}

int a_licz()
{
	return autorzy.ilosc();
}

void add_b(int id_a, string tytul, string data, string wydawnictwo)
{
	ksiegi.dodaj(id_a, tytul, data, wydawnictwo);
}

int b_licz()
{
	return ksiegi.licz_b();
}

void b_del(int nr)
{
	ksiegi.usun(nr);
}
