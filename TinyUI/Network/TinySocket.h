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
			void	SetOperation(DWORD dwOperation);
			DWORD	GetOperation();
		private:
			DWORD	m_dwOperation;
		};
	};
#define OP_ACCEPT	1
#define OP_RECV		2
#define OP_SEND		3
	/// <summary>
	/// 异步套接字
	/// </summary>
	class ProactorSocket
	{
	public:
		explicit ProactorSocket(INT af, INT type, INT pr);
		ProactorSocket(const SOCKET socket);
		ProactorSocket(const ProactorSocket* socket);
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
	/// Accept异步套接字IO
	/// </summary>
	class AcceptSocketIO : public SocketIO
	{
	public:
		AcceptSocketIO();
		BOOL Initialize(INT af, INT type, INT pr);
		ProactorSocket* GetSocket() const;
	private:
		TinyScopedReferencePtr<ProactorSocket> m_socket;
	};
	typedef typename Callback<void(TinyScopedReferencePtr<ProactorSocket>)> AcceptCallback;
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
	protected:
		virtual void DoAccept(AcceptSocketIO* socketIO, DWORD dwNumberOfBytesTransferred);
	private:
		TinyProactorIO				m_proactorIO;
		LPFN_ACCEPTEX				m_lpfnAcceptEx;
		LPFN_GETACCEPTEXSOCKADDRS	m_lpfnGetAcceptExSockaddrs;
		TaskCallback				m_taskCb;//任务回调
		AcceptCallback				m_acceptCb;//返回套接字的回调
	private:
		void OnTask(TinyProactorIO* ps);
	};
}

