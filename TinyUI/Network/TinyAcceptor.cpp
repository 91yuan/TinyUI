#include "../stdafx.h"
#include "TinyAcceptor.h"
#include "vld.h"
#include <process.h>

namespace TinyUI
{
	TinyAcceptor::TinyAcceptor(TinyIOCP& iocp)
		:m_socket(WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, WSA_FLAG_OVERLAPPED)),
		m_iocp(iocp)
	{

	}
	BOOL TinyAcceptor::Open(SOCKADDR_IN address)
	{
		if (m_socket == INVALID_SOCKET)
		{
			return FALSE;
		}
		if (bind(m_socket, (SOCKADDR *)&address, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			return FALSE;
		}
		if (listen(m_socket, 5) == SOCKET_ERROR)
		{
			return FALSE;
		}
		return TRUE;
	}
	BOOL TinyAcceptor::BeginAccept(TinyConnector* connect)
	{
		if (m_socket == INVALID_SOCKET)
		{
			return FALSE;
		}
		return TRUE;
	}
	void TinyAcceptor::Close()
	{
		if (m_socket != INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket = NULL;
		}
	}
	BOOL TinyAcceptor::Shutdown(INT how)
	{
		if (m_socket != INVALID_SOCKET)
		{
			return shutdown(m_socket, how) != SOCKET_ERROR;
		}
		return FALSE;
	}
}