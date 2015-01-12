#include "stdafx.h"
#include "TinyWindowMsg.h"

namespace TinyUI
{
	TinyWindowMsg::TinyWindowMsg() 
		:m_pCurrentMsg(NULL), 
		m_dwState(0)
	{

	};
	TinyWindowMsg::~TinyWindowMsg()
	{
		m_pCurrentMsg = NULL;
	};
	const TinyMsg* TinyWindowMsg::GetCurrentMessage() const
	{
		return m_pCurrentMsg;
	}
	BOOL TinyWindowMsg::IsMsgHandled() const
	{
		const TinyMsg* pMsg = (TinyMsg*)GetCurrentMessage();
		ASSERT(pMsg != NULL);
		ASSERT(pMsg->cbSize >= sizeof(TinyMsg));
		return pMsg->bHandled;
	}
	void TinyWindowMsg::SetMsgHandled(BOOL bHandled)
	{
		TinyMsg* pMsg = (TinyMsg*)GetCurrentMessage();
		ASSERT(pMsg != NULL);
		ASSERT(pMsg->cbSize >= sizeof(TinyMsg));
		pMsg->bHandled = bHandled;
	}
}

