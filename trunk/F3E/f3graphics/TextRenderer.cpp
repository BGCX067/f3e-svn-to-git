#include "TextRenderer.h"

#include <f3base/Common.h>
#include <f3base/Timer.h>

#include "Device.h"
#include "VertexLayout.h"
#include "Shader.h"


namespace f3
{
	namespace graphics
	{
		TextRenderer::TextRenderer( f3g::Device* device, DebugContext* context ) : _device(device), _context(context), _strings(context->strings)
		{
			_matrices = new MatrixSetup();
			f3m::Matrix4f& world = _matrices->world;
			f3m::Matrix4f& view = _matrices->view;
			f3m::Matrix4f& projection = _matrices->projection;


			// world matrix
			world = f3m::Matrix4f::identity();

			// projection matrix
			projection = f3m::createProjection(1.0f, 0.0f, 100.0f, 1024 / (float)1024);

			// view matrix
			view = f3m::createLookAt(f3m::Vector3f(0,0,20), f3m::Vector3f(0,0,0), f3m::Vector3f::Up);
			view = f3m::transpose(view);

			VertexLayoutDefinition def;
			def.insert(def.end(), VertexLayoutElement("POSITION", 0, 0, U32V32, sizeof(f3m::Vector2f)*2, 0, PER_VERTEX ));
			def.insert(def.end(), VertexLayoutElement("TEXCOORD", 1, 0, U32V32, sizeof(f3m::Vector2f)*2, sizeof(f3m::Vector2f), PER_VERTEX ));
			def.insert(def.end(), VertexLayoutElement("INSTPOS", 2, 1, R32G32B32A32, sizeof(CharacterInstanceData), 0, PER_INSTANCE ));
			def.insert(def.end(), VertexLayoutElement("COLOR", 3, 1, R32G32B32A32, sizeof(CharacterInstanceData), 3*4, PER_INSTANCE ));

			_shader = device->getShaderLoader()->load("font");

			VertexLayout* layout = NULL;
			_device->createVertexLayout(&def, _shader, &layout);
			_vertexLayout = layout;

			BufferDescription desc;

			desc.type = VERTEX_BUFFER;
			desc.size = sizeof(f3m::Vector2f) * 2 * 6 * 255;
			_device->createBuffer(desc, NULL, &_uvbuffer);

			desc.type = VERTEX_BUFFER;
			desc.size = sizeof(f3m::Vector2f) * 4000;
			_device->createBuffer(desc, NULL, &_posbuffer);

			desc.type = INDEX_BUFFER;
			desc.size = sizeof(f3g::Index) * 1000;
			_device->createBuffer(desc, NULL, &_indexbuffer);
			
			
			Character currentchar;
			currentchar.x =0.050f;
			currentchar.y =0.050f;
			currentchar.width = 0.90f;
			currentchar.height = 0.90f;

			_vbdata.push_back( f3m::Vector2f( -0.25f, -0.25f ) );	_vbdata.push_back( f3m::Vector2f(currentchar.x,						currentchar.y+currentchar.height));
			_vbdata.push_back( f3m::Vector2f( -0.25f,  0.25f ) );	_vbdata.push_back( f3m::Vector2f(currentchar.x,						currentchar.y));
			_vbdata.push_back( f3m::Vector2f(  0.25f, -0.25f ) );	_vbdata.push_back( f3m::Vector2f(currentchar.x+currentchar.width,	currentchar.y+currentchar.height)); 

			_vbdata.push_back( f3m::Vector2f(  0.25f, -0.25f ) );	_vbdata.push_back( f3m::Vector2f(currentchar.x+currentchar.width,	currentchar.y+currentchar.height));
			_vbdata.push_back( f3m::Vector2f(  0.25f,  0.25f ) );	_vbdata.push_back( f3m::Vector2f(currentchar.x+currentchar.width,	currentchar.y));
			_vbdata.push_back( f3m::Vector2f( -0.25f,  0.25f ) );	_vbdata.push_back( f3m::Vector2f(currentchar.x,						currentchar.y)); 


			Index indices[] = 
			{
				0,1,2,
				3,4,5
			};

			_device->updateBuffer( _indexbuffer, (void*) &(indices[0]), sizeof(Index) * 6);
			_device->updateBuffer( _uvbuffer, (void*) &(_vbdata[0]),sizeof(f3m::Vector2f) * 2 * 6);


			_texture = new f3r::Texture("resources/textures/font.raw");
			_texture->_description.height = 512;
			_texture->_description.width = 512;
			_texture->_description.format = TextureDescription::R8G8B8A8;

			_device->getTextureLoader()->load(_texture);
		}
		
		TextRenderer::~TextRenderer(void)
		{
			_device->releaseBuffer(_buffer);
			delete _buffer;
		}

		void TextRenderer::setupMatrices()
		{
			f3m::Matrix4f& projection = _matrices->projection;

			// projection matrix
			projection = f3m::createProjection(1.0f, 0.0f, 100.0f, _device->width() / (float) _device->height());
		}

		void TextRenderer::render()
		{
			setupMatrices();

			int total_size = 0;
			for (int i = 0; i < _strings.size(); i++)
			{
				total_size += _strings.at(i).text.size();
			}

			CharacterInstanceData* instancedata = new CharacterInstanceData[total_size];

			std::vector<RenderString>::iterator itr = _strings.begin();
			int total_offset = 0;

			while (itr != _strings.end())
			{
				RenderString rs = *itr;
				f3m::Vector3f& pos(rs.position);

				float row = 0.0f;
				float offset = 0.0f;
				for (int i = 0; i < rs.text.size(); i++)
				{
					offset += 0.32f;

					if (rs.text.at(i) == '\n')
					{
						row -= 0.6f;
						offset = 0.0f;
						total_size--;
						total_offset--;
						continue;
					}
					else
						instancedata[i+total_offset] = CharacterInstanceData( f3m::Vector3f( offset + pos._x,row+pos._y, (float) rs.text.at(i) ), rs.color );
				}
				total_offset += rs.text.size();
				itr++;
			}
			
				
			_device->updateBuffer( _posbuffer, (void*) &(instancedata[0]), sizeof(CharacterInstanceData) * total_size);
			delete [] instancedata;

			f3g::Shader* shader = _shader;
			
			_device->setBuffer(0, _uvbuffer,  2*sizeof(f3m::Vector2f), 0);
			_device->setBuffer(1, _posbuffer, sizeof(CharacterInstanceData), 0);

			_device->setVertexLayout(_vertexLayout);
			_device->setRenderMode(Device::TRIANGLES);


			shader->begin();
			shader->setTexture(_texture);
			shader->setWorldMatrix(_matrices->world);
			shader->setViewMatrix(_matrices->view);
			shader->setProjectionMatrix(_matrices->projection);

			while(shader->currentPass() < shader->passCount())
			{
				shader->startPass();
				//_device->drawInstances(6, total_size);
				//_device->drawIndexed(6);
				_device->drawIndexedInstances(6,total_size);
				//_device->drawElements(6);
				shader->endPass();
			}

		}

	}
}