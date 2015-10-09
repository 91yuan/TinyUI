#pragma once
#include "TinyNetwork.h"

namespace TinyUI
{
	namespace Network
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
	};
}

