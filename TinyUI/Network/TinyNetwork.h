#pragma once
#include "../Common//TinyCollection.h"
#include "../IO/TinyIO.h"
#include "../Common/TinyCallback.h"
#include "../IO/TinyIOCP.h"
#include "../IO/TinyTask.h"
#include <WinSock2.h>
#include <mswsock.h>
#pragma comment(lib,"mswsock.lib")
#pragma comment(lib,"Ws2_32.lib")

namespace TinyUI
{
	namespace Network
	{
		PVOID GetExtensionPtr(SOCKET socket, GUID guid);
		/*LPFN_GETACCEPTEXSOCKADDRS   lpfnGetAcceptExSockaddrs = NULL;
		GUID guidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
		DWORD dwBytes = 0;
		if (WSAIoctl(
		m_socket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guidGetAcceptExSockaddrs,
		sizeof(guidGetAcceptExSockaddrs),
		&lpfnGetAcceptExSockaddrs,
		sizeof(lpfnGetAcceptExSockaddrs),
		&dwBytes,
		NULL,
		NULL) == SOCKET_ERROR)
		{
		return FALSE;
		}*/
	}

}

