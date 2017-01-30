// Marc Tremblay
// 100555250
// 01/27/2017

#pragma once

#include <iostream>

namespace jnaut
{
	namespace math
	{
		struct Vector2
		{
			float x, y;
			
			Vector2();
			Vector2(const float &a_x, const float &a_y);

			Vector2& Add(const Vector2 &a_other);
			Vector2& Subtract(const Vector2 &a_other);
			
			Vector2& Multiply(const Vector2 &a_other);
			Vector2& Divide(const Vector2 &a_other);

			friend Vector2 operator+(Vector2 left, const Vector2 &right);
			friend Vector2 operator-(Vector2 left, const Vector2 &right);
			friend Vector2 operator*(Vector2 left, const Vector2 &right);
			friend Vector2 operator/(Vector2 left, const Vector2 &right);

			bool operator==(const Vector2 &other);
			bool operator!=(const Vector2 &other);

			Vector2& operator+=(const Vector2 &other);
			Vector2& operator-=(const Vector2 &other);
			Vector2& operator*=(const Vector2 &other);
			Vector2& operator/=(const Vector2 &other);

			friend std::ostream &operator<<(std::ostream &a_ostream, const Vector2 &a_vector);
		};
	}
}