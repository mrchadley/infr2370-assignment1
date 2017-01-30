// Marc Tremblay
// 100555250
// 01/27/2017

#pragma once

#include <iostream>

namespace jnaut
{
	namespace math
	{
		struct Vector4
		{
			float x, y, z, w;
			
			Vector4();
			Vector4(const float &a_x, const float &a_y, const float &a_z, const float &a_w);

			Vector4& Add(const Vector4 &a_other);
			Vector4& Subtract(const Vector4 &a_other);
			
			Vector4& Multiply(const Vector4 &a_other);
			Vector4& Divide(const Vector4 &a_other);

			friend Vector4 operator+(Vector4 left, const Vector4 &right);
			friend Vector4 operator-(Vector4 left, const Vector4 &right);
			friend Vector4 operator*(Vector4 left, const Vector4 &right);
			friend Vector4 operator/(Vector4 left, const Vector4 &right);

			bool operator==(const Vector4 &other);
			bool operator!=(const Vector4 &other);

			Vector4& operator+=(const Vector4 &other);
			Vector4& operator-=(const Vector4 &other);
			Vector4& operator*=(const Vector4 &other);
			Vector4& operator/=(const Vector4 &other);

			friend std::ostream &operator<<(std::ostream &a_ostream, const Vector4 &a_vector);
		};
	}
}