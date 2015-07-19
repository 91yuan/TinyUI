#include "../stdafx.h"
#include "TinyCollection.h"


namespace TinyUI
{
	TinyPlex* PASCAL TinyPlex::Create(TinyPlex*& ps, UINT_PTR max, UINT_PTR size)
	{
		ASSERT(max > 0 && size > 0);
		TinyPlex* p = (TinyPlex*) new BYTE[sizeof(TinyPlex) + max * size];
		p->nextPtr = ps;
		ps = p;
		return p;
	}
	void TinyPlex::Destory()
	{
		TinyPlex* ps = this;
		while (ps != NULL)
		{
			BYTE* bytes = (BYTE*)ps;
			TinyPlex* nextPtr = ps->nextPtr;
			delete[] bytes;
			ps = nextPtr;
		}
	}
}
