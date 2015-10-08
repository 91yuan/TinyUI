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
	class Environment
	{
	public:
		Environment();
		~Environment();
	private:
		TP_CALLBACK_ENVIRON m_em;
	};
	/// <summary>
	/// 工作线程回调
	/// </summary>
	template<class Function>
	class WorkCallback
	{
	public:
		WorkCallback(const Function fs, PVOID state, PTP_CALLBACK_ENVIRON pEnv);
		static void CALLBACK Callback(PTP_CALLBACK_INSTANCE Instance, PVOID Param, PTP_WORK work);
	private:
		Function	m_fs;
		PVOID		m_state;
		PTP_WORK	m_work;
	};
	/// <summary>
	/// 线程池
	/// </summary>
	class TinyThreadPool : public TinyReference < TinyThreadPool >
	{
	public:
		TinyThreadPool();
	private:
		HANDLE	m_hPOOL;
	};
}

