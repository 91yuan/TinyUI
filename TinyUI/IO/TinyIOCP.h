#pragma once
#include "../Common/TinyCollection.h"
#include "../Common/TinySingle.h"
#include "../Common/TinyCallback.h"
#include "../Common/TinyEvent.h"
#include <string>
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

namespace TinyUI
{
	/// <summary>
	/// IOCP模型
	/// </summary>
	class TinyIOCP : public TinyReference < TinyIOCP >
	{
	public:
		TinyIOCP(DWORD dwConcurrent = 1);
		~TinyIOCP();
		operator HANDLE() const;
		HANDLE		Handle() const;
		BOOL		Register(HANDLE hFileHandle, ULONG_PTR completionKey);
		BOOL		Cancel();
		void		Close();
		HANDLE		GetFileHandle() const;
		ULONG_PTR	GetCompletionKey() const;
	public:
		typedef BOOL(WINAPI* CancelIoEx)(HANDLE, LPOVERLAPPED);
	private:
		HANDLE							m_hIOCP;
		DWORD							m_dwConcurrent;
		ULONG_PTR						m_completionKey;
		HANDLE							m_hFileHandle;
	};
}

