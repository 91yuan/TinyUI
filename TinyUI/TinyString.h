#pragma once
#include "TinyObject.h"
#include <string>

namespace TinyUI
{
	
	class TinyString : public TinyObject
	{
		DECLARE_DYNAMIC(TinyString)
	public:
		TinyString();
		explicit TinyString(const CHAR* s);
		TinyString(const TinyString& s);
		~TinyString();
	public:
		TinyString& Assign(const CHAR* s, INT size);
	private:
		enum
		{
			_BUF_SIZE = 16,
			_ALLOC_MASK = 15
		};
	private:
		INT		_Mysize;
		INT		_Myres;
		CHAR*	_Mystr;
	};
	/*/// <summary>
	/// 字符串操作类
	/// </summary>
	class TinyString : public TinyObject
	{
		/// <summary>
		/// 定义个string柔性数组
		/// </summary>
		struct StringRep
		{
			INT		size;
			INT		capacity;
			CHAR	str[0];
		};
		DECLARE_DYNAMIC(TinyString)
	public:
		TinyString();
		explicit TinyString(const CHAR* s);
		TinyString(const TinyString& s);
		~TinyString();
	public:
		INT			GetSize() const;
		BOOL		IsEmpty() const;
		const CHAR&	Lookup(INT index) const;
		INT			Find(CHAR s) const;
		INT			Find(CHAR s, INT offset) const;
		INT			Find(const CHAR* s); 
		TinyString& Assign(const CHAR* s);
		TinyString& Assign(const CHAR* s, INT size);
		CHAR*		GetData() const;
		CHAR& operator[](INT index) const;
		operator CHAR*() const;
	private:
		void Initialize(INT size, INT capacity);
		void Initialize(INT size);
	private:
		StringRep* m_ps;
		static StringRep	NULLREP;
		const static INT	NPOS;
	};*/
}



