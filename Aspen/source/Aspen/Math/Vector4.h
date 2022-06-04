#pragma once

#include <imgui.h>

namespace Aspen
{
	template<typename Ty = float>
	struct Vector4
	{
		union { Ty x; Ty r; Ty h; };
		union { Ty y; Ty g; Ty s; };
		union { Ty z; Ty b; Ty v; };
		union { Ty w; Ty a; };
		
		Vector4()
			:x(static_cast<Ty>(0.0)), y(static_cast<Ty>(0.0)), z(static_cast<Ty>(0.0)), w(static_cast<Ty>(0.0))
		{
		}

		Vector4(Ty _x, Ty _y, Ty _z, Ty _w)
			:x(_x), y(_y), z(_z), w(_w)
		{
		}

		Vector4(const ImVec4& v)
			:x((Ty)v.x), y((Ty)v.y), z((Ty)v.z), w((Ty)v.w)
		{
		}

		~Vector4() {  }

		// Used floats for scalar
		// Because scalars like 0.5f might be rounded to 0

		Vector4<Ty> operator+(const Vector4<Ty>& v)
		{
			return Vector4<Ty>(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		Vector4<Ty> operator-(const Vector4<Ty>& v)
		{
			return Vector4<Ty>(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		Vector4<Ty> operator*(const Vector4<Ty>& v)
		{
			return Vector4<Ty>(x * v.x, y * v.y, z * v.z, w * v.w);
		}

		Vector4<Ty> operator*(float scalar)
		{
			return Vector4<Ty>(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		friend Vector4<Ty> operator*(float scalar, const Vector4<Ty>& v)
		{
			return v * scalar;
		}

		Vector4<Ty> operator/(const Vector4<Ty>& v)
		{
			return Vector4<Ty>(x / v.x, y / v.y, z / v.z, w / v.w);
		}

		Vector4<Ty> operator/(float scalar)
		{
			return Vector4<Ty>(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		friend Vector4<Ty> operator/(float scalar, const Vector4<Ty>& v)
		{
			return Vector4<Ty>(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
		}

		operator ImVec4() const
		{
			return ImVec4(static_cast<Ty>(x), static_cast<Ty>(y), static_cast<Ty>(z), static_cast<Ty>(w));
		}

		operator ImColor() const
		{
			return ImColor(x, y, z, w);
		}
	};

	template<typename Ty>
	using Color4 = Vector4<Ty>;

	using Vector4i = Vector4<int>;
	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;

	using Color4i = Vector4<int>;
	using Color4f = Vector4<float>;
	using Color4d = Vector4<double>;
}