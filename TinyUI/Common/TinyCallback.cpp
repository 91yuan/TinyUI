#include "../stdafx.h"
#include "TinyObject.h"
#include "TinyCallback.h"

namespace TinyUI
{
	BOOL CallbackBase::IsNull() const
	{
		return m_storage.Ptr() == NULL;
	}
	void CallbackBase::Reset()
	{
		m_storage = NULL;
		m_invoke = NULL;
	}
	BOOL CallbackBase::operator==(const CallbackBase& other) const
	{
		return m_storage.Ptr() == other.m_storage.Ptr() && m_invoke == other.m_invoke;
	}
	CallbackBase::CallbackBase(InvokeBase invoke, InvokerStorageBase* storage)
		: m_invoke(invoke),
		m_storage(storage)
	{

	}
	CallbackBase::CallbackBase(const CallbackBase& other)
		: m_invoke(other.m_invoke),
		m_storage(other.m_storage)
	{
	}
	CallbackBase& CallbackBase::operator = (const CallbackBase& other)
	{
		m_invoke = other.m_invoke;
		m_storage = other.m_storage;
		return *this;
	}
	CallbackBase::~CallbackBase()
	{
	}
};

