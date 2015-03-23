#pragma once
#include "TinyCommon.h"
#include <dbghelp.h>
#include <sstream>
#include <iostream>

namespace TinyUI
{
	/// <summary>
	/// Symbol文件
	/// </summary>
	class SymbolContext
	{
		DISALLOW_COPY_AND_ASSIGN(SymbolContext);
	public:
		static SymbolContext* GetInstance() throw();
		SymbolContext();
		DWORD	GetError();
		void	OutputTraceToStream(const void* const* trace, INT count, std::ostream* os);
	private:
		DWORD m_error;
		static SymbolContext* m_pInstance;
	};
	__declspec(selectany) SymbolContext* SymbolContext::m_pInstance = NULL;
	/// <summary>
	/// 堆栈跟踪
	/// </summary>
	class StackTrace
	{
	public:
		StackTrace();
		StackTrace(_EXCEPTION_POINTERS* pointers);
		StackTrace(const void* const* trace, size_t count);
		~StackTrace();
		const void* const* Addresses(size_t* count);
		void Print();
	private:
		void OutputToStream(std::ostream* os);
		static const INT MAX_TRACES = 62;
		void*	m_trace[MAX_TRACES];
		INT		m_count;
	};
	/// <summary>
	/// 日志类
	/// </summary>
	class TinyLogging
	{

	};
}



