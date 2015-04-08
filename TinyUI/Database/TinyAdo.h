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
	class ADODataParameter;
	/// <summary>
	/// ADO数据库连接
	/// </summary>
	class ADOConnection : public IDbConnection
	{
		friend class ADOCommand;
		DISALLOW_COPY_AND_ASSIGN(ADOConnection);
	public:
		ADOConnection();
		virtual ~ADOConnection();
		virtual LPCSTR			GetConnectionString() const;
		virtual void			SetConnectionString(LPCSTR pzText);
		virtual LONG			GetConnectionTimeout() const;
		virtual void			SetConnectionTimeout(LONG timeMS);
		virtual BOOL			Open();
		virtual BOOL			Close();
		virtual	LONG			GetConnectionState();
		virtual BOOL			BeginTransaction(INT iIsolationLevel = adXactReadUncommitted);
		virtual BOOL			CommitTransaction();
		virtual BOOL			RollbackTransaction();
		virtual void			GetErrors(LPSTR pzError, INT& size);
	private:
		ADOConnectionPtr	m_connectionPtr;
	};
	/// <summary>
	/// ADO数据库命令
	/// </summary>
	class ADOCommand : public IDbCommand
	{
		friend class ADOConnection;
		DISALLOW_IMPLICIT_CONSTRUCTORS(ADOCommand);
	public:
		ADOCommand(ADOConnection& connection);
		virtual ~ADOCommand();
		virtual LPCSTR				GetCommandText() const;
		virtual void				SetCommandText(LPCSTR pzText);
		virtual LONG				GetCommandTimeout() const;
		virtual void				SetCommandTimeout(LONG timeMS);
		virtual INT					GetCommandType();
		virtual void				SetCommandType(INT commandType);
		virtual IDbConnection*		GetConnection();
		virtual	BOOL				Add(IDbDataParameter* ps);
		virtual	BOOL				Remove(INT i);
		virtual	BOOL				Remove(LPCSTR pzName);
		virtual BOOL				RemoveAll();
		virtual INT					ExecuteNonQuery();
		virtual BOOL				ExecuteReader(IDbDataReader* ps);
		virtual BOOL				Cancel();
	private:
		ADOCommandPtr	m_commandPtr;
		ADOConnection&	m_connection;
	};
	/// <summary>
	/// 数据库参数
	/// </summary>
	class ADODataParameter : public IDbDataParameter
	{
		friend class ADOCommand;
		DISALLOW_IMPLICIT_CONSTRUCTORS(ADODataParameter);
	public:
		ADODataParameter(ADOCommand& command);
		virtual ~ADODataParameter();
		virtual BOOL	IsNullable();
		virtual INT		GetDbType();
		virtual void	SetDbType(INT dbTye);
		virtual INT		GetDirection();
		virtual void	SetDirection(INT direction);
		virtual LPCSTR	GetParameterName();
		virtual void	SetParameterName(LPCSTR pzName);
		virtual BYTE	GetPrecision();
		virtual void	SetPrecision(BYTE precision);
		virtual BYTE	GetScale();
		virtual void	SetScale(BYTE scale);
		virtual INT		GetSize();
		virtual void	SetSize(INT size);
		virtual	void	SetNull();
		virtual void	SetBoolean(BOOL val);
		virtual void	SetByte(BYTE val);
		virtual void	SetChar(CHAR val);
		virtual	void	SetBlob(LPBYTE val, LONG size);
		virtual void	SetDateTime(DATE val);
		virtual void	SetDecimal(DECIMAL val);
		virtual void	SetDouble(DOUBLE val);
		virtual void	SetFloat(FLOAT val);
		virtual void	SetInt16(SHORT val);
		virtual void	SetInt32(INT val);
		virtual void	SetInt64(LONG val);
		virtual void	SetString(LPCSTR val);
		virtual BOOL	GetBoolean();
		virtual BYTE	GetByte();
		virtual CHAR	GetChar();
		virtual	INT		GetBlob(BYTE* ps);
		virtual DATE	GetDateTime();
		virtual DECIMAL	GetDecimal();
		virtual DOUBLE	GetDouble();
		virtual FLOAT	GetFloat();
		virtual SHORT	GetInt16();
		virtual INT		GetInt32();
		virtual LONG	GetInt64();
		virtual LPCSTR	GetString();
	private:
		VARIANT			m_value;
		ADOCommand&		m_command;
		ADOParameterPtr	m_parameterPtr;
	};
	/// <summary>
	/// ADO数据读取
	/// </summary>
	class ADODataReader : public IDbDataReader
	{
		friend class ADOCommand;
		DISALLOW_COPY_AND_ASSIGN(ADODataReader);
	public:
		ADODataReader();
		virtual ~ADODataReader();
		virtual BOOL	ReadNext();
		virtual BOOL	ReadPrevious();
		virtual BOOL	ReadFirst();
		virtual BOOL	ReadLast();
		virtual BOOL	Close();
		virtual INT		GetColumnCount();
		virtual BOOL	GetBoolean(INT i);
		virtual BYTE	GetByte(INT i);
		virtual INT		GetBlob(INT i, BYTE* ps);
		virtual CHAR	GetChar(INT i);
		virtual LPCSTR	GetDataTypeName(INT i);
		virtual DATE	GetDateTime(INT i);
		virtual DECIMAL GetDecimal(INT i);
		virtual DOUBLE	GetDouble(INT i);
		virtual FLOAT	GetFloat(INT i);
		virtual SHORT	GetInt16(INT i);
		virtual INT		GetInt32(INT i);
		virtual LONG	GetInt64(INT i);
		virtual LPCSTR	GetName(INT i);
		virtual INT		GetOrdinal(LPCSTR pzName);
		virtual LPCSTR	GetString(INT i);
		virtual BOOL	IsDBNull(INT i);
	private:
		ADORecordsetPtr		m_recordsetPtr;
		FieldsPtr			m_fields;
	};
}