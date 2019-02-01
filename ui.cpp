#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <sstream>
#include "ui.h"
#include "stru.h"
#include "files.h"

using namespace std;


void WindowSize(int, int);
void SetBuffer(int Width, int Height);
void remove_scrollbar();
void Back_Color(string c);
void Gotoxy(int  x, int  y);
void Fore_Color(string c);
void Highlight(int, int, string, int, int, string);
void Highlight(int, int, string);
void menu(int);
void about();
void autor_add();
void autor_print();
void book_add();
void book_print();
void del();
void del_a();
void del_b();
int autor_choose();
bool isnum(string t);
string c = "white", d = "gold";

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(out, &cursorInfo);
}

void WindowSize(int l, int c)
{
	ostringstream ll;
	ll << l;
	string ls = ll.str();

	ostringstream cc;
	cc << c;
	string cs = cc.str();

	string s1 = "MODE CON COLS=";
	string s2 = " LINES=";
	string s = s1 +ls + s2 +cs;
	system(s.c_str());

}

void SetBuffer(int Width, int Height)
{
	/*HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, Width, Height, TRUE); // 800 width, 100 height*/

	int x = Height;
	int y = Width;
	COORD coord;
	coord.X = x;
	coord.Y = y;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = 0;
	Rect.Right = 0;

	// Adjust buffer size:
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle, coord);


}

void remove_scrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

}

void Back_Color(string k)
{
	if (k == "white")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	if (k == "gold")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN );

	}
	if (k == "e")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
}

void Fore_Color(string k)
{

	if (k == "gold")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		
	}
}

void Gotoxy(int  x, int  y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void Highlight(int x1, int y1, string a, int x2, int y2, string b)
{
	Gotoxy(x1, y1);
	Back_Color(d); //higlight color
	cout << a;
	Back_Color(c);
	Gotoxy(x2, y2);
	cout <<b;
}

void Highlight(int x, int y, string a)
{
	Gotoxy(x, y);
	Back_Color(d);
	cout << a;
	Back_Color(c);
}

void welcome_scr()
{
	load();
	Back_Color(c);
	ShowConsoleCursor(false);
	Gotoxy(10, 6);
	cout << "        Witaj        " << endl;
	Gotoxy(10, 7);
	cout << "W Twoim ksiêgozbiorze" << endl;
	Gotoxy(6, 9);
	char a = 178;
	Fore_Color(d);
	for (int i = 0; i < 30; i++)
	{
		Sleep(50);
		cout << a;
	}
	
	cout << endl;
	menu(0);
}

void menu(int o)
{
	system("cls");
	save();
	if (o == 0)
		Highlight(2, 1, " Wyœwietl ksia¿ki ");
	else
	{
		Gotoxy(2, 1);
		cout << " Wyœwietl ksia¿ki ";
	}
		
	if (o == 1)
		Highlight(2, 3, " Dodaj ksia¿kê ");
	else
	{
		Gotoxy(2, 3);
		cout << " Dodaj ksia¿kê ";
	}
		
	if (o == 2)
	{
		Highlight(2, 5, " Wyœwietl autorów ");

	}
		
	else
	{
		Gotoxy(2, 5);
		cout << " Wyœwietl autorów ";
	}
		
	if (o == 3)
		Highlight(2, 7, " Dodaj autora ");
	else
	{
		Gotoxy(2, 7);
		cout << " Dodaj autora ";
	}
		
	if (o == 4)
		Highlight(2, 9, " Usuñ ");
	else
	{
		Gotoxy(2, 9);
		cout << " Usuñ ";
	}
	
	if (o == 5)
		Highlight(2, 11," O programie ");
	else
	{
	Gotoxy(2, 11);
	cout << " O programie " << endl;
	}

	Gotoxy(2, 13);
	cout << " WyjdŸ " << endl;

	for (int i = 0; i < 6; i++)
	{
		Gotoxy(23, i);

		cout << ":";
		
		
	}
	Gotoxy(24, 0);
	cout << "Masz: ";

	Gotoxy(24, 2);
	cout  << b_licz()<<". ksi¹¿ki";

	for (int i = 24; i < 41; i++)
	{
		Gotoxy(i, 5);
		cout << ".";
	}
	
	Gotoxy(24, 4);
	cout <<a_licz()<< ". autorów";

	bool end = false;
	char k{};  
	do
	{
		k = _getch();
		if (k == 80)
		{
			if (o == 0)
			{
				Highlight(2, 3, " Dodaj ksia¿kê ", 2, 1, " Wyœwietl ksia¿ki ");
				o = 1;
			}
			else if (o == 1)
			{
				Highlight(2, 5, " Wyœwietl autorów ", 2, 3," Dodaj ksi¹¿kê ");
				o = 2;
			}
			else if (o == 2)
			{
				Highlight(2, 7, " Dodaj autora ", 2, 5, " Wyœwietl autorów ");
				o = 3;
			}
			else if (o == 3)
			{
				Highlight(2, 9, " Usuñ ", 2, 7, " Dodaj autora ");
				o = 4;
			}
			else if (o == 4)
			{
				Highlight(2, 11, " O programie ", 2, 9, " Usuñ ");
				o = 5;
			}
			else if (o == 5)
			{
				Highlight(2, 13, " WyjdŸ ", 2, 11, " O programie ");
				o = 6;
			}
			else if (o == 6)
			{
				Highlight(2, 1, " Wyœwietl ksi¹¿ki ", 2, 13, " WyjdŸ ");
				o = 0;
			}
		}
		else if (k == 72)
		{
			if (o == 1)
			{
				Highlight(2, 1, " Wyœwietl ksi¹¿ki ", 2, 3, " Dodaj ksi¹¿kê ");
				o = 0;
			}
			else if (o == 2)
			{
				Highlight(2, 3, " Dodaj ksi¹¿kê ", 2, 5, " Wyœwietl autorów ");
				o = 1;
			}
			else if (o == 3)
			{
				Highlight(2, 5, " Wyœwietl autorów ", 2, 7, " Dodaj autora ");
				o = 2;
			}
			else if (o == 4)
			{
				Highlight(2, 7, " Dodaj autora ", 2, 9, " Usuñ ");
				o = 3;
			}
			else if (o == 5)
			{
				Highlight(2, 9, " Usuñ ", 2, 11, " O programie ");
				o = 4;
			}
			else if (o == 6)
			{
				Highlight(2, 11, " O programie ", 2, 13, " WyjdŸ ");
				o = 5;
			}
			else if (o == 0)
			{
				Highlight(2, 13, " WyjdŸ ", 2, 1, " Wy¿wietl ksi¹¿ki ");
				o = 6;
			}
		}
		else if (k == 13)
		{
			if (o == 6)
			{
				save();
				exit(0);
			}
			else if (o == 5)
			{
				about();
				end = true;
			}
			else if (o == 3)
			{
				autor_add();
				end = true;
			}
			else if (o == 1)
			{
				book_add();
				end = true;
			}
			else if (o == 2)
			{
				autor_print();
				
				end = true;
			}
			else if (o == 4)
			{
				del();
				end = true;
			}
			else if (o == 0)
			{
				book_print();
			}
		}
	} while (end == false);
	
}

void about()
{
	system("cls");
	Highlight(1, 0, "<- Wstecz");
	Gotoxy(2, 5);
	cout << "Projekt zaliczeniowy Programowanie I";
	Gotoxy(2, 6);
	cout << "Konrad Lubera";
	Gotoxy(2, 7);
	cout << "RMS Sem. I POLSL";
	char k{};
	do
	{
		k = _getch();
		if (k == 13)
			menu(5);
	} while (k != 27);
}

void autor_print()
{
	system("cls");
	SetBuffer(600, 300);

	Highlight(1, 0, "<- Wstecz");

	print();
	char k{};
	do
	{
		k = _getch();
		if (k == 13)
		{
			WindowSize(41, 15);
			menu(2);
		}
			
	} while (k != 27);	
	
}

void autor_add()
{
	system("cls");
	string imie{}, nazwisko{};
	Gotoxy(1, 0);
	cout << "<- Wstecz" << endl; 
	Highlight(12, 3, "Imie:");
	/*Gotoxy(12, 3);
	cout << "Imie: ";*/
	Gotoxy(8, 5);
	cout << "Nazwisko: ";
	Gotoxy(2, 7);
	cout << "Data urodzenia: DD.MM.RRRR";
	Gotoxy(18, 9);
	cout << "Dodaj";
	char k{}; int w{};
	string name{}, sname{}, date{};
	bool end=false;
	do {
		k = _getch();
		if (k == 80)
		{
			if (w == 0)
			{
				Highlight(8, 5, "Nazwisko:", 12, 3, "Imie:");
				w = 1;
			}
			else if (w == 1) 
			{
				Highlight(2, 7, "Data urodzenia:",8,5,"Nazwisko:");
				w = 2;
			}
			else if (w == 2)
			{
				Highlight(18, 9, "Dodaj", 2, 7, "Data urodzenia:");
				w = 3;
			}
			else if (w == 3)
			{
				Highlight(12, 3, "Imie", 18, 9, "Dodaj");
				w = 0;
			}
		}
		else if (k == 72)
		{
			if (w == 0)
			{
				Highlight(18, 9, "Dodaj", 12, 3, "Imie:");
				w = 3;
			}
			else if (w == 1)
			{
				Highlight(12, 3, "Imie:", 8, 5, "Nazwisko:");
				w = 0;
			}
			else if (w == 2)
			{
				Highlight(8, 5, "Nazwisko", 2, 7, "Data urodzenia:");
				w = 1;
			}
			else if (w == 3)
			{
				Highlight(2, 7, "Data urodzenia:", 18, 9, "Dodaj");
				w = 2;
			}
		}
		else if (k == 75)
		{
			
			if (w == 0)
				Highlight(1, 0, "<- Wstecz", 12, 3, "Imie:");
			else if (w == 1)
				Highlight(1,0,"<- Wstecz",8,5,"Nazwisko:");
			else if (w == 2)
				Highlight(1, 0, "<- Wstecz", 2, 7, "Data urodzenia: ");
			else if (w == 3)
				Highlight(1, 0, "<- Wstecz", 18, 9, "Dodaj");
			w = 4;
		}
		else if (k == 77)
		{
			if (w == 4)
			{
				Highlight(12, 3, "Imie:", 1, 0, "<- Wstecz");
				w = 0;
			}
		}
		else if (k == 13)
		{
			if (w == 0)
			{
				Gotoxy(18, 3);
				ShowConsoleCursor(true);
				getline(cin, name);
				ShowConsoleCursor(false);
			}
			else if (w == 1)
			{
				Gotoxy(18, 5);
				ShowConsoleCursor(true);
				getline(cin, sname);
				ShowConsoleCursor(false);
			}
			else if (w == 2)
			{
				Gotoxy(18, 7);
				ShowConsoleCursor(true);
				cin >> date;
				ShowConsoleCursor(false);
			}
			else if (w == 3)
			{
				if ((name != "") && (sname != ""))
				{
					if (date != "")
					{
						add(name, sname, date);
						Gotoxy(9, 12);
						cout << "POMYŒLNIE DODANO AUTORA";
						Sleep(1000);
						autor_add();
					}
					else
					{
						Gotoxy(9, 12);
						cout << "WYPELNIJ WSZYSTKIE POLA";
						Sleep(1000);
						autor_add();
					}
				}
				else
				{
					Gotoxy(9, 12);
					cout << "WYPELNIJ WSZYSTKIE POLA";
					Sleep(1000);
					autor_add();
				}
			}
			else if (w == 4)
			{
				menu(3);
			}
		}

	} while (end != true);
	system("pause");
}

void book_add()
{
	system("cls");
	Gotoxy(1, 0);
	cout << "<- Wstecz" << endl;
	Highlight(10, 3, "Tytu³:");
	/*Gotoxy(12, 3);
	cout << "Imie: ";*/	
	Gotoxy(10, 5);
	cout << "Autor:";
	Gotoxy(3, 7);
	cout << "Data wydania: DD.MM.RRRR";
	Gotoxy(4, 9);
	cout << "Wydawnictwo:";
	Gotoxy(18, 11);
	cout << "Dodaj";
	char k{}; int w{}, id{};
	string title{}, date{}, pub{};
	bool end = false;
	do {
		k = _getch();
		if (k == 80)
		{
			if (w == 0)
			{
				Highlight(10, 5, "Autor", 10, 3, "Tytu³:");
				w = 1;
			}
			else if (w == 1)
			{
				Highlight(3, 7, "Data wydania:", 10, 5,"Autor" );
				w = 2;
			}
			else if (w == 2)
			{
				Highlight(4, 9, "Wydawnictwo:", 3, 7, "Data wydania:");
				w = 3;
			}
			else if (w == 3)
			{
				Highlight(18,11, "Dodaj", 4,9,"Wydawnictwo:");
				w = 4;
			}
			else if (w == 4)
			{
				Highlight(10, 3, "Tytu³:", 18, 11, "Dodaj");
				w = 0;
			}
		}
		else if (k == 72)
		{
			if (w == 0)
			{
				Highlight(18, 11, "Dodaj", 10, 3, "Tytu³:");
				w = 4;
			}
			else if (w == 1)
			{
				Highlight(10, 3, "Tytu³:", 10, 5, "Autor:");
				w = 0;
			}
			else if (w == 2)
			{
				Highlight(10, 5, "Autor:", 3, 7, "Data wydania:");
				w = 1;
			}
			else if (w == 3)
			{
				Highlight(3, 7, "Data wydania:", 4, 9, "Wydawnictwo:");
				w = 2;
			}
			else if (w == 4)
			{
				Highlight(4, 9, "Wydawnictwo:", 18, 11,"Dodaj");
				w = 3;
			}
		}
		else if (k == 75)
		{

			if (w == 6)
			{

				Highlight(10, 5, "Autor:", 18, 5, "            ");
				w = 1;
			}

			else if (w == 0)
			{
				Highlight(1, 0, "<- Wstecz", 10, 3, "Tytu³:");
				w = 5;
			}
			else if (w == 1)
			{
				Highlight(1, 0, "<- Wstecz", 10, 5, "Autor:"); w = 5;
			}
			else if (w == 2) 
			{
				Highlight(1, 0, "<- Wstecz", 3, 7, "Data wydania:");
				w = 5;
			}
			else if (w == 3)
			{
				Highlight(1, 0, "<- Wstecz", 4, 9, "Wydawnictwo:");
				w = 5;
			}
			else if (w == 4)
			{
			Highlight(1, 0, "<- Wstecz", 18, 11, "Dodaj");
			w = 5;
			}

		}
		else if (k == 77)
		{
			if (w == 5)
			{
			Highlight(10, 3, "Tytu³:", 1, 0, "<- Wstecz");
			w = 0;
			}

		}
		else if (k == 13)
		{
			if (w == 0)
			{
				Gotoxy(18, 3);
				ShowConsoleCursor(true);
				getline(cin, title);
				ShowConsoleCursor(false);
			}
			else if (w == 1)
			{

				Highlight(18, 5, "Wybiez",10,5,"Autor:");
				
				w = 6;


			}
			else if (w == 2)
			{
				Gotoxy(18, 7);
				ShowConsoleCursor(true);
				getline(cin, date);
				ShowConsoleCursor(false);
			}
			else if (w == 3)
			{
				Gotoxy(18, 9);
				ShowConsoleCursor(true);
				getline(cin, pub);
				ShowConsoleCursor(false);
			}
			else if (w == 4)
			{
				if ((title != "") && (pub != ""))
				{
					if (date != "")
					{
						if (id != 0)
						{
							//add(name, sname, date);
							Gotoxy(9, 12);
							cout << "POMYŒLNIE DODANO KSI¥¯KÊ";
							add_b(id, title, date, pub);
							Sleep(1000);
							book_add();
						}
						else
						{
							Gotoxy(9, 12);
							cout << "WYPELNIJ WSZYSTKIE POLA";
							Sleep(1000);
							book_add();
						}
					}
					else  
					{
						Gotoxy(9, 12);
						cout << "WYPELNIJ WSZYSTKIE POLA";
						Sleep(1000);
						book_add();
					}
				}
				else
				{
					Gotoxy(9, 12);
					cout << "WYPELNIJ WSZYSTKIE POLA";
					Sleep(1000);
					book_add();
				}
			}
			
			else if (w == 5)
			{
				menu(1);
			}

			else if (w == 6)
			{
				id = autor_choose();
				Gotoxy(18, 5);
				cout << "WYBRANO";
				w = 1;
				Gotoxy(1, 0);
				cout << "<- Wstecz" << endl;
				Gotoxy(10, 3);
				cout << "Tytu³:" << " " << title;
				Highlight(10, 5, "Autor");
				Gotoxy(3, 7);
				cout << "Data wydania: "<<" " <<date;
				Gotoxy(4, 9);
				cout << "Wydawnictwo:"<<" "<<pub;
				Gotoxy(18, 11);
				cout << "Dodaj";
			}
		}

	} while (end != true);
	system("pause");
}

void del()
{
	system("cls");	

	Gotoxy(1, 0);
	cout << "<- Wstecz" << endl;
	Highlight(13,6, " Usuñ autora ");
	Gotoxy(12, 8);
	cout << " Usuñ  ksi¹¿kê " << endl;
	
	char k{};
	int w = 0;
	bool end = false;
	do {
		k = _getch();

		if (k == 80)
		{
			if (w == 0)
			{
				Highlight(12, 8, " Usuñ  ksi¹¿kê ", 13, 6, " Usuñ autora ");
				w = 1;
			}
			else if (w == 1)
			{
				Highlight(13, 6, " Usuñ autora ", 12, 8, " Usuñ  ksi¹¿kê " );
				w = 0;
			}

		}
		else if (k == 72)
		{
			if (w == 0)
			{
				Highlight(13, 6, " Usuñ autora ", 12, 8, " Usuñ  ksi¹¿kê ");
				w = 1;
			}
			else if (w == 1)
			{
				Highlight(12, 8, " Usuñ  ksi¹¿kê ", 13, 6, " Usuñ autora ");
				w = 0;
			}
		}
		else if (k == 75)
		{
			if (w == 0)
				Highlight(1, 0, "<- Wstecz", 13, 6, " Usuñ autora ");
			else if (w == 1)
				Highlight(1, 0, "<- Wstecz", 12, 8, " Usuñ  ksi¹¿kê ");
			w = 2;
		}
		else if (k == 77)
		{
			if (w == 2)
			{
				Highlight(13, 6, " Usuñ autora ", 1, 0, "<- Wstecz");
				w = 0;
			}
		}
		else if (k == 13)
		{
			if (w == 0)
			{
				del_a();
				end = true;
			}
			else if (w == 1)
			{
				del_b();
				end = true;
			}
			else if (w == 2)
			{
				menu(4);
			}
		}

	} while (end != true);

}

void del_a()
{
	system("cls");
	SetBuffer(250, 250);
	print();
	int b = (a_licz()*4) + 2;
	string odp{};
	Gotoxy(3, b);
	cout << "Wpisz nr który chcesz usun¹æ" << endl;
	Gotoxy(3, b+1);
	cout<<"lub 'WSTECZ' aby wróciæ:"<< endl;
	Gotoxy(3, b + 2);
	ShowConsoleCursor(true);
	cin >> odp;

	if (odp == "WSTECZ")
	{
		ShowConsoleCursor(false);
		WindowSize(41, 15);
		del();

	}	
	else if (isnum(odp) == false)
	{
		Gotoxy(3, b + 3);
		cout << "B£¥D" << endl;
		Sleep(1000);
		del_a();
	}
	else
	{
		int i = atoi(odp.c_str());
		if (i > a_licz() || (i == 0))
		{
			Gotoxy(3, b + 3);
			cout << "NIE MA TAKIEGO AUTORA" << endl;
			Sleep(1000);
			del_a();
		}
		else 
		{
			a_del(i-1);
			Gotoxy(3, b + 3);
			save();
			del_a();
		}
		
	}
	system("pause");
}

void del_b()
{
	system("cls");
	SetBuffer(250, 250);
	drukuj_k(3, 2);
	int b = (b_licz() * 5) + 2;
	string odp{};
	Gotoxy(3, b);
	cout << "Wpisz nr który chcesz usun¹æ" << endl;
	Gotoxy(3, b + 1);
	cout << "lub 'WSTECZ' aby wróciæ:" << endl;
	Gotoxy(3, b + 2);
	ShowConsoleCursor(true);
	cin >> odp;

	if (odp == "WSTECZ")
	{
		ShowConsoleCursor(false);
		WindowSize(41, 15);
		del();

	}
	else if (isnum(odp) == false)
	{
		Gotoxy(3, b + 3);
		cout << "B£¥D" << endl;
		Sleep(1000);
		del_b();
	}
	else
	{
		int i = atoi(odp.c_str());
		if (i > b_licz()  || (i==0))
		{
			Gotoxy(3, b + 3);
			cout << "NIE MA TAKIEJ KSIA¯KI" << endl;
			Sleep(1000);
			del_b();
		}
		else
		{
			b_del(i - 1);
			Gotoxy(3, b + 3);
			cout << "USUNIÊTO POMYŒLNIE" << endl;
			Sleep(1000);
			save();
			del_b();
		}

	}
	system("pause");
}

bool isnum(string t)
{
	for (int a = 0; a < t.length(); a++)
	{
		if (t[a] > '0' + 9 || t[a] < '0') return false;
	}
	return true;
}

int autor_choose()
{
	system("cls");
	SetBuffer(250, 250);
	print();
	int b = (a_licz() * 4) + 2;
	string odp{};
	Gotoxy(3, b);
	cout << "Wpisz nr autora którego " << endl;
	Gotoxy(3, b + 1);
	cout << "chcesz wybraæ:" << endl;
	Gotoxy(3, b + 2);
	ShowConsoleCursor(true);
	cin >> odp;
	if (isnum(odp) == false)
	{
		Gotoxy(3, b + 3);
		cout << "B£¥D" << endl;
		Sleep(1000);
		autor_choose();
	}
	else
	{
		int i = atoi(odp.c_str());
		if (i > a_licz())
		{
			Gotoxy(3, b + 3);
			cout << "NIE MA TAKIEGO AUTORA" << endl;
			Sleep(1000);
			autor_choose();
		}
		else
		{
			Gotoxy(3, b + 3);
			cout << "WYBRANO POMYŒLNIE" << endl;
			Sleep(1000);
			ShowConsoleCursor(false);
			WindowSize(41, 15);
			return i;
		
		}

	}
	return 0;
}

void book_print()
{
	system("cls");
	SetBuffer(600, 300);

	Highlight(1, 0, "<- Wstecz");

	drukuj_k(3, 2);
	char k{};
	do
	{
		k = _getch();
		if (k == 13)
		{
			WindowSize(41, 15);
			menu(2);
		}

	} while (k != 27);

}