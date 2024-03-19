#include "core.h"
#include "./Network/Socket.h"



int main()
{
	
	if (!Socket::GetSck()->Init())   // 소켓 초기화 
	{
		Socket::DestroySck();		 // 초기화 실패시 소켓 메모리 해제
		return 0;
	}
	

	return 0;
}