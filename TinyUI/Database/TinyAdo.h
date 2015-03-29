#pragma once
#include "../Common/TinyCommon.h"
#include "../Common/TinyTime.h"
#include "../Common/TinyCollection.h"
#include "../Common/TinySingle.h"
#include "TinyDatabase.h"
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "EndOfFile") rename_namespace("ADODB")
using namespace ADODB;

typedef _ConnectionPtr	ADOConnectionPtr;
typedef _RecordsetPtr	ADORecordsetPtr;
typedef _CommandPtr		ADOCommandPtr;
typedef _ParameterPtr	ADOParameterPtr;

namespace TinyUI
{
	class ADOConnection;
	class ADOCommand;
	class ADODataReader;
	class ADOTransaction;
	class ADODataParameter;
	class ADODataParameters;
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
		virtual void	Dispose();
		virtual INT		GetErrors(LPSTR pzError, INT size);
	private:
		ADOConnectionPtr				m_connectionPtr;
		TinyScopedPtr<ADOCommand>		m_command;
		TinyScopedPtr<ADOTransaction>	m_transaction;
	};
	/// <summary>
	/// ADO数据库命令
	/// </summary>
	class ADOCommand : public IDbCommand
	{
		friend class ADOConnection;
		friend class ADODataParameters;
		DISALLOW_COPY_AND_ASSIGN(ADOCommand);
	private:
		ADOCommand(ADOConnection& connection);
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
		virtual INT ExecuteNonQuery();//一般UPDATE,DELETE,INSERT语句执行
		virtual IDbDataReader* ExecuteReader(INT iBehavior);
		virtual void Dispose();
	private:
		ADOCommandPtr								m_commandPtr;
		ADOConnection&								m_connection;
		TinyScopedPtr<ADODataParameters>			m_parameters;
		TinyArray<TinyScopedPtr<ADODataReader>*>	m_reader;
	};
	/// <summary>
	/// ADO数据库事务
	/// </summary>
	class ADOTransaction : public IDbTransaction
	{
		friend class ADOConnection;
		DISALLOW_COPY_AND_ASSIGN(ADOTransaction);
	private:
		ADOTransaction(ADOConnection& connection, INT iIsolationLevel = (INT)adXactReadUncommitted);
	public:
		virtual ~ADOTransaction();
		virtual IDbConnection* GetConnection();
		virtual INT GetIsolationLevel();
		virtual BOOL Commit();
		virtual BOOL Rollback();
		virtual void Dispose();
	private:
		ADOConnection&	m_connection;
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
		virtual ~ADODataReader();
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
		ADORecordsetPtr		m_recordsetPtr;
		FieldsPtr			m_fields;
	};
	/// <summary>
	/// ADO参数集合
	/// </summary>
	class ADODataParameters :public IDbDataParameters
	{
		friend class ADOCommand;
		friend class ADODataReader;
		DISALLOW_COPY_AND_ASSIGN(ADODataParameters);
	private:
		ADODataParameters(ADOCommand& command);
	public:
		virtual ~ADODataParameters();
		virtual IDbDataParameter* Add(IDbDataParameter* pValue);
		virtual IDbDataParameter* Add(LPCSTR pzName, VARIANT& pValue);
		virtual IDbDataParameter* Add(LPCSTR pzName, INT dbType);
		virtual IDbDataParameter* Add(LPCSTR pzName, INT dbType, INT size);
		virtual void Remove(IDbDataParameter* value);
		virtual void RemoveAt(INT index);
		virtual void RemoveAt(LPCSTR pzName);
		virtual void RemoveAll();
		virtual INT IndexOf(LPCSTR pzName);
		virtual IDbDataParameter* GetParameter(INT index);
		virtual IDbDataParameter* GetParameter(LPCSTR pzName);
		virtual BOOL Contains(IDbDataParameter* pValue);
	private:
		ADOCommand& m_command;
		TinyArray<IDbDataParameter*> m_parameters;
	};
	/// <summary>
	/// ADO参数
	/// </summary>
	class ADODataParameter : public IDbDataParameter
	{
		friend class ADOCommand;
		friend class ADODataReader;
		friend class ADODataParameters;
		DISALLOW_COPY_AND_ASSIGN(ADODataParameter);
	private:
		ADODataParameter(ADOCommandPtr&	commandPtr);
	public:
		virtual INT GetDbType();
		virtual void SetDbType(INT dbTye);
		virtual INT GetDirection();
		virtual void SetDirection(INT direction);
		virtual BOOL IsNullable();
		virtual LPCSTR GetParameterName();
		virtual void SetParameterName(LPCSTR pzName);
		virtual BYTE GetPrecision();
		virtual void SetPrecision(BYTE precision);
		virtual BYTE GetScale();
		virtual void SetScale(BYTE scale);
		virtual INT GetSize();
		virtual void SetSize(INT size);
		virtual void SetBoolean(BOOL val);
		virtual void SetByte(BYTE val);
		virtual void SetChar(CHAR val);
		virtual void SetBlob(LPBYTE val);
		virtual void SetDateTime(DATE val);
		virtual void SetDecimal(DECIMAL val);
		virtual void SetDouble(DOUBLE val);
		virtual void SetFloat(FLOAT val);
		virtual void SetInt16(SHORT val);
		virtual void SetInt32(INT val);
		virtual void SetInt64(LONG val);
		virtual void SetString(LPCSTR val);
		void		SetValue(VARIANT& val);
	private:
		ADOParameterPtr	m_parameterPtr;
		ADOCommandPtr	m_commandPtr;
		VARIANT m_value;
	};
}