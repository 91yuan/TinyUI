#include "../stdafx.h"
#include "TinyLogging.h"
#include <algorithm>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <ostream>
#include <string>

namespace TinyUI
{
	SymbolContext::SymbolContext() : m_error(ERROR_SUCCESS)
	{
		SymSetOptions(SYMOPT_DEFERRED_LOADS |
			SYMOPT_UNDNAME |
			SYMOPT_LOAD_LINES);
		if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
		{
			m_error = GetLastError();
			assert(false);
			return;
		}
	}
	void SymbolContext::OutputTraceToStream(const void* const* trace, size_t count, std::ostream* os)
	{
		TinyAutoLock lock(m_lock);
		for (size_t i = 0; (i < count) && os->good(); ++i)
		{
			const int kMaxNameLength = 256;
			DWORD_PTR frame = reinterpret_cast<DWORD_PTR>(trace[i]);
			// http://msdn.microsoft.com/en-us/library/ms680578(VS.85).aspx
			ULONG64 buffer[
				(sizeof(SYMBOL_INFO)+
					kMaxNameLength * sizeof(wchar_t)+
					sizeof(ULONG64)-1) /
					sizeof(ULONG64)];
				memset(buffer, 0, sizeof(buffer));
				DWORD64 sym_displacement = 0;
				PSYMBOL_INFO symbol = reinterpret_cast<PSYMBOL_INFO>(&buffer[0]);
				symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
				symbol->MaxNameLen = kMaxNameLength - 1;
				BOOL has_symbol = SymFromAddr(GetCurrentProcess(), frame, &sym_displacement, symbol);
				DWORD line_displacement = 0;
				IMAGEHLP_LINE64 line = {};
				line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
				BOOL has_line = SymGetLineFromAddr64(GetCurrentProcess(), frame, &line_displacement, &line);
				(*os) << "\t";
				if (has_symbol)
				{
					(*os) << symbol->Name << " [0x" << trace[i] << "+"
						<< sym_displacement << "]";
				}
				else
				{
					(*os) << "(No symbol) [0x" << trace[i] << "]";
				}
				if (has_line)
				{
					(*os) << " (" << line.FileName << ":" << line.LineNumber << ")";
				}
				(*os) << "\n";
		}
	}
	DWORD SymbolContext::GetError() const
	{
		return m_error;
	}
	SymbolContext* SymbolContext::GetInstance()
	{
		if (NULL == m_pInstance)
		{
			TinyLock lock;
			lock.Acquire();
			m_pInstance = new SymbolContext();
			lock.Release();
		}
		return m_pInstance;
	}
	//////////////////////////////////////////////////////////////////////////
	StackTrace::StackTrace()
	{
		m_count = CaptureStackBackTrace(0, arraysize(m_trace), m_trace, NULL);
	}
	StackTrace::StackTrace(const void* const* trace, size_t count)
	{
		count = min(count, arraysize(m_trace));
		if (count)
		{
			memcpy(m_trace, trace, count * sizeof(m_trace[0]));
		}
		m_count = count;
	}
	StackTrace::~StackTrace()
	{
	}
	const void *const *StackTrace::Addresses(size_t* count) const
	{
		*count = m_count;
		if (m_count)
			return m_trace;
		return NULL;
	}
	std::string StackTrace::ToString() const
	{
		std::stringstream stream;
		OutputToStream(&stream);
		return stream.str();
	}
	StackTrace::StackTrace(const EXCEPTION_POINTERS* exception_pointers)
	{
		m_count = 0;
		CONTEXT context_record = *exception_pointers->ContextRecord;
		STACKFRAME64 stack_frame;
		memset(&stack_frame, 0, sizeof(stack_frame));
#if defined(_WIN64)
		int machine_type = IMAGE_FILE_MACHINE_AMD64;
		stack_frame.AddrPC.Offset = context_record.Rip;
		stack_frame.AddrFrame.Offset = context_record.Rbp;
		stack_frame.AddrStack.Offset = context_record.Rsp;
#else
		int machine_type = IMAGE_FILE_MACHINE_I386;
		stack_frame.AddrPC.Offset = context_record.Eip;
		stack_frame.AddrFrame.Offset = context_record.Ebp;
		stack_frame.AddrStack.Offset = context_record.Esp;
#endif
		stack_frame.AddrPC.Mode = AddrModeFlat;
		stack_frame.AddrFrame.Mode = AddrModeFlat;
		stack_frame.AddrStack.Mode = AddrModeFlat;
		while (StackWalk64(machine_type,
			GetCurrentProcess(),
			GetCurrentThread(),
			&stack_frame,
			&context_record,
			NULL,
			&SymFunctionTableAccess64,
			&SymGetModuleBase64,
			NULL) &&
			m_count < arraysize(m_trace))
		{
			m_trace[m_count++] = reinterpret_cast<void*>(stack_frame.AddrPC.Offset);
		}
		for (size_t i = m_count; i < arraysize(m_trace); ++i)
			m_trace[i] = NULL;
	}
	void StackTrace::Print() const
	{
		OutputToStream(&std::cerr);
	}
	void StackTrace::OutputToStream(std::ostream* os) const
	{
		SymbolContext* context = SymbolContext::GetInstance();
		DWORD error = context->GetError();
		if (error != ERROR_SUCCESS)
		{
			(*os) << "Error initializing symbols (" << error
				<< ").  Dumping unresolved backtrace:\n";
			for (size_t i = 0; (i < m_count) && os->good(); ++i)
			{
				(*os) << "\t" << m_trace[i] << "\n";
			}
		}
		else {
			(*os) << "Backtrace:\n";
			context->OutputTraceToStream(m_trace, m_count, os);
		}
	}
}


