#include "common.h"
#include "point.h"
#include "screenOut.h"
#include "keyCurControl.h"
#include "game.h"
#include "gameControll.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

#define KEY_SENSITIVE 1000
#define SYS_DELAY  10

static int keyDelayRate = 800;
static int currentMenu = 0;   


void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
}


point GetCurrentCursorPos()
{
	point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;

}



void SetCurrentCursorPos(int x,int y)
{
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void setCurrentMenu(int menuNum)
{
	currentMenu = menuNum;
}
void MenuSelect()
{
	int i;
	int key;
	while(1)
	{
		if(_kbhit() != 0)
		{
			key = _getch();

			switch(key)
			{
			case UP:
				UpMenuSelector();
				break;
			case DOWN:
				DownMenuSelector();
				break;
			case SPACE:
				if(currentMenu == 0)
					SelectMenuController();
				else if(currentMenu == 1)
					SelectWithPersonMenuController();
				break;
			}
		}
	}
}





int ProcessKeyInput()
{
	int i;
	int key;

	for(i=0;i<KEY_SENSITIVE; i++)
	{
		if(_kbhit() != 0) 
        {
            key = _getch();
            	            
            switch(key)
            {
            case UP:
				MyBarUp();
                break;
			case DOWN:
				MyBarDown();
				break;
            case SPACE:
               
                break;
            }
        }
    
        if(i % keyDelayRate == 0)
            Sleep(SYS_DELAY);

	}

}

void InitKeyDelayRate(int rate)
{
	if(rate < 1)
		return;
	keyDelayRate = rate;
}

void KeyDelaySpeedCtl(int addSpeed)
{
	keyDelayRate += addSpeed;
}