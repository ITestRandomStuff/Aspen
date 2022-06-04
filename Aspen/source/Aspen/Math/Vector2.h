#pragma once

#include <imgui.h>

namespace Aspen
{
	template<typename Ty = float>
	struct Vector2
	{
		Ty x, y;

		Vector2()
			:x(static_cast<Ty>(0.0)), y(static_cast<Ty>(0.0))
		{
		}

		Vector2(Ty _x, Ty _y)
			:x(_x), y(_y)
		{
		}

		Vector2(const ImVec2& v)
			:x((Ty)v.x), y((Ty)v.y)
		{
		}

		~Vector2() {  }

		// Used floats for scalar
		// Because scalars like 0.5f might be rounded to 0

		Vector2<Ty> operator+(const Vector2<Ty>& v)
		{
			return Vector2<Ty>(x + v.x, y + v.y);
		}

		Vector2<Ty> operator-(const Vector2<Ty>& v)
		{
			return Vector2<Ty>(x - v.x, y - v.y);
		}

		Vector2<Ty> operator*(const Vector2<Ty>& v)
		{
			return Vector2<Ty>(x * v.x, y * v.y);
		}

		Vector2<Ty> operator*(float scalar)
		{
			return Vector2<Ty>(x * scalar, y * scalar);
		}

		friend Vector2<Ty> operator*(float scalar, const Vector2<Ty>& v)
		{
			return v * scalar;
		}

		Vector2<Ty> operator/(const Vector2<Ty>& v)
		{
			return Vector2<Ty>(x / v.x, y / v.y);
		}

		Vector2<Ty> operator/(float scalar)
		{
			return Vector2<Ty>(x / scalar, y / scalar);
		}

		friend Vector2<Ty> operator/(float scalar, const Vector2<Ty>& v)
		{
			return Vector2<Ty>(scalar / v.x, scalar / v.y);
		}

		operator ImVec2() const
		{
			return ImVec2(static_cast<Ty>(x), static_cast<Ty>(y));
		}
	};

	using Vector2i = Vector2<int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}