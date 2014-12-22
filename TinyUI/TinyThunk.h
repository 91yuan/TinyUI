#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	inline PVOID WINAPI __AllocThunk(VOID);
	inline VOID WINAPI __FreeThunk(PVOID ptr);
#pragma pack(push,1)
	struct _callthunk
	{
		DWORD   m_mov;
		DWORD   m_this;
		BYTE    m_jmp;
		DWORD   m_proc;
		BOOL Initialize(DWORD_PTR proc, void* pThis)
		{
			m_mov = 0x042444C7;  //C7 44 24 0C
			m_this = PtrToUlong(pThis);
			m_jmp = 0xe9;
			m_proc = DWORD((INT_PTR)proc - ((INT_PTR)this + sizeof(_callthunk)));
			FlushInstructionCache(GetCurrentProcess(), this, sizeof(_callthunk));
			return TRUE;
		}

		void* GetCodeAddress()
		{
			return this;
		}
		void* operator new(size_t)
		{
			return __AllocThunk();
		}
		void operator delete(void* pThunk)
		{
			__FreeThunk(pThunk);
		}
	};
#pragma pack(pop)
	inline PVOID WINAPI __AllocThunk(VOID)
	{
		LPVOID address = VirtualAlloc(0, sizeof(_callthunk), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!address) return NULL;
		return address;
	}
	inline VOID WINAPI __FreeThunk(PVOID ptr)
	{
		if (!ptr) return;
		VirtualFree(ptr, 0, MEM_RELEASE);
	}
#pragma pack(push,8)
	class TinyThunk
	{
	public:
		_callthunk *pThunk;
		TinyThunk();
		~TinyThunk();
		BOOL Initialize(DWORD_PTR proc, void *pThis);
		void* GetCodeAddress();
	};

#pragma pack(pop)
	class TinyLoopThunk
	{
	public:
		TinyThunk thunk;
		BOOL Initialize(WNDPROC proc, void* pThis);
		WNDPROC GetWNDPROC();
	};
}



