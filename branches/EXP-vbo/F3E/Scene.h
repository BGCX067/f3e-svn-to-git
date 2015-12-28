#ifndef SCENE_H
#define SCENE_H

#include "Common.h"
#include "Node.h"
#include "CameraNode.h"

namespace f3
{

class Scene
{
public:
	Scene(void);
	~Scene(void);

	static Scene* _default;
	
	CameraNode* _activeCamera;
	Node* _root;
	
	Node* root();
	static Scene* getDefault();
	CameraNode* camera();
};

}

#endif