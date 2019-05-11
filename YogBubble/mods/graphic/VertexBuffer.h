#pragma once
#include "../../stdafx.h"

template<class T>
class VertexBuffer
{
protected:
	ComPtr<ID3D11Buffer> buffer;
	UINT  bufferSize = 0;
public:
	ID3D11Buffer* Get() const;

	ID3D11Buffer* const* GetAddressOf() const;
	HRESULT Initialize(ID3D11Device* m_device, T* data, UINT numIndices)
	{
		bufferSize = numIndices;
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = sizeof(T)*numIndices;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA vertexBufferData = {};
		vertexBufferData.pSysMem = data;
		HRESULT hr = m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, buffer.GetAddressOf());
		return hr;
	}
	UINT BufferSize();
};
template <class T>
ID3D11Buffer* VertexBuffer<T>::Get() const {
	return this->buffer.Get();
}

template <class T>
ID3D11Buffer* const* VertexBuffer<T>::GetAddressOf() const {
	return buffer.GetAddressOf();
}

template <class T>
UINT VertexBuffer<T>::BufferSize() {

	return bufferSize;
}

