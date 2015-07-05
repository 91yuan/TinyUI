#pragma once
#include "../Common//TinyCollection.h"
#include "../IO/TinyIO.h"
#include "../Common/TinyCallback.h"
#include "../IO/TinyIOCP.h"
#include <WinSock2.h>
#include <mswsock.h>
#pragma comment(lib,"mswsock.lib")
#pragma comment(lib,"Ws2_32.lib")

namespace TinyUI
{
#define OP_ACCEPT	1
#define OP_RECV		2
#define OP_SEND		3
	class TinyAcceptor;
	/// <summary>
	/// ½ÓÊÕÌ×½Ó×Ö
	/// </summary>
	class TinyConnector
	{
		friend class TinyAcceptor;
	public:
		TinyConnector(SOCKET socket = INVALID_SOCKET);
		~TinyConnector();
		BOOL	BeginConnect(SOCKADDR_IN address);
	protected:
		SOCKET	m_socket;
	};
}

