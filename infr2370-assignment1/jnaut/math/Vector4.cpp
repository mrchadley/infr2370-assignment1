// Marc Tremblay
// 100555250
// 01/27/2017

#include "Vector4.h"

namespace jnaut
{
	namespace math
	{
		Vector4::Vector4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;

		}

		Vector4::Vector4(const float &a_x, const float &a_y, const float &a_z, const float &a_w)
		{
			x = a_x;
			y = a_y;
			z = a_z;
			w = a_w;
		}

		Vector4& Vector4::Add(const Vector4 &a_other)
		{
			x += a_other.x;
			y += a_other.y;
			z += a_other.z;
			w += a_other.w;

			return *this;
		}

		Vector4& Vector4::Subtract(const Vector4 &a_other)
		{
			x -= a_other.x;
			y -= a_other.y;
			z -= a_other.z;
			w -= a_other.w;

			return *this;
		}

		Vector4& Vector4::Multiply(const Vector4 &a_other)
		{
			x *= a_other.x;
			y *= a_other.y;
			z *= a_other.z;
			w *= a_other.w;

			return *this;
		}

		Vector4& Vector4::Divide(const Vector4 &a_other)
		{
			x /= a_other.x;
			y /= a_other.y;
			z /= a_other.z;
			w /= a_other.w;

			return *this;
		}

		Vector4 operator+(Vector4 left, const Vector4 &right)
		{
			return left.Add(right);
		}

		Vector4 operator-(Vector4 left, const Vector4 &right)
		{
			return left.Subtract(right);
		}

		Vector4 operator*(Vector4 left, const Vector4 &right)
		{
			return left.Multiply(right);
		}

		Vector4 operator/(Vector4 left, const Vector4 &right)
		{
			return left.Divide(right);
		}

		bool Vector4::operator==(const Vector4 &other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool Vector4::operator!=(const Vector4 &other)
		{
			return !(*this == other);
		}

		Vector4& Vector4::operator+=(const Vector4 &other)
		{
			return Add(other);
		}

		Vector4& Vector4::operator-=(const Vector4 &other)
		{
			return Subtract(other);
		}
		Vector4& Vector4::operator*=(const Vector4 &other)
		{
			return Multiply(other);
		}
		Vector4& Vector4::operator/=(const Vector4 &other)
		{
			return Divide(other);
		}

		std::ostream &operator<<(std::ostream &a_stream, const Vector4 &a_vector)
		{
			return a_stream << "Vector4(" << a_vector.x << ", " << a_vector.y << ", " << a_vector.z << ", " << a_vector.w << ")";
		}
	}
}