#pragma once
#include "../Common/TinyCommon.h"
#include "../Common/TinyTime.h"
#include "../Common/TinyCollection.h"
#include "../Common/TinySingle.h"
#include "../ThirdParty/sqlite/sqlite3.h"
#include "TinyDatabase.h"
#pragma comment(lib, "../ThirdParty/sqlite/sqlite.lib")

namespace TinyUI
{
	class SqliteConnection;
	class SqliteCommand;
	class SqliteDataReader;
	class SqliteataParameter;

	enum ConnectionState
	{
		Closed = 0,
		Open = 1,
		Connecting = 2,
		Executing = 4,
		Fetching = 8,
		Broken = 16,
	};
	enum CommandType
	{
		Text = 1,
		StoredProcedure = 4,
		TableDirect = 512,
	};
	enum DbType
	{
		Empty = 0,
		TinyInt = 16,
		SmallInt = 2,
		Integer = 3,
		BigInt = 20,
		UnsignedTinyInt = 17,
		UnsignedSmallInt = 18,
		UnsignedInt = 19,
		UnsignedBigInt = 21,
		Single = 4,
		Double = 5,
		Currency = 6,
		Decimal = 14,
		Numeric = 131,
		Boolean = 11,
		Error = 10,
		UserDefined = 132,
		Variant = 12,
		IDispatch = 9,
		IUnknown = 13,
		GUID = 72,
		Date = 7,
		DBDate = 133,
		DBTime = 134,
		DBTimeStamp = 135,
		BSTR = 8,
		Char = 129,
		VarChar = 200,
		LongVarChar = 201,
		WChar = 130,
		VarWChar = 202,
		LongVarWChar = 203,
		Binary = 128,
		VarBinary = 204,
		LongVarBinary = 205,
		Chapter = 136,
		FileTime = 64,
		PropVariant = 138,
		VarNumeric = 139,
		Array = 8192
	};
	/// <summary>
	/// Sqlite数据库连接
	/// </summary>
	class SqliteConnection : public IDbConnection
	{
		friend class SqliteCommand;
		DISALLOW_COPY_AND_ASSIGN(SqliteConnection);
	public:
		SqliteConnection();
		virtual ~SqliteConnection();
		virtual LPCSTR	GetConnectionString() const;
		virtual void	SetConnectionString(LPCSTR connectionString);
		virtual LONG	GetConnectionTimeout() const;
		virtual void	SetConnectionTimeout(LONG timeMs);
		virtual BOOL	Open();
		virtual BOOL	Close();
		virtual LONG	GetConnectionState();
		virtual BOOL	BeginTransaction(INT iIsolationLevel = 0);
		virtual BOOL	CommitTransaction();
		virtual BOOL	RollbackTransaction();
		virtual void	GetErrors(LPSTR pzError, INT& size);
	private:
		TinyString				m_connectionString;
		sqlite3*				m_sqlite;
	};
	/// <summary>
	/// Sqlite数据库命令,不支持存储过程
	/// </summary>
	class SqliteCommand : public IDbCommand
	{
		friend class SqliteConnection;
		DISALLOW_COPY_AND_ASSIGN(SqliteCommand);
	public:
		SqliteCommand(SqliteConnection& connection);
		virtual ~SqliteCommand();
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
		TinyString					m_commandText;
		SqliteConnection&			m_connection;
		INT							m_queryTime;
		sqlite3_stmt*				m_statement;
	};
	/// <summary>
	/// Sqlite参数
	/// </summary>
	class SqlliteParameter :public IDbDataParameter
	{
		friend class SqliteConnection;
		friend class SqliteCommand;
		DISALLOW_COPY_AND_ASSIGN(SqlliteParameter);
	public:
		SqlliteParameter(SqliteCommand& command);
		virtual ~SqlliteParameter();
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
		virtual void SetNull();
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
		virtual BOOL GetBoolean();
		virtual BYTE GetByte();
		virtual CHAR GetChar();
		virtual LPBYTE GetBlob();
		virtual DATE GetDateTime();
		virtual DECIMAL GetDecimal();
		virtual DOUBLE GetDouble();
		virtual FLOAT GetFloat();
		virtual SHORT GetInt16();
		virtual INT GetInt32();
		virtual LONG GetInt64();
		virtual LPCSTR GetString();
	private:
		SqliteCommand&	m_command;
	};
}