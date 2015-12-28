#include "Vector.h"

#include <assert.h>

f3::math::Vector3f f3::math::Vector3f::Up = Vector3f(0,1,0);

f3::math::Vector3f f3::math::Vector3f::Null = Vector3f(0,0,0);


namespace f3
{
	namespace math
	{
		Vector3f::Vector3f(float x, float y, float z) 
		{
			_x = x;
			_y = y;
			_z = z;
		}

		float Vector3f::length()
		{
			float l = 0.0f;

			l += square(_x);
			l += square(_y);
			l += square(_z);

			return sqrtf(l);
		}

		Vector3f Vector3f::normalize()
		{
			Vector3f rslt(*this);

			float l = length();

			if (l == 0.0f)
			{
				assert(l == 0.0f);
				return rslt; 
			}
			rslt._x = _x / l;
			rslt._y = _y / l;
			rslt._z = _z / l;
		
			return rslt;
		}

		Vector3f& Vector3f::operator+=( const Vector3f& a ) 
		{
			_x += a._x;
			_y += a._y;
			_z += a._z;
			return *this;
		}


		Vector3f& Vector3f::operator-=( const Vector3f& a ) 
		{
			_x -= a._x;
			_y -= a._y;
			_z -= a._z;

			return *this;
		}

		Vector3f Vector3f::cross(Vector3f v1, Vector3f v2)
		{
			Vector3f rslt;
			rslt[0] = v1[1]*v2[2] - v1[2]*v2[1];
			rslt[1] = v1[2]*v2[0] - v1[0]*v2[2];
			rslt[2] = v1[0]*v2[1] - v1[1]*v2[0];

			return rslt;
		}

		Vector3f Vector3f::operator*(const Vector3f a) const 
		{
			Vector3f rslt;

			rslt._x = _x * a._x;
			rslt._y = _y * a._y;
			rslt._z = _z * a._z;

			return rslt;
		}

		Vector3f Vector3f::operator*(const float factor) const 
		{
			Vector3f rslt;

			rslt._x = _x * factor;
			rslt._y = _y * factor;
			rslt._z = _z * factor;

			return rslt;
		}

		std::string Vector3f::toString()
		{
			std::stringstream out(std::stringstream::in | std::stringstream::out);

			out << "{ " << _x << "," << _y << "," << _z << " }";

			return out.str();
		}


		float& Vector3f::operator[](int index)
		{

			if (index == 0)
				return _x;

			if (index == 1)
				return _y;

			if (index == 2)
				return _z;

			return _x;
		}

		std::ostream& Vector3f::print(std::ostream& os) const
		{
			os << "{ " << _x << "," << _y << "," << _z << " }";

			return os;
		}

	}
}

const f3m::Vector3f operator+(const f3m::Vector3f& lhs, const f3m::Vector3f& rhs)
{
	f3m::Vector3f rslt(lhs);
	rslt += rhs;
	return rslt;
}


const f3m::Vector3f operator-(const f3m::Vector3f& lhs, const f3m::Vector3f& rhs)
{
	f3m::Vector3f rslt(lhs);
	rslt -= rhs;
	return rslt;
}

std::ostream& operator<<(std::ostream& os, const f3m::Vector3f& v)
{
	return  v.print(os);
}
