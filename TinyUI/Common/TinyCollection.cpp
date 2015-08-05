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
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyPrime::IsPrime(INT candidate)
	{
		if ((candidate & 1) != 0)
		{
			INT limit = (INT)sqrt((DOUBLE)candidate);
			for (INT divisor = 3; divisor <= limit; divisor += 2)
			{
				if ((candidate % divisor) == 0)
					return FALSE;
			}
			return TRUE;
		}
		return (candidate == 2);
	}
	INT TinyPrime::GetPrime(INT min)
	{
		INT size = ARRAYSIZE(primes);
		for (INT i = 0; i < size; i++)
		{
			INT prime = primes[i];
			if (prime >= min)
			{
				return prime;
			}
		}
		for (INT i = (min | 1); i < MaxValue; i += 2)
		{
			if (IsPrime(i) && ((i - 1) % HashPrime != 0))
			{
				return i;
			}
		}
		return min;
	}
	INT TinyPrime::GetMinPrime()
	{
		return primes[0];
	}
	INT TinyPrime::ExpandPrime(INT oldSize)
	{
		INT newSize = 2 * oldSize;
		if ((UINT)newSize > MaxPrimeArrayLength && MaxPrimeArrayLength > oldSize)
		{
			return MaxPrimeArrayLength;
		}

		return GetPrime(newSize);
	}
}
