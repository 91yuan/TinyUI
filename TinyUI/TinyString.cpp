#include "stdafx.h"
#include "TinyString.h"

namespace TinyUI
{
	/*TinyString::TinyString()
		:m_ps(NULL), m_size(0)
		{

		}
		TinyString::TinyString(const CHAR* s)
		{
		m_size = strlen(s);
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size, s, m_size);
		m_ps[m_size] = '\0';
		}
		TinyString::TinyString(const TinyString& s)
		{
		if (m_ps != NULL)
		{
		SAFE_DELETE_ARRAY(m_ps);
		m_size = s.m_size;
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size*sizeof(CHAR), s.m_ps, s.m_size*sizeof(CHAR));
		}
		else
		{
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size*sizeof(CHAR), s.m_ps, s.m_size*sizeof(CHAR));
		}
		}
		TinyString::~TinyString()
		{
		if (m_ps != NULL)
		{
		SAFE_DELETE_ARRAY(m_ps);
		}
		}
		CHAR TinyString::operator[](INT pos) const
		{
		ASSERT(pos >= 0 && pos <= m_size);
		return m_ps[pos];
		}
		TinyString& TinyString::operator = (const TinyString &s)
		{

		}
		TinyString& TinyString::Assign(const CHAR* s)
		{
		if (m_ps != NULL)
		{
		SAFE_DELETE_ARRAY(m_ps);
		m_size = strlen(s);
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size, s, m_size);
		m_ps[m_size] = '\0';
		}
		else
		{
		m_size = strlen(s);
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size, s, m_size);
		m_ps[m_size] = '\0';
		}
		return (*this);
		}
		TinyString& TinyString::Assign(const CHAR* s, INT n)
		{
		if (m_ps != NULL)
		{
		SAFE_DELETE_ARRAY(m_ps);
		m_size = strlen(s);
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size, s, m_size);
		m_ps[m_size] = '\0';
		}
		else
		{
		m_size = strlen(s);
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size, s, m_size);
		m_ps[m_size] = '\0';
		}
		return (*this);
		}
		TinyString& TinyString::Assign(const TinyString& s)
		{
		if (m_ps != NULL)
		{
		SAFE_DELETE_ARRAY(m_ps);
		m_size = s.m_size;
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size*sizeof(CHAR), s.m_ps, s.m_size*sizeof(CHAR));
		}
		else
		{
		m_ps = new CHAR[m_size + 1];
		ASSERT(m_ps);
		memcpy_s(m_ps, m_size*sizeof(CHAR), s.m_ps, s.m_size*sizeof(CHAR));
		}
		return (*this);
		}
		TinyString& TinyString::Assign(const TinyString& s, INT start, INT n)
		{

		return (*this);
		}
		TinyString& TinyString::operator += (const TinyString &s)
		{
		INT size = m_size + s.m_size;
		CHAR* ps = new CHAR[size + 1];

		}
		TinyString& TinyString::Append(const CHAR* s)
		{
		return (*this);
		}
		TinyString& TinyString::Append(const CHAR* s, INT n)
		{
		return (*this);
		}
		TinyString& TinyString::Append(const TinyString &s)
		{
		return (*this);
		}
		TinyString& TinyString::Append(const TinyString &s, INT pos, INT n)
		{
		return (*this);
		}*/
}

