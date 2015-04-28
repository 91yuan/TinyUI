#include "../stdafx.h"
#include "TinyObject.h"
#include "TinyCallback.h"

namespace TinyUI
{
	BOOL CallbackBase::IsNull() const
	{
		return m_caller.Ptr() == NULL;
	}
	void CallbackBase::Reset()
	{
		m_caller = NULL;
		m_invoke = NULL;
	}
	BOOL CallbackBase::Equals(const CallbackBase& other) const
	{
		return m_caller.Ptr() == other.m_caller.Ptr() &&
			m_invoke == other.m_invoke;
	}
	CallbackBase::CallbackBase(CallbackInvokeBase invoke, TinyScopedReferencePtr<CallbackRunnableBase>* caller)
		: m_invoke(invoke)
	{
		TRACE("调用CallbackBase构造函数\n");
		if (caller)
		{
			m_caller.Swap(*caller);
		}
	}
	CallbackBase::~CallbackBase() {}
};

