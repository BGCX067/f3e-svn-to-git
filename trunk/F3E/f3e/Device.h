#ifndef CANVAS_H
#define CANVAS_H

#include <f3base/IDevice.h>
#include <f3math/Matrix.h>
#include "Node.h"
#include <map>
#include "Font.h"
#include "IWindowListener.h"
#include "SpriteBatch.h"
#include "QuadMesh.h"
#include "Buffer.h"

namespace f3
{
	namespace graphics
	{
		struct MatrixSetup
		{
			f3m::Matrix4f world;
			f3m::Matrix4f view;
			f3m::Matrix4f projection;
		};

		typedef std::map<f3::Mesh*, f3::Mesh*> MeshList;
		typedef std::pair<f3::Mesh*, f3::Mesh*> MeshEntry;

		class Device : public IDevice
		{
			QuadMesh quad;
			
		protected:

			int _width;
			int _height;
			MatrixSetup _matrices;
			MeshList meshes;
			Shader* _shader;
			Window* _window;
			Texture* _fallbackTexture;
			virtual void clear() = 0;
			virtual void present() = 0;

		public:
			enum RenderMode { LINES, TRIANGLES, POINTS };
			IWindowListener* _windowListener;

			Device(Window* window);
			virtual ~Device(void);
			
			void setupMatrices();
			void drawNode(f3::Node* node, f3m::Matrix4f mat);
			virtual void init();
			virtual void draw();
			virtual void resize(int w, int h) = 0;
			virtual void destroy() = 0;
			virtual void drawMesh(f3::Mesh* mesh) = 0;
			virtual void drawFont(f3::Font* font, char character) = 0;
			void Device::drawSpriteBatch(SpriteBatch& batch);
			virtual void setRenderMode(RenderMode mode) = 0;
			virtual void createBuffer(f3g::BufferDescription desc, void* source, f3g::Buffer& target) = 0;
			virtual void setBuffer(f3::I32 slot, f3g::Buffer* buffer, f3::UI32 stride, f3::UI32 offset = 0 ) = 0;
		};

	}
}
#endif