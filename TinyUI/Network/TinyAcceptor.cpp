#include "../stdafx.h"
#include "TinyAcceptor.h"
#include "vld.h"
#include <process.h>

namespace TinyUI
{
	TinyAcceptor::TinyAcceptor(TinyIOCP& iocp, SOCKET socket)
		:m_socket(socket),
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
	BOOL TinyAcceptor::BeginAccept()
	{
		if (m_socket == INVALID_SOCKET)
		{
			return FALSE;
		}
		SOCKET socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (socket == INVALID_SOCKET)
		{
			return FALSE;
		}
		AcceptTask* op = new AcceptTask(socket);
		LPFN_ACCEPTEX lpfnAcceptEx = static_cast<LPFN_ACCEPTEX>(GetExtensionPtr(m_socket, WSAID_ACCEPTEX));
		if (!lpfnAcceptEx(m_socket,
			op->socket(),
			op->data(),
			0,
			sizeof(SOCKADDR_IN) + 16,
			sizeof(SOCKADDR_IN) + 16,
			0,
			op))
		{
			if (WSAGetLastError() != WSA_FLAG_OVERLAPPED)
			{
				SAFE_DELETE(op);
				return FALSE;
			}
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