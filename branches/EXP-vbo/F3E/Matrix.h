#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <sstream>
#include <iostream>

namespace f3
{
	namespace math
	{

		template <class T, const int i>  
		class Matrix
		{
		protected:
			T element[i][i];

		public:
			Matrix(void)
			{
				memset(&element, 0, sizeof(T)*i*i);
			}

			
			Matrix operator*(Matrix<T,i> matrix) 
			{
				Matrix<T,i> rslt;
				float pr = 0;

				for (int k = 0; k < i; k++)
				for (int l = 0; l < i; l++)
				{
					pr = get(k,l) * matrix.get(l,k);
					rslt.set(k,l, pr);
				}
				return rslt;
			}

			Matrix operator+(Matrix<T,i> matrix) 
			{
				Matrix<T,i> rslt;
				T pr = 0;

				for (int k = 0; k < i; k++)
				for (int l = 0; l < i; l++)
				{
					pr = get(k,l) + matrix.get(k,l);
					rslt.set(k,l, pr);
				}
				return rslt;
			}

			T& operator[](int index)
			{
				//assert(0 <= index && index <= i);
				return element[index];
			}
			
			void translate(Vector<T, (i-1)> vector)
			{
				Matrix<T, i> matrix;
				for (int k = 0; k < (i-1); k++)
				{
					matrix.set(k,i-1,vector[k]);
					std::cout << vector[k] << " " << matrix.get(k,0);
					//m[i-1][k] = vector[k];
				}
				std::cout << "rslt: " << (*this + matrix).toString();
			}

			std::string toString()
			{
				std::stringstream out(std::stringstream::in | std::stringstream::out);

				for (int k = 0; k < i; k++)
				{
					out << "\t{ ";
					for (int l = 0; l < i; l++)
					{
						out << element[k][l] << (l == i-1 ? "" : ",");
					}
					out << " }\n";
				}
				
				return "\n{\n" + (out.str()) + "}";
			}
		
			operator std::string() { return toString(); }
		
		private:
			T& get(int row, int col)
			{
				return element[row][col];
			}

			void set(int row, int col, T& val)
			{
				element[row][col] = val;
			}
		};


		//template <class T>
		//class Matrix4 : public Matrix<T, 4>
		//{

		//public:

		//};
		typedef Matrix<float,4> Matrix4f;

	}
}

namespace f3m = f3::math;

#endif