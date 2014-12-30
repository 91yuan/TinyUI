#include "stdafx.h"
#include "TinyString.h"

namespace TinyUI
{
	TinyString::TinyString()
		:_Myres(_BUF_SIZE - 1), 
		_Mysize(0), 
		_Mystr(NULL)
	{

	}
	TinyString::TinyString(const CHAR* s)
	{

	}
	TinyString& TinyString::Assign(const CHAR* s, INT size)
	{
		/*if (this->_Myres < size)
		{
		INT _Maxsize = (INT)(-1 / sizeof (CHAR));
		INT _Newres = size | this->_ALLOC_MASK;
		if (this->_Myres / 2 <= _Newres / 3);
		else if (this->_Myres <= _Maxsize - this->_Myres / 2)
		{
		_Newres = this->_Myres + this->_Myres / 2;
		}
		else
		{
		_Newres = _Maxsize;
		}

		}*/
		return *this;
	}
}

