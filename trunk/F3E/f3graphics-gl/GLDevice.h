#ifndef GLCanvas_H
#define GLCanvas_H

#ifdef WIN32
#include <windows.h>
#endif

#include <gl\glew.h>
#include <f3graphics/Device.h>
#include  <f3graphics/Mesh.h>
#include  <f3scene/Node.h>
#include "GLTextureLoader.h"
#include  <f3scene/MeshNode.h>
#include <f3graphics/VertexLayout.h>
#include <f3graphics/RenderTarget.h>
#include "GLDebug.h"

namespace f3
{
	namespace graphics
	{
		class GLRenderTarget : public RenderTarget
		{
		public:
			GLuint fbo;
		};

		class GLVertexBuffer : public Buffer
		{
		public:
			GLVertexBuffer() : Buffer() {};
			f3::I32 _glbuffer;
		};

		class GLVertexLayout : public VertexLayout
		{
		public:
			GLVertexLayout() : VertexLayout() {};

		};

		class GLDevice : public Device
		{
			f3::UI32 vb,ib;
			f3g::Mesh _mesh;

			int _modes[3];
			GLuint _bufferSlots[16];
			GLDebug debugPrinter;

		protected:
			void clear( f3u::ColorRGBA color, f3::UI32 mode );
			void present();
			Window* _window;
			RenderMode _renderMode;

		public:
			GLDevice(Window* window);
			~GLDevice(void);

			// fundamentals
			virtual void init();
			virtual void destroy();
			virtual void resize( int w, int h );
			
			// drawing
			void drawElements( f3::I32 elements );
			void drawInstances( f3::I32 elements, f3::I32 instances );
			void drawIndexed( f3::I32 elements );
			void drawIndexedInstances(f3::I32 elements, f3::I32 instances);
			
			// setter
			void setTexture( Texture* texture );
			void setRenderMode( RenderMode mode );
			void setVertexLayout( VertexLayoutDefinition &layout );
			void setShader( Shader* shader );
			
			// buffers
			void updateBuffer( Buffer* buffer, void* source, f3::I32 size );
			void createBuffer( BufferDescription desc, void* source, Buffer** target );
			void setBuffer( f3::I32 slot, Buffer* buffer, f3::UI32 stride, f3::UI32 offset = 0 );
			void releaseBuffer( Buffer* buffer );

			// vertexlayouts
			virtual void createVertexLayout( VertexLayoutDefinition* definition, Shader* shader, VertexLayout** target );
			virtual void releaseVertexLayout( VertexLayout* layout );
			void setVertexLayout( VertexLayout* layout );
			void setIndexBuffer(f3g::Buffer* buffer );

			// render targets
			void createRenderTarget(const RenderTargetDescription& desc, RenderTarget** target);
			void setRenderTarget(RenderTarget* target);
			void GLDevice::genMM();
		};
	}
}
#endif