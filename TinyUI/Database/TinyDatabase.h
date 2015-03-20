#pragma once
#include "../Common/TinyCommon.h"
#include "../Common/TinyTime.h"
#include "TinyDatabase.h"

namespace TinyUI
{
	class IDisposable;
	class IDbConnection;
	class IDbTransaction;
	class IDbCommand;
	class IDbDataParameters;
	class IDbDataParameter;
	class IDbDataReader;
	/// <summary>
	/// 定义一种释放分配的资源的方法
	/// </summary>
	class IDisposable
	{
	public:
		virtual void Dispose() = 0;
	};
	/// <summary>
	/// 数据库连接
	/// </summary>
	class IDbConnection :public IDisposable
	{
	public:
		virtual LPCSTR			GetConnectionString() = 0;
		virtual void			SetConnectionString(LPCSTR pzText) = 0;
		virtual LONG			GetConnectionTimeout() = 0;
		virtual void			SetConnectionTimeout(LONG time) = 0;
		virtual IDbTransaction*	BeginTransaction() = 0;
		virtual IDbTransaction*	BeginTransaction(INT iIsolationLevel) = 0;
		virtual BOOL			Open() = 0;
		virtual BOOL			Close() = 0;
		virtual	LONG			GetConnectionState() = 0;
		virtual IDbCommand*		CreateCommand() = 0;
		virtual LPCSTR			GetErrors() = 0;
	};
	/// <summary>
	/// 数据库事务
	/// </summary>
	class IDbTransaction : public IDisposable
	{
	public:
		virtual IDbConnection*	GetConnection() = 0;
		virtual INT				GetIsolationLevel() = 0;
		virtual void			Commit() = 0;
		virtual void			Rollback() = 0;
	};

	/// <summary>
	/// 数据库命令
	/// </summary>
	class IDbCommand : public IDisposable
	{
	public:
		virtual LPCSTR				GetCommandText() = 0;
		virtual BOOL				SetCommandText(LPCSTR pzText) = 0;
		virtual INT					GetCommandTimeout() = 0;
		virtual BOOL				SetCommandTimeout(INT iTime) = 0;
		virtual IDbConnection*		GetConnection() = 0;
		virtual IDbDataParameters*	GetParameters() = 0;
		virtual IDbTransaction*		GetTransaction() = 0;
		virtual void				Cancel() = 0;
		virtual IDbDataParameter*	CreateParameter() = 0;
		virtual INT					ExecuteNonQuery() = 0;
		virtual IDbDataReader*		ExecuteReader() = 0;
		virtual IDbDataReader*		ExecuteReader(INT iBehavior) = 0;
		virtual void				Prepare() = 0;
	};
	/// <summary>
	/// 数据行
	/// </summary>
	class IDataRow
	{
	public:
		virtual INT				GetColumnCount() = 0;
		virtual BOOL			GetBoolean(INT i) = 0;
		virtual BYTE			GetByte(INT i) = 0;
		virtual LONG			GetBytes(INT i, LONG offset, BYTE* buffer, INT bufferOffset, INT size) = 0;
		virtual CHAR			GetChar(INT i) = 0;
		virtual LONG			GetChars(INT i, LONG offset, CHAR* buffer, INT bufferoffset, INT length) = 0;
		virtual IDbDataReader*	GetData(INT i) = 0;
		virtual LPCSTR			GetDataTypeName(INT i) = 0;
		virtual TinyTimeSpan*	GetDateTime(INT i) = 0;
		virtual DOUBLE			GetDouble(INT i) = 0;
		virtual FLOAT			GetFloat(INT i) = 0;
		virtual SHORT			GetInt16(INT i) = 0;
		virtual INT				GetInt32(INT i) = 0;
		virtual LONG			GetInt64(INT i) = 0;
		virtual LPCSTR			GetName(INT i) = 0;
		virtual INT				GetOrdinal(LPCSTR pzName) = 0;
		virtual LPCSTR			GetString(INT i) = 0;
		virtual BOOL			IsDBNull(INT i) = 0;
	};
}