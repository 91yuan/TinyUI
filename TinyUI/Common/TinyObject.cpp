#include "../stdafx.h"
#include "TinyObject.h"

namespace TinyUI
{
	TinyObject::TinyObject()
		:m_reference(NULL)
	{

	}
	TinyObject::~TinyObject()
	{
		Release();
	}
	TinyObject::TinyObject(const TinyObject& other)
	{
		//拷贝引用计数+1
		m_reference = other.m_reference;
		if (m_reference != NULL)
		{
			m_reference->AddRef();
		}
	}

	TinyObject& TinyObject::operator = (const TinyObject& other)
	{
		//赋值引用计数+1
		if (this != &other)
		{
			AddRef(other);
		}
		return *this;
	}

	void TinyObject::AddRef(const TinyObject& clone)
	{
		//忽略自身
		if (m_reference == clone.m_reference)
		{
			return;
		}
		//释放原始数据
		Release();
		//引用新的数据
		if (clone.m_reference != NULL)
		{
			m_reference = clone.m_reference;
			m_reference->AddRef();
		}
	}

	void TinyObject::Release()
	{
		if (m_reference != NULL)
		{
			m_reference->Release();
			m_reference = NULL;
		}
	}
	TinyReference* TinyObject::CreateReference() const
	{
		return NULL;
	}
	TinyReference* TinyObject::CloneReference(const TinyReference* data) const
	{
		return NULL;
	}
};
