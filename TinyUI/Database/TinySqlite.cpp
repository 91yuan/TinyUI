#include "../stdafx.h"
#include "TinySqlite.h"

namespace TinyUI
{

	//SqliteConnection::SqliteConnection()
	//	:m_sqlite(NULL)
	//{

	//}
	//SqliteConnection::~SqliteConnection()
	//{

	//}
	//LPCSTR SqliteConnection::GetConnectionString()
	//{
	//	return m_connectionString.STR();
	//}

	//void SqliteConnection::SetConnectionString(LPCSTR pzText)
	//{
	//	m_connectionString = pzText;
	//}

	//void SqliteConnection::SetConnectionTimeout(LONG time)
	//{
	//	if (m_sqlite != NULL)
	//	{
	//		sqlite3_busy_timeout(m_sqlite, m_timeMS);
	//	}
	//}

	//LONG SqliteConnection::GetConnectionTimeout()
	//{
	//	return m_timeMS;
	//}

	//IDbTransaction* SqliteConnection::BeginTransaction()
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

	//IDbTransaction* SqliteConnection::BeginTransaction(INT iIsolationLevel)
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

	//BOOL SqliteConnection::Open()
	//{
	//	if (::GetFileAttributes(m_connectionString.STR()) == (DWORD)-1)
	//		return FALSE;
	//	INT iRes = ::sqlite3_open(m_connectionString.STR(), &m_sqlite);
	//	if (iRes != SQLITE_OK)
	//	{
	//		return FALSE;
	//	}
	//	sqlite3_busy_timeout(m_sqlite, m_timeMS);
	//	return TRUE;
	//}

	//BOOL SqliteConnection::Close()
	//{
	//	if (m_sqlite != NULL)
	//	{
	//		sqlite3_close(m_sqlite);
	//		m_sqlite = NULL;
	//		return TRUE;
	//	}
	//	return FALSE;
	//}

	//LONG SqliteConnection::GetConnectionState()
	//{
	//	return m_sqlite == NULL ? SqliteClose : SqliteOpen;
	//}

	//IDbCommand* SqliteConnection::CreateCommand()
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

	//INT SqliteConnection::GetErrors(LPSTR pzError, INT size)
	//{
	//	if (m_sqlite != NULL)
	//	{
	//		size = sqlite3_errcode(m_sqlite);
	//		pzError = const_cast<LPSTR>(sqlite3_errmsg(m_sqlite));
	//		return size;
	//	}
	//	return -1;
	//}

	//void SqliteConnection::Dispose()
	//{
	//	if (m_sqlite != NULL)
	//	{
	//		sqlite3_close(m_sqlite);
	//		m_sqlite = NULL;
	//	}
	//}
	////////////////////////////////////////////////////////////////////////////
	//SqliteCommand::SqliteCommand()
	//{

	//}

	//IDbConnection* SqliteTransaction::GetConnection()
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

	//INT SqliteTransaction::GetIsolationLevel()
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

	//BOOL SqliteTransaction::Commit()
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

	//BOOL SqliteTransaction::Rollback()
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

	//void SqliteTransaction::Dispose()
	//{
	//	throw std::logic_error("The method or operation is not implemented.");
	//}

}