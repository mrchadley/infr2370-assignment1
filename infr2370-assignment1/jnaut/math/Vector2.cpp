// Marc Tremblay
// 100555250
// 01/27/2017

#include "Vector2.h"

namespace jnaut
{
	namespace math
	{
		Vector2::Vector2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		Vector2::Vector2(const float &a_x, const float &a_y)
		{
			x = a_x;
			y = a_y;
		}

		Vector2& Vector2::Add(const Vector2 &a_other)
		{
			x += a_other.x;
			y += a_other.y;

			return *this;
		}

		Vector2& Vector2::Subtract(const Vector2 &a_other)
		{
			x -= a_other.x;
			y -= a_other.y;

			return *this;
		}

		Vector2& Vector2::Multiply(const Vector2 &a_other)
		{
			x *= a_other.x;
			y *= a_other.y;

			return *this;
		}

		Vector2& Vector2::Divide(const Vector2 &a_other)
		{
			x /= a_other.x;
			y /= a_other.y;

			return *this;
		}

		Vector2 operator+(Vector2 left, const Vector2 &right)
		{
			return left.Add(right);
		}

		Vector2 operator-(Vector2 left, const Vector2 &right)
		{
			return left.Subtract(right);
		}

		Vector2 operator*(Vector2 left, const Vector2 &right)
		{
			return left.Multiply(right);
		}

		Vector2 operator/(Vector2 left, const Vector2 &right)
		{
			return left.Divide(right);
		}

		bool Vector2::operator==(const Vector2 &other)
		{
			return x == other.x && y == other.y;
		}

		bool Vector2::operator!=(const Vector2 &other)
		{
			return !(*this == other);
		}

		Vector2& Vector2::operator+=(const Vector2 &other)
		{
			return Add(other);
		}

		Vector2& Vector2::operator-=(const Vector2 &other)
		{
			return Subtract(other);
		}
		Vector2& Vector2::operator*=(const Vector2 &other)
		{
			return Multiply(other);
		}
		Vector2& Vector2::operator/=(const Vector2 &other)
		{
			return Divide(other);
		}

		std::ostream &operator<<(std::ostream &a_stream, const Vector2 &a_vector)
		{
			return a_stream << "Vector2(" << a_vector.x << ", " << a_vector.y << ")";
		}
	}
}