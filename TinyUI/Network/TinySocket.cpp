#include "../stdafx.h"
#include "TinySocket.h"
#include "vld.h"
#include <process.h>

namespace TinyUI
{
	ProactorSocket::ProactorSocket()
		:m_socket(NULL)
	{

	}
	ProactorSocket::ProactorSocket(INT af, INT type, INT protocol)
		: m_socket(WSASocket(af, type, protocol, NULL, NULL, WSA_FLAG_OVERLAPPED))
	{
	}
	ProactorSocket::ProactorSocket(SOCKET socket)
		: m_socket(socket)
	{
		memset(&m_remoteAddress, 0, sizeof(SOCKADDR_IN));
	}
	ProactorSocket::ProactorSocket(const ProactorSocket& socket)
		: m_socket(socket.m_socket)
	{

	}
	ProactorSocket& ProactorSocket::operator = (const ProactorSocket& socket)
	{
		m_socket = socket.m_socket;
		return *this;
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
	SOCKET	ProactorSocket::Handle() const
	{
		return m_socket;
	}
	BOOL ProactorSocket::IsAvailible()
	{
		return m_socket != INVALID_SOCKET;
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
		if (m_socket != INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}
	}
	void ProactorSocket::SetRemoteAddress(SOCKADDR_IN remoteAddress)
	{
		memcpy_s(&m_remoteAddress, sizeof(SOCKADDR_IN), &remoteAddress, 1);
	}
	//////////////////////////////////////////////////////////////////////////
	AcceptOP::AcceptOP()
	{
		m_dwOP = OP_ACCEPT;
	}
	CHAR*	AcceptOP::data()
	{
		return m_data;
	}
	//////////////////////////////////////////////////////////////////////////
	TCPServer::TCPServer()
		: ProactorSocket(AF_INET, SOCK_STREAM, 0),
		m_lpfnAcceptEx(NULL),
		m_lpfnGetAcceptExSockaddrs(NULL)
	{
	}
	TCPServer::~TCPServer()
	{

	}
	void TCPServer::OnTask(TinyProactorIO& ps)
	{
		DWORD dwNumberOfBytesTransferred = 0;
		LPOVERLAPPED oa = NULL;
		ULONG_PTR  completionKey = 0;
		for (;;)
		{
			if (GetQueuedCompletionStatus(ps, &dwNumberOfBytesTransferred, (ULONG_PTR*)&completionKey, (LPOVERLAPPED*)&oa, INFINITE))
			{
				Operation* op = reinterpret_cast<Operation*>(oa);
				DWORD dwOperation = op->GetOperation();
				switch (dwOperation)
				{
				case OP_ACCEPT:
				{
					AcceptOP * acceptOP = reinterpret_cast<AcceptOP*>(oa);
					LPSOCKADDR localAddress = 0;
					INT localAddressLength = 0;
					LPSOCKADDR remoteAddress = 0;
					INT remoteAddressLength = 0;
					m_lpfnGetAcceptExSockaddrs((LPVOID)acceptOP->data(),
						0,
						sizeof(sockaddr_in) + 16,
						sizeof(sockaddr_in) + 16,
						&localAddress,
						&localAddressLength,
						&remoteAddress,
						&remoteAddressLength);
					acceptOP->Complete(ps, 0, 0);
				}
				break;
				case OP_RECV:
				{

				}
				break;
				case OP_SEND:
				{

				}
				break;
				}
			}
		}
	}
	BOOL TCPServer::Open(LPCSTR address, USHORT port)
	{
		DWORD dwBytes = 0;
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
			TRACE("AcceptEx ERROR\n");
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
			TRACE("GetAcceptExSockaddrs ERROR\n");
			this->Close();
			return FALSE;
		}
		BOOL bRes = m_proactorIO.Open(1, BindCallback(&TCPServer::OnTask, this));
		if (!bRes)
		{
			this->Close();
			return FALSE;
		}
		bRes = m_proactorIO.Attach((HANDLE)m_socket);
		if (!bRes)
		{
			this->Close();
			return FALSE;
		}
		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(address);
		if (bind(m_socket, (SOCKADDR *)&addr, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			TRACE("bind ERROR\n");
			this->Close();
			return FALSE;
		}
		if (listen(m_socket, 5) == SOCKET_ERROR)
		{
			TRACE("listen ERROR\n");
			this->Close();
			return FALSE;
		}
		return TRUE;
	}
	/// <summary>
	/// 异步请求
	/// </summary>
	BOOL TCPServer::BeginAccept(ProactorSocket& socket, Operation& operation)
	{
		if (socket.IsAvailible())
		{
			AcceptOP& aop = reinterpret_cast<AcceptOP&>(operation);
			DWORD dwBytes = 0;
			if (!m_lpfnAcceptEx(m_socket,
				socket,
				(LPVOID)aop.data(),
				0,
				sizeof(sockaddr_in) + 16,
				sizeof(sockaddr_in) + 16,
				&dwBytes,
				(LPOVERLAPPED)&operation))
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					this->Close();
					TRACE("AcceptEx失败~\n");
					return FALSE;
				}
			}
			TRACE("AcceptEx成功~\n");
			return TRUE;
		}
		return FALSE;
	}
	/// <summary>
	/// 异步发送
	/// </summary>
	BOOL TCPServer::BeginSend()
	{
		return TRUE;
	}
	/// <summary>
	/// 异步接收
	/// </summary>
	BOOL TCPServer::BeginReceive()
	{
		return TRUE;
	}
}
