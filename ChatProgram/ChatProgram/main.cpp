#include "core.h"
#include "./Network/Socket.h"



int main()
{
	
	if (!Socket::GetSck()->Init())   // ���� �ʱ�ȭ 
	{
		Socket::DestroySck();		 // �ʱ�ȭ ���н� ���� �޸� ����
		return 0;
	}
	

	return 0;
}