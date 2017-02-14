#ifndef _GAME_H_
#define _GAME_H_

void PlayWithComputer();
void PlayWithPersonMenu();
void PlayWithPerson(SOCKET hServSock,SOCKET hClntSock);
void Exit();
void ServerMode();
void ClientMode();
void PlayWithServer(SOCKET hServSock);
void PlayWithClient(SOCKET hServSock,SOCKET hClntSock);
#endif