#pragma once
#include "../core.h"
#include <winsock2.h>
#include <thread>

#define PACKET_SIZE 1024			//수신 받을 패킷 사이즈

class Socket
{

private:
	static Socket* sck_sgt;

public:
	static Socket* GetSck()
	{
		if (!sck_sgt)
			sck_sgt = new Socket;
		return sck_sgt;
	}

	static void DestroySck()
	{
		SAFE_DELETE(sck_sgt);
	}


private:
	WSADATA wsa;
	SOCKET skt;
	SOCKADDR_IN clntaddr;
	char msg[PACKET_SIZE] = {};


private:
	int client_size;


public:
	Socket();
	~Socket();



public:
	bool Init();



};

