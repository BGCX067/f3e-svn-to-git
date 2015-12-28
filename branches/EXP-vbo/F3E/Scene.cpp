#include "Scene.h"

namespace f3
{
	Scene* Scene::_default = NULL;

	Scene::Scene(void)
	{
		_root = new Node(NULL);
		_activeCamera = new CameraNode(_root);
	}

	Scene::~Scene(void)
	{
		if (_root != NULL)
		{
			delete _root;
			_root = NULL;
		}
	}

	CameraNode* Scene::camera()
	{
		return _activeCamera;
	}

	Scene* Scene::getDefault()
	{
		if (_default == NULL)
			_default = new Scene();
		
		return _default;
	}

	Node* Scene::root()
	{
		return _root;
	}
}