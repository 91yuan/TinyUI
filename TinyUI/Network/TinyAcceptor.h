#pragma once
#include "TinyNetwork.h"

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
		TinyAcceptor(TinyIOCP& iocp, SOCKET socket);
		BOOL	Open(SOCKADDR_IN address);
		void	Close();
		BOOL	Shutdown(INT how);
		BOOL	BeginAccept();
		static  PVOID GetExtensionPtr(SOCKET socket,GUID guid);
	protected:
		SOCKET			m_socket;
		TinyIOCP&		m_iocp;
	};
}

