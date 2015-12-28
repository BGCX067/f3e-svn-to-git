#ifndef Vector_H
#define Vector_H


#include <string>
#include <sstream>

namespace f3
{
namespace math
{

template <class T, const int i>  
class Vector
{
protected:
	T element[i];

public:
	Vector(void)
	{
		memset(&element, 0, sizeof(T)*i);
	}

	~Vector(void) {};

	Vector operator+(const Vector v1) const 
	{
		Vector<T, i> rslt;

		for (int k = 0; k < i; k++)
		{
			rslt.element[k] = element[k] + v1.element[k];
		}

		return rslt;
	}

	Vector operator-(const Vector v1) const 
	{
		Vector<T, i> rslt;

		for (int k = 0; k < i; k++)
		{
			rslt.element[k] = element[k] - v1.element[k];
		}

		return rslt;
	}

	Vector operator*(const Vector v1) const 
	{
		Vector<T, i> rslt;

		for (int k = 0; k < i; k++)
		{
			rslt.element[k] = element[k] * v1.element[k];
		}

		return rslt;
	}

	std::string toString()
	{
		std::string rslt;
		std::stringstream out;

		for (int k = 0; k < i; k++)
		{
			out << element[k] << (k != i-1 ? "," : "");
		}
		
		return "{" + (out.str()) + "}";
	}
};

template <class T>
class Vector2 : public Vector<T, 2>
{

public:
	Vector2(T x, T y)
	{
		element[0] = x;
		element[1] = y;
	}
	

	~Vector2(void) {};
};

template <class T>
class Vector3 : public Vector<T, 3>
{

public:
	Vector3(T x, T y, T z)
	{
		element[0] = x;
		element[1] = y;
		element[2] = z;
	}
	

	~Vector3(void) {};
};


template <class T>
class Vector4 : public Vector<T, 4>
{

public:
	Vector4(T x, T y, T z, T w)
	{
		element[0] = x;
		element[1] = y;
		element[2] = z;
		element[3] = w;
	}
	

	~Vector4(void) {};
};

}//ns:math
}//ns:f3


namespace f3m = f3::math;

#endif