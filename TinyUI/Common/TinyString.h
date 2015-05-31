#pragma once
#include "TinyObject.h"
#include <string>
#include <vector>

namespace TinyUI
{
	/// <summary>
	/// �Դ�Сд�޹صķ�ʽ�Ƚ������ַ���s1��s2 ���==0
	/// </summary>
	inline INT strcasecmp(const char* s1, const char* s2);
	/// <summary>
	/// �Դ�Сд�޹صķ�ʽ�Ƚ������ַ���s1��s2ǰcount���ַ� ���==0
	/// </summary>
	inline INT strncasecmp(const char* s1, const char* s2, size_t count);
	/// <summary>
	/// Unicode�ַ����Ƚ�
	/// </summary>
	inline INT strncmp16(const wchar_t* s1, const wchar_t* s2, size_t count);
	/// <summary>
	/// ��װvsnprintf��֤�ַ���ʼ����null��β�������ַ�����, ��ʹ�����ض�ʱҲһ��.
	/// </summary>
	INT vsnprintf(char* buffer, size_t size, const char* format, va_list arguments);
	/// <summary>
	/// ��װvswnprintf��֤�ַ���ʼ����null��β�������ַ�����, ��ʹ�����ض�ʱҲһ��.
	/// </summary>
	INT vswprintf(wchar_t* buffer, size_t size, const wchar_t* format, va_list arguments);
	/// <summary>
	/// ���ֽ��ַ��������ֽ��ַ���
	/// </summary>
	std::string WStringToString(const std::wstring str, const DWORD dwType = CP_ACP);
	/// <summary>
	/// ���ֽ��ַ����򵽿��ֽ��ַ���
	/// </summary>
	std::wstring StringToWString(const std::string str, const DWORD dwType = CP_ACP);
	/// <summary>
	/// ASCIIתUTF8
	/// </summary>
	std::string ASCIIToUTF8(const std::string str);
	/// <summary>
	/// UTF8תASCII
	/// </summary>
	std::string UTF8ToASCII(const std::string str);
	/// <summary>
	/// UTF8תUTF16
	/// </summary>
	std::wstring UTF8ToUTF16(const std::string& s);
	/// <summary>
	/// UTF16תUTF8
	/// </summary>
	std::string UTF16ToUTF8(const std::wstring& wide);
	/// <summary>
	/// תСдCHAR
	/// </summary>
	template<class Char>
	inline CHAR ToLowerASCII(CHAR c)
	{
		return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
	}
	/// <summary>
	/// �ַ���������
	/// </summary>
	class TinyString : public TinyObject
	{
		DECLARE_DYNAMIC(TinyString)
	public:
		TinyString();
		explicit TinyString(size_t size);
		TinyString(const CHAR* s);
		TinyString(const TinyString& s);
		TinyString(const TinyString& s, size_t pos, size_t size);
		~TinyString();
	public:
		TinyString& Assign(const CHAR* s);
		TinyString& Assign(const CHAR* s, size_t size);
		TinyString& Assign(const TinyString& str, size_t pos, size_t size);
		TinyString&	Append(const CHAR* s);
		TinyString&	Append(const CHAR* s, size_t size);
		TinyString& Append(const TinyString& str, size_t pos, size_t size);
		TinyString& operator+= (const TinyString& str);
		TinyString& operator+= (const CHAR* s);
		TinyString& operator+= (CHAR s);
		TinyString& operator= (const TinyString& str);
		TinyString& operator= (const CHAR* s);
		TinyString& operator= (CHAR s);
		TinyString& Erase(size_t pos);
		TinyString& Erase(size_t pos, size_t size);
		TinyString& Insert(size_t pos, const CHAR* s);
		TinyString& Insert(size_t pos, const CHAR* s, size_t subsize);
		TinyString& Insert(size_t pos, const TinyString& str);
		TinyString& Insert(size_t pos, const TinyString& str, size_t subpos, size_t subsize);
		INT			Find(const CHAR* s, size_t pos = 0) const;
		INT			Find(const TinyString& str, size_t pos = 0) const;
		INT			Find(const CHAR* s, size_t pos, size_t size) const;
		INT			Find(CHAR s, size_t pos = 0) const;
		BOOL		Compare(const TinyString& str) const throw();
		BOOL		Compare(size_t pos, size_t size, const TinyString& str) const throw();
		BOOL		Compare(const CHAR* s) const  throw();
		BOOL		Compare(size_t pos, size_t size, const CHAR* s) const  throw();
		BOOL		Compare(size_t pos, size_t size, const CHAR* s, size_t count) const  throw();
		size_t		Copy(CHAR* s, size_t pos, size_t size) const;
		TinyString&	Replace(size_t pos, size_t size, const TinyString& str);
		TinyString& Replace(size_t pos, size_t size, const TinyString& str, size_t subpos, size_t subsize);
		TinyString&	Replace(size_t pos, size_t size, const CHAR* s);
		TinyString&	Replace(size_t pos, size_t size, const CHAR* s, size_t subsize);
		TinyString	Substring(size_t pos, size_t size) const;//RVO�Ż�
		const CHAR& GetAt(size_t pos) const;
		BOOL		IsEmpty() const throw();
		const CHAR& operator[](size_t pos)const;
		CHAR&		operator[] (size_t pos);
		size_t		GetSize() const;
		CHAR*		STR() const;
		static TinyString _cdecl Format(const CHAR* s, ...);
		static INT __cdecl A2W(CHAR* mbstr, const WCHAR* wcstr, size_t count);
		static INT __cdecl W2A(WCHAR* wcstr, const CHAR* mbstr, size_t count);
	private:
		enum
		{
			_ALLOC_MASK = 15
		};
	protected:
		CHAR*	_Mystr;
		size_t	_Mysize;
		size_t	_Myres;
	};
	//////////////////////////////////////////////////////////////////////////
	enum TrimPositions
	{
		TRIM_NONE = 0,
		TRIM_LEADING = 1 << 0,
		TRIM_TRAILING = 1 << 1,
		TRIM_ALL = TRIM_LEADING | TRIM_TRAILING,
	};
	const char kWhitespaceASCII[] =
	{
		0x09,
		0x0A,
		0x0B,
		0x0C,
		0x0D,
		0x20,
		0
	};
	template<typename STR>
	TrimPositions TrimStringT(const STR& input, const typename STR::value_type trim_chars[], TrimPositions positions, STR* output);
	BOOL TrimString(const std::string& input, const char trim_chars[], std::string* output);
	TrimPositions TrimWhitespaceASCII(const std::string& input, TrimPositions positions, std::string* output);
	TrimPositions TrimWhitespace(const std::string& input, TrimPositions positions, std::string* output);
	template<typename STR>
	static void SplitStringT(const STR& str, const typename STR::value_type s, bool trim_whitespace, std::vector<STR>* r);
	void SplitString(const std::string& str, char sep, std::vector<std::string>* r);
}



