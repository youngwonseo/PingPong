#ifndef _GAME_CONTROLL_H_
#define _GAME_CONTROLL_H_


void DrawBar(int x,int y);
void DrawBar(int x,int y);

void DrawMap();

int isCollision(int y);

void MyBarUp();
void MyBarDown();
void StartGame();
void YourBarUp();
void YourBarDown();
void MoveBall();




void MoveComputer();
int isGameOver();
void ShowYourLose();
void ShowYourWin();

char * EncodingServerData();
int DecodingServerData(char * receivedData);


#endif


