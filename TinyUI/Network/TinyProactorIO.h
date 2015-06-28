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
	typedef Callback<void(TinyProactorIO*)> CompletionCallback;
	/// <summary>
	/// Proactor模型
	/// </summary>
	class TinyProactorIO : public TinyReference < TinyProactorIO >
	{
	public:
		TinyProactorIO();
		virtual ~TinyProactorIO();
		operator HANDLE() const;
		BOOL	Initialize(DWORD dwConcurrent, CompletionCallback cb);
		BOOL	Attach(HANDLE handle);
		HANDLE	Detach();
	private:
		static UINT WINAPI DoTask(LPVOID ps);
	private:
		HANDLE							m_hIOCP;
		DWORD							m_dwConcurrent;
		TinyArray<HANDLE>				m_tasks;
		CompletionCallback				m_completionCb;
	};
}

