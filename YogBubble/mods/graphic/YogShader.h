#pragma once
#include <string>
#include "../../yogcore/IYogObject.h"
class Environment;
class YogShader:public IYogObject{
public:
	UINT GetId() override { return 0; }

	void SetId(YID id) override { };
	std::string GetName() override { return "shader"; };
	void SetName(std::string) override { };
	void OnInit() override { };
	void OnRelease() override { };
	virtual void CompileFromFile(Environment* d3DEnv, std::wstring path);
};
class YogVertexShader:public YogShader{
public:
	std::string m_shader_name;
	std::string m_shader_id;
	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3DBlob> resources;
	YogVertexShader();
	~YogVertexShader();
	void InitializeShader(Environment* d3dEnv);
	void CompileFromFile(Environment* d3DEnv, std::wstring path) override;
	ComPtr<ID3D11InputLayout> m_inputLayout;
};

class YogPixelShader :public YogShader {
public:
	std::string m_shader_name;
	std::string m_shader_id;
	ComPtr<ID3D11PixelShader> m_pixelShader;
	ComPtr<ID3DBlob> resources;
	YogPixelShader();
	~YogPixelShader();
	void InitializeShader(Environment* d3dEnv);
	void CompileFromFile(Environment* d3DEnv, std::wstring path) override;
	ComPtr<ID3D11InputLayout> m_inputLayout;
};

