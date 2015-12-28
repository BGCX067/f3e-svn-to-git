//#ifndef INCLUDED_HELLOWORLDAPP_H
//#define INCLUDED_HELLOWORLDAPP_H
// 
//// The HelloWorldApp class. This class shows a window
//// containing a statusbar with the text "Hello World"
//class HelloWorldApp : public wxApp
//{
//public:
//	virtual bool OnInit();
//};
// 
//DECLARE_APP(HelloWorldApp)
// 
//#endif // INCLUDED_HELLOWORLDAPP_H asdasdad

//template<typename T, int I>
//class A
//{
//protected:
//	T _value[I];
//
//public:
//	A()
//	{
//		_value;
//	}
//
//	A operator*(A operand)
//	{
//		A rslt;
//		
//		for (int i = 0; i < I; i++)
//		{
//			rslt._value[i] = this->_value[i] * operand._value[i];
//		}
//		return rslt;
//	}
//};
//
//template<typename T>
//class B : public A<float,3>
//{
//	T bla;
//
//public:
//	B()
//	{
//		_value[0] = 1;
//	}
//};
//
//template <class T, const int i>  
//class Vector
//{
//public:
//	T element[i];
//
//	Vector(void);
//	void setValues();
//
//	//template<>
//	//void Vector<float, 3>::setValues(float abc)
//	//{
//	//	std::cout << "SPECIAL";
//	//}
//	
//	Vector operator*(const Vector v1) const 
//	{
//		Vector rslt;
//
//		for (int k = 0; k < i; k++)
//		{
//			rslt.element[k] = element[k] * v1.element[k];
//		}
//
//		return rslt;
//	}
//
//};

//template<class T>
//class Vector<T, 3>
//{
//public:
//	Vector(void)
//	{
//		memset(&element, 0, sizeof(T)*3);
//	}
//};
//
//template<class T, const int i>
//Vector<T,i>::Vector(void)
//{
//	std::cout << "GENERAL CONST";
//	memset(&element, 0, sizeof(T)*i);
//}
//
//template<>
//Vector<float, 3>::Vector(void)
//{
//	std::cout << "SPECIAL CONST";
//}
//
//template<class T, const int i>
//void Vector<T,i>::setValues()
//{
//	std::cout << "GENERAL";
//}
//
//
//template<>
//void Vector<float,3>::setValues()
//{
//	std::cout << "SPECIAL";
//}
//template <class T>
//class Vector3 : public Vector<T, 3>
//{
//
//public:
//
//Vector3(): Vector() {}
//
//	Vector3(T x, T y, T z)
//	{
//		element[0] = x;
//		element[1] = y;
//		element[2] = z;
//	}
//	
//	void operator=(Vector<T, 3> v)
//	{
//		element[0] = v.element[0];
//		element[1] = v.element[1];
//		element[2] = v.element[2];
//	}
//
//	~Vector3(void) {};
//};

//
//class Vec
//{
//public:
//	float element[3];
//
//	Vec(void)
//	{
//		memset(&element, 0, sizeof(float)*3);
//	}
//
//	Vec operator*(const Vec v1) const 
//	{
//		Vec rslt;
//
//		for (int k = 0; k < 3; k++)
//		{
//			rslt.element[k] = element[k] * v1.element[k];
//		}
//
//		return rslt;
//	}
//
//};
//
//class Vec3 : public Vec
//{
//
//public:
//
//Vec3(): Vec() {}
//
//	Vec3(float x, float y, float z)
//	{
//		element[0] = x;
//		element[1] = y;
//		element[2] = z;
//	}
//	
//	void operator=(Vec v)
//	{
//		element[0] = v.element[0];
//		element[1] = v.element[1];
//		element[2] = v.element[2];
//	}
//
//	~Vec3(void) {};
//};
//

//typedef Vector3<float> Vector3f;