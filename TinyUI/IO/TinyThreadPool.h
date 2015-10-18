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
	namespace IO
	{
		/// <summary>
		/// Ïß³Ì³Ø
		/// </summary>
		class TinyThreadPool : public TinyReference < TinyThreadPool >
		{
		public:
			TinyThreadPool();
			~TinyThreadPool();
			BOOL		Initialize(DWORD dwMin, DWORD dwMax);
			PTP_WORK	SubmitTask(PVOID ps, PTP_WORK_CALLBACK cb);
			void		WaitTask(PTP_WORK ps, BOOL fCancelPendingCallbacks);
			void		CloseTask(PTP_WORK ps);
			void		CancelPending();
			void		Close();
		private:
			PTP_POOL			m_pPool;
			PTP_CLEANUP_GROUP   m_pCleanup;
			TP_CALLBACK_ENVIRON m_cbe;
		};
	}
}

