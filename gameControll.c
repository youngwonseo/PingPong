#include "common.h"
#include "game.h"
#include "gameControll.h"
#include "keyCurControl.h"
#include "screenOut.h"

#define BAR_MIN_Y 1
#define BAR_MAX_Y 15

#define BAR_SIZE 5

#define MY_BAR_X  10
#define YOUR_BAR_X 70

#define DATA_FORMAT_SIZE  4




int my_y = BAR_MAX_Y/2;
int your_y = BAR_MAX_Y/2;

int ball_x;
int ball_y;



int ball_direction_x;
int ball_direction_y;

int myScore = 0;
int yourScore = 0;
int stage = 1;

void DrawMap()
{
	
	SetCurrentCursorPos(0,0);
	printf("¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à");
	SetCurrentCursorPos(0,20);
	printf("¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à");
}

void ShowStateBoard(int myScore,int yourScore,int stage)
{
	SetCurrentCursorPos(25,23);
	printf("Stage . %d       My . %d  :  %d  . Your",stage,myScore,yourScore);

}
void DrawBar(int x,int y)
{
	int i;
	for(i=0;i<BAR_SIZE;i++)
	{
		SetCurrentCursorPos(x,y+i);
		printf("¡á");
	}
	
}

void DeleteBar(int x,int y)
{
	int i;
	for(i=0;i<BAR_SIZE;i++)
	{
		SetCurrentCursorPos(x,y+i);
		printf(" ");
	}
}



int isCollision(int y)
{
	if(y < BAR_MIN_Y || y > BAR_MAX_Y)
		return 0;

	return 1;
}

void MyBarUp()
{
	if(!isCollision(my_y-1))
		return;

	DeleteBar(MY_BAR_X,my_y--);
	DrawBar(MY_BAR_X,my_y);
}
void MyBarDown()
{
	if(!isCollision(my_y+1))
		return;

	DeleteBar(MY_BAR_X,my_y++);
	DrawBar(MY_BAR_X,my_y);
}

void YourBarUp()
{
	if(!isCollision(your_y-1))
		return;

	DeleteBar(YOUR_BAR_X,your_y--);
	DrawBar(YOUR_BAR_X,your_y);
}
void YourBarDown()
{
	if(!isCollision(your_y+1))
		return;

	DeleteBar(YOUR_BAR_X,your_y++);
	DrawBar(YOUR_BAR_X,your_y);
}

void DeleteBall()
{
	SetCurrentCursorPos(ball_x,ball_y);
	printf("  ");
}

void DrawBall()
{

	SetCurrentCursorPos(ball_x,ball_y);
	printf("¡Û");
}

void StartGame()
{
	srand((unsigned)time(NULL));
	rand(); rand(); rand();
	ShowStateBoard(myScore,yourScore,stage);

	ball_x = 35;
	ball_y= 10;

	ball_direction_x = -1;;
	ball_direction_y = rand()%2;
	if(ball_direction_y == 0 )
		ball_direction_y  = -1;

	DrawBar(MY_BAR_X,my_y);
	DrawBar(YOUR_BAR_X,your_y);
}

void MoveBall()
{
	
	
	

	if(ball_x - 2== MY_BAR_X && ball_y >= my_y && ball_y <= my_y+ BAR_SIZE-1)
		ball_direction_x *= -1;

	if(ball_x +  2 == YOUR_BAR_X && ball_y >= your_y && ball_y <= your_y+ BAR_SIZE-1)
		ball_direction_x *= -1;

	if(ball_x == 0 || ball_x == 78)
	{
		ball_x == 0 ? yourScore++ : myScore++;
		DeleteBall();
		StartGame();
	}
	if(ball_y - 1 == 0 || ball_y+2 == 20)
		ball_direction_y *= -1;
	
	DeleteBall();
	ball_x += ball_direction_x;
	ball_y += ball_direction_y;
	DrawBall();
	
	

}

void MoveComputer()
{
	DeleteBar(YOUR_BAR_X,your_y);


	if(ball_y > your_y)
		YourBarDown();
	else
		YourBarUp();

	DrawBar(YOUR_BAR_X,your_y);
}


int isGameOver()
{
	if(yourScore >= 15)
	{
		ShowYourLose();
		return 1;
	}
	else if(myScore >= 15)
	{
		ShowYourWin();
		return 1;
	}
	return 0;
}


void ShowYourLose()
{
	SetCurrentCursorPos(30,10);
	SetColor(3);
	puts("your are lose....");
	
}
void ShowYourWin()
{
	SetCurrentCursorPos(30,10);
	SetColor(3);
	puts("your are win!!!");
}

char * EncodingServerData(int type)
{

	char * sendData = (char*)malloc(DATA_FORMAT_SIZE);
	
	memset(sendData,0,DATA_FORMAT_SIZE);
	if(type == 0) //Server -> Client  Moving Motion
	{
		

		memset(sendData+1,(char)my_y,1);
		memset(sendData+2,(char)ball_x,1);
		memset(sendData+3,(char)ball_y,1);
	}
	else if(type== 1) //Server -> Client  Score
	{
		memset(sendData+1,(char)myScore,1);
		memset(sendData+2,(char)yourScore,1);
		memset(sendData+1,(char)stage,1);
	}
	else if(type == 2) //Client -> Server
	{

	}
	return sendData;
}

int DecodingServerData(char * receivedData)
{

	if(receivedData[0] == 0)
	{
		DeleteBar(MY_BAR_X,my_y);
		DeleteBall();

		memcpy((void*)&my_y,receivedData+1,1);
		memcpy((void*)&ball_x,receivedData+2,1);
		memcpy((void*)&ball_y,receivedData+3,1);
		//printf("%d %d %d \n",my_y,ball_x,ball_y);
	
		DrawBar(MY_BAR_X,my_y);


		DeleteBall();
		DrawBall();
	}
	else if(receivedData[0] == 1)
	{
		memcpy((void*)&myScore,receivedData+1,1);
		memcpy((void*)&yourScore,receivedData+2,1);
		memcpy((void*)&stage,receivedData+3,1);
	}
	else if(receivedData[0] == 2)
	{

	}


	return 0;
}