#include "../stdafx.h"
#include "TinyAdo.h"

namespace TinyUI
{
	ADOConnection::ADOConnection()
		:m_connectionPtr(NULL),
		m_pCommand(NULL),
		m_pTransaction(NULL)
	{
		m_connectionPtr.CreateInstance(__uuidof(Connection));
	}
	ADOConnection::~ADOConnection()
	{
		if (m_connectionPtr != NULL)
		{
			m_connectionPtr->Close();
			SAFE_DELETE(m_pCommand);
			SAFE_DELETE(m_pTransaction);
		}
	}
	LPCSTR ADOConnection::GetConnectionString()
	{
		ASSERT(m_connectionPtr);
		return m_connectionPtr->GetConnectionString();
	}
	void ADOConnection::SetConnectionString(LPCSTR connectionString)
	{
		ASSERT(connectionString);
		m_connectionPtr->ConnectionString = connectionString;
	}
	LONG ADOConnection::GetConnectionTimeout()
	{
		ASSERT(m_connectionPtr);
		return m_connectionPtr->GetConnectionTimeout();
	}
	void ADOConnection::SetConnectionTimeout(LONG connectionTimeout)
	{
		ASSERT(m_connectionPtr);
		m_connectionPtr->CommandTimeout = connectionTimeout;
	}
	LONG ADOConnection::GetConnectionState()
	{
		ASSERT(m_connectionPtr);
		return m_connectionPtr->State;
	}
	IDbTransaction* ADOConnection::BeginTransaction()
	{
		ASSERT(m_connectionPtr);
		TinyCriticalSection section;
		section.Initialize();
		section.Lock();
		if (m_pTransaction == NULL)
		{
			m_pTransaction = new ADOTransaction(*this);
		}
		section.Unlock();
		section.Uninitialize();
		if (m_pTransaction)
		{
			m_connectionPtr->BeginTrans();
		}
		return m_pTransaction;
	}
	IDbTransaction* ADOConnection::BeginTransaction(INT iIsolationLevel)
	{
		ASSERT(m_connectionPtr);
		TinyCriticalSection section;
		section.Initialize();
		section.Lock();
		if (m_pTransaction == NULL)
		{
			m_pTransaction = new ADOTransaction(*this, iIsolationLevel);
		}
		section.Unlock();
		section.Uninitialize();
		if (m_pTransaction)
		{
			m_connectionPtr->BeginTrans();
		}
		return m_pTransaction;
	}
	BOOL ADOConnection::Open()
	{
		ASSERT(m_connectionPtr);
		return SUCCEEDED(m_connectionPtr->Open("", "", "", adModeUnknown));
	}
	BOOL ADOConnection::Close()
	{
		ASSERT(m_connectionPtr);
		BOOL bRes = SUCCEEDED(m_connectionPtr->Close());
		SAFE_DELETE(m_pCommand);
		SAFE_DELETE(m_pTransaction);
		return bRes;
	}
	IDbCommand* ADOConnection::CreateCommand()
	{
		TinyCriticalSection section;
		section.Initialize();
		section.Lock();
		if (m_pCommand == NULL)
		{
			m_pCommand = new ADOCommand(*this);
		}
		section.Unlock();
		section.Uninitialize();
		return m_pCommand;
	}
	void ADOConnection::Dispose()
	{
		if (m_connectionPtr != NULL)
		{
			m_connectionPtr->Close();
			SAFE_DELETE(m_pCommand);
			SAFE_DELETE(m_pTransaction);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	ADOCommand::ADOCommand(ADOConnection& connection)
		:m_commandPtr(NULL),
		m_connection(connection),
		m_pParameters(NULL)
	{
		if (SUCCEEDED(m_commandPtr.CreateInstance(__uuidof(Command))))
		{
			m_commandPtr->ActiveConnection = m_connection.m_connectionPtr;
			m_pParameters = new ADODataParameters(*this);
		}
	}
	ADOCommand::~ADOCommand()
	{
		if (m_pParameters != NULL)
		{
			m_pParameters->RemoveAll();
		}
	}
	LPCSTR ADOCommand::GetCommandText()
	{
		return m_commandPtr->GetCommandText();
	}
	void ADOCommand::SetCommandText(LPCSTR pzText)
	{
		ASSERT(m_commandPtr);
		m_commandPtr->CommandText = pzText;
	}
	LONG ADOCommand::GetCommandTimeout()
	{
		ASSERT(m_commandPtr);
		return m_commandPtr->GetCommandTimeout();
	}
	void ADOCommand::SetCommandTimeout(LONG commandTimeout)
	{
		ASSERT(m_commandPtr);
		m_commandPtr->CommandTimeout = commandTimeout;
	}
	INT	ADOCommand::GetCommandType()
	{
		ASSERT(m_commandPtr);
		return (INT)m_commandPtr->CommandType;
	}
	void ADOCommand::SetCommandType(INT commandType)
	{
		ASSERT(m_commandPtr);
		m_commandPtr->CommandType = (CommandTypeEnum)commandType;
	}
	IDbConnection* ADOCommand::GetConnection()
	{
		return &m_connection;
	}
	IDbDataParameters* ADOCommand::GetParameters()
	{
		return m_pParameters;
	}
	IDbTransaction* ADOCommand::GetTransaction()
	{
		return m_connection.m_pTransaction;
	}
	BOOL ADOCommand::Cancel()
	{
		ASSERT(m_commandPtr);
		return SUCCEEDED(m_commandPtr->Cancel());
	}
	IDbDataParameter* ADOCommand::CreateParameter()
	{
		IDbDataParameter* ps = new ADODataParameter();
		if (ps != NULL)
		{
			return m_pParameters->Add(ps);
		}
		return NULL;
	}
	INT ADOCommand::ExecuteNonQuery()
	{
		ASSERT(m_commandPtr);
		ADORecordsetPtr recordsetPtr = m_commandPtr->Execute(NULL, NULL, m_commandPtr->CommandType);
		INT recordCount = 0;
		if (recordsetPtr != NULL)
		{
			recordCount = recordsetPtr->GetRecordCount();
			recordsetPtr->Close();
		}
		return recordCount;
	}
	IDbDataReader* ADOCommand::ExecuteReader(INT iBehavior)
	{
		return new ADODataReader(m_commandPtr->Execute(NULL, NULL, m_commandPtr->CommandType));
	}
	void ADOCommand::Dispose()
	{
		if (m_pParameters != NULL)
		{
			m_pParameters->RemoveAll();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	ADOTransaction::ADOTransaction(ADOConnection& connection, INT iIsolationLevel)
		: m_connection(connection),
		m_iIsolationLevel(iIsolationLevel)
	{
		m_connection.m_connectionPtr->IsolationLevel = (IsolationLevelEnum)iIsolationLevel;
	}
	IDbConnection* ADOTransaction::GetConnection()
	{
		return &m_connection;
	}
	INT ADOTransaction::GetIsolationLevel()
	{
		return m_iIsolationLevel;
	}
	BOOL ADOTransaction::Commit()
	{
		return SUCCEEDED(m_connection.m_connectionPtr->CommitTrans());
	}
	BOOL ADOTransaction::Rollback()
	{
		return SUCCEEDED(m_connection.m_connectionPtr->RollbackTrans());
	}
	void ADOTransaction::Dispose()
	{

	}
	//////////////////////////////////////////////////////////////////////////
	ADODataReader::ADODataReader(ADORecordsetPtr& recordsetPtr)
		:m_recordsetPtr(recordsetPtr)
	{

	}
	BOOL ADODataReader::ReadNext()
	{
		ASSERT(m_recordsetPtr);
		if (SUCCEEDED(m_recordsetPtr->MoveNext()))
		{
			m_fields = m_recordsetPtr->GetFields();
			return TRUE;
		}
		return FALSE;
	}
	BOOL ADODataReader::ReadPrevious()
	{
		ASSERT(m_recordsetPtr);
		if (SUCCEEDED(m_recordsetPtr->MovePrevious()))
		{
			m_fields = m_recordsetPtr->GetFields();
			return TRUE;
		}
		return FALSE;
	}
	BOOL ADODataReader::ReadFirst()
	{
		ASSERT(m_recordsetPtr);
		if (SUCCEEDED(m_recordsetPtr->MoveFirst()))
		{
			m_fields = m_recordsetPtr->GetFields();
			return TRUE;
		}
		return FALSE;
	}
	BOOL ADODataReader::ReadLast()
	{
		ASSERT(m_recordsetPtr);
		if (SUCCEEDED(m_recordsetPtr->MoveLast()))
		{
			m_fields = m_recordsetPtr->GetFields();
			return TRUE;
		}
		return FALSE;
	}
	BOOL ADODataReader::Close()
	{
		ASSERT(m_recordsetPtr);
		return SUCCEEDED(m_recordsetPtr->Close());
	}
	INT ADODataReader::GetColumnCount()
	{
		ASSERT(m_recordsetPtr);
		ASSERT(m_fields);
		return m_fields->GetCount();
	}
	BOOL ADODataReader::GetBoolean(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_BOOL);
		return (BOOL)val.boolVal;
	}
	BYTE ADODataReader::GetByte(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_UI1);
		return (BOOL)val.bVal;
	}
	CHAR ADODataReader::GetChar(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_I1);
		return val.cVal;
	}
	BYTE* ADODataReader::GetBlob(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_BLOB);
		return (BYTE*)val.parray->pvData;
	}
	LPCSTR ADODataReader::GetDataTypeName(INT i)
	{
		switch (m_fields->GetItem(i)->GetType())
		{
		case adEmpty:
			return "Empty";
		case adTinyInt:
			return "TinyInt";
		case adSmallInt:
			return "SmallInt";
		case adInteger:
			return "Integer";
		case adBigInt:
			return "BigInt";
		case adUnsignedTinyInt:
			return "UnsignedTinyInt";
		case adUnsignedSmallInt:
			return "UnsignedSmallInt";
		case adUnsignedInt:
			return "UnsignedInt";
		case adUnsignedBigInt:
			return "UnsignedBigInt";
		case adSingle:
			return "Single";
		case adDouble:
			return "Double";
		case adCurrency:
			return "Currency";
		case adDecimal:
			return "Decimal";
		case adNumeric:
			return "Numeric";
		case adBoolean:
			return "Boolean";
		case adError:
			return "Error";
		case adUserDefined:
			return "UserDefined";
		case adVariant:
			return "Variant";
		case adGUID:
			return "GUID";
		case adDate:
			return "Date";
		case adDBDate:
			return "DBDate";
		case adDBTime:
			return "DBTime";
		case adDBTimeStamp:
			return "DBTimeStamp";
		case adBSTR:
			return "BSTR";
		case adChar:
			return "Char";
		case adVarChar:
			return "VarChar";
		case adLongVarChar:
			return "LongVarChar";
		case adWChar:
			return "WChar";
		case adVarWChar:
			return "VarWChar";
		case adLongVarWChar:
			return "LongVarWChar";
		case adBinary:
			return "Binary";
		case adVarBinary:
			return "VarBinary";
		case adLongVarBinary:
			return "LongVarBinary";
		case adChapter:
			return "Chapter";
		case adFileTime:
			return "FileTime";
		case adPropVariant:
			return "PropVariant";
		case adVarNumeric:
			return "VarNumeric";
		case adArray:
			return "Array";
		default:
			return "Unknow";
		}
	}
	DATE ADODataReader::GetDateTime(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_DATE);
		return val.date;
	}
	DECIMAL ADODataReader::GetDecimal(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_DECIMAL);
		return val.decVal;
	}
	DOUBLE ADODataReader::GetDouble(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_R8);
		return val.dblVal;
	}
	FLOAT ADODataReader::GetFloat(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_R4);
		return val.fltVal;
	}
	SHORT ADODataReader::GetInt16(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_I2);
		return val.iVal;
	}
	INT ADODataReader::GetInt32(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_INT);
		return val.intVal;
	}
	LONG ADODataReader::GetInt64(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_I8);
		return val.lVal;
	}
	LPCSTR ADODataReader::GetName(INT i)
	{
		return m_fields->GetItem(i)->GetName();
	}
	INT ADODataReader::GetOrdinal(LPCSTR pzName)
	{
		INT count = m_fields->GetCount();
		for (INT i = 0; i < count; i++)
		{
			_bstr_t name = m_fields->GetItem(i)->GetName();
			if (name == _bstr_t(pzName))
			{
				return i;
			}
		}
		return -1;
	}
	LPCSTR ADODataReader::GetString(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		ASSERT(val.vt == VT_LPSTR);
		return (LPCSTR)&val.bstrVal;
	}
	BOOL ADODataReader::IsDBNull(INT i)
	{
		_variant_t val = m_fields->GetItem(i)->Value;
		return val.vt == VT_NULL;
	}
	//////////////////////////////////////////////////////////////////////////
	ADODataParameter::ADODataParameter()
		:m_parameterPtr(NULL)
	{
		m_parameterPtr.CreateInstance(__uuidof(Parameter));
	}
	INT ADODataParameter::GetDbType()
	{
		return (INT)m_parameterPtr->Type;
	}
	void ADODataParameter::SetDbType(INT dbTye)
	{
		m_parameterPtr->PutType((DataTypeEnum)dbTye);
	}
	INT ADODataParameter::GetDirection()
	{
		return (INT)m_parameterPtr->GetDirection();
	}
	void ADODataParameter::SetDirection(INT direction)
	{
		m_parameterPtr->PutDirection((ParameterDirectionEnum)direction);
	}
	BOOL ADODataParameter::IsNullable()
	{
		return m_parameterPtr->GetValue().vt == VT_NULL;
	}
	LPCSTR ADODataParameter::GetParameterName()
	{
		return m_parameterPtr->GetName();
	}
	void ADODataParameter::SetParameterName(LPCSTR pzName)
	{
		m_parameterPtr->PutName(pzName);
	}
	VARIANT& ADODataParameter::GetValue()
	{
		return m_parameterPtr->GetValue();
	}
	void ADODataParameter::SetValue(VARIANT& s)
	{
		m_parameterPtr->PutValue(s);
	}
	BYTE ADODataParameter::GetPrecision()
	{
		return m_parameterPtr->GetPrecision();
	}
	void ADODataParameter::SetPrecision(BYTE precision)
	{
		m_parameterPtr->PutPrecision(precision);
	}
	BYTE ADODataParameter::GetScale()
	{
		return m_parameterPtr->GetNumericScale();
	}
	void ADODataParameter::SetScale(BYTE scale)
	{
		m_parameterPtr->PutNumericScale(scale);
	}
	INT ADODataParameter::GetSize()
	{
		return m_parameterPtr->GetSize();
	}
	void ADODataParameter::SetSize(INT size)
	{
		m_parameterPtr->PutSize(size);
	}
	//////////////////////////////////////////////////////////////////////////
	IDbDataParameter* ADODataParameters::Add(IDbDataParameter* value)
	{
		ASSERT(value);
		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Append(reinterpret_cast<ADODataParameter*>(value)->m_parameterPtr)))
		{
			m_command.m_commandPtr->Parameters->Refresh();
			if (m_parameters.Add(value))
			{
				return value;
			}
		}
		return NULL;
	}
	IDbDataParameter* ADODataParameters::Add(LPCSTR pzName, VARIANT& pValue)
	{
		IDbDataParameter* ps = new ADODataParameter();
		if (ps != NULL)
		{
			ps->SetParameterName(pzName);
			ps->SetValue(pValue);
			return Add(ps);
		}
		return NULL;
	}
	IDbDataParameter* ADODataParameters::Add(LPCSTR pzName, INT dbType)
	{
		IDbDataParameter* ps = new ADODataParameter();
		if (ps != NULL)
		{
			ps->SetParameterName(pzName);
			ps->SetDbType(dbType);
			return Add(ps);
		}
		return NULL;
	}
	IDbDataParameter* ADODataParameters::Add(LPCSTR pzName, INT dbType, INT size)
	{
		IDbDataParameter* ps = new ADODataParameter();
		if (ps != NULL)
		{
			ps->SetParameterName(pzName);
			ps->SetDbType(dbType);
			ps->SetSize(size);
			return Add(ps);
		}
		return NULL;
	}
	void ADODataParameters::Remove(IDbDataParameter* value)
	{
		ASSERT(value);
		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Delete(value->GetParameterName())))
		{
			m_command.m_commandPtr->Parameters->Refresh();
			if (m_parameters.Remove(value))
			{
				SAFE_DELETE(value);
			}
		}
	}
	void ADODataParameters::RemoveAt(INT index)
	{
		ASSERT(index >= 0 && index < m_parameters.GetSize());
		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Delete(index)))
		{
			m_command.m_commandPtr->Parameters->Refresh();
			IDbDataParameter* value = GetParameter(index);
			if (m_parameters.Remove(value))
			{
				SAFE_DELETE(value);
			}
		}
	}
	void ADODataParameters::RemoveAt(LPCSTR pzName)
	{
		ASSERT(pzName);
		m_command.m_commandPtr->Parameters->GetItem(pzName);
		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Delete(pzName)))
		{
			m_command.m_commandPtr->Parameters->Refresh();
			IDbDataParameter* value = GetParameter(pzName);
			if (m_parameters.Remove(value))
			{
				SAFE_DELETE(value);
			}
		}
	}
	void ADODataParameters::RemoveAll()
	{
		if (DeleteAll())
		{
			//É¾³ý·ÖÅäÄÚ´æ
			for (INT i = 0; i < m_parameters.GetSize(); i++)
			{
				delete m_parameters[i];
			}
			m_parameters.RemoveAll();
		}
	}
	INT ADODataParameters::IndexOf(LPCSTR pzName)
	{
		INT count = m_command.m_commandPtr->Parameters->GetCount();
		for (INT i = 0; i < count; i++)
		{
			if (m_command.m_commandPtr->Parameters->GetItem(i)->GetName() == _bstr_t(pzName))
			{
				return i;
			}
		}
		return -1;
	}
	IDbDataParameter* ADODataParameters::GetParameter(INT index)
	{
		ASSERT(index >= 0 && index < m_parameters.GetSize());
		return m_parameters[index];
	}
	IDbDataParameter* ADODataParameters::GetParameter(LPCSTR pzName)
	{
		ASSERT(pzName);
		INT index = IndexOf(pzName);
		if (index >= 0)
		{
			return m_parameters[IndexOf(pzName)];
		}
		return NULL;
	}
	BOOL ADODataParameters::Contains(IDbDataParameter* value)
	{
		ASSERT(value);
		return m_parameters.Lookup(value) >= 0;
	}
	BOOL ADODataParameters::DeleteAll()
	{
		INT count = m_command.m_commandPtr->Parameters->GetCount();
		for (INT i = 0; i < count; i++)
		{
			if (FAILED(m_command.m_commandPtr->Parameters->Delete(i)))
			{
				return FALSE;
			}
		}
		m_command.m_commandPtr->Parameters->Refresh();
		return TRUE;
	}
}