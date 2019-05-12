#pragma once
#include <wrl/client.h>
#include <string>
#include <d3d11.h>
#include "../../yogcore/Graphic/Color.h"
#include <assimp/material.h>
enum class TextureStorageType {
	Invalid,
	None,
	EmbeddedIndexCompressed,
	EmbeddedIndexNonCompressed,
	EmbeddedNonCompressed,
	Disk,
	EmbeddedCompressed
};
class Texture{
public:
	Texture(ID3D11Device *device, const Color& color, aiTextureType type);
	Texture(ID3D11Device *device, const Color& colorData, UINT width,UINT height,aiTextureType type);
	Texture(ID3D11Device *device, const std::string & filePath, UINT width, UINT height, aiTextureType type);
	aiTextureType GetType();
	ID3D11ShaderResourceView * GetTextureResourceView();
	ID3D11ShaderResourceView ** GetTextureResourceViewAddress();
private:
	void Initialize1X1ColorTexture(ID3D11Device *device, const Color& color, aiTextureType type);
	void InitializeColorTexture(ID3D11Device *device, const Color* colorData, UINT width, UINT height, aiTextureType type);
	ComPtr<ID3D11Resource> texture = nullptr;
	ComPtr<ID3D11ShaderResourceView> textureView = nullptr;
	aiTextureType  type = aiTextureType::aiTextureType_UNKNOWN;
};
