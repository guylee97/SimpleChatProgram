#include "Socket.h"
Socket* Socket::sck_sgt = NULL;						//�̱��� ������ ���� static���� �ʱ�ȭ


Socket::Socket()
{
}

Socket::~Socket()
{
}

void recv_msg(SOCKET skt)							//Ŭ���̾�Ʈ�κ��� �޽����� ���� �޴� �Լ�
{
	char buffer[PACKET_SIZE] = {};

	while (!WSAGetLastError()) {					//����� �������� �ʴ� ��� ����ؼ� �޽��� ���� ����
		ZeroMemory(&buffer, PACKET_SIZE);
		recv(skt, buffer, PACKET_SIZE, 0);
		cout << "���� �޼���: " << buffer << endl;
	}

}


bool Socket::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)		//������ ���� 2.2���� ���
	{
		cout << "socket_startup failed";
		return 0;
	}
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//IPv4 ���, ���������� ������ TCP ���� ���
	if (skt == INVALID_SOCKET)
	{
		cout << "socket error";
		return 0;
	}

	servaddr.sin_family = AF_INET;					//IPv4 �ּ� ü�� ���
	servaddr.sin_port = htons(4444);				//��� ��Ʈ ����
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//�ڽ� IP ����

	bind(skt, (SOCKADDR*)&servaddr, sizeof(servaddr));//���ε� �Լ�
	listen(skt, SOMAXCONN);							//������ ����ΰ� ����Ѵ�.

	client_size = sizeof(clntaddr);
	ZeroMemory(&clntaddr, client_size);
	client_skt = accept(skt, (SOCKADDR*)&clntaddr, &client_size);//Ŭ���̾�Ʈ ������ ���� ���Ͽ� �����Ѵ�.
	thread recv_Thread(recv_msg,client_skt);		//Ŭ���̾�Ʈ�κ��� �޽����� �޴� �����带 ����.

	while (!WSAGetLastError())						//������ �������� ä�� �Ұ�
	{
		cin >> buffer;
		send(client_skt, buffer, strlen(buffer), 0);//CMDâ�� ���� ������ ������.
	}

	recv_Thread.join();			//������ �������� ��� �޸� ����
	closesocket(client_skt);
	closesocket(skt);
	WSACleanup();

	return true;
}
