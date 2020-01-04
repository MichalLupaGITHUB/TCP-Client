#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

class TCPClinet
{
private:
	string IPAddresess;
	int port;

	WSADATA data;
	WORD ver;

	int wsResult;
	SOCKET sock;
	sockaddr_in hint;
	int connResult;
	char buf[4096];

	string userInput;
	int sendResult;
	int bytesReceived;

	void TCPClient_Init();
	void TCPClient_CreateSocekt();
	void TCPClient_Bind_IP_Port();
	void TCPClient_ConnectToServer();
	void TCPClinet_DataExchange();
	void TCPClient_CloseSocket();

public:

	TCPClinet();
	void ClientRun();

public:
	//
protected:
	//
};
