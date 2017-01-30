// Marc Tremblay
// 100555250
// 01/29/2017

#pragma once

#include <iostream>

namespace jnaut
{
	namespace math
	{
		struct Vector3
		{
			float x, y, z;
			
			Vector3();
			Vector3(const float &a_x, const float &a_y, const float &a_z);

			Vector3& Add(const Vector3 &a_other);
			Vector3& Subtract(const Vector3 &a_other);
			
			Vector3& Multiply(const Vector3 &a_other);
			Vector3& Divide(const Vector3 &a_other);

			friend Vector3 operator+(Vector3 left, const Vector3 &right);
			friend Vector3 operator-(Vector3 left, const Vector3 &right);
			friend Vector3 operator*(Vector3 left, const Vector3 &right);
			friend Vector3 operator/(Vector3 left, const Vector3 &right);

			bool operator==(const Vector3 &other);
			bool operator!=(const Vector3 &other);

			Vector3& operator+=(const Vector3 &other);
			Vector3& operator-=(const Vector3 &other);
			Vector3& operator*=(const Vector3 &other);
			Vector3& operator/=(const Vector3 &other);

			friend std::ostream &operator<<(std::ostream &a_ostream, const Vector3 &a_vector);
		};
	}
}