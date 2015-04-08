#include "../stdafx.h"
#include "TinyAdo.h"

namespace TinyUI
{
	//////////////////////////////////////////////////////////////////////////
	ADOConnection::ADOConnection()
	{
		m_connectionPtr.CreateInstance(__uuidof(ADODB::Connection));
	}
	ADOConnection::~ADOConnection()
	{
		TRACE("析构ADOConnection\n");
	}
	LPCSTR	ADOConnection::GetConnectionString() const
	{
		ASSERT(m_connectionPtr);
		return m_connectionPtr->GetConnectionString();
	}
	void	ADOConnection::SetConnectionString(LPCSTR pzText)
	{
		ASSERT(m_connectionPtr);
		return m_connectionPtr->PutConnectionString(pzText);
	}
	LONG	ADOConnection::GetConnectionTimeout() const
	{
		ASSERT(m_connectionPtr);
		return m_connectionPtr->GetConnectionTimeout();
	}
	void	ADOConnection::SetConnectionTimeout(LONG timeMs)
	{
		ASSERT(m_connectionPtr);
		m_connectionPtr->PutConnectionTimeout(timeMs);
	}
	BOOL	ADOConnection::Open()
	{
		ASSERT(m_connectionPtr);
		BOOL bRes = FALSE;
		try
		{
			m_connectionPtr->Provider = "SQLNCLI10";
			m_connectionPtr->CursorLocation = adUseClient; //游标类型   
			m_connectionPtr->CommandTimeout = 6000;
			if (!m_connectionPtr->State)
				bRes = SUCCEEDED(m_connectionPtr->Open("", "", "", adModeUnknown));
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return bRes;
	}
	BOOL	ADOConnection::Close()
	{
		ASSERT(m_connectionPtr);
		try
		{
			if (m_connectionPtr->State)
			{
				return SUCCEEDED(m_connectionPtr->Close());
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	LONG	ADOConnection::GetConnectionState()
	{
		ASSERT(m_connectionPtr);
		return m_connectionPtr->GetState();
	}
	BOOL	ADOConnection::BeginTransaction(INT iIsolationLevel)
	{
		ASSERT(m_connectionPtr);
		try
		{
			if (m_connectionPtr->State)
			{
				m_connectionPtr->PutIsolationLevel((IsolationLevelEnum)iIsolationLevel);
				m_connectionPtr->BeginTrans();
			}
			return TRUE;
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL	ADOConnection::CommitTransaction()
	{
		ASSERT(m_connectionPtr);
		try
		{
			if (m_connectionPtr->State)
			{
				return SUCCEEDED(m_connectionPtr->CommitTrans());
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;

	}
	BOOL	ADOConnection::RollbackTransaction()
	{
		ASSERT(m_connectionPtr);
		try
		{
			if (m_connectionPtr->State)
			{
				return SUCCEEDED(m_connectionPtr->RollbackTrans());
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	void	ADOConnection::GetErrors(LPSTR pzError, INT& size)
	{
		ASSERT(m_connectionPtr);
		m_connectionPtr->Errors->Clear();
		TinyString str;
		INT count = m_connectionPtr->Errors->Count;
		for (INT i = 0; i < count; i++)
		{
			ErrorPtr errorPtr = m_connectionPtr->Errors->GetItem(i);
			TinyString desc = TinyString::Format("Number:%d,SQLState:%s,Desc:%s\n", errorPtr->GetNumber(), errorPtr->GetSQLState(), errorPtr->GetDescription());
			str += desc;
		}
		strcpy_s(pzError, size, str.STR());
	}
	//////////////////////////////////////////////////////////////////////////
	ADOCommand::ADOCommand(ADOConnection& connection)
		:m_connection(connection)
	{
		if (SUCCEEDED(m_commandPtr.CreateInstance(__uuidof(Command))))
		{
			m_commandPtr->ActiveConnection = m_connection.m_connectionPtr;
			m_commandPtr->NamedParameters = TRUE;
			m_commandPtr->CommandType = adCmdStoredProc;
		}
	}
	ADOCommand::~ADOCommand()
	{
		TRACE("析构ADOCommand\n");
	}
	LPCSTR	ADOCommand::GetCommandText() const
	{
		ASSERT(m_commandPtr);
		return m_commandPtr->GetCommandText();
	}
	void	ADOCommand::SetCommandText(LPCSTR pzText)
	{
		ASSERT(m_commandPtr);
		m_commandPtr->PutCommandText(pzText);
	}
	LONG	ADOCommand::GetCommandTimeout() const
	{
		ASSERT(m_commandPtr);
		return m_commandPtr->GetCommandTimeout();
	}
	void	ADOCommand::SetCommandTimeout(LONG time)
	{
		ASSERT(m_commandPtr);
		m_commandPtr->PutCommandTimeout(time);
	}
	INT		ADOCommand::GetCommandType()
	{
		ASSERT(m_commandPtr);
		return m_commandPtr->GetCommandType();
	}
	void	ADOCommand::SetCommandType(INT commandType)
	{
		ASSERT(m_commandPtr);
		return m_commandPtr->PutCommandType((CommandTypeEnum)commandType);
	}
	IDbConnection*	ADOCommand::GetConnection()
	{
		return &m_connection;
	}
	BOOL	ADOCommand::Add(IDbDataParameter* value)
	{
		ASSERT(value);
		try
		{
			ADODataParameter* ps = reinterpret_cast<ADODataParameter*>(value);
			if (SUCCEEDED(m_commandPtr->Parameters->Append(ps->m_parameterPtr)))
			{
				return TRUE;
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL	ADOCommand::Remove(INT i)
	{
		try
		{
			_variant_t vtIndex;
			vtIndex.vt = VT_I2;
			vtIndex.iVal = i;
			if (SUCCEEDED(m_commandPtr->Parameters->Delete(vtIndex)))
			{
				return TRUE;
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL	ADOCommand::Remove(LPCSTR pzName)
	{
		ASSERT(pzName);
		try
		{
			if (SUCCEEDED(m_commandPtr->Parameters->Delete(pzName)))
			{
				return TRUE;
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL	ADOCommand::RemoveAll()
	{
		try
		{
			INT count = m_commandPtr->Parameters->GetCount();;
			for (INT i = count - 1; i > 0; i--)
			{
				_variant_t vtIndex;
				vtIndex.vt = VT_I2;
				vtIndex.iVal = i;
				if (FAILED(m_commandPtr->Parameters->Delete(vtIndex)))
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	INT		ADOCommand::ExecuteNonQuery()
	{
		ASSERT(m_commandPtr);
		VARIANT vi = { 0 };
		try
		{
			m_commandPtr->PutPrepared(TRUE);
			m_commandPtr->Execute(&vi, NULL, (LONG)m_commandPtr->CommandType);
			return vi.lVal;
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return vi.lVal;
	}
	BOOL	ADOCommand::ExecuteReader(IDbDataReader* ps)
	{
		ASSERT(ps);
		try
		{
			m_commandPtr->PutPrepared(TRUE);
			VARIANT vi = { 0 };
			ADORecordsetPtr recordsetPtr = m_commandPtr->Execute(&vi, NULL, m_commandPtr->CommandType);
			ADODataReader* reader = reinterpret_cast<ADODataReader*>(ps);
			reader->m_recordsetPtr = recordsetPtr.GetInterfacePtr();
			return TRUE;
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL ADOCommand::Cancel()
	{
		try
		{
			return SUCCEEDED(m_commandPtr->Cancel());
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	ADODataParameter::ADODataParameter(ADOCommand& command)
		:m_command(command)
	{
		if (SUCCEEDED(m_parameterPtr.CreateInstance(__uuidof(Parameter))))
		{
			m_parameterPtr->PutDirection(adParamInput);
		}
	}
	ADODataParameter::~ADODataParameter()
	{
		TRACE("析构ADODataParameter\n");
	}
	BOOL	ADODataParameter::IsNullable()
	{
		ASSERT(m_parameterPtr);
		return m_parameterPtr->GetValue().vt == VT_NULL;
	}
	INT		ADODataParameter::GetDbType()
	{
		ASSERT(m_parameterPtr);
		return (INT)m_parameterPtr->GetType();
	}
	void	ADODataParameter::SetDbType(INT dbTye)
	{
		ASSERT(m_parameterPtr);
		try
		{
			m_parameterPtr->PutType((DataTypeEnum)dbTye);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	INT		ADODataParameter::GetDirection()
	{
		ASSERT(m_parameterPtr);
		return m_parameterPtr->GetDirection();
	}
	void	ADODataParameter::SetDirection(INT direction)
	{
		ASSERT(m_parameterPtr);
		try
		{
			m_parameterPtr->PutDirection((ParameterDirectionEnum)direction);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	LPCSTR	ADODataParameter::GetParameterName()
	{
		ASSERT(m_parameterPtr);
		return m_parameterPtr->GetName();
	}
	void	ADODataParameter::SetParameterName(LPCSTR pzName)
	{
		ASSERT(m_parameterPtr);
		try
		{
			m_parameterPtr->PutName(pzName);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	BYTE	ADODataParameter::GetPrecision()
	{
		ASSERT(m_parameterPtr);
		return m_parameterPtr->GetPrecision();
	}
	void	ADODataParameter::SetPrecision(BYTE precision)
	{
		ASSERT(m_parameterPtr);
		try
		{
			m_parameterPtr->PutPrecision(precision);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	BYTE	ADODataParameter::GetScale()
	{
		ASSERT(m_parameterPtr);
		return m_parameterPtr->GetNumericScale();
	}
	void	ADODataParameter::SetScale(BYTE scale)
	{
		ASSERT(m_parameterPtr);
		try
		{
			m_parameterPtr->PutNumericScale(scale);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	INT		ADODataParameter::GetSize()
	{
		ASSERT(m_parameterPtr);
		return m_parameterPtr->GetSize();
	}
	void	ADODataParameter::SetSize(INT size)
	{
		ASSERT(m_parameterPtr);
		try
		{
			m_parameterPtr->PutSize(size);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetNull()
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_NULL;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetBoolean(BOOL val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_BOOL;
			V_BOOL(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetByte(BYTE val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_UI1;
			V_UI1(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetChar(CHAR val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_I1;
			V_I1(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetBlob(LPBYTE val, LONG size)
	{
		ASSERT(m_parameterPtr);
		try
		{
			SAFEARRAY   *psa = NULL;
			SAFEARRAYBOUND  rgsabound[1];
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = size;
			psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
			for (LONG i = 0; i < (LONG)size; i++)
			{
				SafeArrayPutElement(psa, &i, val++);
			}
			m_value.vt = VT_ARRAY | VT_UI1;
			m_value.parray = psa;
			m_parameterPtr->AppendChunk(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}

	}
	void	ADODataParameter::SetDateTime(DATE val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_DATE;
			V_DATE(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetDecimal(DECIMAL val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_DECIMAL;
			V_DECIMAL(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetDouble(DOUBLE val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_R8;
			V_R8(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetFloat(FLOAT val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_R4;
			V_R4(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetInt16(SHORT val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_I2;
			V_I2(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetInt32(INT val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_I4;
			V_I4(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetInt64(LONG val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_I8;
			V_I8(&m_value) = val;
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	void	ADODataParameter::SetString(LPCSTR val)
	{
		ASSERT(m_parameterPtr);
		try
		{
			V_VT(&m_value) = VT_BSTR;
			V_BSTR(&m_value) = _bstr_t(val);
			m_parameterPtr->PutValue(m_value);
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
	}
	BOOL	ADODataParameter::GetBoolean()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_BOOL);
		return val.boolVal;
	}
	BYTE	ADODataParameter::GetByte()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_UI1);
		return val.bVal;
	}
	CHAR	ADODataParameter::GetChar()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_I1);
		return val.cVal;
	}
	INT		ADODataParameter::GetBlob(BYTE* ps)
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == (VT_ARRAY | VT_UI1));
		INT size = val.parray->rgsabound[0].cElements;
		if (ps != NULL)
		{
			BYTE *buffer = NULL;
			SafeArrayAccessData(val.parray, (void **)&buffer);
			memcpy_s(ps, size, buffer, size);
			SafeArrayUnaccessData(val.parray);
		}
		return size;
	}
	DATE	ADODataParameter::GetDateTime()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_DATE);
		return val.date;
	}
	DECIMAL	ADODataParameter::GetDecimal()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_DECIMAL);
		return val.decVal;
	}
	DOUBLE	ADODataParameter::GetDouble()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_R8);
		return val.dblVal;
	}
	FLOAT	ADODataParameter::GetFloat()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_R4);
		return val.fltVal;
	}
	SHORT	ADODataParameter::GetInt16()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_I2);
		return val.iVal;
	}
	INT		ADODataParameter::GetInt32()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_I4);
		return val.lVal;
	}
	LONG	ADODataParameter::GetInt64()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_I8);
		return val.llVal;
	}
	LPCSTR	ADODataParameter::GetString()
	{
		_variant_t val = m_parameterPtr->GetValue();
		ASSERT(val.vt == VT_BSTR);
		return (LPCSTR)_com_util::ConvertBSTRToString(val.bstrVal);
	}
	//////////////////////////////////////////////////////////////////////////
	ADODataReader::ADODataReader()
	{
		m_recordsetPtr.CreateInstance(__uuidof(Recordset));
	}
	ADODataReader::~ADODataReader()
	{
		m_recordsetPtr.Release();
		TRACE("析构ADODataReader\n");
	}
	BOOL ADODataReader::ReadNext()
	{
		ASSERT(m_recordsetPtr);
		try
		{
			if (m_recordsetPtr->State &&
				SUCCEEDED(m_recordsetPtr->MoveNext()))
			{
				m_fields = m_recordsetPtr->GetFields();
				return !m_recordsetPtr->EndOfFile;
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}

		return FALSE;
	}
	BOOL ADODataReader::ReadPrevious()
	{
		ASSERT(m_recordsetPtr);
		try
		{
			if (m_recordsetPtr->State
				&& SUCCEEDED(m_recordsetPtr->MovePrevious()))
			{
				m_fields = m_recordsetPtr->GetFields();
				return !m_recordsetPtr->EndOfFile;
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL ADODataReader::ReadFirst()
	{
		ASSERT(m_recordsetPtr);
		try
		{
			if (m_recordsetPtr->State
				&& SUCCEEDED(m_recordsetPtr->MoveFirst()))
			{
				m_fields = m_recordsetPtr->GetFields();
				return !m_recordsetPtr->EndOfFile;
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL ADODataReader::ReadLast()
	{
		ASSERT(m_recordsetPtr);
		try
		{
			if (m_recordsetPtr->State
				&& SUCCEEDED(m_recordsetPtr->MoveLast()))
			{
				m_fields = m_recordsetPtr->GetFields();
				return !m_recordsetPtr->EndOfFile;
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	BOOL ADODataReader::Close()
	{
		ASSERT(m_recordsetPtr);
		try
		{
			if (m_recordsetPtr->State)
			{
				return SUCCEEDED(m_recordsetPtr->Close());
			}
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return FALSE;
	}
	INT ADODataReader::GetColumnCount()
	{
		ASSERT(m_recordsetPtr);
		ASSERT(m_fields);
		return m_fields->GetCount();
	}
	BOOL ADODataReader::GetBoolean(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_BOOL);
		return (BOOL)val.boolVal;
	}
	BYTE ADODataReader::GetByte(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_UI1);
		return (BOOL)val.bVal;
	}
	CHAR ADODataReader::GetChar(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_I1);
		return val.cVal;
	}
	INT ADODataReader::GetBlob(INT i, BYTE* ps)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		INT size = m_fields->GetItem(vtIndex)->ActualSize;
		if (ps != NULL)
		{
			_variant_t val = m_fields->GetItem(vtIndex)->GetChunk(size);
			ASSERT(val.vt == (VT_ARRAY | VT_UI1));
			BYTE *buffer = NULL;
			SafeArrayAccessData(val.parray, (void **)&buffer);
			memcpy_s(ps, size, buffer, size);
			SafeArrayUnaccessData(val.parray);
		}
		return size;
	}
	LPCSTR ADODataReader::GetDataTypeName(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		switch (m_fields->GetItem(vtIndex)->GetType())
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
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_DATE);
		return val.date;
	}
	DECIMAL ADODataReader::GetDecimal(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_DECIMAL);
		return val.decVal;
	}
	DOUBLE ADODataReader::GetDouble(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_R8);
		return val.dblVal;
	}
	FLOAT ADODataReader::GetFloat(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_R4);
		return val.fltVal;
	}
	SHORT ADODataReader::GetInt16(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_I2);
		return val.iVal;
	}
	INT ADODataReader::GetInt32(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_I4);
		return val.lVal;
	}
	LONG ADODataReader::GetInt64(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_I8);
		return val.lVal;
	}
	LPCSTR ADODataReader::GetName(INT i)
	{
		try
		{
			_variant_t vtIndex;
			vtIndex.vt = VT_I2;
			vtIndex.iVal = i;
			return _com_util::ConvertBSTRToString(m_fields->GetItem(vtIndex)->GetName());
		}
		catch (_com_error& e)
		{
			TRACE(e.Description());
			TRACE("\n");
		}
		return NULL;
	}
	INT ADODataReader::GetOrdinal(LPCSTR pzName)
	{
		INT count = m_fields->GetCount();
		for (INT i = 0; i < count; i++)
		{
			_variant_t vtIndex;
			vtIndex.vt = VT_I2;
			vtIndex.iVal = i;
			_bstr_t name = m_fields->GetItem(vtIndex)->GetName();
			if (name == _bstr_t(pzName))
			{
				return i;
			}
		}
		return -1;
	}
	LPCSTR ADODataReader::GetString(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		ASSERT(val.vt == VT_BSTR);
		return (LPCSTR)_com_util::ConvertBSTRToString(val.bstrVal);
	}
	BOOL ADODataReader::IsDBNull(INT i)
	{
		_variant_t vtIndex;
		vtIndex.vt = VT_I2;
		vtIndex.iVal = i;
		_variant_t val = m_fields->GetItem(vtIndex)->Value;
		return val.vt == VT_NULL;
	}
}