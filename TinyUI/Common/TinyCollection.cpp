#include "../stdafx.h"
#include "TinyCollection.h"


namespace TinyUI
{
	TinyPlex* PASCAL TinyPlex::Create(TinyPlex*& ps, UINT_PTR nMax, UINT_PTR nElementSize)
	{
		ASSERT(nMax > 0 && nElementSize > 0);
		TinyPlex* pPlex = (TinyPlex*)malloc(sizeof(TinyPlex) + nMax * nElementSize);
		if (pPlex == NULL) return NULL;
		pPlex->pNext = ps;
		ps = pPlex;
		return pPlex;
	}
	void TinyPlex::Destory()
	{
		TinyPlex* pPlex = NULL;
		pPlex = this;
		while (pPlex != NULL)
		{
			TinyPlex* pNext = NULL;
			pNext = pPlex->pNext;
			free(pPlex);
			pPlex = pNext;
		}
	}
}
