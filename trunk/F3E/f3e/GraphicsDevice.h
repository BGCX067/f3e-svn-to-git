#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include "Mesh.h"
#include "Texture.h"
#include "Matrix.h"

namespace f3
{
	namespace graphics 
	{
		class GraphicsDevice
		{
		public:
			
			GraphicsDevice(void);
			~GraphicsDevice(void);

			virtual void loadTexture(f3r::Texture* texture) = 0;
			virtual void setTexture(f3r::Texture* texture) = 0;
			virtual void present() = 0;
			virtual void clear() = 0;
		};
	}
}

#endif