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
	/*class SqliteConnection;
	class SqliteCommand;
	class SqliteDataReader;
	class SqliteTransaction;
	class SqliteataParameter;
	class SqliteDataParameters;


	enum SqliteState
	{
	SqliteOpen = 0,
	SqliteClose = 1
	};
	/// <summary>
	/// Sqlite连接
	/// </summary>
	class SqliteConnection : public IDbConnection
	{
	friend class SqliteCommand;
	friend class SqliteTransaction;
	DISALLOW_COPY_AND_ASSIGN(SqliteConnection);
	public:
	SqliteConnection();
	virtual ~SqliteConnection();
	virtual LPCSTR GetConnectionString() override;
	virtual void SetConnectionString(LPCSTR pzText) override;
	virtual void SetConnectionTimeout(LONG time) override;
	virtual LONG GetConnectionTimeout() override;
	virtual IDbTransaction* BeginTransaction() override;
	virtual IDbTransaction* BeginTransaction(INT iIsolationLevel) override;
	virtual BOOL Open() override;
	virtual BOOL Close() override;
	virtual LONG GetConnectionState() override;
	virtual IDbCommand* CreateCommand() override;
	virtual INT GetErrors(LPSTR pzError, INT size) override;
	virtual void Dispose() override;
	public:
	TinyString				m_connectionString;
	INT						m_timeMS;
	sqlite3*				m_sqlite;
	};
	/// <summary>
	/// Sqlite命令
	/// </summary>
	class SqliteCommand : public IDbCommand
	{
	DISALLOW_COPY_AND_ASSIGN(SqliteCommand);
	private:
	SqliteCommand();
	public:
	virtual ~SqliteCommand();
	virtual LPCSTR				GetCommandText();
	virtual void				SetCommandText(LPCSTR pzText);
	virtual LONG				GetCommandTimeout();
	virtual void				SetCommandTimeout(LONG iTime);
	virtual INT					GetCommandType();
	virtual void				SetCommandType(INT commandType);
	virtual IDbConnection*		GetConnection();
	virtual IDbDataParameters*	GetParameters();
	virtual IDbTransaction*		GetTransaction();
	virtual BOOL				Cancel();
	virtual IDbDataParameter*	CreateParameter();
	virtual INT					ExecuteNonQuery();
	virtual IDbDataReader*		ExecuteReader(INT iBehavior);
	};
	/// <summary>
	/// Sqlite事务
	/// </summary>
	class SqliteTransaction : public IDbTransaction
	{
	DISALLOW_COPY_AND_ASSIGN(SqliteTransaction);
	private:
	SqliteTransaction();
	public:
	virtual ~SqliteTransaction();
	virtual IDbConnection* GetConnection() override;
	virtual INT GetIsolationLevel() override;
	virtual BOOL Commit() override;
	virtual BOOL Rollback() override;
	virtual void Dispose() override;
	};*/
}