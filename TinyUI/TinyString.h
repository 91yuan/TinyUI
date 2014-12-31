#pragma once
#include "TinyObject.h"
#include <string>

namespace TinyUI
{
	/// <summary>
	/// ×Ö·û´®²Ù×÷Àà
	/// </summary>
	class TinyString : public TinyObject
	{
		DECLARE_DYNAMIC(TinyString)
	public:
		TinyString();
		explicit TinyString(const CHAR* s);
		TinyString(const TinyString& s);
		~TinyString();
	public:
		TinyString& Assign(const CHAR* s);
		TinyString& Assign(const CHAR* s, size_t size);
		TinyString& Assign(const TinyString& str, size_t pos, size_t size);
		TinyString&	Append(const CHAR* s);
		TinyString&	Append(const CHAR* s, size_t size);
		TinyString& Append(const TinyString& str, size_t pos, size_t size);
		TinyString& Erase(size_t pos);
		TinyString& Erase(size_t pos, size_t size);
		TinyString& Insert(size_t pos, const CHAR* s, size_t size);
		size_t		GetSize() const;
		CHAR*		STR() const;
	private:
		enum
		{
			_ALLOC_MASK = 15
		};
	private:
		CHAR*	_Mystr;
		size_t	_Mysize;
		size_t	_Myres;
	};
}



