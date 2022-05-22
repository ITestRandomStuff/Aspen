#pragma once

namespace Aspen
{
	template<typename Ty = float>
	class Vector2
	{
	public:
		Ty x, y;

		Vector2(Ty p_x = 0, Ty p_y = 0)
			:x(p_x), y(p_y)
		{
		}

		virtual ~Vector2() {  };

		Vector2 operator+=(const Vector2& v)
		{
			x += v.x;	y += v.y;
			return *this;
		}

		Vector2 operator-=(const Vector2& v)
		{
			x -= v.x;	y -= v.y;
			return *this;
		}
		
		Vector2& operator*=(const Vector2& v)
		{
			x *= v.x;	y *= v.y;
			return *this;
		}

		Vector2& operator*=(const Ty& scalar)
		{
			x *= scalar;	y *= scalar;
			return *this;
		}
		
		Vector2& operator/=(const Vector2& v)
		{
			x /= v.x;	y /= v.y;
			return *this;
		}
		
		Vector2& operator/=(const Ty& scalar)
		{
			x /= scalar;	y /= scalar;
			return *this;
		}

		Vector2 operator+(const Vector2& v) const
		{
			Vector2 ret = *this;
			ret += v;

			return ret;
		}

		Vector2 operator-(const Vector2& v) const
		{
			Vector2 ret = *this;
			ret -= v;

			return ret;
		}

		Vector2 operator*(const Vector2& v) const
		{
			Vector2 ret = *this;
			ret *= v;

			return ret;
		}

		Vector2 operator*(const Ty& scalar) const
		{
			Vector2 ret = *this;
			ret *= scalar;

			return ret;
		}

		friend Vector2 operator*(const Ty& scalar, const Vector2& v)
		{
			return v * scalar;
		}
		
		Vector2 operator/(const Vector2& v) const
		{
			Vector2 ret = *this;
			ret /= v;

			return ret;
		}

		Vector2 operator/(const Ty& scalar) const
		{
			Vector2 ret = *this;
			ret /= scalar;

			return ret;
		}

		friend Vector2 operator/(const Ty& scalar, const Vector2& v)
		{
			return Vector2(scalar / v.x, scalar / v.y);
		}
	};

	using Vector2i = Vector2<int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}