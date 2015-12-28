#ifndef DX10MESHLOADER_H
#define DX10MESHLOADER_H

#include "Mesh.h"
#include <d3d10.h>
#include <d3dx10.h>

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    D3DXVECTOR3 Pos;
};


class DX10MeshLoader
{
	ID3D10Buffer* _vertexbuffer;
	ID3D10Device* _device;
	
public:
	DX10MeshLoader(ID3D10Device* device);
	~DX10MeshLoader(void);
	void load(f3::Mesh* mesh);
};

#endif