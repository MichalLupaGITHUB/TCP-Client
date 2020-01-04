#include "TCPClinet.h"

// Constructor
TCPClinet::TCPClinet()
{

}

// Initialization
void TCPClinet::TCPClient_Init()
{
	IPAddresess = "127.0.0.1";
	port = 54000;
	ver = MAKEWORD(2, 2);
	wsResult = WSAStartup(ver, &data);

	if (wsResult != 0)
	{
		cerr << "Cannot create socket" << wsResult << endl;
		return;
	}
}

// Creating Socket
void TCPClinet::TCPClient_CreateSocekt()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Cannot create socket" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
}

// Binding Port with IP
void TCPClinet::TCPClient_Bind_IP_Port()
{
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, IPAddresess.c_str(), &hint.sin_addr);
}

// Connection to Server
void TCPClinet::TCPClient_ConnectToServer()
{
	connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Cannot connect with SERVER" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
}

// Data Exchanging with Server
void TCPClinet::TCPClinet_DataExchange()
{
	do
	{
		cout << ">";
		getline(cin, userInput);

		if (userInput.size() > 0)
		{
			sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}
	} while (userInput.size() > 0);
}

// Closing socket
void TCPClinet::TCPClient_CloseSocket()
{
	closesocket(sock);
	WSACleanup();
}

// Clinet Run
void TCPClinet::ClientRun()
{
	TCPClient_Init();
	TCPClient_CreateSocekt();
	TCPClient_Bind_IP_Port();
	TCPClient_ConnectToServer();
	TCPClinet_DataExchange();
	TCPClient_CloseSocket();
}