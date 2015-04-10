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
	void SqliteConnection::GetErrors(LPSTR ps, INT& size)
	{
		ASSERT(m_sqlite);
		ps = const_cast<LPSTR>(sqlite3_errmsg(m_sqlite));
		size = strlen(ps);
	}
	INT	SqliteConnection::GetRowID()
	{
		ASSERT(m_sqlite);
		return sqlite3_last_insert_rowid(m_sqlite);
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
		if (statement != NULL
			&& BindParameters(statement))
		{
			INT i = 0;
			while (sqlite3_step(statement) == SQLITE_ROW)
				i++;
			ReleaseSTMT(statement);
			return i;
		}
		return -1;
	}
	BOOL	SqliteCommand::ExecuteReader(IDbDataReader* ps)
	{
		ASSERT(ps);
		sqlite3_stmt* statement = GetSTMT();
		if (statement != NULL
			&& BindParameters(statement))
		{
			SqliteDataReader* reader = reinterpret_cast<SqliteDataReader*>(ps);
			reader->m_statement = statement;
			return TRUE;
		}
		return FALSE;
	}
	BOOL SqliteCommand::Cancel()
	{
		ASSERT(m_connection.m_sqlite);
		sqlite3_interrupt(m_connection.m_sqlite);
		return TRUE;
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
	BOOL SqliteCommand::ResetSTMT(sqlite3_stmt* statement)
	{
		ASSERT(statement);
		return sqlite3_reset(statement) == SQLITE_OK;
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
			case VARENUM::VT_I1:
				iRes = sqlite3_bind_int(statement, index, value->GetChar());
				break;
			case VARENUM::VT_I2:				iRes = sqlite3_bind_int(statement, index, value->GetInt16());
				break;
			case VARENUM::VT_UI1:
				iRes = sqlite3_bind_int(statement, index, value->GetByte());
				break;
			case VARENUM::VT_I4:
				iRes = sqlite3_bind_int(statement, index, value->GetInt32());
				break;;
			case VARENUM::VT_BOOL:
				iRes = sqlite3_bind_int(statement, index, value->GetBoolean());
				break;
			case VARENUM::VT_I8:
				iRes = sqlite3_bind_int64(statement, index, value->GetInt64());
				break;
			case VARENUM::VT_R4:
				iRes = sqlite3_bind_double(statement, index, value->GetFloat());
				break;
			case VARENUM::VT_R8:
				iRes = sqlite3_bind_double(statement, index, value->GetDouble());
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
		if (sqlite3_clear_bindings(statement) != SQLITE_OK)
			return FALSE;
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
		return m_value.vt == VT_NULL;
	}
	LPCSTR SqlliteParameter::GetParameterName()
	{
		return m_parameterName.STR();
	}
	void SqlliteParameter::SetParameterName(LPCSTR pzName)
	{
		m_parameterName = pzName;
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
		m_value.vt = VT_NULL;
	}
	void SqlliteParameter::SetSize(INT size)
	{
		m_size = size;
	}
	void SqlliteParameter::SetBoolean(BOOL val)
	{
		m_value.vt = VT_BOOL;
		m_value.boolVal = val;
	}
	void SqlliteParameter::SetByte(BYTE val)
	{
		m_value.vt = VT_UI1;
		m_value.bVal = val;
	}
	void SqlliteParameter::SetChar(CHAR val)
	{
		m_value.vt = VT_I1;
		m_value.cVal = val;
	}
	void SqlliteParameter::SetBlob(LPBYTE val, LONG size)
	{
		m_value.vt = VT_ARRAY | VT_BLOB;
		m_value.pbVal = val;
		m_value.lVal = size;
	}
	void SqlliteParameter::SetDateTime(DATE val)
	{
		m_value.vt = VT_DATE;
		m_value.date = val;
	}
	void SqlliteParameter::SetDecimal(DECIMAL val)
	{
		throw exception("不支持的方法!");
	}
	void SqlliteParameter::SetDouble(DOUBLE val)
	{
		m_value.vt = VT_R4;
		m_value.dblVal = val;
	}
	void SqlliteParameter::SetFloat(FLOAT val)
	{
		m_value.vt = VT_R8;
		m_value.fltVal = val;
	}
	void SqlliteParameter::SetInt16(SHORT val)
	{
		m_value.vt = VT_I2;
		m_value.iVal = val;
	}
	void SqlliteParameter::SetInt32(INT val)
	{
		m_value.vt = VT_I4;
		m_value.intVal = val;
	}
	void SqlliteParameter::SetInt64(LONG val)
	{
		m_value.vt = VT_I8;
		m_value.lVal = val;
	}
	void SqlliteParameter::SetString(LPCSTR val)
	{
		m_value.vt = VT_BSTR;
		m_value.bstrVal = _com_util::ConvertStringToBSTR(val);
	}
	BOOL SqlliteParameter::GetBoolean()
	{
		return m_value.boolVal;
	}
	BYTE SqlliteParameter::GetByte()
	{
		return m_value.bVal;
	}
	CHAR SqlliteParameter::GetChar()
	{
		return m_value.cVal;
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
		return m_value.date;
	}
	DECIMAL SqlliteParameter::GetDecimal()
	{
		throw exception("不支持的方法!");
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
		return m_value.iVal;
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
	SqliteDataReader::SqliteDataReader()
		:m_statement(NULL)
	{

	}
	SqliteDataReader::~SqliteDataReader()
	{
		Close();
	}
	BOOL SqliteDataReader::ReadNext()
	{
		ASSERT(m_statement);
		return sqlite3_step(m_statement) == SQLITE_ROW;
	}
	BOOL SqliteDataReader::ReadPrevious()
	{
		throw exception("不支持的方法!");
	}
	BOOL SqliteDataReader::ReadFirst()
	{
		throw exception("不支持的方法!");
	}
	BOOL SqliteDataReader::ReadLast()
	{
		throw exception("不支持的方法!");
	}
	BOOL SqliteDataReader::Close()
	{
		ASSERT(m_statement);
		return ReleaseSTMT(m_statement);
	}
	INT SqliteDataReader::GetColumnCount()
	{
		ASSERT(m_statement);
		return sqlite3_column_count(m_statement);
	}
	BOOL SqliteDataReader::GetBoolean(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_INTEGER);
		return static_cast<BOOL> (sqlite3_column_int(m_statement, i));
	}
	BYTE SqliteDataReader::GetByte(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_INTEGER);
		return static_cast<BYTE> (sqlite3_column_int(m_statement, i));
	}
	CHAR SqliteDataReader::GetChar(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_INTEGER);
		return static_cast<CHAR> (sqlite3_column_int(m_statement, i));
	}
	INT SqliteDataReader::GetBlob(INT i, BYTE* ps)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_BLOB);
		INT size = sqlite3_column_bytes(m_statement, i);
		if (ps == NULL)
		{
			return size;
		}
		const void* val = sqlite3_column_blob(m_statement, i);
		memcpy_s(ps, size, (BYTE*)val, size);
		return size;
	}
	LPCSTR SqliteDataReader::GetDataTypeName(INT i)
	{
		INT type = sqlite3_column_type(m_statement, i);
		switch (type)
		{
		case SQLITE_FLOAT:
			return TEXT("Float");
		case SQLITE_BLOB:
			return TEXT("Blob");
		case SQLITE_INTEGER:
			return TEXT("Interger");
		case SQLITE_TEXT:
			return TEXT("Text");
		}
		return TEXT("");
	}
	DATE SqliteDataReader::GetDateTime(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_TEXT);
		_variant_t val(sqlite3_column_text(m_statement, i));
		val.ChangeType(VT_DATE);
		return val.date;
	}
	DECIMAL SqliteDataReader::GetDecimal(INT i)
	{
		ASSERT(m_statement);
		throw exception("不支持的方法!");
	}
	DOUBLE SqliteDataReader::GetDouble(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_FLOAT);
		return static_cast<DOUBLE> (sqlite3_column_double(m_statement, i));
	}
	FLOAT SqliteDataReader::GetFloat(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_FLOAT);
		return static_cast<FLOAT> (sqlite3_column_double(m_statement, i));
	}
	SHORT SqliteDataReader::GetInt16(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_INTEGER);
		return static_cast<SHORT> (sqlite3_column_int(m_statement, i));
	}
	INT SqliteDataReader::GetInt32(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_INTEGER);
		return static_cast<INT> (sqlite3_column_int(m_statement, i));
	}
	LONG SqliteDataReader::GetInt64(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_INTEGER);
		return static_cast<LONG> (sqlite3_column_int(m_statement, i));
	}
	LPCSTR SqliteDataReader::GetName(INT i)
	{
		ASSERT(m_statement);
		return sqlite3_column_name(m_statement, i);
	}
	INT SqliteDataReader::GetOrdinal(LPCSTR pzName)
	{
		ASSERT(m_statement);
		INT count = sqlite3_column_count(m_statement);
		for (INT i = 0; i < count; i++)
		{
			LPCSTR ps = sqlite3_column_name(m_statement, i);
			if (!strcmp(ps, pzName)) return i;
		}
		return -1;
	}
	LPCSTR SqliteDataReader::GetString(INT i)
	{
		ASSERT(m_statement);
		ASSERT(sqlite3_column_type(m_statement, i) == SQLITE_TEXT);
		return reinterpret_cast<LPCSTR>(sqlite3_column_text(m_statement, i));
	}
	BOOL SqliteDataReader::IsDBNull(INT i)
	{
		ASSERT(m_statement);
		return sqlite3_column_type(m_statement, i) == SQLITE_NULL;
	}
	BOOL SqliteDataReader::ReleaseSTMT(sqlite3_stmt* statement)
	{
		ASSERT(statement);
		return sqlite3_finalize(statement) == SQLITE_OK;
	}
	BOOL SqliteDataReader::ResetSTMT(sqlite3_stmt* statement)
	{
		ASSERT(statement);
		return sqlite3_reset(statement) == SQLITE_OK;
	}
}