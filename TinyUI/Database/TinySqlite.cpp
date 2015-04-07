#include "../stdafx.h"
#include "TinySqlite.h"

namespace TinyUI
{
	SqliteConnection::SqliteConnection()
		:m_sqlite(NULL),
		m_mutex(NULL)
	{
		m_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
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
		if (m_mutex != NULL)
		{
			sqlite3_free(m_mutex);
			m_mutex = NULL;
		}
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
		return StoredProcedure;
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
		return m_parameters.Add(value);
	}
	BOOL	SqliteCommand::Remove(INT i)
	{
		return m_parameters.RemoveAt(i);
	}
	BOOL	SqliteCommand::Remove(LPCSTR pzName)
	{
		for (INT i = 0; i < m_parameters.GetSize(); i++)
		{
			if (!strcmp(m_parameters[i]->GetParameterName(), pzName))
			{
				return m_parameters.RemoveAt(i);
			}
		}
		return FALSE;
	}
	BOOL	SqliteCommand::RemoveAll()
	{
		m_parameters.RemoveAll();
		return TRUE;
	}
	INT		SqliteCommand::ExecuteNonQuery()
	{
		sqlite3_stmt* statement = GetSTMT();
		BindParameters(statement);
		INT rows = 0;
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			rows++;
		}
		ReleaseSTMT(statement);
		return rows;
	}
	BOOL	SqliteCommand::ExecuteReader(IDbDataReader* ps)
	{
		sqlite3_stmt* statement = GetSTMT();
		BindParameters(statement);
		return ReleaseSTMT(statement);
	}
	BOOL SqliteCommand::Cancel()
	{
		return FALSE;
	}
	sqlite3_stmt* SqliteCommand::GetSTMT()
	{
		sqlite3_stmt* statement = NULL;
		if (sqlite3_prepare_v2(m_connection.m_sqlite, m_commandText.STR(), -1, &statement, NULL) == SQLITE_OK)
		{
			return statement;
		}
		return NULL;
	}
	BOOL SqliteCommand::ReleaseSTMT(sqlite3_stmt* statement)
	{
		ASSERT(statement);
		return sqlite3_finalize(statement) == SQLITE_OK;
	}
	BOOL SqliteCommand::BindParameter(sqlite3_stmt* statement, IDbDataParameter* value)
	{
		ASSERT(statement);
		INT iRes = SQLITE_OK;
		INT index = sqlite3_bind_parameter_index(statement, value->GetParameterName());
		if (value->IsNullable())
		{
			iRes = sqlite3_bind_null(statement, index);
		}
		else
		{
			VARENUM dbType = (VARENUM)value->GetDbType();
			switch (dbType)
			{
			case VARENUM::VT_I4:
				iRes = sqlite3_bind_int(statement, index, value->GetInt32());
				break;;
			case VARENUM::VT_I8:
				iRes = sqlite3_bind_int64(statement, index, value->GetInt64());
				break;
			case VARENUM::VT_R4:
				iRes = sqlite3_bind_double(statement, index, value->GetFloat());
				break;
			case VARENUM::VT_R8:
				iRes = sqlite3_bind_double(statement, index, value->GetDouble());
				break;
			case VARENUM::VT_BOOL:
				iRes = sqlite3_bind_int(statement, index, value->GetBoolean());
				break;
			case VARENUM::VT_DATE:
			{
				DATE date = value->GetDateTime();
				TinyOleDateTime oleDate(date);
				TinyString str = oleDate.Format("yyyy-MM-dd HH:mm:ss.fff");
				iRes = sqlite3_bind_text(statement, index, str.STR(), str.GetSize(), SQLITE_STATIC);
			}
			break;
			case VARENUM::VT_LPSTR:
				iRes = sqlite3_bind_text(statement, index, value->GetString(), -1, NULL);
				break;
			}
		}
		return iRes == SQLITE_OK;
	}
	BOOL SqliteCommand::BindParameters(sqlite3_stmt* statement)
	{
		ASSERT(statement);
		if (sqlite3_reset(statement) != SQLITE_OK)
		{
			return FALSE;
		}
		for (INT i = 0; i < m_parameters.GetSize(); i++)
		{
			if (!BindParameter(statement, m_parameters[i]))
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	//////////////////////////////////////////////////////////////////////////
	SqlliteParameter::SqlliteParameter(SqliteCommand& command)
		:m_command(command)
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
	void SqlliteParameter::SetNull()
	{

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