#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGDI.h"

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
	/*/// <summary>
	/// 3Dæÿ’Û±‰ªª
	/// </summary>
	class TinyMatrix44
	{
	public:
		FLOAT transX() const { return fMat[3][0]; }
		FLOAT transY() const { return fMat[3][1]; }
		FLOAT transZ() const { return fMat[3][2]; }
		FLOAT scaleX() const { return fMat[0][0]; }
		FLOAT scaleY() const { return fMat[1][1]; }
		FLOAT scaleZ() const { return fMat[2][2]; }
		FLOAT perspX() const { return fMat[0][3]; }
		FLOAT perspY() const { return fMat[1][3]; }
		FLOAT perspZ() const { return fMat[2][3]; }
		void set3x3(FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m20, FLOAT m21, FLOAT m22);
		void setTranslate(FLOAT dx, FLOAT dy, FLOAT dz);
		void preTranslate(FLOAT dx, FLOAT dy, FLOAT dz);
		void postTranslate(FLOAT dx, FLOAT dy, FLOAT dz);
		void setScale(FLOAT sx, FLOAT sy, FLOAT sz);
		void preScale(FLOAT sx, FLOAT sy, FLOAT sz);
		void postScale(FLOAT sx, FLOAT sy, FLOAT sz);
		inline void setScale(FLOAT scale) {
			this->setScale(scale, scale, scale);
		}
		inline void preScale(FLOAT scale) {
			this->preScale(scale, scale, scale);
		}
		inline void postScale(FLOAT scale) {
			this->postScale(scale, scale, scale);
		}
		void setRotateDegreesAbout(FLOAT x, FLOAT y, FLOAT z,FLOAT degrees) {
			this->setRotateAbout(x, y, z, degrees * PI / 180);
		}
		void setRotateAbout(FLOAT x, FLOAT y, FLOAT z,FLOAT radians);
		void setRotateAboutUnit(FLOAT x, FLOAT y, FLOAT z, FLOAT radians);
		void setConcat(const TinyMatrix44& a, const TinyMatrix44& b);
		inline void preConcat(const TinyMatrix44& m) {
			this->setConcat(*this, m);
		}
		inline void postConcat(const TinyMatrix44& m) {
			this->setConcat(m, *this);
		}	
		TinyMatrix44(const TinyMatrix44& src) {
			memcpy(fMat, src.fMat, sizeof(fMat));
			fTypeMask = src.fTypeMask;
		}
		TinyMatrix44(const TinyMatrix44& a, const TinyMatrix44& b) {
			this->setConcat(a, b);
		}
		TinyMatrix44& operator=(const TinyMatrix44& src) {
			if (&src != this) {
				memcpy(fMat, src.fMat, sizeof(fMat));
				fTypeMask = src.fTypeMask;
			}
			return *this;
		}
		bool operator==(const TinyMatrix44& other) const;
		bool operator!=(const TinyMatrix44& other) const {
			return !(other == *this);
		}
	private:
		FLOAT  fMat[4][4];
		mutable unsigned    fTypeMask;
	};*/
};


