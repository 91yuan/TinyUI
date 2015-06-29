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
	class TinyProactorIO;
	typedef Callback<void(TinyProactorIO*)> TaskCallback;
	/// <summary>
	/// Proactor模型
	/// </summary>
	class TinyProactorIO : public TinyReference < TinyProactorIO >
	{
	public:
		TinyProactorIO();
		virtual ~TinyProactorIO();
		operator HANDLE() const;
		HANDLE	Handle() const;
		BOOL	Open(DWORD dwConcurrent, TaskCallback cb);
		BOOL	Cancel();
		void	Close();
		BOOL	Attach(HANDLE handle);
		HANDLE	Detach();
	private:
		static UINT WINAPI DoTask(LPVOID ps);
	private:
		HANDLE							m_hIOCP;
		DWORD							m_dwConcurrent;
		TinyArray<HANDLE>				m_tasks;
		TaskCallback				m_completionCb;
	};
	/// <summary>
	/// IOCP操作
	/// </summary>
	class IOCPOperation : public OVERLAPPED
	{
	public:
		IOCPOperation();
		~IOCPOperation();
		void	Complete(TinyProactorIO& owner, const DWORD dwError, DWORD dwBytestransferred);
		void	Pending(TinyProactorIO& owner, const DWORD dwError, DWORD dwBytestransferred);
		void	Reset();
		CHAR*	Alloc(size_t size);
	protected:
		Callback<void(TinyProactorIO& owner, const DWORD dwError, DWORD dwBytestransferred)> CompleteCallback;
		Callback<void(TinyProactorIO& owner, const DWORD dwError, DWORD dwBytestransferred)> PendingCallback;
	private:
		TinyScopedArray<CHAR> m_buffer;
	};
}

