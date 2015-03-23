#include "../stdafx.h"
#include "TinyLogging.h"
#include "TinySingle.h"

namespace TinyUI
{
	SymbolContext::SymbolContext()
		:m_error(ERROR_SUCCESS)
	{
		SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);
		if (SymInitialize(GetCurrentProcess(), NULL, TRUE))
		{
			m_error = ERROR_SUCCESS;
		}
		else
		{
			m_error = GetLastError();
		}
	}
	SymbolContext* SymbolContext::GetInstance() throw()
	{
		TinyCriticalSection section;
		section.Initialize();
		if (m_pInstance == NULL)
		{
			section.Lock();
			if (m_pInstance == NULL)
			{
				m_pInstance = new SymbolContext();
			}
			section.Unlock();
		}
		section.Uninitialize();
		return m_pInstance;
	}
	void SymbolContext::OutputTraceToStream(const void* const* trace, INT count, std::ostream* os)
	{
		TinyCriticalSection section;
		section.Initialize();
		section.Lock();
		for (size_t i = 0; (i < static_cast<size_t>(count)) && os->good(); ++i)
		{
			const int kMaxNameLength = 256;
			DWORD_PTR frame = reinterpret_cast<DWORD_PTR>(trace[i]);
			//http://msdn.microsoft.com/en-us/library/ms680578(VS.85).aspx
			ULONG64 buffer[(sizeof(SYMBOL_INFO)+
				kMaxNameLength*sizeof(wchar_t)+sizeof(ULONG64)-1) / sizeof(ULONG64)];
			memset(buffer, 0, sizeof(buffer));
			DWORD64 sym_displacement = 0;
			PSYMBOL_INFO symbol = reinterpret_cast<PSYMBOL_INFO>(&buffer[0]);
			symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
			symbol->MaxNameLen = kMaxNameLength - 1;
			BOOL bSymbol = SymFromAddr(GetCurrentProcess(), frame, &sym_displacement, symbol);
			DWORD lineDisplacement = 0;
			IMAGEHLP_LINE64 line = { 0 };
			line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
			BOOL has_line = SymGetLineFromAddr64(GetCurrentProcess(), frame, &lineDisplacement, &line);
			(*os) << "\t";
			if (bSymbol)
			{
				(*os) << symbol->Name << " [0x" << trace[i] << "+"
					<< sym_displacement << "]";
			}
			else
			{
				// 没有符号信息.
				(*os) << "(No symbol) [0x" << trace[i] << "]";
			}
			if (has_line)
			{
				(*os) << " (" << line.FileName << ":" << line.LineNumber << ")";
			}
			(*os) << "\n";
		}
		section.Unlock();
		section.Uninitialize();
	}
	DWORD SymbolContext::GetError()
	{
		return m_error;
	}
	//////////////////////////////////////////////////////////////////////////
	StackTrace::StackTrace()
	{
		m_count = CaptureStackBackTrace(0, arraysize(m_trace), m_trace, NULL);
	}
	StackTrace::StackTrace(_EXCEPTION_POINTERS* pointers)
	{
		m_count = 0;
		STACKFRAME64 stackFrame;
		memset(&stackFrame, 0, sizeof(stackFrame));
#if defined(_WIN64)
		int machine_type = IMAGE_FILE_MACHINE_AMD64;
		stackFrame.AddrPC.Offset = pointers->ContextRecord->Rip;
		stackFrame.AddrFrame.Offset = pointers->ContextRecord->Rbp;
		stackFrame.AddrStack.Offset = pointers->ContextRecord->Rsp;
#else
		int machine_type = IMAGE_FILE_MACHINE_I386;
		stackFrame.AddrPC.Offset = pointers->ContextRecord->Eip;
		stackFrame.AddrFrame.Offset = pointers->ContextRecord->Ebp;
		stackFrame.AddrStack.Offset = pointers->ContextRecord->Esp;
#endif
		stackFrame.AddrPC.Mode = AddrModeFlat;
		stackFrame.AddrFrame.Mode = AddrModeFlat;
		stackFrame.AddrStack.Mode = AddrModeFlat;
		while (StackWalk64(machine_type,
			GetCurrentProcess(),
			GetCurrentThread(),
			&stackFrame,
			pointers->ContextRecord,
			NULL,
			&SymFunctionTableAccess64,
			&SymGetModuleBase64,
			NULL) && m_count < arraysize(m_trace))
		{
			m_trace[m_count++] = reinterpret_cast<void*>(stackFrame.AddrPC.Offset);
		}
	}
	StackTrace::StackTrace(const void* const* trace, size_t count)
	{
		m_count = min(count, arraysize(m_trace));
		if (count)
		{
			memcpy(m_trace, trace, count*sizeof(m_trace[0]));
		}
		m_count = static_cast<int>(count);
	}
	const void* const* StackTrace::Addresses(size_t* count)
	{
		*count = m_count;
		if (m_count)
		{
			return m_trace;
		}
		return NULL;
	}
	void StackTrace::Print()
	{
		OutputToStream(&std::cerr);
	}
	void StackTrace::OutputToStream(std::ostream* os)
	{
		SymbolContext* context = SymbolContext::GetInstance();
		if (context->GetError() != ERROR_SUCCESS)
		{
			(*os) << "Error initializing symbols (" << context->GetError()
				<< ").  Dumping unresolved backtrace:\n";
			for (int i = 0; (i < m_count) && os->good(); ++i)
			{
				(*os) << "\t" << m_trace[i] << "\n";
			}
		}
		else
		{
			(*os) << "Backtrace:\n";
			context->OutputTraceToStream(m_trace, m_count, os);
		}
	}
	//////////////////////////////////////////////////////////////////////////

}


