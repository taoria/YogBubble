#pragma once
#include "IndexBuffer.h"
#include "YogShader.h"
#include "VertexBuffer.h"
#include "graphic.h"
#include "../../yogcore/Entity/Entity.h"
class YogModel{
private:
	VertexBuffer<Dot> vertexBuffer;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	ID3D11ShaderResourceView* m_texture;
	XMMATRIX worldMatrix =XMMatrixIdentity();
	ConstantBuffer<VS_CB_DATA>* m_cbData;;
	IndexBuffer indexBuffer;

public:
	void UpdateWorldMatrix();
	void UpdateFromTransform();
	YogModel();
	~YogModel();
	Entity *entity = nullptr;
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11ShaderResourceView *texture,ConstantBuffer<VS_CB_DATA> &cb_vs_data);
	bool Initialize(Environment* environment);
	void SetTexture(ID3D11ShaderResourceView *m_texture);
	void Draw(const XMMATRIX& viewProjectionMatrix);
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;
};

