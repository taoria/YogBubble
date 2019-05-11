#pragma once
#include"../../stdafx.h"
#include "../../tools/helper.h"
template<class T>
class ConstantBuffer
{
	
private:
	ComPtr<ID3D11Buffer > constantBuffer;
public:
	ConstantBuffer();
	~ConstantBuffer();
	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	bool ApplyChanges(ID3D11DeviceContext* deviceContext);

	ID3D11Buffer* Get() const;

	ID3D11Buffer* const * GetAddressOf() const;
	T data;
};

template <class T>
ConstantBuffer<T>::ConstantBuffer(){}

template <class T>
ConstantBuffer<T>::~ConstantBuffer(){}

template <class T>
HRESULT ConstantBuffer<T>::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	
	constantBufferDesc.ByteWidth = sizeof(T) + 16 - (sizeof(T)) % 16;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	HRESULT hr = device->CreateBuffer(&constantBufferDesc, 0, constantBuffer.GetAddressOf());
	return hr;
}

template <class T>
bool ConstantBuffer<T>::ApplyChanges(ID3D11DeviceContext* deviceContext) {
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	HRESULT hr = deviceContext->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	if (FAILED(hr)) {
		LOG_F(YOG_DEBUG, "mapping resource error ,error code:%X", hr);
		return false;
	}
	CopyMemory(mappedSubresource.pData, &data, sizeof(T));
	deviceContext->Unmap(constantBuffer.Get(), 0);
	return true;
}

template <class T>
ID3D11Buffer* ConstantBuffer<T>::Get() const {
	return constantBuffer.Get();
}

template <class T>
ID3D11Buffer* const* ConstantBuffer<T>::GetAddressOf() const {
	return constantBuffer.GetAddressOf();
}
