#include "../stdafx.h"
#include "TinySqlite.h"
#include <stdlib.h>
using namespace std;

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
		throw exception("不支持的参数!");
	}
	void SqliteConnection::SetConnectionTimeout(LONG timeMs)
	{
		throw exception("不支持的参数!");
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
		return sqlite3_exec(m_sqlite, "BEGIN TRANSACTION", NULL, NULL, NULL) == SQLITE_OK;
	}
	BOOL SqliteConnection::CommitTransaction()
	{
		return sqlite3_exec(m_sqlite, "COMMIT TRANSACTION", NULL, NULL, NULL) == SQLITE_OK;
	}
	BOOL SqliteConnection::RollbackTransaction()
	{
		return sqlite3_exec(m_sqlite, "ROLLBACK TRANSACTION", NULL, NULL, NULL) == SQLITE_OK;
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
		throw exception("没有实现的方法!");
	}
	void	SqliteCommand::SetCommandType(INT commandType)
	{
		throw exception("没有实现的方法!");
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
			case VARENUM::VT_BLOB:
			{
				INT size = value->GetBlob(NULL);
				BYTE* ps = new BYTE[size];
				size = value->GetBlob(ps);
				iRes = sqlite3_bind_blob(statement, index, ps, size, NULL);
			}
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
		:m_command(command),
		m_size(0)
	{
		memset(&m_value, 0, sizeof(VARIANT));
	}
	SqlliteParameter::~SqlliteParameter()
	{

	}
	INT SqlliteParameter::GetDbType()
	{
		return m_value.vt;
	}
	void SqlliteParameter::SetDbType(INT dbTye)
	{
		m_value.vt = dbTye;
	}
	INT SqlliteParameter::GetDirection()
	{
		return (INT)Input;
	}
	void SqlliteParameter::SetDirection(INT direction)
	{
		if (direction != Input)
		{
			throw exception("不支持的参数!");
		}
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
		throw exception("不支持的方法!");
	}
	void SqlliteParameter::SetPrecision(BYTE precision)
	{
		throw exception("不支持的方法!");
	}
	BYTE SqlliteParameter::GetScale()
	{
		throw exception("不支持的方法!");
	}
	void SqlliteParameter::SetScale(BYTE scale)
	{
		throw exception("不支持的方法!");
	}
	INT SqlliteParameter::GetSize()
	{
		return m_size;
	}
	void SqlliteParameter::SetNull()
	{

	}
	void SqlliteParameter::SetSize(INT size)
	{
		m_size = size;
	}
	void SqlliteParameter::SetBoolean(BOOL val)
	{
		m_value.boolVal = val;
	}
	void SqlliteParameter::SetByte(BYTE val)
	{
		throw exception("不支持的参数!");
	}
	void SqlliteParameter::SetChar(CHAR val)
	{
		throw exception("不支持的参数!");
	}
	void SqlliteParameter::SetBlob(LPBYTE val, LONG size)
	{
		m_value.pbVal = val;
		m_value.lVal = size;
	}
	void SqlliteParameter::SetDateTime(DATE val)
	{
		m_value.date = val;
	}
	void SqlliteParameter::SetDecimal(DECIMAL val)
	{
		m_value.decVal = val;
	}
	void SqlliteParameter::SetDouble(DOUBLE val)
	{
		m_value.dblVal = val;
	}
	void SqlliteParameter::SetFloat(FLOAT val)
	{
		m_value.fltVal = val;
	}
	void SqlliteParameter::SetInt16(SHORT val)
	{
		throw exception("不支持的参数!");
	}
	void SqlliteParameter::SetInt32(INT val)
	{
		m_value.intVal = val;
	}
	void SqlliteParameter::SetInt64(LONG val)
	{
		m_value.lVal = val;
	}
	void SqlliteParameter::SetString(LPCSTR val)
	{
		m_value.bstrVal = _com_util::ConvertStringToBSTR(val);
	}
	BOOL SqlliteParameter::GetBoolean()
	{
		return m_value.boolVal;
	}
	BYTE SqlliteParameter::GetByte()
	{
		throw exception("不支持的参数!");
	}
	CHAR SqlliteParameter::GetChar()
	{
		throw exception("不支持的参数!");
	}
	INT SqlliteParameter::GetBlob(BYTE* ps)
	{
		if (ps != NULL)
		{
			memcpy_s(ps, m_value.lVal, m_value.pbVal, m_value.lVal);
		}
		return m_value.lVal;
	}
	DATE SqlliteParameter::GetDateTime()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
	DECIMAL SqlliteParameter::GetDecimal()
	{
		return m_value.decVal;
	}
	DOUBLE SqlliteParameter::GetDouble()
	{
		return m_value.dblVal;
	}
	FLOAT SqlliteParameter::GetFloat()
	{
		return m_value.fltVal;
	}
	SHORT SqlliteParameter::GetInt16()
	{
		throw exception("不支持的参数!");
	}
	INT SqlliteParameter::GetInt32()
	{
		return m_value.intVal;
	}
	LONG SqlliteParameter::GetInt64()
	{
		return m_value.lVal;
	}
	LPCSTR SqlliteParameter::GetString()
	{
		return _com_util::ConvertBSTRToString(m_value.bstrVal);
	}
	//////////////////////////////////////////////////////////////////////////
	BOOL SqliteDataReader::ReadNext()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqliteDataReader::ReadPrevious()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqliteDataReader::ReadFirst()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqliteDataReader::ReadLast()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqliteDataReader::Close()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	INT SqliteDataReader::GetColumnCount()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqliteDataReader::GetBoolean(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BYTE SqliteDataReader::GetByte(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	CHAR SqliteDataReader::GetChar(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	INT SqliteDataReader::GetBlob(INT i, BYTE* ps)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LPCSTR SqliteDataReader::GetDataTypeName(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	DATE SqliteDataReader::GetDateTime(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	DECIMAL SqliteDataReader::GetDecimal(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	DOUBLE SqliteDataReader::GetDouble(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	FLOAT SqliteDataReader::GetFloat(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	SHORT SqliteDataReader::GetInt16(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	INT SqliteDataReader::GetInt32(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LONG SqliteDataReader::GetInt64(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LPCSTR SqliteDataReader::GetName(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	INT SqliteDataReader::GetOrdinal(LPCSTR pzName)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LPCSTR SqliteDataReader::GetString(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	BOOL SqliteDataReader::IsDBNull(INT i)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}