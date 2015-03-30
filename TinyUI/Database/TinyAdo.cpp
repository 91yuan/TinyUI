#include "../stdafx.h"
#include "TinyAdo.h"

namespace TinyUI
{
	//ADOConnection::ADOConnection()
	//	:m_connectionPtr(NULL)
	//{
	//	m_connectionPtr.CreateInstance(__uuidof(ADODB::Connection));
	//}
	//ADOConnection::~ADOConnection()
	//{
	//	TRACE("析构ADOConnection\n");
	//	Dispose();
	//}
	//LPCSTR ADOConnection::GetConnectionString()
	//{
	//	ASSERT(m_connectionPtr);
	//	return m_connectionPtr->GetConnectionString();
	//}
	//void ADOConnection::SetConnectionString(LPCSTR connectionString)
	//{
	//	ASSERT(connectionString);
	//	m_connectionPtr->ConnectionString = connectionString;
	//}
	//LONG ADOConnection::GetConnectionTimeout()
	//{
	//	ASSERT(m_connectionPtr);
	//	return m_connectionPtr->GetConnectionTimeout();
	//}
	//void ADOConnection::SetConnectionTimeout(LONG connectionTimeout)
	//{
	//	ASSERT(m_connectionPtr);
	//	m_connectionPtr->CommandTimeout = connectionTimeout;
	//}
	//LONG ADOConnection::GetConnectionState()
	//{
	//	ASSERT(m_connectionPtr);
	//	return m_connectionPtr->State;
	//}
	//IDbTransaction* ADOConnection::BeginTransaction()
	//{
	//	ASSERT(m_connectionPtr);
	//	TinyCriticalSection section;
	//	section.Initialize();
	//	section.Lock();
	//	m_transaction.Reset(new ADOTransaction(*this));
	//	m_connectionPtr->BeginTrans();
	//	section.Unlock();
	//	section.Uninitialize();
	//	return m_transaction;
	//}
	//IDbTransaction* ADOConnection::BeginTransaction(INT iIsolationLevel)
	//{
	//	ASSERT(m_connectionPtr);
	//	TinyCriticalSection section;
	//	section.Initialize();
	//	section.Lock();
	//	m_transaction.Reset(new ADOTransaction(*this));
	//	m_connectionPtr->BeginTrans();
	//	section.Unlock();
	//	section.Uninitialize();
	//	return m_transaction;
	//}
	//BOOL ADOConnection::Open()
	//{
	//	ASSERT(m_connectionPtr);
	//	BOOL bRes = FALSE;
	//	try
	//	{
	//		m_connectionPtr->Provider = "SQLNCLI10";
	//		m_connectionPtr->CursorLocation = adUseClient; //游标类型   
	//		m_connectionPtr->CommandTimeout = 6000;
	//		if (!m_connectionPtr->State)
	//			bRes = SUCCEEDED(m_connectionPtr->Open("", "", "", adModeUnknown));
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return bRes;
	//}
	//BOOL ADOConnection::Close()
	//{
	//	ASSERT(m_connectionPtr);
	//	try
	//	{
	//		if (m_connectionPtr->State)
	//		{
	//			return SUCCEEDED(m_connectionPtr->Close());
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return FALSE;
	//}
	//IDbCommand* ADOConnection::CreateCommand()
	//{
	//	try
	//	{
	//		TinyCriticalSection section;
	//		section.Initialize();
	//		section.Lock();
	//		m_command.Reset(new ADOCommand(*this));
	//		section.Unlock();
	//		section.Uninitialize();
	//		return m_command;
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return NULL;
	//}
	//void ADOConnection::Dispose()
	//{
	//	try
	//	{
	//		if (m_connectionPtr != NULL &&
	//			m_connectionPtr->State)
	//		{
	//			m_connectionPtr->Close();
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//}
	//INT	ADOConnection::GetErrors(LPSTR pzError, INT size)
	//{
	//	ASSERT(m_connectionPtr);
	//	m_connectionPtr->Errors->Clear();
	//	TinyString str;
	//	INT count = m_connectionPtr->Errors->Count;
	//	for (INT i = 0; i < count; i++)
	//	{
	//		ErrorPtr errorPtr = m_connectionPtr->Errors->GetItem(i);
	//		TinyString desc = TinyString::Format("Number:%d,SQLState:%s,Desc:%s\n", errorPtr->GetNumber(), errorPtr->GetSQLState(), errorPtr->GetDescription());
	//		str += desc;
	//	}
	//	strcpy_s(pzError, size, str.STR());
	//	return str.GetSize();
	//}
	////////////////////////////////////////////////////////////////////////////
	//ADOCommand::ADOCommand(ADOConnection& connection)
	//	:m_commandPtr(NULL),
	//	m_connection(connection),
	//	m_parameters(NULL)
	//{
	//	if (SUCCEEDED(m_commandPtr.CreateInstance(__uuidof(Command))))
	//	{
	//		m_commandPtr->ActiveConnection = m_connection.m_connectionPtr;
	//		m_commandPtr->NamedParameters = TRUE;
	//		m_parameters.Reset(new ADODataParameters(*this));
	//	}
	//}
	//ADOCommand::~ADOCommand()
	//{
	//	TRACE("析构ADOCommand\n");
	//	if (m_parameters != NULL)
	//	{
	//		m_parameters->RemoveAll();
	//	}
	//}
	//LPCSTR ADOCommand::GetCommandText()
	//{
	//	return m_commandPtr->GetCommandText();
	//}
	//void ADOCommand::SetCommandText(LPCSTR pzText)
	//{
	//	ASSERT(m_commandPtr);
	//	m_commandPtr->CommandText = pzText;
	//}
	//LONG ADOCommand::GetCommandTimeout()
	//{
	//	ASSERT(m_commandPtr);
	//	return m_commandPtr->GetCommandTimeout();
	//}
	//void ADOCommand::SetCommandTimeout(LONG commandTimeout)
	//{
	//	ASSERT(m_commandPtr);
	//	m_commandPtr->CommandTimeout = commandTimeout;
	//}
	//INT	ADOCommand::GetCommandType()
	//{
	//	ASSERT(m_commandPtr);
	//	return (INT)m_commandPtr->CommandType;
	//}
	//void ADOCommand::SetCommandType(INT commandType)
	//{
	//	ASSERT(m_commandPtr);
	//	m_commandPtr->CommandType = (CommandTypeEnum)commandType;
	//}
	//IDbConnection* ADOCommand::GetConnection()
	//{
	//	return &m_connection;
	//}
	//IDbDataParameters* ADOCommand::GetParameters()
	//{
	//	return m_parameters;
	//}
	//IDbTransaction* ADOCommand::GetTransaction()
	//{
	//	return m_connection.m_transaction;
	//}
	//BOOL ADOCommand::Cancel()
	//{
	//	ASSERT(m_commandPtr);
	//	try
	//	{
	//		return SUCCEEDED(m_commandPtr->Cancel());
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return FALSE;
	//}
	//IDbDataParameter* ADOCommand::CreateParameter()
	//{
	//	return new ADODataParameter(m_commandPtr);
	//}
	//INT ADOCommand::ExecuteNonQuery()
	//{
	//	ASSERT(m_commandPtr);
	//	VARIANT vi = { 0 };
	//	try
	//	{
	//		VARIANT vi = { 0 };
	//		ADORecordsetPtr recordsetPtr = m_commandPtr->Execute(&vi, NULL, (LONG)m_commandPtr->CommandType);
	//		return vi.lVal;
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return vi.lVal;
	//}
	//IDbDataReader* ADOCommand::ExecuteReader(INT iBehavior)
	//{
	//	try
	//	{
	//		VARIANT vi = { 0 };
	//		ADORecordsetPtr recordsetPtr = m_commandPtr->Execute(&vi, NULL, m_commandPtr->CommandType);
	//		m_reader.Reset(new ADODataReader(recordsetPtr));
	//		return m_reader;
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return NULL;
	//}
	//void ADOCommand::Dispose()
	//{
	//	if (m_parameters != NULL)
	//	{
	//		m_parameters->RemoveAll();
	//	}
	//}
	////////////////////////////////////////////////////////////////////////////
	//ADOTransaction::ADOTransaction(ADOConnection& connection, INT iIsolationLevel)
	//	: m_connection(connection),
	//	m_iIsolationLevel(iIsolationLevel)
	//{
	//	m_connection.m_connectionPtr->IsolationLevel = (IsolationLevelEnum)iIsolationLevel;
	//}
	//ADOTransaction::~ADOTransaction()
	//{
	//	TRACE("析构ADOTransaction\n");
	//}
	//IDbConnection* ADOTransaction::GetConnection()
	//{
	//	return &m_connection;
	//}
	//INT ADOTransaction::GetIsolationLevel()
	//{
	//	return m_iIsolationLevel;
	//}
	//BOOL ADOTransaction::Commit()
	//{
	//	return SUCCEEDED(m_connection.m_connectionPtr->CommitTrans());
	//}
	//BOOL ADOTransaction::Rollback()
	//{
	//	return SUCCEEDED(m_connection.m_connectionPtr->RollbackTrans());
	//}
	//void ADOTransaction::Dispose()
	//{

	//}
	////////////////////////////////////////////////////////////////////////////
	//ADODataReader::ADODataReader(ADORecordsetPtr& recordsetPtr)
	//{
	//	if (SUCCEEDED(m_recordsetPtr.CreateInstance(__uuidof(Recordset))))
	//	{
	//		m_recordsetPtr = recordsetPtr.GetInterfacePtr();
	//	}
	//}
	//ADODataReader::~ADODataReader()
	//{
	//	m_recordsetPtr->Release();
	//	TRACE("析构ADODataReader\n");
	//}
	//BOOL ADODataReader::ReadNext()
	//{
	//	ASSERT(m_recordsetPtr);
	//	try
	//	{
	//		if (m_recordsetPtr->State &&
	//			SUCCEEDED(m_recordsetPtr->MoveNext()))
	//		{
	//			m_fields = m_recordsetPtr->GetFields();
	//			return !m_recordsetPtr->EndOfFile;
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}

	//	return FALSE;
	//}
	//BOOL ADODataReader::ReadPrevious()
	//{
	//	ASSERT(m_recordsetPtr);
	//	try
	//	{
	//		if (m_recordsetPtr->State
	//			&& SUCCEEDED(m_recordsetPtr->MovePrevious()))
	//		{
	//			m_fields = m_recordsetPtr->GetFields();
	//			return !m_recordsetPtr->EndOfFile;
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return FALSE;
	//}
	//BOOL ADODataReader::ReadFirst()
	//{
	//	ASSERT(m_recordsetPtr);
	//	try
	//	{
	//		if (m_recordsetPtr->State
	//			&& SUCCEEDED(m_recordsetPtr->MoveFirst()))
	//		{
	//			m_fields = m_recordsetPtr->GetFields();
	//			return !m_recordsetPtr->EndOfFile;
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return FALSE;
	//}
	//BOOL ADODataReader::ReadLast()
	//{
	//	ASSERT(m_recordsetPtr);
	//	try
	//	{
	//		if (m_recordsetPtr->State
	//			&& SUCCEEDED(m_recordsetPtr->MoveLast()))
	//		{
	//			m_fields = m_recordsetPtr->GetFields();
	//			return !m_recordsetPtr->EndOfFile;
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return FALSE;
	//}
	//BOOL ADODataReader::Close()
	//{
	//	ASSERT(m_recordsetPtr);
	//	try
	//	{
	//		if (m_recordsetPtr->State)
	//		{
	//			return SUCCEEDED(m_recordsetPtr->Close());
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return FALSE;
	//}
	//INT ADODataReader::GetColumnCount()
	//{
	//	ASSERT(m_recordsetPtr);
	//	ASSERT(m_fields);
	//	return m_fields->GetCount();
	//}
	//BOOL ADODataReader::GetBoolean(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_BOOL);
	//	return (BOOL)val.boolVal;
	//}
	//BYTE ADODataReader::GetByte(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_UI1);
	//	return (BOOL)val.bVal;
	//}
	//CHAR ADODataReader::GetChar(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_I1);
	//	return val.cVal;
	//}
	//BYTE* ADODataReader::GetBlob(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_BLOB);
	//	return (BYTE*)val.parray->pvData;
	//}
	//LPCSTR ADODataReader::GetDataTypeName(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	switch (m_fields->GetItem(vtIndex)->GetType())
	//	{
	//	case adEmpty:
	//		return "Empty";
	//	case adTinyInt:
	//		return "TinyInt";
	//	case adSmallInt:
	//		return "SmallInt";
	//	case adInteger:
	//		return "Integer";
	//	case adBigInt:
	//		return "BigInt";
	//	case adUnsignedTinyInt:
	//		return "UnsignedTinyInt";
	//	case adUnsignedSmallInt:
	//		return "UnsignedSmallInt";
	//	case adUnsignedInt:
	//		return "UnsignedInt";
	//	case adUnsignedBigInt:
	//		return "UnsignedBigInt";
	//	case adSingle:
	//		return "Single";
	//	case adDouble:
	//		return "Double";
	//	case adCurrency:
	//		return "Currency";
	//	case adDecimal:
	//		return "Decimal";
	//	case adNumeric:
	//		return "Numeric";
	//	case adBoolean:
	//		return "Boolean";
	//	case adError:
	//		return "Error";
	//	case adUserDefined:
	//		return "UserDefined";
	//	case adVariant:
	//		return "Variant";
	//	case adGUID:
	//		return "GUID";
	//	case adDate:
	//		return "Date";
	//	case adDBDate:
	//		return "DBDate";
	//	case adDBTime:
	//		return "DBTime";
	//	case adDBTimeStamp:
	//		return "DBTimeStamp";
	//	case adBSTR:
	//		return "BSTR";
	//	case adChar:
	//		return "Char";
	//	case adVarChar:
	//		return "VarChar";
	//	case adLongVarChar:
	//		return "LongVarChar";
	//	case adWChar:
	//		return "WChar";
	//	case adVarWChar:
	//		return "VarWChar";
	//	case adLongVarWChar:
	//		return "LongVarWChar";
	//	case adBinary:
	//		return "Binary";
	//	case adVarBinary:
	//		return "VarBinary";
	//	case adLongVarBinary:
	//		return "LongVarBinary";
	//	case adChapter:
	//		return "Chapter";
	//	case adFileTime:
	//		return "FileTime";
	//	case adPropVariant:
	//		return "PropVariant";
	//	case adVarNumeric:
	//		return "VarNumeric";
	//	case adArray:
	//		return "Array";
	//	default:
	//		return "Unknow";
	//	}
	//}
	//DATE ADODataReader::GetDateTime(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_DATE);
	//	return val.date;
	//}
	//DECIMAL ADODataReader::GetDecimal(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_DECIMAL);
	//	return val.decVal;
	//}
	//DOUBLE ADODataReader::GetDouble(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_R8);
	//	return val.dblVal;
	//}
	//FLOAT ADODataReader::GetFloat(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_R4);
	//	return val.fltVal;
	//}
	//SHORT ADODataReader::GetInt16(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_I2);
	//	return val.iVal;
	//}
	//INT ADODataReader::GetInt32(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_I4);
	//	return val.lVal;
	//}
	//LONG ADODataReader::GetInt64(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_I8);
	//	return val.lVal;
	//}
	//LPCSTR ADODataReader::GetName(INT i)
	//{
	//	try
	//	{
	//		_variant_t vtIndex;
	//		vtIndex.vt = VT_I2;
	//		vtIndex.iVal = i;
	//		return _com_util::ConvertBSTRToString(m_fields->GetItem(vtIndex)->GetName());
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return NULL;
	//}
	//INT ADODataReader::GetOrdinal(LPCSTR pzName)
	//{
	//	INT count = m_fields->GetCount();
	//	for (INT i = 0; i < count; i++)
	//	{
	//		_variant_t vtIndex;
	//		vtIndex.vt = VT_I2;
	//		vtIndex.iVal = i;
	//		_bstr_t name = m_fields->GetItem(vtIndex)->GetName();
	//		if (name == _bstr_t(pzName))
	//		{
	//			return i;
	//		}
	//	}
	//	return -1;
	//}
	//LPCSTR ADODataReader::GetString(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	ASSERT(val.vt == VT_BSTR);
	//	return (LPCSTR)_com_util::ConvertBSTRToString(val.bstrVal);
	//}
	//BOOL ADODataReader::IsDBNull(INT i)
	//{
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = i;
	//	_variant_t val = m_fields->GetItem(vtIndex)->Value;
	//	return val.vt == VT_NULL;
	//}
	////////////////////////////////////////////////////////////////////////////
	//ADODataParameter::ADODataParameter(ADOCommandPtr&	commandPtr)
	//	:m_parameterPtr(NULL),
	//	m_commandPtr(commandPtr)
	//{
	//	if (SUCCEEDED(m_parameterPtr.CreateInstance(__uuidof(Parameter))))
	//	{
	//		m_parameterPtr->Direction = adParamInput;
	//	}
	//}
	//INT ADODataParameter::GetDbType()
	//{
	//	return (INT)m_parameterPtr->Type;
	//}
	//void ADODataParameter::SetDbType(INT dbTye)
	//{
	//	m_parameterPtr->PutType((DataTypeEnum)dbTye);
	//}
	//INT ADODataParameter::GetDirection()
	//{
	//	return (INT)m_parameterPtr->GetDirection();
	//}
	//void ADODataParameter::SetDirection(INT direction)
	//{
	//	m_parameterPtr->PutDirection((ParameterDirectionEnum)direction);
	//}
	//BOOL ADODataParameter::IsNullable()
	//{
	//	return m_parameterPtr->GetValue().vt == VT_NULL;
	//}
	//LPCSTR ADODataParameter::GetParameterName()
	//{
	//	return m_parameterPtr->GetName();
	//}
	//void ADODataParameter::SetParameterName(LPCSTR pzName)
	//{
	//	m_parameterPtr->PutName(pzName);
	//}
	//BYTE ADODataParameter::GetPrecision()
	//{
	//	return m_parameterPtr->GetPrecision();
	//}
	//void ADODataParameter::SetPrecision(BYTE precision)
	//{
	//	m_parameterPtr->PutPrecision(precision);
	//}
	//BYTE ADODataParameter::GetScale()
	//{
	//	return m_parameterPtr->GetNumericScale();
	//}
	//void ADODataParameter::SetScale(BYTE scale)
	//{
	//	m_parameterPtr->PutNumericScale(scale);
	//}
	//INT ADODataParameter::GetSize()
	//{
	//	return m_parameterPtr->GetSize();
	//}
	//void ADODataParameter::SetSize(INT size)
	//{
	//	m_parameterPtr->PutSize(size);
	//}

	//void ADODataParameter::SetBoolean(BOOL val)
	//{
	//	V_VT(&m_value) = VT_BOOL;
	//	V_BOOL(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetByte(BYTE val)
	//{
	//	V_VT(&m_value) = VT_UI1;
	//	V_UI1(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetChar(CHAR val)
	//{
	//	V_VT(&m_value) = VT_I1;
	//	V_I1(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetBlob(LPBYTE val)
	//{

	//}

	//void ADODataParameter::SetDateTime(DATE val)
	//{
	//	V_VT(&m_value) = VT_DATE;
	//	V_DATE(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetDecimal(DECIMAL val)
	//{
	//	V_VT(&m_value) = VT_DECIMAL;
	//	V_DECIMAL(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetDouble(DOUBLE val)
	//{
	//	V_VT(&m_value) = VT_R8;
	//	V_R8(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetFloat(FLOAT val)
	//{
	//	V_VT(&m_value) = VT_R4;
	//	V_R4(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetInt16(SHORT val)
	//{
	//	V_VT(&m_value) = VT_I2;
	//	V_I2(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetInt32(INT val)
	//{
	//	V_VT(&m_value) = VT_I4;
	//	V_I4(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetInt64(LONG val)
	//{
	//	V_VT(&m_value) = VT_I8;
	//	V_I8(&m_value) = val;
	//	m_parameterPtr->PutValue(m_value);
	//}

	//void ADODataParameter::SetString(LPCSTR val)
	//{
	//	V_VT(&m_value) = VT_BSTR;
	//	V_BSTR(&m_value) = _bstr_t(val);
	//	m_parameterPtr->PutValue(m_value);
	//}
	//void ADODataParameter::SetValue(VARIANT& val)
	//{
	//	m_value = val;
	//	m_parameterPtr->PutValue(val);
	//}
	////////////////////////////////////////////////////////////////////////////
	//ADODataParameters::ADODataParameters(ADOCommand& command)
	//	:m_command(command)
	//{

	//}
	//ADODataParameters::~ADODataParameters()
	//{
	//	TRACE("析构ADODataParameters\n");
	//}
	//IDbDataParameter* ADODataParameters::Add(IDbDataParameter* value)
	//{
	//	ASSERT(value);
	//	try
	//	{
	//		ADODataParameter* ps = reinterpret_cast<ADODataParameter*>(value);
	//		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Append(ps->m_parameterPtr)))
	//		{
	//			m_command.m_commandPtr->Parameters->Refresh();
	//			if (m_parameters.Add(value))
	//			{
	//				return value;
	//			}
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//	return NULL;
	//}
	//IDbDataParameter* ADODataParameters::Add(LPCSTR pzName, VARIANT& val)
	//{
	//	ASSERT(m_command.m_commandPtr);
	//	IDbDataParameter* ps = new ADODataParameter(m_command.m_commandPtr);
	//	if (ps != NULL)
	//	{
	//		ps->SetParameterName(pzName);
	//		return Add(ps);
	//	}
	//	return NULL;
	//}
	//IDbDataParameter* ADODataParameters::Add(LPCSTR pzName, INT dbType)
	//{
	//	ASSERT(m_command.m_commandPtr);
	//	IDbDataParameter* ps = new ADODataParameter(m_command.m_commandPtr);
	//	if (ps != NULL)
	//	{
	//		ps->SetParameterName(pzName);
	//		ps->SetDbType(dbType);
	//		return Add(ps);
	//	}
	//	return NULL;
	//}
	//IDbDataParameter* ADODataParameters::Add(LPCSTR pzName, INT dbType, INT size)
	//{
	//	ASSERT(m_command.m_commandPtr);
	//	IDbDataParameter* ps = new ADODataParameter(m_command.m_commandPtr);
	//	if (ps != NULL)
	//	{
	//		ps->SetParameterName(pzName);
	//		ps->SetDbType(dbType);
	//		ps->SetSize(size);
	//		return Add(ps);
	//	}
	//	return NULL;
	//}
	//void ADODataParameters::Remove(IDbDataParameter* value)
	//{
	//	ASSERT(value);
	//	try
	//	{
	//		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Delete(value->GetParameterName())))
	//		{
	//			m_command.m_commandPtr->Parameters->Refresh();
	//			if (m_parameters.Remove(value))
	//			{
	//				SAFE_DELETE(value);
	//			}
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//}
	//void ADODataParameters::RemoveAt(INT index)
	//{
	//	ASSERT(index >= 0 && index < m_parameters.GetSize());
	//	try
	//	{
	//		_variant_t vtIndex;
	//		vtIndex.vt = VT_I2;
	//		vtIndex.iVal = index;
	//		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Delete(vtIndex)))
	//		{
	//			m_command.m_commandPtr->Parameters->Refresh();
	//			IDbDataParameter* value = GetParameter(index);
	//			if (m_parameters.Remove(value))
	//			{
	//				SAFE_DELETE(value);
	//			}
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//}
	//void ADODataParameters::RemoveAt(LPCSTR pzName)
	//{
	//	ASSERT(pzName);
	//	try
	//	{
	//		m_command.m_commandPtr->Parameters->GetItem(pzName);
	//		if (SUCCEEDED(m_command.m_commandPtr->Parameters->Delete(pzName)))
	//		{
	//			m_command.m_commandPtr->Parameters->Refresh();
	//			IDbDataParameter* value = GetParameter(pzName);
	//			if (m_parameters.Remove(value))
	//			{
	//				SAFE_DELETE(value);
	//			}
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}

	//}
	//void ADODataParameters::RemoveAll()
	//{
	//	try
	//	{
	//		INT count = m_parameters.GetSize();
	//		for (INT i = count - 1; i > 0; i--)
	//		{
	//			m_parameters.Remove(m_parameters[i]);
	//		}
	//	}
	//	catch (_com_error& e)
	//	{
	//		TRACE(e.Description());
	//		TRACE("\n");
	//	}
	//}
	//INT ADODataParameters::IndexOf(LPCSTR pzName)
	//{
	//	_ParameterPtr parameterPtr = m_command.m_commandPtr->Parameters->GetItem(pzName);
	//	INT count = m_parameters.GetSize();
	//	for (INT i = 0; i < count; i++)
	//	{
	//		ADODataParameter* ps = reinterpret_cast<ADODataParameter*>(m_parameters[i]);
	//		if (ps->m_parameterPtr == parameterPtr)
	//		{
	//			return i;
	//		}
	//	}
	//	return -1;
	//}
	//IDbDataParameter* ADODataParameters::GetParameter(INT index)
	//{
	//	ASSERT(index >= 0 && index < m_parameters.GetSize());
	//	ADODataParameter* ps = reinterpret_cast<ADODataParameter*>(m_parameters[index]);
	//	_variant_t vtIndex;
	//	vtIndex.vt = VT_I2;
	//	vtIndex.iVal = index;
	//	_ParameterPtr parameterPtr = m_command.m_commandPtr->Parameters->GetItem(vtIndex);
	//	return ps->m_parameterPtr != parameterPtr ? NULL : ps;
	//}
	//IDbDataParameter* ADODataParameters::GetParameter(LPCSTR pzName)
	//{
	//	ASSERT(pzName);
	//	_ParameterPtr parameterPtr = m_command.m_commandPtr->Parameters->GetItem(pzName);
	//	INT count = m_parameters.GetSize();
	//	for (INT i = 0; i < count; i++)
	//	{
	//		ADODataParameter* ps = reinterpret_cast<ADODataParameter*>(m_parameters[i]);
	//		if (ps->m_parameterPtr == parameterPtr)
	//		{
	//			return ps;
	//		}
	//	}
	//	return NULL;
	//}
	//BOOL ADODataParameters::Contains(IDbDataParameter* value)
	//{
	//	ASSERT(value);
	//	return m_parameters.Lookup(value) >= 0;
	//}
}