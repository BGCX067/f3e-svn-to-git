#include "CameraNode.h"

namespace f3
{

	CameraNode::CameraNode(Node* parent) : Node(Node::Type::CAMERA, parent)
	{
		_near = 0.01f;
		_far = 100.0f;
		//f3m::Vector3f pos = f31m::Vector3f::Up * f3m::Vector3f::Up;
		_clearcolor.r = 0.13f;
		_clearcolor.g = 0.13f;
		_clearcolor.b = 0.13f;

		setPosition(f3m::Vector3f(5,0,10));
		setTarget(f3m::Vector3f(5,0,0));
	}

	CameraNode::~CameraNode(void)
	{
	}

	void CameraNode::setTarget(f3m::Vector3f target)
	{
		_target = target;
	}

	float CameraNode::nearPlane()
	{
		return _near;
	}

	float CameraNode::farPlane()
	{
		return _far;
	}

	f3m::Vector3f CameraNode::target()
	{
		return _target;
	}

	f3u::ColorRGBA CameraNode::clearColor()
	{
		return _clearcolor;
	}

}