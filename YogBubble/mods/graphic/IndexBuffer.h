#pragma once
#include "../../stdafx.h"
class IndexBuffer{
private:
	ComPtr<ID3D11Buffer> buffer;
	UINT  bufferSize = 0;
public:
	IndexBuffer();
	~IndexBuffer();

	ID3D11Buffer* Get() const;

	ID3D11Buffer* const* GetAddressOf() const;

	UINT BufferSize() const;

	HRESULT Initialize(ID3D11Device* device, DWORD* data, UINT numIndices);
};
