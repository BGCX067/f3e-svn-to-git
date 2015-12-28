#ifndef RenderManager_h__
#define RenderManager_h__


#include <f3math/Vector.h>
#include <f3base/Common.h>
#include <vector>
#include <f3graphics/VertexLayoutElement.h>
#include "Buffer.h"
#include "DebugContext.h"


namespace f3
{
	namespace graphics
	{
		struct MatrixSetup;
		class Device;
		class Shader;
		class VertexLayout;

		class DebugRenderer
		{
			std::vector<f3m::Vector3f>& lines;
			std::vector<Point>& points;
			std::vector<Sphere> spheres;

			VertexLayout* _vertexLayout;
			Buffer* _buffer;
			
			f3g::Device* _device;
			Shader* _shader; 
			DebugContext* _context;

		public:
			DebugRenderer(f3g::Device* device, DebugContext* context);
			~DebugRenderer(void);
			void render(MatrixSetup &_matrices);
		};
	}
}
#endif // RenderManager_h__
