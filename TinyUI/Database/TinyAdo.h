#pragma once
#include "../Common/TinyCommon.h"
#include "../Common/TinyTime.h"
#include "TinyDatabase.h"
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
typedef ::_ConnectionPtr ADOConnectionPtr;
typedef ::_Connection	 ADOConnection;
typedef ::_RecordsetPtr  ADORecordsetPtr;

namespace TinyUI
{
	/// <summary>
	/// ADO数据库连接
	/// </summary>
	class ADOConnection : public IDbConnection
	{
	public:
		ADOConnection();
		virtual LPCSTR GetConnectionString();
		virtual void SetConnectionString(LPCSTR connectionString);
		virtual LONG GetConnectionTimeout();
		virtual void SetConnectionTimeout(LONG connectionTimeout);
		virtual IDbTransaction* BeginTransaction();
		virtual IDbTransaction* BeginTransaction(INT iIsolationLevel);
		virtual BOOL Open();
		virtual BOOL Close();
		virtual	LONG GetConnectionState();
		virtual IDbCommand* CreateCommand();
		virtual void Dispose();
	private:
		LPCSTR				m_pzErrors;
		LONG				m_connectionTimeout;
		CHAR				m_connectionString[MAX_PATH];
		ADOConnectionPtr	m_connectionPtr;
		ADORecordsetPtr		m_recordsetPtr;
	};
}