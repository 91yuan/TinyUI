#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
#define PI             3.14159265F
#define DegreesToRadians(degrees) ((degrees) * (PI / 180))
#define FLOAT_NearlyZero         (1.0F / (1 << 12))

	inline BOOL NearlyZero(FLOAT x, FLOAT tolerance = FLOAT_NearlyZero);
	FLOAT SinCos(FLOAT radians, FLOAT* cosValue);
	/// <summary>
	/// æÿ’Û¿‡
	/// <summary>
	class TinyMatrix : public XFORM
	{
	public:
		TinyMatrix();
		TinyMatrix(FLOAT eM11, FLOAT eM12, FLOAT eM21, FLOAT eM22, FLOAT eDx, FLOAT eDy);
	public:
		TinyMatrix& SetTranslate(FLOAT dx, FLOAT dy);
		TinyMatrix& SetScale(FLOAT sx, FLOAT sy);
		TinyMatrix& SetShear(FLOAT sh, FLOAT sv);
		TinyMatrix& SetRotate(FLOAT degrees);
		void Reset();
		BOOL operator==(const TinyMatrix &) const;
		BOOL operator!=(const TinyMatrix &) const;
		TinyMatrix &operator*=(const TinyMatrix &);
		TinyMatrix operator*(const TinyMatrix &) const;
		TinyMatrix &operator=(const TinyMatrix &);
	};
	/// <summary>
	/// æÿ’Û±‰ªª
	/// </summary>
};


