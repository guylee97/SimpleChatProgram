#include "Socket.h"
Socket* Socket::sck_sgt = NULL;						//싱글톤 패턴을 위한 static변수 초기화


Socket::Socket()
{
}

Socket::~Socket()
{
}

void recv_msg(SOCKET skt)							//클라이언트로부터 메시지를 전달 받는 함수
{
	char buffer[PACKET_SIZE] = {};

	while (!WSAGetLastError()) {					//통신이 끊어지지 않는 경우 계속해서 메시지 전달 받음
		ZeroMemory(&buffer, PACKET_SIZE);
		recv(skt, buffer, PACKET_SIZE, 0);
		cout << "받은 메세지: " << buffer << endl;
	}

}


bool Socket::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)		//윈도우 소켓 2.2버젼 사용
	{
		cout << "socket_startup failed";
		return 0;
	}
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//IPv4 사용, 연결지향형 소켓중 TCP 소켓 사용
	if (skt == INVALID_SOCKET)
	{
		cout << "socket error";
		return 0;
	}

	servaddr.sin_family = AF_INET;					//IPv4 주소 체계 사용
	servaddr.sin_port = htons(4444);				//사용 포트 지정
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//자신 IP 배정

	bind(skt, (SOCKADDR*)&servaddr, sizeof(servaddr));//바인드 함수
	listen(skt, SOMAXCONN);							//소켓을 열어두고 대기한다.

	client_size = sizeof(clntaddr);
	ZeroMemory(&clntaddr, client_size);
	client_skt = accept(skt, (SOCKADDR*)&clntaddr, &client_size);//클라이언트 소켓을 서버 소켓에 연결한다.
	thread recv_Thread(recv_msg,client_skt);		//클라이언트로부터 메시지를 받는 쓰레드를 연다.

	while (!WSAGetLastError())						//연결이 끊어지면 채팅 불가
	{
		cin >> buffer;
		send(client_skt, buffer, strlen(buffer), 0);//CMD창에 적힌 내용을 보낸다.
	}

	recv_Thread.join();			//연결이 끊어지면 모든 메모리 해제
	closesocket(client_skt);
	closesocket(skt);
	WSACleanup();

	return true;
}
