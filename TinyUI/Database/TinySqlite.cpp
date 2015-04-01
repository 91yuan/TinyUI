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
		Close();
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
				sqlite3_close(m_sqlite);
				sqlite3_open(m_connectionString.STR(), &m_sqlite);
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
		return sqlite3_open(m_connectionString.STR(), &m_sqlite) == SQLITE_OK;
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
		return m_sqlite != NULL ? ConnectionState::Open : ConnectionState::Closed;
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
		: m_connection(connection),
		m_commandType(CmdText)
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
		return m_commandType;
	}
	void	SqliteCommand::SetCommandType(INT commandType)
	{
		m_commandType = commandType;
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
	//////////////////////////////////////////////////////////////////////////
	SqlliteParameter::SqlliteParameter(SqliteCommand& command)
		:m_command(command),
		m_stmt(NULL)
	{

	}
	SqlliteParameter::~SqlliteParameter()
	{

	}
	INT SqlliteParameter::GetDbType()
	{

	}

	void SqlliteParameter::SetDbType(INT dbTye)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	INT SqlliteParameter::GetDirection()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetDirection(INT direction)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqlliteParameter::IsNullable()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LPCSTR SqlliteParameter::GetParameterName()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetParameterName(LPCSTR pzName)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BYTE SqlliteParameter::GetPrecision()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetPrecision(BYTE precision)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BYTE SqlliteParameter::GetScale()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetScale(BYTE scale)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	INT SqlliteParameter::GetSize()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetSize(INT size)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetBoolean(BOOL val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetByte(BYTE val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetChar(CHAR val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetBlob(LPBYTE val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetDateTime(DATE val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetDecimal(DECIMAL val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetDouble(DOUBLE val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetFloat(FLOAT val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetInt16(SHORT val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetInt32(INT val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetInt64(LONG val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SqlliteParameter::SetString(LPCSTR val)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqlliteParameter::GetBoolean()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BYTE SqlliteParameter::GetByte()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	CHAR SqlliteParameter::GetChar()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LPBYTE SqlliteParameter::GetBlob()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	DATE SqlliteParameter::GetDateTime()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	DECIMAL SqlliteParameter::GetDecimal()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	DOUBLE SqlliteParameter::GetDouble()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	FLOAT SqlliteParameter::GetFloat()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	SHORT SqlliteParameter::GetInt16()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	INT SqlliteParameter::GetInt32()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LONG SqlliteParameter::GetInt64()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LPCSTR SqlliteParameter::GetString()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}