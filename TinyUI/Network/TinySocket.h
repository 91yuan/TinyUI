#pragma once
#include "../Common//TinyCollection.h"
#include "../IO/TinyIO.h"
#include "../Common/TinyCallback.h"
#include "TinyProactorIO.h"
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
	/// 异步套接字
	/// </summary>
	class ProactorSocket : public TinyReference < ProactorSocket >
	{
	public:
		ProactorSocket();
		ProactorSocket(INT af, INT type, INT protocol);
		explicit ProactorSocket(SOCKET socket);
		ProactorSocket(const ProactorSocket& socket);
		ProactorSocket& operator= (const ProactorSocket& socket);
		virtual ~ProactorSocket();
		operator SOCKET() const;
		SOCKET	Handle() const;
	public:
		BOOL IsAvailible();
		BOOL SetOption(INT optname, const char FAR* optval, INT optlen);
		BOOL GetOption(INT optname, char* optval, INT* optlen);
		void Close();
		void SetRemoteAddress(SOCKADDR_IN remoteAddress);
	protected:
		SOCKET		m_socket;
		SOCKADDR_IN m_remoteAddress;
	};
	/// <summary>
	/// Accept操作
	/// </summary>
	class AcceptOP : public Operation
	{
	public:
		AcceptOP();
		CHAR*	data();
	private:
		CHAR	m_data[(sizeof(SOCKADDR_IN) + 16) * 2];
	};
	/// <summary>
	/// TCP服务器
	/// </summary>
	class TCPServer : public ProactorSocket
	{
		DISALLOW_COPY_AND_ASSIGN(TCPServer)
	public:
		TCPServer();
		~TCPServer();
	public:
		BOOL Open(LPCSTR ips, USHORT port);
		BOOL BeginAccept(ProactorSocket& socket, Operation& operation);
		BOOL BeginSend();
		BOOL BeginReceive();
	private:
		TinyProactorIO				m_proactorIO;
		LPFN_ACCEPTEX				m_lpfnAcceptEx;
		LPFN_GETACCEPTEXSOCKADDRS	m_lpfnGetAcceptExSockaddrs;
	private:
		void OnTask(TinyProactorIO& ps);
	};
}

