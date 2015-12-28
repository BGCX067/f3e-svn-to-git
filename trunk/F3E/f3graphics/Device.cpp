#include "Device.h"
#include <f3scene/CameraNode.h>
#include <f3scene/Graph.h>
#include <f3scene/MeshNode.h>
#include <f3scene/GlyphNode.h>
#include "WindowListener.h"
#include <f3base/Window.h>
#include <f3base/Timer.h>
#include <f3base/Common.h>
#include "Shader.h"
#include "QuadMesh.h"
#include "MeshLoader.h"


namespace f3
{
	namespace graphics
	{
		Device::Device(Window* window)
		{
			f3u::log << f3u::info << "creating device" << f3u::endl;
			_window = window;
			_stoneTexture = new f3g::Texture("resources/textures/TitanHearthStone.tga");//f3_RGBA_8b_128.raw");
			_fallbackTexture = new f3g::Texture("resources/textures/font.tga");//f3_RGBA_8b_128.raw");
			_nmTexture = new f3g::Texture("resources/textures/nm.tga");//f3_RGBA_8b_128.raw");
			//_fallbackTexture->_description.height = 128;
			//_fallbackTexture->_description.width = 128;
			//_fallbackTexture->_description.format = TextureDescription::R8G8B8A8;
		}

		Device::~Device(void)
		{
		}

		void Device::setupMatrices()
		{
			f3m::Matrix4f& world = _matrices.world;
			f3m::Matrix4f& view = _matrices.view;
			f3m::Matrix4f& projection = _matrices.projection;

			f3::scene::CameraNode* cam = f3::scene::graph.camera();

			// world matrix
			world = f3m::Matrix4f::identity();
			
			// projection matrix
			if (currentRenderTarget() == NULL)
				projection = f3m::createProjection(1.0f, cam->nearPlane(), cam->farPlane(), _width / (float)_height);
			else
				projection = f3m::createProjection(1.0f, cam->nearPlane(), cam->farPlane(), _currentRenderTarget->desc._width / (float)_currentRenderTarget->desc._height);

			// view matrix
			view = f3m::createLookAt(cam->position(), cam->target(), f3m::Vector3f::Up);
			view = f3m::transpose(view);
		}

		int Device::width()
		{
			if (currentRenderTarget() != NULL)
				return currentRenderTarget()->desc._width;

			return _width;
		}

		int Device::height()
		{
			if (currentRenderTarget() != NULL)
				return currentRenderTarget()->desc._height;

			return _height;
		}

		void Device::draw()
		{
			// Render to Texture
			setRenderTarget(rt);
			clear(f3u::ColorRGBA(0.0f,0.0f,0.0f, 1.0f), COLOR_BUFFER );
			/*setupMatrices();
			drawNode(f3s::graph.root(), f3m::Matrix4f::identity());*/

			setupMatrices();
			_debugDR->render(_matrices);

			// Render to Device default Surface
			setRenderTarget(NULL);
			clear(f3u::ColorRGBA(0.3f,0.3f,0.3f, 1.0f), COLOR_BUFFER | DEPTH_BUFFER );

			setupMatrices();
			_batch2.draw(f3m::Vector3f(0.0f,0.0f,0.0f), rt->texture, 20.0f);
			_batch2.draw(f3m::Vector3f(0.0f,0.0f,0.0f), _stoneTexture, 1.0f);
			drawSpriteBatch(_batch2, _shader);

			_batch2._sprites.clear();
			setupMatrices();
			_batch.draw(f3m::Vector3f(5.0f,5.0f,0.0f), _nmTexture,2.25f);
			
			drawSpriteBatch(_batch, _nmshader);
			_batch._sprites.clear();

			_debugTR->render();

			present();

			f3g::debug.clear();
		}
		
		void Device::drawNode(f3::scene::Node* node, f3m::Matrix4f pm)
		{
			f3m::Matrix4f wmat = pm;
			
			if (node->data() != NULL && (node->isType(scene::Node::MESH)))
			{
				_shader->setTexture(_fallbackTexture);
				if(node->parent()->isType(scene::Node::MESH))
				{
					node->rot += -0.001f* f3u::timer.elapsed();
				}

				f3m::Matrix4f rot = f3m::Matrix4f::rotationZ(node->rot);
				
				wmat = f3m::multiply(wmat, f3m::Matrix4f::translation(node->position()));
				wmat = f3m::multiply(wmat, rot);

				_matrices.world = f3m::transpose(wmat);
				
				if (node->isType(f3s::Node::MESH))
				{
					f3s::MeshNode* meshnode = (f3s::MeshNode*) node;
					f3g::Mesh* mesh = (f3g::Mesh*) node->data();
					drawMesh(mesh);
				}
			}

			f3s::NodeList* nl = node->children();
			f3s::NodeList::iterator itr = nl->begin();

			while (itr != nl->end())
			{
				drawNode((*itr), wmat);
				itr++;
			}
		}

		void Device::drawSpriteBatch(SpriteBatch& batch, Shader* shader)
		{
			setRenderMode(TRIANGLES);

			f3g::SpriteList::iterator itr = batch._sprites.begin();

			f3m::Matrix4f world;

			while (itr != batch._sprites.end())
			{
				world = f3m::Matrix4f::identity();
				shader->setTexture(itr->texture);

				world = f3m::multiply(f3m::Matrix4f::translation(itr->position), world.scale(f3m::Vector3f(itr->size,itr->size,itr->size)));
				world = f3m::transpose(world);

				_matrices.world = world;			
			
				drawMesh(&quad, shader);
				itr++;
			}
		}

		void Device::init()
		{
			_windowListener = new WindowListener(this);
			_window->_listener = _windowListener;
			_debugDR = new DebugRenderer(this, &f3g::debug);
			_debugTR = new TextRenderer(this, &f3g::debug);
			resize(_window->width(), _window->height());
			getTextureLoader()->load(_fallbackTexture);
			getTextureLoader()->load(_stoneTexture);
			getTextureLoader()->load(_nmTexture);
			_shader = getShaderLoader()->load("std");
			_nmshader = getShaderLoader()->load("normal");

			f3m::Vector3f start(0,0,0), end(5,5,5);
			f3g::debug.addLine(start,end);

			_meshloader = new f3g::MeshLoader(this);


			RenderTargetDescription rtdesc;
			rtdesc._width = 1024;
			rtdesc._height = 1024;
			rt = NULL;
			createRenderTarget(rtdesc, &rt);
		}
		
		void Device::drawMesh(f3g::Mesh* mesh, f3g::Shader* shader)
		{
			if (shader == NULL)
				shader = _shader;


			if( mesh->_buffer1 == NULL)
			{
				getMeshLoader()->load(mesh);
				f3u::log << f3u::info << "Loading Mesh" << f3u::endl;
			}

			// set vertex buffer
			UINT stride1 = sizeof(float) * 3;
			UINT offset1 = 0;
			setBuffer(0, mesh->_buffer1, stride1, offset1);

			// set texture coordinates buffer
			UINT stride2 = sizeof(float) * 2;
			UINT offset2 = 0;
			setBuffer(1, mesh->_buffer2, stride2, offset2);

			// new
			setRenderMode(Device::TRIANGLES);
			setVertexLayout(_shader->_layout);
			
			shader->begin();
			shader->setWorldMatrix(_matrices.world);
			shader->setProjectionMatrix(_matrices.projection);
			shader->setViewMatrix(_matrices.view);

			
			while(shader->currentPass() < shader->passCount())
			{
				shader->startPass();
				drawElements(mesh->_vertices.size());
				shader->endPass();
			}
		}
		
		Shader* Device::currentShader()
		{
			return _shader;
		}
		
		IMeshLoader* Device::getMeshLoader()
		{
			return _meshloader;
		}

		ITextureLoader* Device::getTextureLoader()
		{
			return _textureloader;
		}

		IShaderLoader* Device::getShaderLoader()
		{
			return _shaderloader;
		}

		RenderTarget* Device::currentRenderTarget()
		{
			return _currentRenderTarget;
		}

	}
}