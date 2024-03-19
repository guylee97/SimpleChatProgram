#include "Socket.h"
Socket* Socket::sck_sgt = NULL;


Socket::Socket()
{
}

Socket::~Socket()
{
}




void recv_msg(SOCKET skt)
{
	char buffer[PACKET_SIZE] = {};
	string cmd;
	while (!WSAGetLastError()) {
		ZeroMemory(&buffer, PACKET_SIZE); 
		recv(skt, buffer, PACKET_SIZE, 0);
		cmd = buffer; 
		if (cmd == "disconnect") break; 
		cout << "받은 메세지: " << buffer << endl;
	}
}



bool Socket::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "socket_startup failed";
		return 0;
	}
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (skt == INVALID_SOCKET)
	{
		cout << "socket error";
		return 0;
	}

	clntaddr.sin_family = AF_INET;
	clntaddr.sin_port = htons(4444);
	clntaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while(1)
	{
		if(!connect(skt,(SOCKADDR*)&clntaddr,sizeof(clntaddr))) break;
	}

	thread recvThread(recv_msg, skt);

	while (!WSAGetLastError())
	{
		cin >> msg;
		send(skt, msg, strlen(msg), 0);
	}
	
	recvThread.join();
	closesocket(skt);
	WSACleanup();

	return true;
}
