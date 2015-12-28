#include "Scene.h"

namespace f3
{
	//Scene* Scene::_default = NULL;

	Scene::Scene(void)
	{
		_root = new Node();
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
		static Scene* def = NULL;

		if (def == NULL)
			def = new Scene();
		
		return def;
	}

	Node* Scene::root()
	{
		return _root;
	}
}