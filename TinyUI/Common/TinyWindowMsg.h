#pragma once
#include "TinyMsg.h"
#include "TinyThunk.h"

namespace TinyUI
{
	class TinyWindowMsg : public TinyMessageMap,public TinyObject
	{
		DECLARE_DYNAMIC(TinyWindowMsg)
	protected:
		const TinyMsg*	m_pCurrentMsg;
		DWORD			m_dwState;
	public:
		TinyWindowMsg();
		virtual ~TinyWindowMsg();
		const TinyMsg* GetCurrentMessage() const;
		BOOL IsMsgHandled() const;
		void SetMsgHandled(BOOL bHandled);
	};
}



