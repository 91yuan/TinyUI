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
		TableDirect = 512
	};
	enum ParameterDirection
	{
		Input = 1,
		Output = 2,
		InputOutput = 3,
		ReturnValue = 6
	};
	enum DbType
	{
		DT_NULL = VT_NULL,
		DT_INT = VT_I4,
		DT_INT64 = VT_I8,
		DT_FLOAT = VT_R4,
		DT_DOUBLE = VT_R8,
		DT_DATE = VT_DATE,
		DT_TEXT = VT_BSTR,
		DT_BLOB = VT_BLOB,
		DT_DECIMAL = VT_DECIMAL
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
		sqlite3_stmt*				GetSTMT();
		BOOL						ReleaseSTMT(sqlite3_stmt* statement);
		BOOL						BindParameter(sqlite3_stmt* statement, IDbDataParameter* value);
		BOOL						BindParameters(sqlite3_stmt* statement);
	private:
		TinyArray<IDbDataParameter*>m_parameters;
		TinyString					m_commandText;
		SqliteConnection&			m_connection;
		INT							m_queryTime;
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
		virtual void SetBlob(LPBYTE val, LONG size);
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
		virtual INT	GetBlob(BYTE* ps);
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
		VARIANT			m_value;
		INT				m_size;
	};
	/// <summary>
	/// Sqlite 读取
	/// </summary>
	class SqliteDataReader :public IDbDataReader
	{
	public:
		virtual BOOL ReadNext() override;
		virtual BOOL ReadPrevious() override;
		virtual BOOL ReadFirst() override;
		virtual BOOL ReadLast() override;
		virtual BOOL Close() override;
		virtual INT GetColumnCount() override;
		virtual BOOL GetBoolean(INT i) override;
		virtual BYTE GetByte(INT i) override;
		virtual CHAR GetChar(INT i) override;
		virtual INT GetBlob(INT i, BYTE* ps) override;
		virtual LPCSTR GetDataTypeName(INT i) override;
		virtual DATE GetDateTime(INT i) override;
		virtual DECIMAL GetDecimal(INT i) override;
		virtual DOUBLE GetDouble(INT i) override;
		virtual FLOAT GetFloat(INT i) override;
		virtual SHORT GetInt16(INT i) override;
		virtual INT GetInt32(INT i) override;
		virtual LONG GetInt64(INT i) override;
		virtual LPCSTR GetName(INT i) override;
		virtual INT GetOrdinal(LPCSTR pzName) override;
		virtual LPCSTR GetString(INT i) override;
		virtual BOOL IsDBNull(INT i) override;
	};
}