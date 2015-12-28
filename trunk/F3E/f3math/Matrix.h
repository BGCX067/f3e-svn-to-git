#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <sstream>
#include <iostream>
#include <math.h>
#include "Vector.h"

namespace f3
{
	namespace math
	{	

		class Matrix4f
		{
		protected:
			float element[4][4];

		public:


			Matrix4f(void)
			{
				memset(&element, 0, sizeof(float)*4*4);
			}

			
			Matrix4f operator*(Matrix4f matrix) 
			{
				Matrix4f result;

				float r = 0.0f;
				
				for (int n = 0; n < 4; n++)
				for (int l = 0; l < 4; l++)
				{
					r = 0.0f;

					for (int m = 0; m < 4; m++)
					{
						r += get(l,m)*matrix.get(m,n);
					}
					
					result.set(l,n,r);
				}

				return result;
			}

			Matrix4f operator*(float factor) 
			{
				Matrix4f rslt;
				float pr = 0;


			}

			Matrix4f operator+(Matrix4f matrix) 
			{
				Matrix4f rslt;
				float pr = 0;

				for (int k = 0; k < 4; k++)
				for (int l = 0; l < 4; l++)
				{
					pr = get(k,l) + matrix.get(k,l);
					rslt.set(k,l, pr);
				}
				return rslt;
			}

			float& operator[](int index)
			{
				//assert(0 <= index && index <= i);
				return *(element[index]);
			}
			
			void translate(Vector3f vector)
			{
				Matrix4f m = identity();
				for (int k = 0; k < 3; k++)
				{
					m.set(k,3, vector[k]);
				}

				*this = *this * m;
			}

			static Matrix4f scale(Vector3f vector)
			{
				Matrix4f rslt = identity();

				rslt.set(0, 0, vector[0]);
				rslt.set(1, 1, vector[1]);
				rslt.set(2, 2, vector[2]);
				
				return rslt;
			}

			static Matrix4f translation(Vector3f vector)
			{
				Matrix4f rslt = identity();

				rslt.set(0,3, vector._x);
				rslt.set(1,3, vector._y);
				rslt.set(2,3, vector._z);
				
				return rslt;
			}

			static Matrix4f identity()
			{
				Matrix4f rslt;

				rslt.set(0, 0, 1.0f);
				rslt.set(1, 1, 1.0f);
				rslt.set(2, 2, 1.0f);
				rslt.set(3, 3, 1.0f);

				return rslt;
			}

			static Matrix4f rotationX(float angle)
			{
				Matrix4f rslt = identity();
				
				rslt.set( 1,1, std::cos(angle) );
				rslt.set( 1,2,-std::sin(angle) );
				rslt.set( 2,1, std::sin(angle) );
				rslt.set( 2,2, std::cos(angle) );
				
				return rslt;
			}

			static Matrix4f rotationY(float angle)
			{
				Matrix4f rslt = identity();

				rslt.set( 0,0, std::cos(angle) );
				rslt.set( 0,2, std::sin(angle) );
				rslt.set( 2,0,-std::sin(angle) );
				rslt.set( 2,2, std::cos(angle) );

				return rslt;
			}

			static Matrix4f rotationZ(float angle)
			{
				Matrix4f rslt = identity();

				rslt.set( 0,0, std::cos(angle) );
				rslt.set( 0,1,-std::sin(angle) );
				rslt.set( 1,0, std::sin(angle) );
				rslt.set( 1,1, std::cos(angle) );

				return rslt;
			}

			std::string toString()
			{
				std::stringstream out(std::stringstream::in | std::stringstream::out);

				for (int k = 0; k < 4; k++)
				{
					out << "\t{ ";
					for (int l = 0; l < 4; l++)
					{
						out << element[k][l] << (l == 4-1 ? "" : ",");
					}
					out << " }\n";
				}
				
				return "{\n" + (out.str()) + "}";
			}
		
			operator std::string() { return toString(); }

			inline float& get(int row, int col)
			{
				return element[row][col];
			}

			inline void set(int row, int col, float val)
			{
				element[row][col] = val;
			}

			
		};
				
		Matrix4f transpose(Matrix4f& m);
		Matrix4f createProjection(float fov, float nearPlane, float farPlane, float aspect);
		Matrix4f createLookAt(Vector3f eye, Vector3f target, Vector3f up);
		Matrix4f multiply(Matrix4f& m1, Matrix4f& m2);
		Vector3f multiply(Vector3f& v1, Matrix4f& m1);
	}
}

namespace f3m = f3::math;

std::ostream& operator<<(std::ostream& os, f3m::Matrix4f& m);

#endif