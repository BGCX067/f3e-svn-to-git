#include "CameraNode.h"

namespace f3
{

CameraNode::CameraNode(Node* parent) : Node(parent)
{
	_near = 3.0f;
	_far = 100.0f;
	//f3m::Vector3f pos = f31m::Vector3f::Up * f3m::Vector3f::Up;

	setPosition(f3m::Vector3f(0,0,50));
	setTarget(f3m::Vector3f(0,0,0));
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

}