#include "stru.h"
#include "ui.h"
#include <iostream>
#include <string>
#include <Windows.h>

void autor::drukuj_a()
{
	cout << imie << endl;
	cout << nazwisko << endl;
	cout << data << endl;
}

void Lista_Autorow::dodaj_a(string imie, string nazwisko, string data)
{
	Autor Nowy = new autor;

	Nowy->id = ilosc() + 1;
	Nowy->imie = imie ;
	Nowy->nazwisko = nazwisko;
	Nowy->data = data;

	if (pierwszy == nullptr)
		pierwszy = Nowy;
	else
	{
		Autor biezacy = pierwszy;
		while (biezacy->kolejny != nullptr)
			biezacy = biezacy->kolejny;

		biezacy->kolejny = Nowy;
	}

}

void Lista_Autorow::drukuj_la(int x, int y)
{
	Autor biezacy = pierwszy;
	int i=1;
	int c = y;
	while (biezacy != nullptr)
	{
		Gotoxy(0, c);
		cout << i << ". ";
		Gotoxy(x, c);
		cout << biezacy->imie;
		Gotoxy(x,c+1 );
		cout << biezacy->nazwisko;
		Gotoxy(x, c+2);
		cout << biezacy->data << endl;
		//cout << biezacy->books;
		c += 4;
		//biezacy->drukuj_a();
		cout << endl;
		biezacy = biezacy->kolejny;
		i++;
	}
	
}

int Lista_Autorow::ilosc()
{
	int i{};
	Autor biezacy = pierwszy;
	while (biezacy != nullptr)
	{
		i++;
		biezacy = biezacy->kolejny;
	}
	return i;
}

void Lista_Autorow::usun(int nr)
{
		Autor wczesniejszy, biezacy;
		int ind = 0;

		if (pierwszy == nullptr) return;
		if (nr == 0)
		{
			biezacy= pierwszy->kolejny;
			if (pierwszy->books == true)
			{
				cout << "NIE MOGÊ USUN¥Æ - NAPISA£ KSI¥¯KÊ";
				Sleep(1000);
			}
			else 
			{
			delete pierwszy;
			pierwszy = biezacy;
			}
		}
		else 
		{
			biezacy = pierwszy;
			wczesniejszy = pierwszy;
			while (biezacy->kolejny != nullptr&&ind < nr) 
			{
				wczesniejszy = biezacy;
				biezacy = biezacy->kolejny;
				ind++;
			}
			if (biezacy != nullptr) 
			{
				wczesniejszy->kolejny = biezacy->kolejny;
				if (biezacy->books == true)
				{
					cout << "NIE MOGÊ USUN¥Æ - NAPISA£ KSI¥¯KÊ";
					Sleep(1000);
				}
				else
				{
				delete biezacy;
				cout << "USUNIÊTO POMYŒLNIE" << endl;
				Sleep(1000);
				}
				
			}
		}
}

void ksiegozbior::dodaj(int id_a, string tytul, string data, string wydawnictwo)
{
	ksiazka* Nowa = new ksiazka;

	Nowa->id_a = id_a;
	Nowa->tytul = tytul;
	Nowa->data = data;
	Nowa->wydawnictwo=wydawnictwo;

	if (pierwsza == nullptr)
		pierwsza = Nowa;
	else
	{
		Ksiazka biezaca = pierwsza;
		while (biezaca->kolejna != nullptr)
			biezaca = biezaca->kolejna;

		biezaca->kolejna = Nowa;
	}

}

void ksiegozbior::usun(int nr)
{
	Ksiazka wczesniejsza, biezaca;
	int ind = 0;
	if (pierwsza == nullptr) return;
	if (nr == 0) {
		biezaca = pierwsza->kolejna;
		delete pierwsza;
		pierwsza = biezaca;
	}
	else {
		biezaca = pierwsza;
		wczesniejsza = pierwsza;
		while (biezaca->kolejna != nullptr&&ind < nr) {
			wczesniejsza = biezaca;
			biezaca = biezaca->kolejna;
			ind++;
		}
		if (biezaca != nullptr) {
			wczesniejsza->kolejna = biezaca->kolejna;
			delete biezaca;
		}
	}
}

int ksiegozbior::licz_b()
{
	int i{};
	Ksiazka biezaca = pierwsza;
	while (biezaca != nullptr)
	{
		i++;
		biezaca = biezaca->kolejna;
	}
	return i;
}