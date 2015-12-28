#include "DX10MeshLoader.h"

DX10MeshLoader::DX10MeshLoader(ID3D10Device* device)
{
	_device = device;
}

DX10MeshLoader::~DX10MeshLoader(void)
{
}

void DX10MeshLoader::load(f3::Mesh* mesh)
{
    // Create vertex buffer
    //SimpleVertex vertices[] =
    //{
    //    D3DXVECTOR3( 0.0f, 0.5f, 0.5f ),
    //    D3DXVECTOR3( 0.5f, -0.5f, 0.5f ),
    //    D3DXVECTOR3( -0.5f, -0.5f, 0.5f ),
    //};

	std::vector<f3m::Vector3f> _v;
	_v.insert(_v.end(), f3m::Vector3f(0.0f, 0.98f, 0.0f));
	_v.insert(_v.end(), f3m::Vector3f(0.55f, -0.55f, 0.0f));
	_v.insert(_v.end(), f3m::Vector3f(-0.55f, -0.55f, 0.0f));

    D3D10_BUFFER_DESC bd;
    bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(f3m::Vector3f) * _v.size();
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = &_v[0];
    
	_device->CreateBuffer(&bd, &InitData, &_vertexbuffer);

    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    _device->IASetVertexBuffers(0, 1,&_vertexbuffer, &stride, &offset);
    _device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}