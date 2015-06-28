#include "../stdafx.h"
#include "TinySocket.h"
#include "vld.h"
#include <process.h>

namespace TinyUI
{
	extern "C"
	{
		void SocketIO::SetOperation(DWORD dwOperation)
		{
			m_dwOperation = dwOperation;
		}
		DWORD SocketIO::GetOperation()
		{
			return m_dwOperation;
		}
		SocketIO::SocketIO()
		{
			hEvent = WSACreateEvent();
			if (hEvent == NULL) throw("SocketIO创建事件失败!");
		}
		SocketIO::~SocketIO()
		{
			if (hEvent != NULL)
			{
				CloseHandle(hEvent);
				hEvent = NULL;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	ProactorSocket::ProactorSocket(INT af, INT type, INT protocol)
	{
		memset(&m_remoteAddress, 0, sizeof(SOCKADDR_IN));
		m_socket = WSASocket(af, type, protocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
		if (m_socket == INVALID_SOCKET) throw("WSASocket失败!");
	}
	ProactorSocket::~ProactorSocket()
	{
		if (m_socket != INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket = NULL;
		}
	}
	ProactorSocket::operator SOCKET() const
	{
		return m_socket;
	}
	BOOL ProactorSocket::SetOption(INT optname, const char FAR* optval, INT optlen)
	{
		return SOCKET_ERROR != setsockopt(m_socket, SOL_SOCKET, optname, optval, optlen);
	}
	BOOL ProactorSocket::GetOption(INT optname, char* optval, INT* optlen)
	{
		return SOCKET_ERROR != getsockopt(m_socket, SOL_SOCKET, optname, optval, optlen);
	}
	void ProactorSocket::Close()
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	void ProactorSocket::SetRemoteAddress(SOCKADDR_IN remoteAddress)
	{
		memcpy_s(&m_remoteAddress, sizeof(SOCKADDR_IN), &remoteAddress, 1);
	}
	//////////////////////////////////////////////////////////////////////////
	TCPServer::TCPServer()
		:ProactorSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP),
		m_lpfnAcceptEx(NULL),
		m_lpfnGetAcceptExSockaddrs(NULL)
	{

	}
	TCPServer::~TCPServer()
	{

	}
	void TCPServer::OnTask(TinyProactorIO* ps)
	{
		for (;;)
		{
			DWORD dwNumberOfBytesTransferred;
			SocketIO* socketIOPtr = NULL;
			if (!GetQueuedCompletionStatus(ps, &dwNumberOfBytesTransferred, 0, (LPOVERLAPPED*)&socketIOPtr, INFINITE))
			{

			}
		}
	}
	BOOL TCPServer::Initialize(LPCSTR ips, USHORT port)
	{
		DWORD dwBytes;
		GUID guidAcceptEx = WSAID_ACCEPTEX;
		if (WSAIoctl(m_socket,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&guidAcceptEx,
			sizeof(guidAcceptEx),
			&m_lpfnAcceptEx,
			sizeof(m_lpfnAcceptEx),
			&dwBytes,
			NULL,
			NULL))
		{
			this->Close();
			return FALSE;
		}
		GUID guidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
		if (WSAIoctl(m_socket,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&guidGetAcceptExSockaddrs,
			sizeof(guidGetAcceptExSockaddrs),
			&m_lpfnGetAcceptExSockaddrs,
			sizeof(m_lpfnGetAcceptExSockaddrs),
			&dwBytes,
			NULL,
			NULL))
		{
			this->Close();
			return FALSE;
		}
		sockaddr_in address = { 0 };
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = inet_addr(ips);
		if (bind(m_socket, (SOCKADDR *)&address, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			this->Close();
			return FALSE;
		}
		if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
		{
			this->Close();
			return FALSE;
		}
		return TRUE;
	}
	BOOL TCPServer::BeginAccept()
	{
		/*ProactorSocket acceptSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (acceptSocket == INVALID_SOCKET)
		{
			this->Close();
			return FALSE;
		}
		OVERLAPPED olOverlap;
		CHAR lpOutputBuf[1024];
		INT buffer = 1024;
		DWORD dwBytes;
		if (!m_lpfnAcceptEx(m_socket,
			acceptSocket,
			lpOutputBuf,
			buffer - ((sizeof(sockaddr_in) + 16) * 2),
			sizeof(sockaddr_in) + 16,
			sizeof(sockaddr_in) + 16,
			&dwBytes,
			&olOverlap))
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				this->Close();
				acceptSocket.Close();
				return FALSE;
			}
		}*/
		return TRUE;
	}
	BOOL TCPServer::BeginSend()
	{
		return TRUE;
	}
}
