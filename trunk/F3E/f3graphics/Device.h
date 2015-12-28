#ifndef CANVAS_H
#define CANVAS_H

#include <f3base/IDevice.h>
#include <f3base/ColorRGBA.h>
#include <f3base/IWindowListener.h>

#include <f3math/Matrix.h>
#include <f3scene/Node.h>
#include <map>
#include "SpriteBatch.h"
#include "QuadMesh.h"
#include "Buffer.h"
#include "DebugRenderer.h"
#include "TextRenderer.h"
#include "VertexLayout.h"
#include <f3graphics/RenderTarget.h>

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

		typedef std::map<f3g::Mesh*, f3g::Mesh*> MeshList;
		typedef std::pair<f3g::Mesh*, f3g::Mesh*> MeshEntry;

		class Device : public IDevice
		{
			QuadMesh quad;
			IMeshLoader* _meshloader;
			RenderTarget* rt;

			SpriteBatch _batch;
			SpriteBatch _batch2;
		
		public:
			enum ClearMode { DEPTH_BUFFER = 0x1, COLOR_BUFFER = 0x2 };
		
		protected:
			int _width;
			int _height;
			MatrixSetup _matrices;
			Shader* _shader;
			Shader* _nmshader;
			Window* _window;
			RenderTarget* _currentRenderTarget;
			Texture* _fallbackTexture;
			Texture* _nmTexture;
			Texture* _stoneTexture;
			ITextureLoader* _textureloader;
			IShaderLoader* _shaderloader;

			virtual void clear( f3u::ColorRGBA color, f3::UI32 mode ) = 0;
			virtual void present() = 0;

		public:
			enum RenderMode { LINES, TRIANGLES, POINTS };
			IWindowListener* _windowListener;

			Device(Window* window);
			virtual ~Device(void);
			
			DebugRenderer* _debugDR;
			TextRenderer* _debugTR;
			Shader* currentShader();
			RenderTarget* currentRenderTarget();
			
			int width();
			int height();

			// fundamentals
			virtual void init();
			virtual void draw();
			virtual void resize(int w, int h) = 0;
			virtual void destroy() = 0;
			
			// drawing
			virtual void setupMatrices();
			virtual void drawNode(f3::scene::Node* node, f3m::Matrix4f mat);
			virtual void drawElements(f3::I32 elements) = 0;
			virtual void drawInstances(f3::I32 elements, f3::I32 instances) = 0;
			virtual void drawMesh(f3g::Mesh* mesh, f3g::Shader* shader = NULL);
			virtual void drawSpriteBatch(SpriteBatch& batch, Shader* shader);
			virtual void drawIndexed( f3::I32 elements ) = 0;
			virtual void drawIndexedInstances(f3::I32 elements, f3::I32 instances) = 0;
			
			// setter
			virtual void setRenderMode(RenderMode mode) = 0;
			virtual void setShader(Shader* shader) = 0;
			
			// loaders
			IMeshLoader* getMeshLoader();
			ITextureLoader* getTextureLoader();
			IShaderLoader* getShaderLoader();
			
			// buffers
			virtual void releaseBuffer( Buffer* buffer ) = 0;
			virtual void createBuffer( BufferDescription desc, void* source, Buffer** target ) = 0;
			virtual void setBuffer( f3::I32 slot, Buffer* buffer, f3::UI32 stride, f3::UI32 offset = 0 ) = 0;
			virtual void setIndexBuffer(f3g::Buffer* buffer ) = 0;
			virtual void updateBuffer( Buffer* buffer, void* source, f3::I32 size ) = 0;

			// vertexlayouts
			virtual void createVertexLayout( VertexLayoutDefinition* definition, Shader* shader, VertexLayout** target ) = 0;
			virtual void releaseVertexLayout( VertexLayout* layout ) = 0;
			virtual void setVertexLayout( VertexLayout* layout ) = 0;

			// rendertargets
			virtual void createRenderTarget(const RenderTargetDescription& desc, RenderTarget** target) = 0;
			virtual void setRenderTarget(RenderTarget* target) = 0;
			virtual void genMM() = 0;
		};

	}
}
#endif