#include "IndexBuffer.h"



IndexBuffer::IndexBuffer()
{
}


IndexBuffer::~IndexBuffer()
{
}

ID3D11Buffer* IndexBuffer::Get() const{
	return buffer.Get();
}

ID3D11Buffer* const* IndexBuffer::GetAddressOf() const{
	return buffer.GetAddressOf();
}

UINT IndexBuffer::BufferSize() const{
	return bufferSize;
}

HRESULT IndexBuffer::Initialize(ID3D11Device* device,const UINT* data, UINT numIndices){

	this->bufferSize = numIndices;
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.ByteWidth = sizeof(UINT) * numIndices;

	D3D11_SUBRESOURCE_DATA indexBufferData;
	indexBufferData.pSysMem = data;
	HRESULT hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf());
	return hr;
}
