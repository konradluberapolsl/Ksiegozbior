#pragma once
#include <string>

using namespace std;

struct autor
{
	int id;
	string imie;
	string nazwisko;
	string data;
	bool books;

	autor* kolejny{};

	

	void drukuj_a();
};

using Autor = autor * ;

struct ksiazka
{
	int id_a;
	string tytul;
	string data;
	string wydawnictwo;
		

	ksiazka* kolejna{};
};

using Ksiazka = ksiazka * ;

struct Lista_Autorow
{
	
	autor *pierwszy{};
	
	void dodaj_a(string imie, string nazwisko, string data);

	void drukuj_la(int x, int y);

	void save_a();

	void usun(int nr);

	int ilosc();
};

struct ksiegozbior
{
	Ksiazka pierwsza{};

	void dodaj(int id_a, string tytul, string data, string wydawnictwo);

	void usun(int);

	int licz_b();

	void save_b();
};