#pragma once
#include "../Common//TinyCollection.h"
#include "../IO/TinyIO.h"
#include "../Common/TinyCallback.h"
#include "TinyProactorIO.h"
#include <string>
#include <WinSock2.h>
#include <mswsock.h>
#pragma comment(lib,"mswsock.lib")
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

namespace TinyUI
{
	extern "C"
	{
		class SocketIO : public OVERLAPPED, public TinyReference < SocketIO >
		{
		public:
			SocketIO();
			virtual ~SocketIO();
		public:
			void SetOperation(DWORD dwOperation);
			DWORD GetOperation();
		private:
			DWORD		m_dwOperation;
		};
	};
	/// <summary>
	/// 异步套接字
	/// </summary>
	class ProactorSocket
	{
	public:
		explicit ProactorSocket(INT af, INT type, INT pr);
		virtual ~ProactorSocket();
		operator SOCKET() const;
		BOOL SetOption(INT optname, const char FAR* optval, INT optlen);
		BOOL GetOption(INT optname, char* optval, INT* optlen);
		void Close();
		void SetRemoteAddress(SOCKADDR_IN remoteAddress);
	protected:
		SOCKET m_socket;
		SOCKADDR_IN m_remoteAddress;
	};
	/// <summary>
	/// TCP服务器
	/// </summary>
	class TCPServer : public ProactorSocket
	{
	public:
		TCPServer();
		~TCPServer();
	public:
		BOOL Initialize(LPCSTR ips, USHORT port);
		BOOL BeginAccept();
		BOOL BeginSend();
		BOOL BeginReceive();
	private:
		TinyProactorIO m_proactorIO;
		LPFN_ACCEPTEX  m_lpfnAcceptEx;
		LPFN_GETACCEPTEXSOCKADDRS m_lpfnGetAcceptExSockaddrs;
	private:
		void OnTask(TinyProactorIO* ps);
	};
}

