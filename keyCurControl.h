#ifndef _KEY_CUR_CONTROL_H_
#define _KEY_CUR_CONTROL_H_

#include "point.h"

void RemoveCursor();


point GetCurrentCursorPos();



void SetCurrentCursorPos(int x,int y);
int ProcessKeyInput();

void MenuSelect();

void setCurrentMenu(int menu);

#endif