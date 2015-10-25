#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		/*static const char Width[];
		static const char Height[];
		static const char BackgroundColor[];
		static const char PaddingLeft[];
		static const char PaddingTop[];
		static const char PaddingRight[];
		static const char PaddingBottom[];
		static const char MarginLeft[];
		static const char MarginTop[];
		static const char MarginRight[];
		static const char MarginBottom[];
		static const char TextAlign[];
		static const char TextColor[];
		static const char FontFamily[];
		static const char FontSize[];
		static const char FontColor[];
		static const char FontStyle[];
		static const char FontWeight[];*/

		class Vector2F
		{
		public:
			Vector2F();
			Vector2F(FLOAT x, FLOAT y);
			FLOAT X() const;
			void SetX(FLOAT x);
			FLOAT Y() const;
			void SetY(FLOAT y);
			BOOL IsZero() const;
			void Add(const Vector2F& other);
			void Subtract(const Vector2F& other);
			void operator+=(const Vector2F& other);
			void operator-=(const Vector2F& other);
			void SetMin(const Vector2F& other);
			void SetMax(const Vector2F& other);
			DOUBLE LengthSquared() const;
			FLOAT Length() const;
			void Scale(DOUBLE scale);
			void Scale(DOUBLE x_scale, DOUBLE y_scale);
			TinyString ToString() const;
		private:
			FLOAT x_;
			FLOAT y_;
		};
		class Vector3F
		{
		public:
			Vector3F();
			Vector3F(FLOAT x, FLOAT y, FLOAT z);
			explicit Vector3F(const Vector2F& other);
			FLOAT X() const;
			void SetX(FLOAT x);
			FLOAT Y() const;
			void SetY(FLOAT y);
			FLOAT Z() const;
			void SetZ(FLOAT z);
			BOOL IsZero() const;
			void Add(const Vector3F& other);
			void Subtract(const Vector3F& other);
			void operator+=(const Vector3F& other);
			void operator-=(const Vector3F& other);
			void SetMin(const Vector3F& other);
			void SetMax(const Vector3F& other);
			DOUBLE LengthSquared() const;
			FLOAT Length() const;
			void Scale(FLOAT scale);
			void Scale(FLOAT x_scale, FLOAT y_scale, FLOAT z_scale);
			void Cross(const Vector3F& other);
			TinyString ToString() const;
		private:
			FLOAT x_;
			FLOAT y_;
			FLOAT z_;
		};
	}
}



