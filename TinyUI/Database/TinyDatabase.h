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
		virtual INT				GetErrors(LPSTR pzError, INT size) = 0;
	};
	/// <summary>
	/// 数据库事务
	/// </summary>
	class IDbTransaction : public IDisposable
	{
	public:
		virtual IDbConnection*	GetConnection() = 0;
		virtual INT				GetIsolationLevel() = 0;
		virtual BOOL			Commit() = 0;
		virtual BOOL			Rollback() = 0;
	};

	/// <summary>
	/// 数据库命令
	/// </summary>
	class IDbCommand : public IDisposable
	{
	public:
		virtual LPCSTR				GetCommandText() = 0;
		virtual void				SetCommandText(LPCSTR pzText) = 0;
		virtual LONG				GetCommandTimeout() = 0;
		virtual void				SetCommandTimeout(LONG iTime) = 0;
		virtual INT					GetCommandType() = 0;
		virtual void				SetCommandType(INT commandType) = 0;
		virtual IDbConnection*		GetConnection() = 0;
		virtual IDbDataParameters*	GetParameters() = 0;
		virtual IDbTransaction*		GetTransaction() = 0;
		virtual BOOL				Cancel() = 0;
		virtual IDbDataParameter*	CreateParameter() = 0;
		virtual INT					ExecuteNonQuery() = 0;
		virtual IDbDataReader*		ExecuteReader(INT iBehavior) = 0;
	};
	/// <summary>
	/// 数据行
	/// </summary>
	class IDbDataRow
	{
	public:
		virtual INT				GetColumnCount() = 0;
		virtual BOOL			GetBoolean(INT i) = 0;
		virtual BYTE			GetByte(INT i) = 0;
		virtual CHAR			GetChar(INT i) = 0;
		virtual	BYTE*			GetBlob(INT i) = 0;
		virtual LPCSTR			GetDataTypeName(INT i) = 0;
		virtual DATE			GetDateTime(INT i) = 0;
		virtual DECIMAL			GetDecimal(INT i) = 0;
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
	/// <summary>
	/// 数据读取
	/// </summary>
	class IDbDataReader :public IDbDataRow
	{
	public:
		virtual BOOL ReadNext() = 0;
		virtual BOOL ReadPrevious() = 0;
		virtual BOOL ReadFirst() = 0;
		virtual BOOL ReadLast() = 0;
		virtual BOOL Close() = 0;
	};
	/// <summary>
	/// Command 对象的参数
	/// </summary>
	class IDbDataParameter
	{
	public:
		virtual INT GetDbType() = 0;
		virtual void SetDbType(INT dbTye) = 0;
		virtual INT GetDirection() = 0;
		virtual void SetDirection(INT direction) = 0;
		virtual BOOL IsNullable() = 0;
		virtual LPCSTR GetParameterName() = 0;
		virtual void SetParameterName(LPCSTR pzName) = 0;
		virtual BYTE GetPrecision() = 0;
		virtual void SetPrecision(BYTE precision) = 0;
		virtual BYTE GetScale() = 0;
		virtual void SetScale(BYTE scale) = 0;
		virtual INT GetSize() = 0;
		virtual void SetSize(INT size) = 0;
		virtual void SetBoolean(BOOL val) = 0;
		virtual void SetByte(BYTE val) = 0;
		virtual void SetChar(CHAR val) = 0;
		virtual	void SetBlob(LPBYTE val) = 0;
		virtual void SetDateTime(DATE val) = 0;
		virtual void SetDecimal(DECIMAL val) = 0;
		virtual void SetDouble(DOUBLE val) = 0;
		virtual void SetFloat(FLOAT val) = 0;
		virtual void SetInt16(SHORT val) = 0;
		virtual void SetInt32(INT val) = 0;
		virtual void SetInt64(LONG val) = 0;
		virtual void SetString(LPCSTR val) = 0;
	};
	/// <summary>
	/// Command 对象的参数集合
	/// </summary>
	class IDbDataParameters
	{
	public:
		virtual IDbDataParameter* Add(IDbDataParameter* pValue) = 0;
		virtual IDbDataParameter* Add(LPCSTR pzName, VARIANT& pValue) = 0;
		virtual IDbDataParameter* Add(LPCSTR pzName, INT dbType) = 0;
		virtual IDbDataParameter* Add(LPCSTR pzName, INT dbType, INT size) = 0;
		virtual void Remove(IDbDataParameter* value) = 0;
		virtual void RemoveAt(INT index) = 0;
		virtual void RemoveAt(LPCSTR pzName) = 0;
		virtual void RemoveAll() = 0;
		virtual INT IndexOf(LPCSTR pzName) = 0;
		virtual IDbDataParameter* GetParameter(INT index) = 0;
		virtual IDbDataParameter* GetParameter(LPCSTR pzName) = 0;
		virtual BOOL Contains(IDbDataParameter* pValue) = 0;
	};
}