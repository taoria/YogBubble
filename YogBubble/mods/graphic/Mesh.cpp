#include "Mesh.h"

void Mesh::Draw(){
	UINT offset = 0;
	for(int i=0;i<textures.size();i++){
		if(textures[i].GetType()==aiTextureType_DIFFUSE){
			m_deviceContext->PSSetShaderResources(0, 1, textures[i].GetTextureResourceViewAddress());
			break;
		}
	}
	m_deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.stride.get(), &offset);
	m_deviceContext->DrawIndexed(indexBuffer.BufferSize(), 0, 0);
}

Mesh::Mesh(ID3D11Device* mesh, ID3D11DeviceContext* context, const std::vector<Dot>& dots,
	const std::vector<UINT>& is, std::vector<Texture> textures){
	
	Initialize(mesh, context, dots, is,textures);
}


Mesh::Mesh(ID3D11Device* mesh, ID3D11DeviceContext* context, const std::vector<Dot>& dots,
	const std::vector<unsigned>& is, const std::vector<Texture>& vector, const XMMATRIX& xmmatrix){
	this->transformMatrix = xmmatrix;
	Initialize(mesh, context, dots, is, vector);

}

const XMMATRIX& Mesh::GetTransformMatrix(){
	return transformMatrix;
}

bool Mesh::Initialize(ID3D11Device* mDevice, ID3D11DeviceContext* mDeviceContext, const std::vector<Dot>& vector,
                      const std::vector<UINT>& indices, std::vector<Texture> textures){
	m_deviceContext = mDeviceContext;
	this->textures = textures;
	vertexBuffer.Initialize(mDevice, vector.data(), vector.size());
	indexBuffer.Initialize(mDevice, indices.data(), indices.size());

	//TO DO LOG HERE
	return true;
}

Mesh::Mesh(const Mesh& mesh){
	m_deviceContext = mesh.m_deviceContext;
	indexBuffer = mesh.indexBuffer;
	vertexBuffer = mesh.vertexBuffer;
	textures = mesh.textures;
	transformMatrix = mesh.transformMatrix;
}
