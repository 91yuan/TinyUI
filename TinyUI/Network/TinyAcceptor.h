#pragma once
#include "../Common//TinyCollection.h"
#include "../IO/TinyIO.h"
#include "../Common/TinyCallback.h"
#include "../IO/TinyIOCP.h"
#include "TinyConnector.h"
#include <WinSock2.h>
#include <mswsock.h>
#pragma comment(lib,"mswsock.lib")
#pragma comment(lib,"Ws2_32.lib")

namespace TinyUI
{
#define OP_ACCEPT	1
#define OP_RECV		2
#define OP_SEND		3
	/// <summary>
	/// ½ÓÊÕÌ×½Ó×Ö
	/// </summary>
	class TinyAcceptor
	{
		friend class TinyConnector;
	public:
		TinyAcceptor(TinyIOCP& iocp);
		BOOL	Open(SOCKADDR_IN address);
		void	Close();
		BOOL	Shutdown(INT how);
		BOOL	BeginAccept(TinyConnector* connect);
	protected:
		SOCKET		m_socket;
		TinyIOCP&	m_iocp;
	};
}

