#pragma once
#include "../../stdafx.h"
#include "constantBuffer.h"


class IndexBuffer{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT  bufferSize = 0;
public:
	IndexBuffer();
	~IndexBuffer();

	ID3D11Buffer* Get() const;

	ID3D11Buffer* const* GetAddressOf() const;

	UINT BufferSize() const;
	HRESULT Initialize(ID3D11Device* device, const UINT* data, UINT numIndices);

	//HRESULT Initialize(ID3D11Device* device, DWORD* data, UINT numIndices);
};
