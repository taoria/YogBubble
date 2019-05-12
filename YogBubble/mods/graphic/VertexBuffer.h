#pragma once
#include "../../stdafx.h"

template<class T>
class VertexBuffer
{
protected:
	ComPtr<ID3D11Buffer> buffer;
	
public:
	std::shared_ptr<UINT> stride;
	UINT  bufferSize = 0;
	ID3D11Buffer* Get() const;
	VertexBuffer();
	VertexBuffer(const VertexBuffer& v);
	VertexBuffer<T> & operator = (const VertexBuffer<T>& a);
	ID3D11Buffer* const* GetAddressOf() const;
	HRESULT Initialize(ID3D11Device* m_device, const T* data, UINT numIndices)
	{
		if(buffer.Get()!=nullptr){
			buffer.Reset();
		}
		if(stride.get()==nullptr){
			this->stride = std::make_shared<UINT>(sizeof(T));
		}
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
VertexBuffer<T>::VertexBuffer(){

}

template <class T>
VertexBuffer<T>::VertexBuffer(const VertexBuffer& v){
	bufferSize = v.bufferSize;
	this->buffer = v.buffer;
	stride = v.stride;
}

template <class T>
VertexBuffer<T>& VertexBuffer<T>::operator=(const VertexBuffer<T>& a){
	this->bufferSize = a.bufferSize;
	this->buffer = a.buffer;
	this->stride = a.stride;
		return *this;
}

template <class T>
ID3D11Buffer* const* VertexBuffer<T>::GetAddressOf() const {
	return buffer.GetAddressOf();
}

template <class T>
UINT VertexBuffer<T>::BufferSize() {

	return bufferSize;
}

