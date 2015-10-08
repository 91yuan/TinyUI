#include "../stdafx.h"
#include "vld.h"
#include <process.h>
#include "TinyThreadPool.h"

namespace TinyUI
{
	Environment::Environment()
	{
		InitializeThreadpoolEnvironment(&m_em);
	}
	Environment::~Environment()
	{

	}
	//////////////////////////////////////////////////////////////////////////
	template<class Function>
	WorkCallback::WorkCallback(const Function fs, PVOID state, PTP_CALLBACK_ENVIRON pEv)
		:m_fs(fs),
		m_state(state)
	{
		m_work = CreateThreadpoolWork(Callback, this, pEv);
		if (m_work != NULL)
		{
			SubmitThreadpoolWork(m_work);
		}
	}
	template<class Function>
	void CALLBACK WorkCallback::Callback(PTP_CALLBACK_INSTANCE instance, PVOID param, PTP_WORK work)
	{
		UNREFERENCED_PARAMETER(instance);
		UNREFERENCED_PARAMETER(work);
		TaskCallback<Function> *cb = reinterpret_cast<TaskCallback<Function>*>(param);
		cb->m_fs(cb->m_state);
		SAFE_DELETE(cb);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyThreadPool::TinyThreadPool()
		:m_hPOOL(NULL)
	{

	}
}
