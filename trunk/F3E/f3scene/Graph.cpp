#include "Stdafx.h"

#include "Graph.h"

namespace f3
{
	//Scene* Scene::_default = NULL;

	namespace scene
	{
		Graph::Graph(void)
		{
			_root = new Node();
			_activeCamera = new CameraNode(_root);
		}

		Graph::~Graph(void)
		{
			if (_root != NULL)
			{
				delete _root;
				_root = NULL;
			}
		}

		CameraNode* Graph::camera()
		{
			return _activeCamera;
		}

		Node* Graph::root()
		{
			return _root;
		}

		Graph graph;
	}

}