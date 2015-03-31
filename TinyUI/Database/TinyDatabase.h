#pragma once
#include "../Common/TinyCommon.h"
#include "../Common/TinyTime.h"
#include "TinyDatabase.h"

namespace TinyUI
{
	class IDisposable;
	class IDbConnection;
	class IDbCommand;
	class IDbDataParameter;
	class IDbDataReader;
	/// <summary>
	/// 数据库连接接口
	/// </summary>
	class IDbConnection
	{
	public:
		virtual LPCSTR			GetConnectionString() const = 0;
		virtual void			SetConnectionString(LPCSTR pzText) const = 0;
		virtual LONG			GetConnectionTimeout() const = 0;
		virtual void			SetConnectionTimeout(LONG time) const = 0;
		virtual BOOL			Open() = 0;
		virtual BOOL			Close() = 0;
		virtual	LONG			GetConnectionState() = 0;
		virtual BOOL			BeginTransaction(INT iIsolationLevel = 0) = 0;
		virtual BOOL			CommitTransaction() = 0;
		virtual BOOL			RollbackTransaction() = 0;
		virtual void			GetErrors(LPSTR pzError, INT& size) = 0;
	};
	/// <summary>
	/// 数据库命令接口
	/// </summary>
	class IDbCommand
	{
	public:
		virtual LPCSTR				GetCommandText() const = 0;
		virtual void				SetCommandText(LPCSTR pzText) const = 0;
		virtual LONG				GetCommandTimeout() const = 0;
		virtual void				SetCommandTimeout(LONG time) const = 0;
		virtual INT					GetCommandType() = 0;
		virtual void				SetCommandType(INT commandType) = 0;
		virtual IDbConnection*		GetConnection() = 0;
		virtual	BOOL				Add(IDbDataParameter* ps) = 0;
		virtual	BOOL				Remove(INT i) = 0;
		virtual	BOOL				Remove(LPCSTR pzName) = 0;
		virtual BOOL				RemoveAll() = 0;
		virtual INT					ExecuteNonQuery() = 0;
		virtual BOOL				ExecuteReader(IDbDataReader* ps) = 0;
		virtual	BOOL				Cancel() = 0;
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
		virtual INT		GetDbType() = 0;
		virtual void	SetDbType(INT dbTye) = 0;
		virtual INT		GetDirection() = 0;
		virtual void	SetDirection(INT direction) = 0;
		virtual BOOL	IsNullable() = 0;
		virtual LPCSTR	GetParameterName() = 0;
		virtual void	SetParameterName(LPCSTR pzName) = 0;
		virtual BYTE	GetPrecision() = 0;
		virtual void	SetPrecision(BYTE precision) = 0;
		virtual BYTE	GetScale() = 0;
		virtual void	SetScale(BYTE scale) = 0;
		virtual INT		GetSize() = 0;
		virtual void	SetSize(INT size) = 0;
		//////////////////////////////////////////////////////////////////////////
		virtual void	SetBoolean(BOOL val) = 0;
		virtual void	SetByte(BYTE val) = 0;
		virtual void	SetChar(CHAR val) = 0;
		virtual	void	SetBlob(LPBYTE val) = 0;
		virtual void	SetDateTime(DATE val) = 0;
		virtual void	SetDecimal(DECIMAL val) = 0;
		virtual void	SetDouble(DOUBLE val) = 0;
		virtual void	SetFloat(FLOAT val) = 0;
		virtual void	SetInt16(SHORT val) = 0;
		virtual void	SetInt32(INT val) = 0;
		virtual void	SetInt64(LONG val) = 0;
		virtual void	SetString(LPCSTR val) = 0;
		virtual BOOL	GetBoolean() = 0;
		virtual BYTE	GetByte() = 0;
		virtual CHAR	GetChar() = 0;
		virtual	LPBYTE	GetBlob() = 0;
		virtual DATE	GetDateTime() = 0;
		virtual DECIMAL	GetDecimal() = 0;
		virtual DOUBLE	GetDouble() = 0;
		virtual FLOAT	GetFloat() = 0;
		virtual SHORT	GetInt16() = 0;
		virtual INT		GetInt32() = 0;
		virtual LONG	GetInt64() = 0;
		virtual LPCSTR	GetString() = 0;
	};
}