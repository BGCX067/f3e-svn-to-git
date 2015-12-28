#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <iostream>
#include <sstream>

//
//struct Vector3f
//{
//	float x,y,z;
//};

namespace f3
{
	namespace math
	{
		inline float square(float val)
		{
			return val*val;
		}

		class Vector2f
		{
		public:
			float _x, _y;

			Vector2f(float x  = 0.0f, float y = 0.0f)
			{
				_x = x;
				_y = y;
			}
		};

		class Vector3f
		{
		public:
			float _x;
			float _y;
			float _z;
			static Vector3f Up;
			static Vector3f Null;

			Vector3f() {};	
			Vector3f(float x, float y, float z);
			~Vector3f(void) {};
				
			static Vector3f cross(Vector3f v1, Vector3f v2);
			float length();
			Vector3f normalize();

			Vector3f operator*(const Vector3f a) const;
			Vector3f operator*(const float factor) const;
			Vector3f& operator+=( const Vector3f& a );
			Vector3f& operator-=( const Vector3f& a );
			
			std::string toString();
			float& operator[](int index);
			std::ostream& print(std::ostream& os) const;
		};		

		//template <class T, int J>
		//const Vector3f<T,J> operator+(const Vector3f<T,J>& lhs, const Vector3f<T,J>& rhs)
		//{
		//	Vector3f<T,J> ret( lhs );
		//	ret += rhs;
		//	return ret;
		//}

		//template <class T>
		//const Vector3<T> operator+(const Vector3<T>& lhs, const Vector3<T>& rhs)
		//{
		//	Vector3<T> ret( lhs );
		//	ret += rhs;
		//	return ret;
		//}

		//template <class T>
		

		//template <class T>
		//const Vector3<T> operator*(const Vector3<T>& lhs, const float& rhs)
		//{
		//	Vector3<T> ret( lhs );
		//	ret[0] *= rhs;
		//	ret[1] *= rhs;
		//	ret[2] *= rhs;
		//	return ret;
		//}


	}//ns:math
}//ns:f3

namespace f3m = f3::math;


const f3m::Vector3f operator-(const f3m::Vector3f& lhs, const f3m::Vector3f& rhs);
const f3m::Vector3f operator+(const f3m::Vector3f& lhs, const f3m::Vector3f& rhs);

std::ostream& operator<<(std::ostream& os, const f3m::Vector3f& v);

#endif