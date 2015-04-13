#include "../stdafx.h"
#include <stdarg.h>
#include "TinyString.h"

namespace TinyUI
{
	inline INT strcasecmp(const char* s1, const char* s2)
	{
		return _stricmp(s1, s2);
	}
	inline INT strncasecmp(const char* s1, const char* s2, size_t count)
	{
		return _strnicmp(s1, s2, count);
	}
	inline INT strncmp16(const wchar_t* s1, const wchar_t* s2, size_t count)
	{
		return ::wcsncmp(s1, s2, count);
	}
	inline INT vsnprintf(char* buffer, size_t size, const char* format, va_list arguments)
	{
		INT length = vsnprintf_s(buffer, size, size - 1, format, arguments);
		if (length < 0)
		{
			return _vscprintf(format, arguments);
		}
		return length;
	}
	inline INT vswprintf(wchar_t* buffer, size_t size, const wchar_t* format, va_list arguments)
	{
		int length = _vsnwprintf_s(buffer, size, size - 1, format, arguments);
		if (length < 0)
		{
			return _vscwprintf(format, arguments);
		}
		return length;
	}
	std::string WStringToString(const std::wstring str, const DWORD dwType)
	{
		int nMultiByteLenght = WideCharToMultiByte(dwType, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
		char* pMultiByteBuffer = new char[nMultiByteLenght];
		nMultiByteLenght = WideCharToMultiByte(dwType, 0, str.c_str(), -1, pMultiByteBuffer, nMultiByteLenght, NULL, NULL);
		std::string sRet = pMultiByteBuffer;
		delete[] pMultiByteBuffer;
		return sRet;
	}
	std::wstring StringToWString(const std::string str, const DWORD dwType)
	{
		int nWideCharLenght = MultiByteToWideChar(dwType, 0, str.c_str(), -1, NULL, 0);
		wchar_t* pWideCharBuffer = new wchar_t[nWideCharLenght];
		nWideCharLenght = MultiByteToWideChar(dwType, 0, str.c_str(), -1, pWideCharBuffer, nWideCharLenght);
		std::wstring sRet = pWideCharBuffer;
		delete[] pWideCharBuffer;
		return sRet;
	}
	std::string ASCIIToUTF8(const std::string str)
	{
		std::wstring temp = StringToWString(str, CP_ACP);
		return WStringToString(temp, CP_UTF8);
	}
	std::string UTF8ToASCII(const std::string str)
	{
		std::wstring temp = StringToWString(str, CP_UTF8);
		return WStringToString(temp, CP_ACP);
	}
	std::wstring UTF8ToUTF16(const std::string& s)
	{
		return StringToWString(UTF8ToASCII(s));
	}
	std::string UTF16ToUTF8(const std::wstring& wide)
	{
		std::string temp = WStringToString(wide);
		return ASCIIToUTF8(temp);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyString::TinyString()
		:_Myres(0),
		_Mysize(0),
		_Mystr(NULL)
	{
		//TRACE("调用构造函数TinyString()\n");
	}
	TinyString::TinyString(size_t size)
		:_Myres(size),
		_Mysize(size),
		_Mystr(NULL)
	{

		_Mystr = new CHAR[_Mysize];
		//TRACE("调用构造函数TinyString(INT size)\n");
	}
	TinyString::TinyString(const CHAR* s)
		: _Myres(0),
		_Mysize(0),
		_Mystr(NULL)
	{
		//TRACE("调用构造函数TinyString(const CHAR* s)\n");
		ASSERT(s);
		Assign(s, strlen(s));
	}
	TinyString::TinyString(const TinyString& s)
		:_Myres(0),
		_Mysize(0),
		_Mystr(NULL)
	{
		//TRACE("调用拷贝构造函数TinyString(const TinyString& s)\n");
		size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
		Assign(s, 0, _Maxsize);
	}
	TinyString::TinyString(const TinyString& s, size_t pos, size_t size)
		:_Myres(0),
		_Mysize(0),
		_Mystr(NULL)
	{
		//TRACE("调用拷贝构造函数TinyString(const TinyString& s, size_t pos, size_t size)\n");
		Assign(s, pos, size);
	}
	TinyString::~TinyString()
	{
		SAFE_DELETE_ARRAY(this->_Mystr);
		this->_Myres = this->_Mysize = 0;
	}
	TinyString& TinyString::Append(const CHAR* s)
	{
		ASSERT(s);
		return Append(s, strlen(s));
	}
	TinyString& TinyString::Append(const CHAR* s, size_t _Newsize)
	{
		ASSERT(s);
		if (_Newsize > 0)
		{
			size_t Newsize = this->_Mysize + _Newsize;
			//容量不足扩充
			if (this->_Myres < Newsize)
			{
				size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
				size_t _Newres = Newsize | this->_ALLOC_MASK;
				size_t _size = (_Myres * 3) / 2;//扩充一半
				if (_Maxsize < _Newres)
					_Newres = Newsize;
				else if (_Newres < _size && _size <= _Maxsize)
					_Newres = _size;
				ASSERT(_Newres >= _Newsize);
				CHAR *_Ptr = NULL;
				_Ptr = new CHAR[_Newres + 1];
				if (0 < this->_Mysize)//拷贝存在的
				{
					memcpy(_Ptr, this->_Mystr, this->_Mysize);
				}
				this->_Myres = _Newres;
				memcpy(_Ptr + this->_Mysize, s, _Newsize);//附加内存
				this->_Mysize = Newsize;
				_Ptr[this->_Mysize] = '\0';
				SAFE_DELETE_ARRAY(this->_Mystr);
				this->_Mystr = _Ptr;
			}
			else//拷贝内存
			{
				memcpy(this->_Mystr + this->_Mysize, s, _Newsize);
				this->_Mysize = Newsize;
				this->_Mystr[this->_Mysize] = '\0';
			}
		}
		return *this;
	}
	TinyString& TinyString::Append(const TinyString& str, size_t pos, size_t size)
	{
		size_t _Num = str.GetSize() - pos;
		if (_Num < size)
			size = _Num;
		if (0 < size)
		{
			size_t Newsize = this->_Mysize + size;
			//容量不足扩充
			if (this->_Myres < Newsize)
			{
				size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
				size_t _Newres = Newsize | this->_ALLOC_MASK;
				size_t _size = (_Myres * 3) / 2;//扩充一半
				if (_Maxsize < _Newres)
					_Newres = Newsize;
				else if (_Newres < _size && _size <= _Maxsize)
					_Newres = _size;
				ASSERT(_Newres >= size);
				CHAR *_Ptr = NULL;
				_Ptr = new CHAR[_Newres + 1];
				if (0 < this->_Mysize)//拷贝存在的
				{
					memcpy(_Ptr, this->_Mystr, this->_Mysize);
				}
				this->_Myres = _Newres;
				memcpy(_Ptr + this->_Mysize, str.STR() + pos, size);//附加内存
				this->_Mysize = Newsize;
				_Ptr[this->_Mysize] = '\0';
				SAFE_DELETE_ARRAY(this->_Mystr);
				this->_Mystr = _Ptr;
			}
			else//拷贝内存
			{
				memcpy(this->_Mystr + this->_Mysize, str.STR() + pos, size);
				this->_Mysize = Newsize;
				this->_Mystr[this->_Mysize] = '\0';
			}
		}
		return (*this);
	}
	TinyString& TinyString::operator += (const TinyString& str)
	{
		return Append(str, 0, str.GetSize());
	}
	TinyString& TinyString::operator += (const CHAR* s)
	{
		return Append(s);
	}
	TinyString& TinyString::operator += (CHAR s)
	{
		return Append(&s);
	}
	TinyString& TinyString::operator = (const TinyString& str)
	{
		TRACE("调用赋值构造函数TinyString::operator = (const TinyString& str)\n");
		return Assign(str, 0, str.GetSize());
	}
	TinyString& TinyString::operator = (const CHAR* s)
	{
		TRACE("调用赋值构造函数TinyString::operator = (const CHAR* s)\n");
		return Assign(s);
	}
	TinyString& TinyString::operator = (CHAR s)
	{
		TRACE("调用赋值构造函数TinyString::operator = (CHAR s)\n");
		return Assign(&s);
	}
	TinyString& TinyString::Assign(const CHAR* s)
	{
		ASSERT(s);
		return Assign(s, strlen(s));
	}
	TinyString& TinyString::Assign(const CHAR* s, size_t _Newsize)
	{
		//容量不足扩充
		if (this->_Myres < _Newsize)
		{
			size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
			size_t _Newres = _Newsize | this->_ALLOC_MASK;
			size_t _size = (_Myres * 3) / 2;//扩充一半
			if (_Maxsize < _Newres)
				_Newres = _Newsize;
			else if (_Newres < _size && _size <= _Maxsize)
				_Newres = _size;
			ASSERT(_Newres >= _Newsize);
			CHAR *_Ptr = NULL;
			_Ptr = new CHAR[_Newres + 1];
			memcpy(_Ptr, s, _Newsize);
			this->_Myres = _Newres;
			this->_Mysize = _Newsize;
			_Ptr[this->_Mysize] = '\0';
			SAFE_DELETE_ARRAY(this->_Mystr);
			this->_Mystr = _Ptr;
		}
		else//拷贝内存
		{
			memcpy(this->_Mystr, s, _Newsize);
			this->_Mysize = _Newsize;
			this->_Mystr[this->_Mysize] = '\0';
		}
		return *this;
	}
	TinyString& TinyString::Assign(const TinyString& str, size_t pos, size_t size)
	{
		ASSERT(str.GetSize() > pos);
		size_t _Num = str.GetSize() - pos;
		if (size < _Num)
			_Num = size;
		if (this == &str)//substring
		{
			Erase(pos + _Num);
			Erase(0, pos);
		}
		else
		{
			//容量不足扩充
			if (this->_Myres < _Num)
			{
				size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
				size_t _Newres = _Num | this->_ALLOC_MASK;
				size_t _size = (_Myres * 3) / 2;//扩充一半
				if (_Maxsize < _Newres)
					_Newres = _Num;
				else if (_Newres < _size && _size <= _Maxsize)
					_Newres = _size;
				ASSERT(_Newres >= _Num);
				CHAR *_Ptr = NULL;
				_Ptr = new CHAR[_Newres + 1];
				if (0 < this->_Mysize)//拷贝存在的
				{
					memcpy(_Ptr, this->_Mystr, this->_Mysize);
				}
				this->_Myres = _Newres;
				memcpy(_Ptr, str.STR() + pos, _Num);//附加内存
				this->_Mysize = _Num;
				_Ptr[this->_Mysize] = '\0';
				SAFE_DELETE_ARRAY(this->_Mystr);
				this->_Mystr = _Ptr;
			}
			else//拷贝内存
			{
				memcpy(this->_Mystr, str.STR() + pos, _Num);//附加内存
				this->_Mysize = _Num;
				this->_Mystr[this->_Mysize] = '\0';
			}
		}
		return *this;
	}
	TinyString& TinyString::Erase(size_t pos)
	{
		ASSERT(this->_Mysize >= pos);
		this->_Mysize = pos;
		this->_Mystr[this->_Mysize] = '\0';
		return (*this);
	}
	TinyString& TinyString::Erase(size_t pos, size_t size)
	{
		ASSERT(this->_Mysize >= pos);
		if (this->_Mysize - pos <= size)
		{
			this->_Mysize = pos;
			this->_Mystr[this->_Mysize] = '\0';
		}
		else if (0 < size)
		{
			CHAR* _Ptr = this->_Mystr + pos;
			size_t _Newsize = this->_Mysize - size;
			memmove(_Ptr, _Ptr + size, _Newsize - pos);
			this->_Mysize = _Newsize;
			this->_Mystr[this->_Mysize] = '\0';
		}
		return (*this);
	}
	TinyString& TinyString::Insert(size_t pos, const CHAR* s)
	{
		ASSERT(s);
		return Insert(pos, s, strlen(s));
	}
	TinyString& TinyString::Insert(size_t pos, const CHAR* s, size_t size)
	{
		ASSERT(this->_Mysize >= pos);
		if (0 < size)
		{
			size_t _Num = this->_Mysize + size;
			//容量不足扩充
			if (this->_Myres < _Num)
			{
				size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
				size_t _Newres = _Num | this->_ALLOC_MASK;
				size_t _size = (_Myres * 3) / 2;//扩充一半
				if (_Maxsize < _Newres)
					_Newres = _Num;
				else if (_Newres < _size && _size <= _Maxsize)
					_Newres = _size;
				ASSERT(_Newres >= size);
				CHAR *_Ptr = NULL;
				_Ptr = new CHAR[_Newres + 1];
				if (0 < this->_Mysize)//拷贝存在的
				{
					memcpy(_Ptr, this->_Mystr, this->_Mysize);
				}
				this->_Myres = _Newres;
				memmove(_Ptr + pos + size, _Ptr + pos, this->_Mysize - pos);
				memcpy(_Ptr + pos, s, size);
				this->_Mysize = _Num;
				_Ptr[this->_Mysize] = '\0';
				SAFE_DELETE_ARRAY(this->_Mystr);
				this->_Mystr = _Ptr;
			}
			else//拷贝内存
			{
				memmove(this->_Mystr + pos + size, this->_Mystr + pos, this->_Mysize - pos);
				memcpy(this->_Mystr + pos, s, size);
				this->_Mysize = _Num;
				this->_Mystr[this->_Mysize] = '\0';
			}
		}
		return (*this);
	}
	TinyString& TinyString::Insert(size_t pos, const TinyString& str)
	{
		return Insert(pos, str, 0, str.GetSize());
	}
	TinyString& TinyString::Insert(size_t pos, const TinyString& str, size_t subpos, size_t subsize)
	{
		ASSERT(this->_Mysize >= pos && str.GetSize() >= subpos);
		size_t _Num = str.GetSize() - subpos;
		if (_Num < subsize)
			subsize = _Num;
		if (0 < subsize)
		{
			_Num = this->_Mysize + subsize;

			//容量不足扩充
			if (this->_Myres < _Num)
			{
				size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
				size_t _Newres = _Num | this->_ALLOC_MASK;
				size_t _size = (_Myres * 3) / 2;//扩充一半
				if (_Maxsize < _Newres)
					_Newres = _Num;
				else if (_Newres < _size && _size <= _Maxsize)
					_Newres = _size;
				ASSERT(_Newres >= subsize);
				CHAR *_Ptr = NULL;
				_Ptr = new CHAR[_Newres + 1];
				if (0 < this->_Mysize)//拷贝存在的
				{
					memcpy(_Ptr, this->_Mystr, this->_Mysize);
				}
				this->_Myres = _Newres;
				memmove(_Ptr + pos + subsize, _Ptr + pos, this->_Mysize - pos);
				if (this == &str)
				{
					memmove(_Ptr + pos, _Ptr + (pos < subpos ? subpos + subsize : subpos), subsize);
				}
				else
				{
					memcpy(_Ptr + pos, str.STR() + subpos, subsize);
				}

				this->_Mysize = _Num;
				_Ptr[this->_Mysize] = '\0';
				SAFE_DELETE_ARRAY(this->_Mystr);
				this->_Mystr = _Ptr;
			}
			else//拷贝内存
			{
				memmove(this->_Mystr + pos + subsize,
					this->_Mystr + pos,
					this->_Mysize - pos);
				if (this == &str)
				{
					memmove(this->_Mystr + pos,
						this->_Mystr + (pos < subpos ? subpos + subsize : subpos),
						subsize);
				}
				else
				{
					memcpy(this->_Mystr + pos, str.STR() + subpos, subsize);
				}
				this->_Mysize = _Num;
				this->_Mystr[this->_Mysize] = '\0';
			}
		}
		return (*this);
	}
	size_t	TinyString::GetSize() const
	{
		return _Mysize;
	}
	CHAR* TinyString::STR() const
	{
		return _Mystr;
	}
	TinyString _cdecl TinyString::Format(const CHAR* s, ...)
	{
		va_list args;
		va_start(args, s);
		INT size;
		CHAR szBuffer[512];
		size = _vsntprintf_s(szBuffer, 512, s, args);
		ASSERT(size >= 0);
		va_end(args);
		return TinyString(szBuffer, 0, size);//一个构造函数代价
	}
	INT	TinyString::Find(const CHAR* s, size_t pos) const
	{
		return Find(s, pos, strlen(s));
	}
	INT	TinyString::Find(const TinyString& str, size_t pos) const
	{
		return Find(str.STR(), pos, str.GetSize());
	}
	INT	TinyString::Find(const CHAR* s, size_t pos, size_t size) const
	{
		ASSERT(s);
		if (size == 0 && pos <= this->_Mysize)
			return pos;
		size_t _Nm = 0;
		if (pos < this->_Mysize && size <= (_Nm = this->_Mysize - pos))
		{
			const CHAR *_Uptr, *_Vptr;
			for (_Nm -= size - 1, _Vptr = this->_Mystr + pos;
				(_Uptr = (CHAR*)memchr(_Vptr, *s, _Nm)) != 0;
				_Nm -= _Uptr - _Vptr + 1, _Vptr = _Uptr + 1)
			{
				if (memcmp(_Uptr, s, size) == 0)
				{
					return (_Uptr - this->_Mystr);
				}
			}
		}
		return -1;
	}
	INT	TinyString::Find(CHAR s, size_t pos) const
	{
		return Find(&s, 0, 1);
	}
	BOOL TinyString::Compare(const TinyString& str) const throw()
	{
		return Compare(0, str.GetSize(), str.STR());
	}
	BOOL TinyString::Compare(size_t pos, size_t size, const TinyString& str) const throw()
	{
		return Compare(pos, size, str.STR());
	}
	BOOL TinyString::Compare(const CHAR* s) const  throw()
	{
		ASSERT(s);
		return Compare(0, strlen(s), s);
	}
	BOOL TinyString::Compare(size_t pos, size_t size, const CHAR* s) const  throw()
	{
		return Compare(pos, size, s, strlen(s));
	}
	BOOL TinyString::Compare(size_t pos, size_t size, const CHAR* s, size_t subsize) const  throw()
	{
		ASSERT(s);
		if (this->_Mysize - pos < size)
			size = this->_Mysize - pos;
		return memcmp(this->_Mystr + pos, s, size < subsize ? size : subsize) == 0 ? TRUE : FALSE;
	}
	size_t	TinyString::Copy(CHAR* s, size_t pos, size_t size) const
	{
		ASSERT(s);
		ASSERT(this->_Mysize >= pos);
		if (this->_Mysize - pos < size)
			size = this->_Mysize - pos;
		memcpy(s, this->_Mystr + pos, size);
		return size;
	}
	const CHAR& TinyString::GetAt(size_t pos) const
	{
		ASSERT(this->_Mysize >= pos);
		return this->_Mystr[pos];
	}
	const CHAR& TinyString::operator[](size_t pos)const
	{
		ASSERT(this->_Mysize >= pos);
		return this->_Mystr[pos];
	}
	CHAR& TinyString::operator[](size_t pos)
	{
		ASSERT(this->_Mysize >= pos);
		return this->_Mystr[pos];
	}
	TinyString&	TinyString::Replace(size_t pos, size_t size, const CHAR* s, size_t subsize)
	{
		ASSERT(this->_Mysize >= pos);
		if (this->_Mysize - pos < size)
			size = this->_Mysize - pos;
		size_t _Nm = this->_Mysize - size - pos;
		if (subsize < size)
		{
			memmove(this->_Mystr + pos + subsize,
				this->_Mystr + pos + size,
				_Nm);
		}
		if (0 < subsize || 0 < size)
		{
			size_t Newsize = this->_Mysize + subsize - size;
			if (Newsize < size)
				size = Newsize;
			if (0 < size)
			{
				//容量不足扩充
				if (this->_Myres < Newsize)
				{
					size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
					size_t _Newres = Newsize | this->_ALLOC_MASK;
					size_t _size = (_Myres * 3) / 2;//扩充一半
					if (_Maxsize < _Newres)
						_Newres = Newsize;
					else if (_Newres < _size && _size <= _Maxsize)
						_Newres = _size;
					ASSERT(_Newres >= size);
					CHAR *_Ptr = NULL;
					_Ptr = new CHAR[_Newres + 1];
					if (0 < this->_Mysize)//拷贝存在的
					{
						memcpy(_Ptr, this->_Mystr, this->_Mysize);
					}
					this->_Myres = _Newres;
					if (size < subsize)
					{
						memmove(_Ptr + pos + subsize, _Ptr + pos + size, _Nm);
					}
					memcpy(_Ptr + pos, s, subsize);
					this->_Mysize = Newsize;
					_Ptr[this->_Mysize] = '\0';
					SAFE_DELETE_ARRAY(this->_Mystr);
					this->_Mystr = _Ptr;
				}
				else//拷贝内存
				{
					if (size < subsize)
					{
						memmove(this->_Mystr + pos + subsize, this->_Mystr + pos + size, _Nm);
					}
					memcpy(this->_Mystr + pos, s, subsize);
					this->_Mysize = Newsize;
					this->_Mystr[this->_Mysize] = '\0';
				}
			}
		}
		return (*this);
	}
	TinyString&	TinyString::Replace(size_t pos, size_t size, const CHAR* s)
	{
		ASSERT(s);
		return Replace(pos, size, s, strlen(s));
	}
	TinyString&	TinyString::Replace(size_t pos, size_t size, const TinyString& str)
	{
		return Replace(pos, size, str, 0, str.GetSize());
	}
	TinyString& TinyString::Replace(size_t pos, size_t size, const TinyString& str, size_t subpos, size_t subsize)
	{
		ASSERT(this->_Mysize >= pos || str.GetSize() > subpos);
		if (this->_Mysize - pos < size)
			size = this->_Mysize - pos;
		size_t _Num = str.GetSize() - subpos;
		if (_Num < subsize)
			subsize = _Num;
		size_t _Nm = this->_Mysize - size - pos;
		size_t _Newsize = this->_Mysize + subsize - size;
		if (this->_Mysize < _Newsize)
		{
			//容量不足扩充
			if (this->_Myres < _Newsize)
			{
				size_t _Maxsize = (size_t)((size_t)-1 / sizeof(CHAR));
				size_t _Newres = _Newsize | this->_ALLOC_MASK;
				size_t _size = (_Myres * 3) / 2;//扩充一半
				if (_Maxsize < _Newres)
					_Newres = _Newsize;
				else if (_Newres < _size && _size <= _Maxsize)
					_Newres = _size;
				ASSERT(_Newres >= _Newsize);
				CHAR *_Ptr = NULL;
				_Ptr = new CHAR[_Newres + 1];
				if (0 < this->_Mysize)//拷贝存在的
				{
					memcpy(_Ptr, this->_Mystr, this->_Mysize);
				}
				this->_Myres = _Newres;
				SAFE_DELETE_ARRAY(this->_Mystr);
				this->_Mystr = _Ptr;
			}
		}
		if (this != &str)
		{
			memmove(this->_Mystr + pos + subsize, this->_Mystr + pos + size, _Nm);
			memcpy(this->_Mystr + pos, str.STR() + subpos, subsize);
		}
		else if (subsize <= size)
		{
			memmove(this->_Mystr + pos, this->_Mystr + subpos, subsize);
			memmove(this->_Mystr + pos + subsize, this->_Mystr + pos + size, _Nm);
		}
		else if (subpos <= pos)
		{
			memmove(this->_Mystr + pos + subsize, this->_Mystr + pos + size, _Nm);
			memmove(this->_Mystr + pos, this->_Mystr + subpos, subsize);
		}
		else if (pos + size <= subpos)
		{
			memmove(this->_Mystr + pos + subsize, this->_Mystr + pos + size, _Nm);
			memmove(this->_Mystr + pos, this->_Mystr + (subpos + subsize - size), subsize);
		}
		else
		{
			memmove(this->_Mystr + pos, this->_Mystr + subpos, size);
			memmove(this->_Mystr + pos + subsize, this->_Mystr + pos + size, _Nm);
			memmove(this->_Mystr + pos + size, this->_Mystr + subpos + subsize, subsize - size);
		}
		this->_Mysize = _Newsize;
		this->_Mystr[this->_Mysize] = '\0';
		return (*this);
	}
	TinyString	TinyString::Substring(size_t pos, size_t size) const
	{
		return TinyString(*this, pos, size);
	}
	BOOL TinyString::IsEmpty() const throw()
	{
		return (this->_Mysize == 0);
	}
	INT __cdecl TinyString::A2W(CHAR* mbstr, const WCHAR* wcstr, size_t count)
	{
		if (count == 0 && mbstr != NULL)
			return 0;
		INT result = ::WideCharToMultiByte(CP_ACP, 0, wcstr, -1, mbstr, (INT)count, NULL, NULL);
		ASSERT(mbstr == NULL || result <= (INT)count);
		if (result > 0)
		{
			mbstr[result - 1] = 0;
		}
		return result;
	}
	INT __cdecl TinyString::W2A(WCHAR* wcstr, const CHAR* mbstr, size_t count)
	{
		if (count == 0 && wcstr != NULL)
			return 0;
		INT result = ::MultiByteToWideChar(CP_ACP, 0, mbstr, -1, wcstr, (INT)count);
		ASSERT(wcstr == NULL || result <= (INT)count);
		if (result > 0)
		{
			wcstr[result - 1] = 0;
		}
		return result;
	}
	//////////////////////////////////////////////////////////////////////////
}

