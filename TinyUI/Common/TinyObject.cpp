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
		//�������ü���+1
		m_reference = other.m_reference;
		if (m_reference != NULL)
		{
			m_reference->AddRef();
		}
	}

	TinyObject& TinyObject::operator = (const TinyObject& other)
	{
		//��ֵ���ü���+1
		if (this != &other)
		{
			AddRef(other);
		}
		return *this;
	}

	void TinyObject::AddRef(const TinyObject& clone)
	{
		//��������
		if (m_reference == clone.m_reference)
		{
			return;
		}
		//�ͷ�ԭʼ����
		Release();
		//�����µ�����
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
