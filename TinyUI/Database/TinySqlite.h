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

	enum SqliteState
	{
		SqliteOpen = 0,
		SqliteClose = 1
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
		virtual LPCSTR GetConnectionString() const;
		virtual void SetConnectionString(LPCSTR connectionString);
		virtual LONG GetConnectionTimeout() const;
		virtual void SetConnectionTimeout(LONG timeMs);
		virtual BOOL Open();
		virtual BOOL Close();
		virtual LONG GetConnectionState();
		virtual BOOL BeginTransaction(INT iIsolationLevel = 0);
		virtual BOOL CommitTransaction();
		virtual BOOL RollbackTransaction();
		virtual void GetErrors(LPSTR pzError, INT& size);
	private:
		TinyString				m_connectionString;
		sqlite3*				m_sqlite;
	};
	/// <summary>
	/// Sqlite数据库命令
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
	};
}