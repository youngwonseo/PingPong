#include "common.h"
#include "keyCurControl.h"
#include "screenOut.h"
#include "game.h"

#define MENU_1  20
#define MENU_2  22
#define MENU_3  24
#define MENU_4  26

#define MENU_SELECTOR_POS_X  22
#define MENU_X 28


int currentMaxMenu;
int currentMenuSelector_y = MENU_1;


void SetColor(int color)
{
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),color);
}



void ShowLogo()
{
	SetCurrentCursorPos(0,3);
	SetColor(12);
	puts("      □□□    ★");
	puts("    □□□□□  ★★★");
	puts("    □□□□□  ★★★★★");
	puts("    □□□□□  ★★★");
	puts("      □□□    ★");


	SetCurrentCursorPos(0,10);
	SetColor(11);
	puts("  ■■■    ■  ■      ■   ■■■     ■■■     ■■   ■      ■   ■■■");
	puts("  ■    ■  ■  ■■    ■ ■           ■    ■ ■    ■ ■■    ■ ■");
	puts("  ■■■    ■  ■  ■  ■ ■    ■■   ■■■   ■    ■ ■ ■   ■ ■    ■■");
	puts("  ■        ■  ■    ■■ ■      ■   ■       ■    ■ ■    ■■ ■      ■");
	puts("  ■        ■  ■      ■   ■■■     ■         ■■   ■      ■   ■■■");
	SetColor(15);
	puts("                                 SWL GAMES");

}
void ShowMenu(){
	setCurrentMenu(0);
	currentMenuSelector_y = MENU_1;
	currentMaxMenu = MENU_4;
	SetColor(14);
	SetCurrentCursorPos(MENU_X,MENU_1);
	puts("1. 컴퓨터와 게임하기");
	SetCurrentCursorPos(MENU_X,MENU_2);
	puts("2. 사람과 게임하기");
	SetCurrentCursorPos(MENU_X,MENU_3);
	puts("3. 기록보기");
	SetCurrentCursorPos(MENU_X,MENU_4);
	puts("4. 종료");
	
	SetCurrentCursorPos(MENU_SELECTOR_POS_X,currentMenuSelector_y);
	SetColor(15);
	printf("▶");

	
}

void ShowWithPersonMenu()
{
	setCurrentMenu(1);
	currentMenuSelector_y = MENU_1;
	currentMaxMenu = MENU_3;
	SetColor(14);
	SetCurrentCursorPos(MENU_X,MENU_1);
	puts("1. 방 만들기");
	SetCurrentCursorPos(MENU_X,MENU_2);
	puts("2. 방 참여하기");
	SetCurrentCursorPos(MENU_X,MENU_3);
	puts("3. 뒤로");

	SetCurrentCursorPos(MENU_SELECTOR_POS_X,currentMenuSelector_y);
	SetColor(15);
	printf("▶");
}


void DownMenuSelector()
{
	SetCurrentCursorPos(MENU_SELECTOR_POS_X,currentMenuSelector_y);
	printf(" ");
	if(!(currentMenuSelector_y >= currentMaxMenu))
		currentMenuSelector_y+=2;
	
	SetCurrentCursorPos(MENU_SELECTOR_POS_X,currentMenuSelector_y);
	printf("▶");
}
void UpMenuSelector()
{

	SetCurrentCursorPos(MENU_SELECTOR_POS_X,currentMenuSelector_y);
	printf(" ");

	if(!(currentMenuSelector_y <= MENU_1))
		currentMenuSelector_y-=2;

	SetCurrentCursorPos(MENU_SELECTOR_POS_X,currentMenuSelector_y);
	printf("▶");
}
void SelectMenuController()
{
	
	switch(currentMenuSelector_y)
	{
	case MENU_1:
		PlayWithComputer();
		break;
	case MENU_2:
		PlayWithPersonMenu();
		break;
	case MENU_3:
		break;
	case MENU_4:
		Exit();
		break;
	}
}


void SelectWithPersonMenuController()
{
	
	switch(currentMenuSelector_y)
	{
	case MENU_1:
		ServerMode();
		break;
	case MENU_2:
		ClientMode();
		break;
	case MENU_3:
		SetCurrentCursorPos(MENU_SELECTOR_POS_X,currentMenuSelector_y);
		printf("  ");
		ShowMenu();
		break;
	}
}

