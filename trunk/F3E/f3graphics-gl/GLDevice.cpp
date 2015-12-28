
#include "F3GL.h"

#include "GLDevice.h"
#include <f3base/Common.h>
//#include "GLMeshLoader.h"
#include <f3scene/Graph.h>
#include "GLShader.h"
#include <f3math/Matrix.h>
#include "GLTexture.h"
#include <f3base/ColorRGBA.h>
#include <f3graphics/MeshLoader.h>
#include <f3graphics/ShaderLoader.h>

namespace f3
{
	namespace graphics
	{

		GLDevice::GLDevice(Window* window) : Device(window)
		{
			f3u::log << f3u::info << "Creating OpenGL Canvas" << f3u::endl;
			
			_modes[TRIANGLES] = GL_TRIANGLES;
			_modes[POINTS] = GL_POINTS;
			_modes[LINES] = GL_LINES;

			_window = window;
			_renderMode = TRIANGLES;
		}

		GLDevice::~GLDevice(void)
		{
		}
		
		void GLDevice::clear( f3u::ColorRGBA color, f3::UI32 mode )
		{
			glClearColor(color.r, color.g, color.b, color.a);

			int clearmode = 0x0;
			
			if ((DEPTH_BUFFER & mode) == DEPTH_BUFFER)
				clearmode |= GL_DEPTH_BUFFER_BIT;
			
			if ((COLOR_BUFFER & mode) == COLOR_BUFFER)
				clearmode |= GL_COLOR_BUFFER_BIT;

			glClear(clearmode);
		}

		void GLDevice::setRenderTarget( RenderTarget* target )
		{

			if (target == NULL)
			{
				glPopAttrib();
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

				if (_currentRenderTarget != NULL)
				{
					_shader->setTexture(_currentRenderTarget->texture);
					genMM();
				}
				//glGenerateMipmapEXT(0);
				_currentRenderTarget = NULL;
				return;
			}
			GLRenderTarget* rt = (GLRenderTarget*) target;
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, rt->fbo);
			
			glPushAttrib(GL_VIEWPORT_BIT);
			glViewport(0, 0, rt->desc._width, rt->desc._height);
			glScissor(0, 0, rt->desc._width, rt->desc._height);
			_currentRenderTarget = rt;
		}

		void GLDevice::genMM()
		{

			//glGenerateMipmap(GL_TEXTURE_2D);
		}

		void GLDevice::createRenderTarget(const RenderTargetDescription& desc, RenderTarget** target)
		{
			GLRenderTarget* rt = new GLRenderTarget();

			// create target texture
			GLuint texture;
			glGenTextures(1, &texture);

			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, desc._width, desc._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			//glGenerateMipmapEXT(GL_TEXTURE_2D);

			// Generate The Texture
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, desc._width, desc._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			// create frame buffer object
			GLuint fbo = 0;
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			GLTexture* gltexture =  new GLTexture();
			gltexture->setData(texture);

			rt->texture = new Texture("");
			rt->texture->_shaderResource = gltexture;
			rt->fbo = fbo;
			rt->desc = desc;

			*target = rt;
		}

		void GLDevice::present()
		{
			// present is done in window class
			// -> check out GLWindow

			// Post Last OpenGL Error
			//GLenum erslt = glGetError();
			//
			//if (GL_NO_ERROR != erslt)
			//{
			//	char buffer[255];
			//	sprintf_s(buffer, "OpenGL Error: %s", glewGetErrorString(erslt));
			//	f3::util::log.write(Log::L_ERROR, buffer);
			//}
		}

		void GLDevice::destroy()
		{
		}

		void GLDevice::releaseBuffer(f3g::Buffer* buffer)
		{
			GLVertexBuffer* vb = (GLVertexBuffer*) buffer;
			glDeleteBuffers(1, (GLuint*) &vb->_glbuffer);
		}

		void GLDevice::setShader( Shader* shader )
		{
			//GLShader* glshader = (GLShader*) shader;
				//glUseProgram(glshader->program());
			_shader = shader;
		}

#pragma region vertexlayouts

		void GLDevice::createVertexLayout( VertexLayoutDefinition* definition, Shader* shader, VertexLayout** target )
		{
			GLVertexLayout* layout = new GLVertexLayout();

			layout->_definition = *definition;

			*target = layout;
		}

		void GLDevice::releaseVertexLayout( VertexLayout* layout )
		{

		}

		void GLDevice::setVertexLayout(VertexLayout* vl)
		{
			VertexLayoutDefinition& layout = vl->_definition;

			f3g::VertexLayoutDefinition::iterator itr = layout.begin();

			while (itr != layout.end())
			{
				int elements = 0;
				int type = GL_FLOAT;
				if (itr->_format == X32Y32Z32)
				{
					elements = 3;
					type = GL_FLOAT;
				}
				if (itr->_format == U32V32)
				{
					elements = 2;
					type = GL_FLOAT;
				}
				if (itr->_format == R32G32B32A32)
				{
					type = GL_FLOAT;
					elements = 4;
				}
				if (itr->_type == PER_INSTANCE)
					glVertexAttribDivisorARB(itr->_semanticSlot,1);
				else
					glVertexAttribDivisorARB(itr->_semanticSlot,0);

				glBindBuffer(GL_ARRAY_BUFFER, _bufferSlots[itr->_bufferSlot]);
				glVertexAttribPointer(itr->_semanticSlot, elements, type, GL_FALSE, itr->_stride, (void*) itr->_offset);
				glEnableVertexAttribArray(itr->_semanticSlot);
				++itr;
			}
		}

#pragma endregion vertexlayouts

#pragma region drawing
		void GLDevice::drawElements(f3::I32 elements)
		{
			glDrawArrays(_modes[_renderMode], 0, elements);
		}

		void GLDevice::drawIndexed(f3::I32 elements)
		{
			glDrawElements (_modes[_renderMode], elements, GL_UNSIGNED_SHORT, 0);
		}

		void GLDevice::drawInstances(f3::I32 elements, f3::I32 instances)
		{
			glDrawArraysInstanced(_modes[_renderMode], 0, elements, instances);
		}

		void GLDevice::drawIndexedInstances(f3::I32 elements, f3::I32 instances)
		{
			glDrawElementsInstanced(_modes[_renderMode], elements, GL_UNSIGNED_SHORT, NULL, instances);
		}
#pragma endregion drawing

		void GLDevice::init()
		{
			glClearDepth(1.0f);
			//glEnable(GL_DEPTH_TEST);
			glEnable (GL_BLEND); 
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthFunc(GL_LEQUAL);
			char buffer[255];
			sprintf_s(buffer, "OpenGL Version: %s", glGetString(GL_VERSION));
			f3u::log << f3u::info << buffer << f3u::endl;


			_textureloader = new f3g::GLTextureLoader();
			_shaderloader = new f3g::ShaderLoader<GLDevice, GLShader>(this);

			GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
			GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light1_position[] = { 5.1,5.1, -0.20, 1.0 };


			glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular);
			glLightfv(GL_LIGHT0, GL_POSITION, light1_position);

			Device::init();

			debugPrinter.init();
		}

		void GLDevice::resize(int width, int height)		// Resize And Initialize The GL Window
		{
			_width = width;
			_height = height;

			if (height==0)										// Prevent A Divide By Zero By
				height=1;										

			glViewport(0,0,_width,_height);						// Reset The Current viewport
		}

		void GLDevice::setTexture(f3g::Texture* texture)
		{
			f3r::GLTexture* glTexture = (f3r::GLTexture*) texture->_shaderResource;
			//int my_sampler_uniform_location = glGetUniformLocation(p, "my_color_texture");

			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_2D, glTexture->data());
		}

		//***************************
		//****** BUFFERS START ******
		//***************************
#pragma region buffers
		void GLDevice::setIndexBuffer(f3g::Buffer* buffer )
		{
			GLVertexBuffer* vb = (GLVertexBuffer*) buffer;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vb->_glbuffer);
		}

		void GLDevice::setBuffer( f3::I32 slot, f3g::Buffer* buffer, f3::UI32 stride, f3::UI32 offset /*= 0 */ )
		{
			GLVertexBuffer* vb = (GLVertexBuffer*) buffer;
			_bufferSlots[slot] = vb->_glbuffer;
		}

		void GLDevice::setRenderMode( RenderMode mode )
		{
			_renderMode = mode;
		}

		void GLDevice::createBuffer( f3g::BufferDescription desc, void* source, f3g::Buffer** target )
		{
			GLVertexBuffer* vb = new GLVertexBuffer();

			GLuint buffer;

			// create buffer(s)
			glGenBuffers(
				1,			// number of buffers 
				&buffer		// buffer reference
				);

			// bind buffer 
			GLenum target_type;

			// vertexbuffer
			if (desc.type == VERTEX_BUFFER)
			{
				target_type = GL_ARRAY_BUFFER;
			}
			// indexbuffer
			else if (desc.type == INDEX_BUFFER)
			{
				target_type = GL_ELEMENT_ARRAY_BUFFER;
			}
			else
			{
				assert(true);
			}

			glBindBuffer(target_type, buffer);
			glBufferData(target_type, desc.size, NULL, GL_DYNAMIC_DRAW);

			// if data is specified, copy data to buffer
			if (source != NULL)
				glBufferSubData(target_type, 0, desc.size, source);

			vb->_glbuffer = buffer;

			*target = vb;
		}

		void GLDevice::updateBuffer( Buffer* buffer, void* source, f3::I32 size )
		{
			GLVertexBuffer* vb = (GLVertexBuffer*) buffer;

			glBindBuffer( GL_ARRAY_BUFFER, vb->_glbuffer );
			glBufferSubData( GL_ARRAY_BUFFER, 0, size, source );
		}

#pragma endregion buffers
		//*************************
		//****** BUFFERS END ******
		//*************************
	}
}