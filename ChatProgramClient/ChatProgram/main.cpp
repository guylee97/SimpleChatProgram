#include "core.h"
#include "./Network/Socket.h"

int main()
{
	if (!Socket::GetSck()->Init())   
	{
		Socket::DestroySck();
		return 0;
	}


	return 0;
}