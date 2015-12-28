#ifndef SCENE_H
#define SCENE_H

#include <f3base/Common.h>
#include "Node.h"
#include "CameraNode.h"

namespace f3
{
	namespace scene
	{
		class Graph
		{
			CameraNode* _activeCamera;
			Node* _root;

		public:
			Graph(void);
			~Graph(void);
	
			Node* root();
			CameraNode* camera();
		};


		extern DLL Graph graph;
	}
}

#endif