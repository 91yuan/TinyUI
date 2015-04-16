#include "stdafx.h"
#include "Algorithm.h"

/// <summary>
/// ’€∞Î≤È’“
/// </summary>
INT A1(INT _array[], INT size, INT key)
{
	INT min = 0;
	INT max = size;
	while (min <= max)
	{
		INT mid = (min + max) / 2;
		INT val = _array[mid];
		if (val == key)
		{
			return mid;
		}
		if (val > key)
		{
			max = mid - 1;
		}
		else
		{
			min = mid + 1;
		}
	}
};
/// <summary>
/// √∞≈›≈≈–Ú
/// </summary>
void A2(INT _array[], INT size)
{
	for (INT i = 0; i < size; i++)
	{
		for (INT j = i; j < size; j++)
		{
			if (_array[i] > _array[j])
			{
				INT temp = _array[i];
				_array[i] = _array[j];
				_array[j] = temp;
			}
		}
	}
};
/// <summary>
/// øÏÀŸ≈≈–Ú
/// </summary>
void A3(INT _array[], INT size)
{

}