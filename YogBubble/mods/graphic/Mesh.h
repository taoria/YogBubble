#pragma once
#include "graphic.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Mesh{
private:
	std::vector<Texture> textures;
	XMMATRIX transformMatrix;
public:
	void Draw();
	Mesh(ID3D11Device* mesh, ID3D11DeviceContext* context, const std::vector<Dot>& dots, const std::vector<UINT>& is,
	     std::vector<Texture> textures);
	Mesh();
	Mesh(ID3D11Device* mesh, ID3D11DeviceContext* context, const std::vector<Dot>& dots, const std::vector<unsigned>& is, const std::vector<Texture>& vector, const XMMATRIX& xmmatrix);
	const XMMATRIX & GetTransformMatrix();
	bool Initialize(ID3D11Device* mDevice, ID3D11DeviceContext* mDeviceContext, const std::vector<Dot>& vector,
	                const std::vector<UINT>& indices, std::vector<Texture> textures);
	//bool Initialize(ID3D11Device *mDevice, ID3D11DeviceContext *mDeviceContext, std::vector<Dot> &vector, std::vector<UINT>& indices);
	Mesh(const Mesh& mesh);
	VertexBuffer<Dot> vertexBuffer;
	IndexBuffer indexBuffer;
	ID3D11DeviceContext *m_deviceContext;
	

};
