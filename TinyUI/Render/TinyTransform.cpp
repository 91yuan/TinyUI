#include "../stdafx.h"
#include "TinyTransform.h"

namespace TinyUI
{
	inline BOOL NearlyZero(FLOAT x, FLOAT tolerance)
	{
		return fabsf(x) < tolerance;
	}
	FLOAT SinCos(FLOAT radians, FLOAT* cosValue)
	{
		FLOAT sinValue = sinf(radians);
		if (cosValue)
		{
			*cosValue = cosf(radians);
			if (NearlyZero(*cosValue))
			{
				*cosValue = 0;
			}
		}
		if (NearlyZero(sinValue))
		{
			sinValue = 0;
		}
		return sinValue;
	}
	//////////////////////////////////////////////////////////////////////////
	TinyMatrix::TinyMatrix()
	{
		this->eDx = 0.0F;
		this->eDy = 0.0F;
		this->eM11 = 0.0F;
		this->eM12 = 0.0F;
		this->eM21 = 0.0F;
		this->eM22 = 0.0F;
	}
	TinyMatrix::TinyMatrix(FLOAT eM11, FLOAT eM12, FLOAT eM21, FLOAT eM22, FLOAT eDx, FLOAT eDy)
	{
		this->eDx = eDx;
		this->eDy = eDy;
		this->eM11 = eM11;
		this->eM12 = eM12;
		this->eM21 = eM21;
		this->eM22 = eM22;
	}
	TinyMatrix& TinyMatrix::SetTranslate(FLOAT dx, FLOAT dy)
	{
		eDx += dx*eM11 + dy*eM21;
		eDy += dy*eM22 + dx*eM12;
		return *this;
	}
	TinyMatrix& TinyMatrix::SetScale(FLOAT sx, FLOAT sy)
	{
		eM11 *= sx;
		eM12 *= sx;
		eM21 *= sy;
		eM22 *= sy;
		return *this;
	}
	TinyMatrix& TinyMatrix::SetShear(FLOAT sh, FLOAT sv)
	{
		FLOAT e11 = sv*eM21;
		FLOAT e12 = sv*eM22;
		FLOAT e21 = sh*eM11;
		FLOAT e22 = sh*eM12;
		eM11 += e11;
		eM12 += e12;
		eM21 += e21;
		eM22 += e22;
		return *this;
	}
	void TinyMatrix::Reset()
	{
		eM11 = eM22 = 1.0;
		eM12 = eM21 = eDx = eDy = 0.0;
	}
	TinyMatrix& TinyMatrix::SetRotate(FLOAT degrees)
	{
		FLOAT sina = 0;
		FLOAT cosa = 0;
		sina = SinCos(DegreesToRadians(degrees), &cosa);
		FLOAT e11 = cosa*eM11 + sina*eM21;
		FLOAT e12 = cosa*eM12 + sina*eM22;
		FLOAT e21 = -sina*eM11 + cosa*eM21;
		FLOAT e22 = -sina*eM12 + cosa*eM22;
		eM11 = e11;
		eM12 = e12;
		eM21 = e21;
		eM22 = e22;
		return *this;
	}
	BOOL TinyMatrix::operator == (const TinyMatrix &o) const
	{
		return eM11 == o.eM11 && eM12 == o.eM12 && eM21 == o.eM21 && eM22 == o.eM22 &&eDx == o.eDx &&eDy == o.eDy;
	}
	BOOL TinyMatrix::operator != (const TinyMatrix &o) const
	{
		return eM11 != o.eM11 || eM12 != o.eM12 || eM21 != o.eM21 || eM22 != o.eM22 || eDx != o.eDx || eDy != o.eDy;
	}
	TinyMatrix& TinyMatrix::operator *= (const TinyMatrix &o)
	{
		FLOAT e11 = eM11 * o.eM11 + eM12 * o.eM21;
		FLOAT e12 = eM11 * o.eM12 + eM12 * o.eM22;
		FLOAT e21 = eM21 * o.eM11 + eM22 * o.eM21;
		FLOAT e22 = eM21 * o.eM12 + eM22 * o.eM22;
		FLOAT tdx = eDx * o.eM11 + eDy * o.eM21 + o.eDx;
		FLOAT tdy = eDx * o.eM12 + eDy * o.eM22 + o.eDy;
		eM11 = e11;
		eM12 = e12;
		eM21 = e21;
		eM22 = e22;
		eDx = tdx;
		eDy = tdy;
		return *this;
	}
	TinyMatrix TinyMatrix::operator*(const TinyMatrix &o) const
	{
		FLOAT e11 = eM11*o.eM11 + eM12*o.eM21;
		FLOAT e12 = eM11*o.eM12 + eM12*o.eM22;
		FLOAT e21 = eM21*o.eM11 + eM22*o.eM21;
		FLOAT tm22 = eM21*o.eM12 + eM22*o.eM22;
		FLOAT tdx = eDx*o.eM11 + eDy*o.eM21 + o.eDx;
		FLOAT tdy = eDx*o.eM12 + eDy*o.eM22 + o.eDy;
		return TinyMatrix(e11, e12, e21, tm22, tdx, tdy);
	}
	TinyMatrix& TinyMatrix::operator = (const TinyMatrix &o)
	{
		eM11 = o.eM11;
		eM12 = o.eM12;
		eM21 = o.eM21;
		eM22 = o.eM22;
		eDx = o.eDx;
		eDy = o.eDy;
		return *this;
	}
};