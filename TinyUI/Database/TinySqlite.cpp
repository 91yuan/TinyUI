#include "../stdafx.h"
#include "TinySqlite.h"

namespace TinyUI
{
	SqliteConnection::SqliteConnection()
		:m_sqlite(NULL)
	{

	}
	SqliteConnection::~SqliteConnection()
	{

	}
	LPCSTR SqliteConnection::GetConnectionString() const
	{
		return m_connectionString.STR();
	}
	void SqliteConnection::SetConnectionString(LPCSTR connectionString)
	{
		ASSERT(connectionString);
		if (::GetFileAttributes(connectionString) == (DWORD)-1)
			return;
		//数据库连接改变
		if (!m_connectionString.Compare(connectionString))
		{
			m_connectionString = connectionString;
			if (m_sqlite != NULL)
			{
				if (sqlite3_close(m_sqlite) == SQLITE_OK &&
					sqlite3_open(m_connectionString.STR(), &m_sqlite) == SQLITE_OK)
				{
					sqlite3_busy_timeout(m_sqlite, m_timeMs);
				}
			}
		}
	}
	LONG SqliteConnection::GetConnectionTimeout() const
	{
		return -1;
	}
	void SqliteConnection::SetConnectionTimeout(LONG timeMs)
	{

	}
	BOOL SqliteConnection::Open()
	{
		if (::GetFileAttributes(m_connectionString.STR()) == (DWORD)-1)
			return FALSE;
		Close();
		INT iRes = sqlite3_open(m_connectionString.STR(), &m_sqlite);
		if (iRes == SQLITE_OK)
		{
			sqlite3_busy_timeout(m_sqlite, m_timeMs);
			return TRUE;
		}
		return FALSE;
	}
	BOOL SqliteConnection::Close()
	{
		if (m_sqlite != NULL)
		{
			sqlite3_close(m_sqlite);
			m_sqlite = NULL;
			return TRUE;
		}
		return FALSE;
	}
	LONG SqliteConnection::GetConnectionState()
	{
		return m_sqlite != NULL ? SqliteOpen : SqliteClose;
	}
	BOOL SqliteConnection::BeginTransaction(INT iIsolationLevel /*= 0*/)
	{
		"BEGIN TRANSACTION";
	}
	BOOL SqliteConnection::CommitTransaction()
	{
		"COMMIT TRANSACTION";
	}
	BOOL SqliteConnection::RollbackTransaction()
	{
		"ROLLBACK TRANSACTION";
	}
	void SqliteConnection::GetErrors(LPSTR pzError, INT& size)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	SqliteCommand::SqliteCommand(SqliteConnection& connection)
		: m_connection(connection)
	{

	}
	SqliteCommand::~SqliteCommand()
	{
		TRACE("析构SqliteCommand\n");
	}
	LPCSTR	SqliteCommand::GetCommandText() const
	{
		return m_commandText.STR();
	}
	void	SqliteCommand::SetCommandText(LPCSTR commandText)
	{
		m_commandText = commandText;
	}
	LONG	SqliteCommand::GetCommandTimeout() const
	{
		return m_queryTime;
	}
	void	SqliteCommand::SetCommandTimeout(LONG time)
	{
		m_queryTime = time;
	}
	INT		SqliteCommand::GetCommandType()
	{

	}
	void	SqliteCommand::SetCommandType(INT commandType)
	{

	}
	IDbConnection*	SqliteCommand::GetConnection()
	{
		return &m_connection;
	}
	BOOL	SqliteCommand::Add(IDbDataParameter* value)
	{

	}
	BOOL	SqliteCommand::Remove(INT i)
	{

	}
	BOOL	SqliteCommand::Remove(LPCSTR pzName)
	{

	}
	BOOL	SqliteCommand::RemoveAll()
	{

	}
	INT		SqliteCommand::ExecuteNonQuery()
	{

	}
	BOOL	SqliteCommand::ExecuteReader(IDbDataReader* ps)
	{

	}
	BOOL SqliteCommand::Cancel()
	{

	}
}