#ifndef SCENE_H
#define SCENE_H

#include <f3base/Common.h>
#include "Node.h"
#include "CameraNode.h"

namespace f3
{

class DLL Scene
{
	//static Scene* _default;
	CameraNode* _activeCamera;
	Node* _root;

public:
	Scene(void);
	~Scene(void);
	
	Node* root();
	static Scene* getDefault();
	CameraNode* camera();
};

}

#endif