#include "../stdafx.h"
#include "TinyThunk.h"

namespace TinyUI
{
	TinyThunk::TinyThunk()
	{
		pThunk = NULL;
	}
	TinyThunk::~TinyThunk()
	{
		if (pThunk)
		{
			delete pThunk;
		}
	}
	BOOL TinyThunk::Initialize(DWORD_PTR proc, void *pThis)
	{
		if (pThunk == NULL)
		{
			pThunk = new _callthunk;
			if (pThunk == NULL)
			{
				return FALSE;
			}
		}
		return pThunk->Initialize(proc, pThis);
	}
	void* TinyThunk::GetCodeAddress()
	{
		return pThunk->GetCodeAddress();
	}
	////////////////////////////////////////////////////////////////////////////
	BOOL TinyLoopThunk::Initialize(WNDPROC proc, void* pThis)
	{
		return thunk.Initialize((DWORD_PTR)proc, pThis);
	}
	WNDPROC TinyLoopThunk::GetWNDPROC()
	{
		return (WNDPROC)thunk.GetCodeAddress();
	}
}


