#ifndef VECTOR_H
#define VECTOR_H


#include <string>
#include <sstream>

namespace f3
{
namespace math
{

template <class T, const int i>  
class vector
{
protected:
	T element[i];

public:
	vector(void)
	{
		memset(&element, 0, sizeof(T)*i);
	}

	~vector(void) {};

	vector operator+(const vector v1) const 
	{
		vector<T, i> rslt;

		for (int k = 0; k < i; k++)
		{
			rslt.element[k] = element[k] + v1.element[k];
		}

		return rslt;
	}

	vector operator-(const vector v1) const 
	{
		vector<T, i> rslt;

		for (int k = 0; k < i; k++)
		{
			rslt.element[k] = element[k] - v1.element[k];
		}

		return rslt;
	}

	vector operator*(const vector v1) const 
	{
		vector<T, i> rslt;

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
class vector2 : public vector<T, 2>
{

public:
	vector2(T x, T y)
	{
		element[0] = x;
		element[1] = y;
	}
	

	~vector2(void) {};
};

template <class T>
class vector3 : public vector<T, 3>
{

public:
	vector3(T x, T y, T z)
	{
		element[0] = x;
		element[1] = y;
		element[2] = z;
	}
	

	~vector3(void) {};
};


template <class T>
class vector4 : public vector<T, 4>
{

public:
	vector4(T x, T y, T z, T w)
	{
		element[0] = x;
		element[1] = y;
		element[2] = z;
		element[3] = w;
	}
	

	~vector4(void) {};
};

}//ns:math
}//ns:f3


namespace f3m = f3::math;

#endif