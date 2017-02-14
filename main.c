#include "common.h"
#include "keyCurControl.h"
#include "screenOut.h"
#include "game.h"
int main()
{

	
	
	RemoveCursor();


	while(1)
	{
		system("cls");
		ShowLogo();
		ShowMenu();
		MenuSelect();	
	}
}