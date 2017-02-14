
#define PORT  7000

#include "common.h"
#include "keyCurControl.h"
#include "screenOut.h"
#include "game.h"
#include "gameControll.h"
#pragma comment(lib, "ws2_32.lib")



void PlayWithComputer()
{
	/*
	int ballSpeed = 10;
	int frame = 0;
	*/
	int computerSpeed = 1;
	int computerMovingFrame = 0;

	system("cls");
	DrawMap();
	StartGame();
	
	while(1)
	{
		
		
		ProcessKeyInput();
		
		
		
		MoveBall();
		
		computerMovingFrame++;

		if(computerMovingFrame == computerSpeed)
		{
			MoveComputer();
			computerMovingFrame = 0;
			
		}

		if(isGameOver())
		{
			system("pause");
			return;
		}	
	}
	
}


void PlayWithPersonMenu()
{
	system("cls");
	ShowLogo();
	ShowWithPersonMenu();

}

void ErrorHandling(char * message)
{
	puts(message);
	exit(1);
}


void ServerMode()
{
	
	WSADATA wsaData;
	SOCKET hServSock,hClntSock;
	SOCKADDR_IN servAdr,clntAdr;
	int clntAdrSize;
	

	system("cls");
	ShowLogo();
	SetCurrentCursorPos(30,18);
	printf("나의 IP :%s \n");
	SetCurrentCursorPos(27,20);
	puts("상대방 접속 대기중");

	if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET,SOCK_STREAM,0);
	if(hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error!");

	memset(&servAdr,0,sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(PORT);

	if(bind(hServSock,(SOCKADDR*)&servAdr,sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if(listen(hServSock,5) == SOCKET_ERROR)
		ErrorHandling("listen() error");


	clntAdrSize = sizeof(clntAdr);
	hClntSock = accept(hServSock,(SOCKADDR*)&clntAdr,&clntAdrSize);
	if(hClntSock==-1)
		ErrorHandling("accept() error!");
	else
	{
		SetCurrentCursorPos(27,20);
		puts("             접속완료                   ");
		Sleep(2000);
	}


	PlayWithClient(hServSock,hClntSock);
	

	
	closesocket(hServSock);
	closesocket(hClntSock);
	WSACleanup();


	

}

void ClientMode()
{
	
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAdr;
	char serverIP[20];

	
	system("cls");
	ShowLogo();
	

	SetCurrentCursorPos(30,18);
	printf("상대방의  IP : ");
	scanf("%s",serverIP);
	
	
	

	if(WSAStartup(MAKEWORD(2,2),&wsaData) !=0)
		ErrorHandling("WSAStartup() error!");
	

	hSocket = socket(PF_INET,SOCK_STREAM,0);
	if(hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");



	memset(&servAdr,0,sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(serverIP);
	servAdr.sin_port = htons(PORT);


	SetCurrentCursorPos(30,20);
	if(connect(hSocket,(SOCKADDR*)&servAdr,sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	else
	{
		SetCurrentCursorPos(30,20);
		puts("접속완료");
	}


	PlayWithServer(hSocket);


	
	closesocket(hSocket);
	WSACleanup();
	
	

}
void Exit()
{
	exit(0);
}
DWORD WINAPI Receiver(LPVOID p)
{
	char receivedData[4];
	SOCKET hSocket = (SOCKET)p;
	int isOver=0;

	while(1)
	{
		
		if(SOCKET_ERROR == recv(hSocket,receivedData,4,0))
			break;
		
		isOver = DecodingServerData(receivedData);
		if(isOver == 1)
			break;
	}

}
void PlayWithClient(SOCKET hServSock,SOCKET hClntSock)
{
	int ballSpeed = 5;
	int frame = 0;
	int computerSpeed = 10;
	int computerMovingFrame = 50;
	char * sendData;
	HANDLE receiver = CreateThread(NULL,0,Receiver,0,0,NULL);
	system("cls");
	DrawMap();
	StartGame();
	
	while(1)
	{		
		ProcessKeyInput();

		
		MoveBall();
		sendData = EncodingServerData();
		
		send(hClntSock,sendData,4,0);
		free(sendData);
	
	
		if(isGameOver())
		{
			system("pause");
			return;
		}	
	}
}


void PlayWithServer(SOCKET hServSock)
{
	char recivedData[4];
	int isOver=0;
	system("cls");
	DrawMap();
	

	
	while(1)
	{
		
		if(SOCKET_ERROR == recv(hServSock,recivedData,4,0))
			break;
		
		isOver = DecodingServerData(recivedData);
		if(isOver == 1)
			break;
	}



}