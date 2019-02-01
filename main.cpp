#include <iostream>
#include <string>
#include <windows.h>
#include "ui.h"
using namespace std;

int main()
{
 	system("chcp 1250");
	WindowSize(41, 15);
	SetConsoleTitle("Ksiêgozbiór");
	ShowConsoleCursor(false);
	welcome_scr();
}