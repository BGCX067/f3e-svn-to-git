#include "Matrix.h"
#include "Vector.h"

std::ostream& operator<<(std::ostream& os, f3m::Matrix4f& m)
{
	os << m.toString() << std::endl;
	return os;
}

namespace f3
{
	namespace math
	{
		Matrix4f createProjection(float fov, float nearPlane, float farPlane, float aspect)
		{
			Matrix4f m;
			fov = fov/2.0f;
			float f = 1.0f/tanf(fov);
			float dp = nearPlane - farPlane;
			
			m.set(0,0, f/aspect);
			m.set(1,1, f);
			m.set(2,2, (farPlane+nearPlane)/dp);
			m.set(3,2, (2*farPlane*nearPlane)/dp);
			m.set(2,3, -1);

			return m;
		}

		Matrix4f transpose(Matrix4f& m)
		{
			Matrix4f rslt;

			for (int l = 0; l < 4; l++)
			for (int k = 0; k < 4; k++)
			{
				rslt.set(k,l, m.get(l,k));
			}
			return rslt;
		}

		Matrix4f createLookAt(Vector3f eye, Vector3f target, Vector3f up)
		{
			Matrix4f rslt;
			Vector3f f = target - eye;
			f = f.normalize();
			Vector3f s = f3m::Vector3f::cross(f, up);
			Vector3f u = f3m::Vector3f::cross(s, f);
			
			rslt.set(0,0,s[0]);
			rslt.set(0,1,s[1]);
			rslt.set(0,2,s[2]);
			rslt.set(1,0,u[0]);
			rslt.set(1,1,u[1]);
			rslt.set(1,2,u[2]);
			rslt.set(2,0,-f[0]);
			rslt.set(2,1,-f[1]);
			rslt.set(2,2,-f[2]);
			rslt.set(3,3,1);

			
			rslt.translate(eye * -1);
			return rslt;
		}


		Matrix4f multiply(Matrix4f& m1, Matrix4f& m2)
		{
			Matrix4f result;

			float r = 0.0f;
			
			for (int n = 0; n < 4; n++)
			for (int l = 0; l < 4; l++)
			{
				r = 0.0f;

				for (int m = 0; m < 4; m++)
				{
					r += m1.get(l,m)*m2.get(m,n);
				}
				
				result.set(l,n,r);
			}

			return result;
		}

		f3::math::Vector3f multiply( Vector3f& v1, Matrix4f& m1 )
		{
			Vector3f rslt;

			rslt._x = m1.get(0,0)*v1._x + m1.get(0,1)*v1._y + m1.get(0,2)*v1._z + m1.get(0,3)*1;
			rslt._y = m1.get(1,0)*v1._x + m1.get(1,1)*v1._y + m1.get(1,2)*v1._z + m1.get(1,3)*1;
			rslt._z = m1.get(2,0)*v1._x + m1.get(2,1)*v1._y + m1.get(2,2)*v1._z + m1.get(2,3)*1;

			return rslt;
		}

	}
}