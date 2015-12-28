#ifndef CAMERANODE_H
#define CAMERANODE_H

#include "Node.h"
#include "ColorRGBA.h"
#include <f3math/Vector.h>

namespace f3
{
	class CameraNode : public Node
	{
		f3u::ColorRGBA _clearcolor;
		f3m::Vector3f _target;
		float _near;
		float _far;

	public:
		CameraNode(Node* parent = NULL);
		~CameraNode(void);
		void setTarget(f3m::Vector3f target);
		float nearPlane();
		float farPlane();
		f3m::Vector3f target();
		f3u::ColorRGBA clearColor();
	};
}

#endif