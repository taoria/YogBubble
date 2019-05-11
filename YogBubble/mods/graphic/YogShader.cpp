#include "YogShader.h"
#include "../../tools/helper.h"
#include "Environment.h"
void YogShader::CompileFromFile(Environment* d3DEnv, std::wstring path){
	
}
YogVertexShader::YogVertexShader(){}
YogVertexShader::~YogVertexShader(){}

void YogVertexShader::InitializeShader(Environment* d3dEnv){
	CompileFromFile(d3dEnv, L"D:\\YogBuild\\vertex_shader.cso");
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	UINT numElements = ARRAYSIZE(layoutDesc);


	HRESULT hr = d3dEnv->GetDirectDevice()->CreateInputLayout(layoutDesc, numElements, resources->GetBufferPointer(), resources->GetBufferSize(), m_inputLayout.GetAddressOf());
}

void YogVertexShader::CompileFromFile(Environment* d3DEnv, std::wstring path){
	HRESULT hr = D3DReadFileToBlob(path.c_str(), resources.GetAddressOf());
	if(FAILED(hr)){
		YogDebugger::DebugError(L"failed to load shader");
	}
	hr = d3DEnv->GetDirectDevice()->CreateVertexShader(resources->GetBufferPointer(), resources->GetBufferSize(), NULL, this->m_vertexShader.GetAddressOf());
}

YogPixelShader::YogPixelShader(){}
YogPixelShader::~YogPixelShader(){}

void YogPixelShader::InitializeShader(Environment* d3dEnv){

	CompileFromFile(d3dEnv, L"E:\\YogBuild\\pixel_shader.cso");
	// D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
	// 	{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA}
	// };
	// UINT numElements = ARRAYSIZE(layoutDesc);
	//
	//
	// HRESULT hr = d3dEnv->GetDirectDevice()->CreateInputLayout(layoutDesc, numElements, resources->GetBufferPointer(), resources->GetBufferSize(), m_inputLayout.GetAddressOf());
}

void YogPixelShader::CompileFromFile(Environment* d3DEnv, std::wstring path){
	HRESULT hr = D3DReadFileToBlob(path.c_str(), resources.GetAddressOf());
	if (FAILED(hr)) {
		LOG_F(YOG_ERROR, "there is error happend when %X",hr);
	}
	hr = d3DEnv->GetDirectDevice()->CreatePixelShader(resources->GetBufferPointer(), resources->GetBufferSize(), NULL, this->m_pixelShader.GetAddressOf());
}

