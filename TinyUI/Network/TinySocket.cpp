#include "../stdafx.h"
#include "TinySocket.h"
#include "vld.h"
#include <process.h>

namespace TinyUI
{

	//////////////////////////////////////////////////////////////////////////
	ProactorSocket::ProactorSocket(INT af, INT type, INT protocol)
	{
		memset(&m_remoteAddress, 0, sizeof(SOCKADDR_IN));
		m_socket = WSASocket(af, type, protocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
		if (m_socket == INVALID_SOCKET) throw("WSASocket失败!");
	}
	ProactorSocket::ProactorSocket(const SOCKET socket)
		:m_socket(socket)
	{

	}
	ProactorSocket::ProactorSocket(const ProactorSocket& socket)
		: m_socket(socket.m_socket)
	{

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
		DWORD dwNumberOfBytesTransferred = 0;
		LPOVERLAPPED oa = NULL;
		ULONG_PTR    sclient = 0;
		for (;;)
		{
			if (GetQueuedCompletionStatus(ps->Handle(), &dwNumberOfBytesTransferred, (ULONG_PTR*)&sclient, (LPOVERLAPPED*)&oa, INFINITE))
			{
				TRACE("GetQueuedCompletionStatus成功~\n");
				//OVERLAPPED_PLUS* oap = reinterpret_cast<OVERLAPPED_PLUS*>(ps);
				//SocketIO<ProactorSocket*>* socketIO = reinterpret_cast<SocketIO<ProactorSocket*>*>(oap->IO);
				//DWORD dwOperation = socketIO->GetOperation();
				//switch (dwOperation)
				//{
				//case OP_ACCEPT:
				//	TRACE("OP_ACCEPT\n");
				//	//DoAccept(socketIOPtr, dwNumberOfBytesTransferred);
				//	break;
				//case OP_RECV:
				//	TRACE("OP_RECV\n");
				//	break;
				//case OP_SEND:
				//	TRACE("OP_SEND\n");
				//	break;
				//default:
				//	TRACE("无效的SocketIO~\n");
				//	break;
				//}
			}
			DWORD error = GetLastError();
			TRACE("GetQueuedCompletionStatus失败~\n");
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
		m_taskCb = BindCallback(&TCPServer::OnTask, this);
		m_proactorIO.Open(1, m_taskCb);
		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(address);
		if (bind(m_socket, (SOCKADDR *)&addr, sizeof(sockaddr_in)) == SOCKET_ERROR)
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
	/// <summary>
	/// 异步请求
	/// </summary>
	BOOL TCPServer::BeginAccept(IOCPOperation& operation, ProactorSocket& socket)
	{
		if (socket.IsAvailible())
		{
			DWORD dwReceiveDataLength = 1024;
			CHAR* outputBuffer = operation.Alloc(1024);
			DWORD dwBytes = 0;
			if (!m_lpfnAcceptEx(m_socket,
				socket,
				outputBuffer,
				dwReceiveDataLength - ((sizeof(SOCKADDR_STORAGE) + 16) * 2),
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
