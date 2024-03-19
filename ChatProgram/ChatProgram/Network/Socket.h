#pragma once
#include "../core.h"
#include <winsock2.h>
#include <thread>

#define PACKET_SIZE 1024

class Socket
{
private:
	static Socket* sck_sgt;				//���� �ν��Ͻ�

public:
	static Socket* GetSck()				//�̱��� ������ �̿��� ���� �ʱ�ȭ	
	{
		if (!sck_sgt)
			sck_sgt = new Socket;
		return sck_sgt;
	}

	static void DestroySck()			//��ũ�θ� �̿��� ���� ����
	{
		SAFE_DELETE(sck_sgt);
	}



private:
	WSADATA wsa;						//���� ���̺귯�� �ʱ�ȭ�� ���� ����
	SOCKET skt,client_skt;				//���� ���ϰ� Ŭ���̾�Ʈ ����
	SOCKADDR_IN servaddr, clntaddr;		//���� �ּҿ� Ŭ���̾�Ʈ �ּ�
	char buffer[PACKET_SIZE] = { 0 };	//�޽��� ������ ���� ����

private:
	int client_size;					//Ŭ���̾�Ʈ ���� �ּ� ũ��


public:
	Socket();							
	~Socket();

public:
	bool Init();						//��� ������ ���� �ʱ�ȭ �Լ�



};

