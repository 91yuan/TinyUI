#include "../stdafx.h"
#include "TinySocket.h"
#include "vld.h"

namespace TinyUI
{
	ScopeIO::ScopeIO()
		: m_data(NULL)
	{
	}
	ScopeIO::ScopeIO(INT size)
	{
		m_data = new CHAR[size];
	}
	ScopeIO::ScopeIO(CHAR* data)
		: m_data(data)
	{
	}
	ScopeIO::~ScopeIO()
	{
		SAFE_DELETE_ARRAY(m_data);
	}
	CHAR* ScopeIO::Ptr()
	{
		return m_data;
	}
	//////////////////////////////////////////////////////////////////////////
	
}
