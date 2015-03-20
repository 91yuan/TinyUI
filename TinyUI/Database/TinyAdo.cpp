#include "../stdafx.h"
#include "TinyAdo.h"

namespace TinyUI
{
	ADOConnection::ADOConnection()
		:m_pzErrors(NULL)
	{

	}
	LPCSTR ADOConnection::GetConnectionString()
	{
		return m_connectionString;
	}

	void ADOConnection::SetConnectionString(LPCSTR connectionString)
	{
		ASSERT(connectionString);
		if (strcmp(m_connectionString, connectionString))
		{
			strcpy_s(m_connectionString, MAX_PATH, connectionString);
		}

	}

	LONG ADOConnection::GetConnectionTimeout()
	{
		return m_connectionTimeout;
	}

	void ADOConnection::SetConnectionTimeout(LONG connectionTimeout)
	{
		if (m_connectionTimeout != connectionTimeout)
		{
			m_connectionTimeout = connectionTimeout;
			m_connectionPtr->CommandTimeout = m_connectionTimeout;
		}

	}
	LONG ADOConnection::GetConnectionState()
	{
		return m_connectionPtr->State;
	}
	IDbTransaction* ADOConnection::BeginTransaction()
	{
		return NULL;
	}

	IDbTransaction* ADOConnection::BeginTransaction(INT iIsolationLevel)
	{
		return NULL;
	}

	BOOL ADOConnection::Open()
	{
		HRESULT hRes = S_OK;
		hRes = m_connectionPtr.CreateInstance(__uuidof(Connection));
		if (SUCCEEDED(hRes))
		{
			m_connectionPtr->ConnectionTimeout = m_connectionTimeout;
			hRes = m_connectionPtr->Open(m_connectionString, "", "", adModeUnknown);
			if (SUCCEEDED(hRes)) return TRUE;
			return FALSE;
		}
		return FALSE;
	}

	BOOL ADOConnection::Close()
	{
		return SUCCEEDED(m_connectionPtr->Close());
	}

	IDbCommand* ADOConnection::CreateCommand()
	{
		return NULL;
	}

	void ADOConnection::Dispose()
	{
		m_connectionPtr->Release();
	}

}