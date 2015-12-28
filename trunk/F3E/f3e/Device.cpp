#include "Device.h"
#include "CameraNode.h"
#include "Scene.h"
#include "MeshNode.h"
#include "GlyphNode.h"
#include "WindowListener.h"
#include <f3base/Window.h>
#include <f3base/Timer.h>
#include <f3base/Common.h>
#include "Shader.h"
#include "QuadMesh.h"

namespace f3
{
	namespace graphics
	{
		Device::Device(Window* window)
		{
			_window = window;
			_fallbackTexture = new f3r::Texture("resources/textures/ship.raw");//f3_RGBA_8b_128.raw");
			_fallbackTexture->_description.height = 128;
			_fallbackTexture->_description.width = 128;
			_fallbackTexture->_description.format = TextureDescription::Format::R8G8B8A8;
		}

		Device::~Device(void)
		{
		}

		void Device::setupMatrices()
		{
			f3m::Matrix4f& world = _matrices.world;
			f3m::Matrix4f& view = _matrices.view;
			f3m::Matrix4f& projection = _matrices.projection;

			f3::CameraNode* cam = f3::Scene::getDefault()->camera();

			// world matrix
			world = f3m::Matrix4f::identity();
			
			// projection matrix
			projection = f3m::createProjection(1.0f, cam->nearPlane(), cam->farPlane(), _width / (float)_height);

			// view matrix
			view = f3m::createLookAt(cam->position(), cam->target(), f3m::Vector3f::Up);
			view = f3m::transpose(view);
		}

		void Device::draw()
		{
			clear();
			setupMatrices();
			_shader->setProjectionMatrix(_matrices.projection);
			_shader->setViewMatrix(_matrices.view);

			//_matrices.world = f3m::transpose(_matrices.world);
			_shader->setWorldMatrix(_matrices.world);
			SpriteBatch batch;
			f3m::Vector3f v(0.0f,5.0f,0.0f);
			batch.draw(v, _fallbackTexture);
			drawSpriteBatch(batch);

			setRenderMode(Device::RenderMode::TRIANGLES);
			drawNode(f3::Scene::getDefault()->root(), f3m::Matrix4f::identity());

			present();
		}

		void Device::drawNode(f3::Node* node, f3m::Matrix4f pm)
		{
			f3m::Matrix4f wmat = pm;
			
			if (node->data() != NULL && (node->isType(Node::Type::MESH) || node->isType(Node::Type::GLYPH)))
			{
				if(node->parent()->isType(Node::Type::MESH))
				{
				node->rot += -0.001f* f3u::timer.elapsed();
				}
				f3m::Matrix4f rot = f3m::Matrix4f::rotationZ(node->rot);
				
				wmat = f3m::multiply(wmat, f3m::Matrix4f::translation(node->position()));
				wmat = f3m::multiply(wmat, rot);
				//wmat.translate(node->position());
				//wmat = /*pm * */f3m::transpose(wmat);	

				_matrices.world = f3m::transpose(wmat);
				_shader->setWorldMatrix(_matrices.world);


				if (node->isType(Node::Type::MESH))
				{
					setTexture(_fallbackTexture);
					f3::MeshNode* meshnode = (f3::MeshNode*) node;
					f3::Mesh* mesh = (f3::Mesh*) node->data();
					drawMesh(mesh);
				}
				//else if (node->isType(Node::Type::GLYPH))
				//	drawFont((f3::Font*) mesh, ((f3::GlyphNode*) node)->_character);
			}

			f3::NodeList* nl = node->children();
			f3::NodeList::iterator itr = nl->begin();

			while (itr != nl->end())
			{
				drawNode((*itr), wmat);
				itr++;
			}
		}

		void Device::drawSpriteBatch(SpriteBatch& batch)
		{
			f3g::SpriteList::iterator itr = batch._sprites.begin();

			f3m::Matrix4f world = f3m::Matrix4f::identity();

			while (itr != batch._sprites.end())
			{
				world.translate(itr->position);
				world = f3m::transpose(world);
				_shader->setWorldMatrix(world);
				drawMesh(&quad);
				itr++;
			}
		}

		void Device::init()
		{
			_windowListener = new WindowListener(this);
			_window->_listener = _windowListener;
			resize(_window->width(), _window->height());
			getTextureLoader()->load(_fallbackTexture);
		}

	}
}