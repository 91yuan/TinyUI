#include "../stdafx.h"
#include "TinyCollection.h"
#include <exception>

namespace TinyUI
{
	TinyPlex* PASCAL TinyPlex::Create(TinyPlex*& ps, UINT_PTR nMax, UINT_PTR nElementSize)
	{
		ASSERT(nMax > 0 && nElementSize > 0);
		TinyPlex* p = (TinyPlex*)new BYTE[sizeof(TinyPlex) + nMax * nElementSize];
		if (p == NULL) return NULL;
		p->pNext = ps;
		ps = p;
		return p;
	}
	void TinyPlex::Destory()
	{
		TinyPlex* p = this;
		while (p != NULL)
		{
			BYTE* bytes = (BYTE*)p;
			TinyPlex* pNext = p->pNext;
			delete[] bytes;
			p = pNext;
		}
	}
}
