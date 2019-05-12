#include "Texture.h"
#include "../../yogcore/Entity/Entity.h"

Texture::Texture(ID3D11Device* device, const Color& color, aiTextureType type){
	Initialize1X1ColorTexture(device, color, type);
}

Texture::Texture(ID3D11Device* device, const std::string& filePath, UINT width, UINT height, aiTextureType type){
	this->type = type;
	if(YogString::GetFileExtension(filePath)==".dds"){
		HRESULT hr = DirectX::CreateDDSTextureFromFile(device, YogString::s2ws(filePath).c_str(), texture.GetAddressOf(), textureView.GetAddressOf());
		//TO DO LOG HERE
		if(FAILED(hr)){
			this->Initialize1X1ColorTexture(device, Color::UnloaededTextureColor, type);
			return;
		}
	}else{

		HRESULT hr = DirectX::CreateDDSTextureFromFile(device, YogString::s2ws(filePath).c_str(), texture.GetAddressOf(), textureView.GetAddressOf());
		//TO DO LOG HERE
		if (FAILED(hr)) {
			this->Initialize1X1ColorTexture(device, Color::UnloaededTextureColor, type);
			
		}
		return;
	}
}

aiTextureType Texture::GetType(){
	return type;
}

ID3D11ShaderResourceView* Texture::GetTextureResourceView(){
	return textureView.Get();

}

ID3D11ShaderResourceView** Texture::GetTextureResourceViewAddress(){
	return textureView.GetAddressOf();
}

void Texture::Initialize1X1ColorTexture(ID3D11Device* device, const Color& color, aiTextureType type){
	InitializeColorTexture(device, &color, 1, 1, type);
}

void Texture::InitializeColorTexture(ID3D11Device* device, const Color* colorData, UINT width, UINT height,
	aiTextureType type){
	this->type = type;
	CD3D11_TEXTURE2D_DESC texture2DDesc(DXGI_FORMAT_B8G8R8A8_UNORM, width, height);
	ID3D11Texture2D * pTexture2D = nullptr;
	D3D11_SUBRESOURCE_DATA initialData{};
	initialData.pSysMem = colorData;
	initialData.SysMemPitch = width*sizeof(Color);
	HRESULT hr = device->CreateTexture2D(&texture2DDesc, &initialData, &pTexture2D);
	//TO DO LOG HERE

	texture = static_cast<ID3D11Texture2D*>(pTexture2D);
	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, texture2DDesc.Format);

	hr = device->CreateShaderResourceView(texture.Get(), &srvDesc, textureView.GetAddressOf());

}
