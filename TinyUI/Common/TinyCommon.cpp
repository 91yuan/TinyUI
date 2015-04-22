#include "../stdafx.h"
#include "TinyCommon.h"

namespace TinyUI
{
	void Trace(LPCTSTR lpszFormat, ...)
	{
		va_list args;
		va_start(args, lpszFormat);

		INT nBuf;
		TCHAR szBuffer[512];

#pragma warning(push)//���浱ǰ�ı���������״̬
#pragma warning(disable : 4996)
		nBuf = _vsntprintf(szBuffer, ARRAYSIZE(szBuffer), lpszFormat, args);
#pragma warning(pop)//�ָ�ԭ�ȵľ���״̬

		ASSERT(nBuf >= 0);

		OutputDebugString(szBuffer);

		va_end(args);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyReferenceBase::TinyReferenceBase()
		:m_cRef(0)
	{

	}
	TinyReferenceBase::~TinyReferenceBase()
	{

	}
	void TinyReferenceBase::AddRef() const
	{
		InterlockedIncrement(&m_cRef);
	}
	BOOL TinyReferenceBase::Release() const
	{
		return !InterlockedDecrement(&m_cRef);
	}
	LONG TinyReferenceBase::GetReference() const
	{
		return this->m_cRef;
	}
	//////////////////////////////////////////////////////////////////////////
	template<class T, typename Traits>
	TinyReference<T, Traits>::TinyReference()
	{

	}
	template<class T, typename Traits>
	TinyReference<T, Traits>::~TinyReference()
	{

	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::AddRef() const
	{
		TinyReferenceBase::AddRef();
	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::Release() const
	{
		if (TinyReferenceBase::Release())
		{
			Traits::Destruct(static_cast<const T*>(this));
		}
	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::Delete(const T* x)
	{
		delete x;
	}
};
