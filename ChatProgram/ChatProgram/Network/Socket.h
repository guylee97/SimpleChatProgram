#pragma once
#include "../core.h"
#include <winsock2.h>
#include <thread>

#define PACKET_SIZE 1024

class Socket
{
private:
	static Socket* sck_sgt;				//소켓 인스턴스

public:
	static Socket* GetSck()				//싱글톤 패턴을 이용한 소켓 초기화	
	{
		if (!sck_sgt)
			sck_sgt = new Socket;
		return sck_sgt;
	}

	static void DestroySck()			//매크로를 이용한 소켓 해제
	{
		SAFE_DELETE(sck_sgt);
	}



private:
	WSADATA wsa;						//소켓 라이브러리 초기화를 위한 변수
	SOCKET skt,client_skt;				//서버 소켓과 클라이언트 소켓
	SOCKADDR_IN servaddr, clntaddr;		//서버 주소와 클라이언트 주소
	char buffer[PACKET_SIZE] = { 0 };	//메시지 전달을 위한 버퍼

private:
	int client_size;					//클라이언트 서버 주소 크기


public:
	Socket();							
	~Socket();

public:
	bool Init();						//통신 시작을 위한 초기화 함수



};

