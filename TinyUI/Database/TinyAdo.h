#pragma once
#include "../Common/TinyCommon.h"
#include "../Common/TinyTime.h"
#include "../Common/TinySingle.h"
#include "TinyDatabase.h"
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
typedef ::_ConnectionPtr ADOConnectionPtr;
typedef ::_Connection	 ADOConnection;
typedef ::_RecordsetPtr  ADORecordsetPtr;
typedef ::_CommandPtr	 ADOCommandPtr;

namespace TinyUI
{
	class ADOConnection;
	class ADOCommand;
	class ADODataReader;
	class ADOTransaction;
	/// <summary>
	/// ADO数据库连接
	/// </summary>
	class ADOConnection : public IDbConnection
	{
		friend class ADOCommand;
		friend class ADOTransaction;
		DISALLOW_COPY_AND_ASSIGN(ADOConnection);
	public:
		ADOConnection();
		virtual ~ADOConnection();
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
		ADOConnectionPtr	m_connectionPtr;
		ADOCommand*			m_pCommand;
		ADOTransaction*		m_pTransaction;
	};
	/// <summary>
	/// ADO数据库命令
	/// </summary>
	class ADOCommand : public IDbCommand
	{
		friend class ADOConnection;
		DISALLOW_COPY_AND_ASSIGN(ADOCommand);
	private:
		ADOCommand(ADOConnection* connection);
	public:
		virtual ~ADOCommand();
		virtual LPCSTR GetCommandText();
		virtual void SetCommandText(LPCSTR pzText);
		virtual LONG GetCommandTimeout();
		virtual void SetCommandTimeout(LONG commandTimeout);
		virtual INT	GetCommandType();
		virtual void SetCommandType(INT commandType);
		virtual IDbConnection* GetConnection();
		virtual IDbDataParameters* GetParameters();
		virtual IDbTransaction* GetTransaction();
		virtual BOOL Cancel();
		virtual IDbDataParameter* CreateParameter();
		/// <summary>
		/// 返回受影响的行数
		/// </summary>
		virtual INT ExecuteNonQuery();
		virtual IDbDataReader* ExecuteReader(INT iBehavior);
		virtual void Dispose();
	private:
		ADOCommandPtr	m_commandPtr;
		ADOConnection*	m_pConnection;
	};
	/// <summary>
	/// ADO数据库事务
	/// </summary>
	class ADOTransaction : public IDbTransaction
	{
		friend class ADOConnection;
		DISALLOW_COPY_AND_ASSIGN(ADOTransaction);
	private:
		ADOTransaction(ADOConnection* connection, INT iIsolationLevel = (INT)adXactUnspecified);
	public:
		virtual IDbConnection* GetConnection();
		virtual INT GetIsolationLevel();
		virtual BOOL Commit();
		virtual BOOL Rollback();
		virtual void Dispose();
	private:
		ADOConnection*	m_pConnection;
		INT				m_iIsolationLevel;
	};
	/// <summary>
	/// ADO数据集读取
	/// </summary>
	class ADODataReader : public IDbDataReader
	{
		friend class ADOCommand;
		friend class ADODataRow;
		DISALLOW_COPY_AND_ASSIGN(ADODataReader);
	private:
		ADODataReader(ADORecordsetPtr& recordsetPtr);
	public:
		virtual BOOL ReadNext();
		virtual BOOL ReadPrevious();
		virtual BOOL ReadFirst();
		virtual BOOL ReadLast();
		virtual BOOL Close();
		virtual INT GetColumnCount();
		virtual BOOL GetBoolean(INT i);
		virtual BYTE GetByte(INT i);
		virtual BYTE* GetBlob(INT i);
		virtual CHAR GetChar(INT i);
		virtual LPCSTR GetDataTypeName(INT i);
		virtual DATE GetDateTime(INT i);
		virtual DECIMAL GetDecimal(INT i);
		virtual DOUBLE GetDouble(INT i);
		virtual FLOAT GetFloat(INT i);
		virtual SHORT GetInt16(INT i);
		virtual INT GetInt32(INT i);
		virtual LONG GetInt64(INT i);
		virtual LPCSTR GetName(INT i);
		virtual INT GetOrdinal(LPCSTR pzName);
		virtual LPCSTR GetString(INT i);
		virtual BOOL IsDBNull(INT i);
	private:
		ADORecordsetPtr	m_recordsetPtr;
		FieldsPtr		m_fields;
	};
}