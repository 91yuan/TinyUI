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
		BOOL	Initialize(DWORD dwConcurrent, TaskCallback cb);
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
}

