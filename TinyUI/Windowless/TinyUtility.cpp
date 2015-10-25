#include "../stdafx.h"
#include "TinyUtility.h"

namespace TinyUI
{
	namespace Windowless
	{
		/*const char Width[] = "width";
		const char Height[] = "height";
		const char BackgroundColor[] = "background-color";
		const char PaddingLeft[] = "padding-left";
		const char PaddingTop[] = "padding-top";
		const char PaddingRight[] = "padding-right";
		const char PaddingBottom[] = "padding-bottom";
		const char MarginLeft[] = "margin-left";
		const char MarginTop[] = "margin-top";
		const char MarginRight[] = "margin-right";
		const char MarginBottom[] = "margin-bottom";
		const char TextAlign[] = "text-align";
		const char TextColor[] = "text-color";
		const char FontFamily[] = "font-family";
		const char FontSize[] = "font-size";
		const char FontColor[] = "font-color";
		const char FontStyle[] = "font-style";
		const char FontWeight[] = "font-weight";*/

		Vector2F::Vector2F()
			:x_(0.0),
			y_(0.0)
		{
		}
		Vector2F::Vector2F(FLOAT x, FLOAT y)
			: x_(x),
			y_(y)
		{
		}
		FLOAT Vector2F::X() const
		{
			return x_;
		}
		FLOAT Vector2F::Y() const
		{
			return y_;
		}
		void Vector2F::SetX(FLOAT x)
		{
			x_ = x;
		}
		void Vector2F::SetY(FLOAT y)
		{
			y_ = y;
		}
		BOOL Vector2F::IsZero() const
		{
			return x_ == 0 && y_ == 0;
		}
		void Vector2F::Add(const Vector2F& other)
		{
			x_ += other.x_;
			y_ += other.y_;
		}
		void Vector2F::Subtract(const Vector2F& other)
		{
			x_ -= other.x_;
			y_ -= other.y_;
		}
		void Vector2F::operator += (const Vector2F& other)
		{
			Add(other);
		}
		void Vector2F::operator -= (const Vector2F& other)
		{
			Subtract(other);
		}
		void Vector2F::SetMin(const Vector2F& other)
		{
			x_ = x_ <= other.x_ ? x_ : other.x_;
			y_ = y_ <= other.y_ ? y_ : other.y_;
		}
		void Vector2F::SetMax(const Vector2F& other)
		{
			x_ = x_ >= other.x_ ? x_ : other.x_;
			y_ = y_ >= other.y_ ? y_ : other.y_;
		}
		DOUBLE Vector2F::LengthSquared() const
		{
			return static_cast<double>(x_)* x_ + static_cast<double>(y_)* y_;
		}
		FLOAT Vector2F::Length() const
		{
			return static_cast<float>(std::sqrt(LengthSquared()));
		}
		void Vector2F::Scale(DOUBLE scale)
		{
			Scale(scale);
		}
		void Vector2F::Scale(DOUBLE x_scale, DOUBLE y_scale)
		{
			x_ *= x_scale;
			y_ *= y_scale;;
		}
		TinyString Vector2F::ToString() const
		{
			return TinyString::Format("[%f %f]", x_, y_);
		}
		//////////////////////////////////////////////////////////////////////////
		Vector3F::Vector3F()
			:x_(0),
			y_(0),
			z_(0)
		{

		}
		Vector3F::Vector3F(FLOAT x, FLOAT y, FLOAT z)
			:x_(x),
			y_(y),
			z_(z)
		{

		}
		Vector3F::Vector3F(const Vector2F& other)
			:x_(other.X()),
			y_(other.Y()),
			z_(0)
		{

		}
		FLOAT Vector3F::X() const
		{
			return x_;
		}
		void Vector3F::SetX(FLOAT x)
		{
			x_ = x;
		}
		FLOAT Vector3F::Y() const
		{
			return y_;
		}
		void Vector3F::SetY(FLOAT y)
		{
			y_ = y;
		}
		FLOAT Vector3F::Z() const
		{
			return z_;
		}
		void Vector3F::SetZ(FLOAT z)
		{
			z_ = z;
		}
		BOOL Vector3F::IsZero() const
		{
			return x_ == 0 && y_ == 0 && z_ == 0;
		}
		void Vector3F::Add(const Vector3F& other)
		{
			x_ += other.x_;
			y_ += other.y_;
			z_ += other.z_;
		}
		void Vector3F::Subtract(const Vector3F& other)
		{
			x_ -= other.x_;
			y_ -= other.y_;
			z_ -= other.z_;
		}
		void Vector3F::operator += (const Vector3F& other)
		{
			Add(other);
		}
		void Vector3F::operator -= (const Vector3F& other)
		{
			Subtract(other);
		}
		void Vector3F::SetMin(const Vector3F& other)
		{
			x_ = x_ <= other.x_ ? x_ : other.x_;
			y_ = y_ <= other.y_ ? y_ : other.y_;
			z_ = z_ <= other.z_ ? z_ : other.z_;
		}
		void Vector3F::SetMax(const Vector3F& other)
		{
			x_ = x_ >= other.x_ ? x_ : other.x_;
			y_ = y_ >= other.y_ ? y_ : other.y_;
			z_ = z_ >= other.z_ ? z_ : other.z_;
		}
		DOUBLE Vector3F::LengthSquared() const
		{
			return static_cast<double>(x_)* x_ + static_cast<double>(y_)* y_ + static_cast<double>(z_)* z_;
		}
		FLOAT Vector3F::Length() const
		{
			return static_cast<float>(std::sqrt(LengthSquared()));
		}
		void Vector3F::Scale(FLOAT scale)
		{
			Scale(scale, scale, scale);
		}
		void Vector3F::Scale(FLOAT x_scale, FLOAT y_scale, FLOAT z_scale)
		{
			x_ *= x_scale;
			y_ *= y_scale;
			z_ *= z_scale;
		}
		void Vector3F::Cross(const Vector3F& other)
		{
			FLOAT x = y_ * other.Z() - z_ * other.Y();
			FLOAT y = z_ * other.X() - x_ * other.Z();
			FLOAT z = x_ * other.Y() - y_ * other.X();
			x_ = x;
			y_ = y;
			z_ = z;
		}
		TinyString Vector3F::ToString() const
		{
			return TinyString::Format("[%f %f %f]", x_, y_, z_);
		}
	}
}
