#include "stdafx.h"
#include "TinyString.h"

namespace TinyUI
{
	TinyString::TinyString()
		:_Myres(0),
		_Mysize(0),
		_Mystr(NULL)
	{
	}
	TinyString::TinyString(const CHAR* s)
	{
		ASSERT(s);
		Assign(s, strlen(s));
	}
	TinyString::TinyString(const TinyString& s)
	{
		size_t _Maxsize = (size_t)((size_t)-1 / sizeof (CHAR));
		Assign(s, 0, _Maxsize);
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
		size_t Newsize = this->_Mysize + _Newsize;
		//»›¡ø≤ª◊„¿©≥‰
		if (this->_Myres < Newsize)
		{
			size_t _Maxsize = (size_t)((size_t)-1 / sizeof (CHAR));
			size_t _Newres = Newsize | this->_ALLOC_MASK;
			size_t _size = (_Myres * 3) / 2;//¿©≥‰“ª∞Î
			if (_Maxsize < _Newres)
				_Newres = Newsize;
			else if (_Newres < _size && _size <= _Maxsize)
				_Newres = _size;
			ASSERT(_Newres >= _Newsize);
			CHAR *_Ptr = NULL;
			_Ptr = new CHAR[_Newres + 1];
			if (0 < this->_Mysize)//øΩ±¥¥Ê‘⁄µƒ
			{
				memcpy(_Ptr, this->_Mystr, this->_Mysize);
			}
			this->_Myres = _Newres;
			memcpy(_Ptr + this->_Mysize, s, _Newsize);//∏Ωº”ƒ⁄¥Ê
			this->_Mysize = Newsize;
			_Ptr[this->_Mysize] = '\0';
			SAFE_DELETE_ARRAY(this->_Mystr);
			this->_Mystr = _Ptr;
		}
		else//øΩ±¥ƒ⁄¥Ê
		{
			memcpy(this->_Mystr + this->_Mysize, s, _Newsize);
			this->_Mysize = Newsize;
			this->_Mystr[this->_Mysize] = '\0';
		}
		return *this;
	}
	TinyString& TinyString::Append(const TinyString& str, size_t pos, size_t size)
	{
		size_t _Num = str.GetSize() - pos;
		if (_Num < size)
			size = _Num;
		size_t Newsize = this->_Mysize + size;
		//»›¡ø≤ª◊„¿©≥‰
		if (this->_Myres < Newsize)
		{
			size_t _Maxsize = (size_t)((size_t)-1 / sizeof (CHAR));
			size_t _Newres = Newsize | this->_ALLOC_MASK;
			size_t _size = (_Myres * 3) / 2;//¿©≥‰“ª∞Î
			if (_Maxsize < _Newres)
				_Newres = Newsize;
			else if (_Newres < _size && _size <= _Maxsize)
				_Newres = _size;
			ASSERT(_Newres >= size);
			CHAR *_Ptr = NULL;
			_Ptr = new CHAR[_Newres + 1];
			if (0 < this->_Mysize)//øΩ±¥¥Ê‘⁄µƒ
			{
				memcpy(_Ptr, this->_Mystr, this->_Mysize);
			}
			this->_Myres = _Newres;
			memcpy(_Ptr + this->_Mysize, str.STR() + pos, size);//∏Ωº”ƒ⁄¥Ê
			this->_Mysize = Newsize;
			_Ptr[this->_Mysize] = '\0';
			SAFE_DELETE_ARRAY(this->_Mystr);
			this->_Mystr = _Ptr;
		}
		else//øΩ±¥ƒ⁄¥Ê
		{
			memcpy(this->_Mystr + this->_Mysize, str.STR() + pos, size);
			this->_Mysize = Newsize;
			this->_Mystr[this->_Mysize] = '\0';
		}
		return (*this);
	}
	TinyString& TinyString::Assign(const CHAR* s)
	{
		ASSERT(s);
		return Assign(s, strlen(s));
	}
	TinyString& TinyString::Assign(const CHAR* s, size_t _Newsize)
	{
		//»›¡ø≤ª◊„¿©≥‰
		if (this->_Myres < _Newsize)
		{
			size_t _Maxsize = (size_t)((size_t)-1 / sizeof (CHAR));
			size_t _Newres = _Newsize | this->_ALLOC_MASK;
			size_t _size = (_Myres * 3) / 2;//¿©≥‰“ª∞Î
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
		else//øΩ±¥ƒ⁄¥Ê
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
			//»›¡ø≤ª◊„¿©≥‰
			if (this->_Myres < _Num)
			{
				size_t _Maxsize = (size_t)((size_t)-1 / sizeof (CHAR));
				size_t _Newres = _Num | this->_ALLOC_MASK;
				size_t _size = (_Myres * 3) / 2;//¿©≥‰“ª∞Î
				if (_Maxsize < _Newres)
					_Newres = _Num;
				else if (_Newres < _size && _size <= _Maxsize)
					_Newres = _size;
				ASSERT(_Newres >= _Num);
				CHAR *_Ptr = NULL;
				_Ptr = new CHAR[_Newres + 1];
				if (0 < this->_Mysize)//øΩ±¥¥Ê‘⁄µƒ
				{
					memcpy(_Ptr, this->_Mystr, this->_Mysize);
				}
				this->_Myres = _Newres;
				memcpy(_Ptr, str.STR() + pos, _Num);//∏Ωº”ƒ⁄¥Ê
				this->_Mysize = _Num;
				_Ptr[this->_Mysize] = '\0';
				SAFE_DELETE_ARRAY(this->_Mystr);
				this->_Mystr = _Ptr;
			}
			else//øΩ±¥ƒ⁄¥Ê
			{
				memcpy(this->_Mystr, str.STR() + pos, _Num);//∏Ωº”ƒ⁄¥Ê
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
	TinyString& TinyString::Insert(size_t pos, const CHAR* s, size_t size)
	{
		return *this;
	}
	size_t	TinyString::GetSize() const
	{
		return _Mysize;
	}
	CHAR* TinyString::STR() const
	{
		return _Mystr;
	}
}

