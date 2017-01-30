// Marc Tremblay
// 100555250
// 01/27/2017

#include "Vector3.h"

namespace jnaut
{
	namespace math
	{
		Vector3::Vector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Vector3::Vector3(const float &a_x, const float &a_y, const float &a_z)
		{
			x = a_x;
			y = a_y;
			z = a_z;
		}

		Vector3& Vector3::Add(const Vector3 &a_other)
		{
			x += a_other.x;
			y += a_other.y;
			z += a_other.z;

			return *this;
		}

		Vector3& Vector3::Subtract(const Vector3 &a_other)
		{
			x -= a_other.x;
			y -= a_other.y;
			z -= a_other.z;

			return *this;
		}

		Vector3& Vector3::Multiply(const Vector3 &a_other)
		{
			x *= a_other.x;
			y *= a_other.y;
			z *= a_other.z;

			return *this;
		}

		Vector3& Vector3::Divide(const Vector3 &a_other)
		{
			x /= a_other.x;
			y /= a_other.y;
			z /= a_other.z;

			return *this;
		}

		Vector3 operator+(Vector3 left, const Vector3 &right)
		{
			return left.Add(right);
		}

		Vector3 operator-(Vector3 left, const Vector3 &right)
		{
			return left.Subtract(right);
		}

		Vector3 operator*(Vector3 left, const Vector3 &right)
		{
			return left.Multiply(right);
		}

		Vector3 operator/(Vector3 left, const Vector3 &right)
		{
			return left.Divide(right);
		}

		bool Vector3::operator==(const Vector3 &other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool Vector3::operator!=(const Vector3 &other)
		{
			return !(*this == other);
		}

		Vector3& Vector3::operator+=(const Vector3 &other)
		{
			return Add(other);
		}

		Vector3& Vector3::operator-=(const Vector3 &other)
		{
			return Subtract(other);
		}
		Vector3& Vector3::operator*=(const Vector3 &other)
		{
			return Multiply(other);
		}
		Vector3& Vector3::operator/=(const Vector3 &other)
		{
			return Divide(other);
		}

		std::ostream &operator<<(std::ostream &a_stream, const Vector3 &a_vector)
		{
			return a_stream << "Vector3(" << a_vector.x << ", " << a_vector.y << ", " << a_vector.z << ")";
		}
	}
}