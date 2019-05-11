#include "YogModel.h"
#include "Environment.h"


void YogModel::UpdateWorldMatrix(){
	worldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z) * XMMatrixTranslation(pos.x, pos.y, pos.z);
	//XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, 0);
}

void YogModel::UpdateFromTransform(){
	Vec3 vec3 = entity->GetRotation();
	Vec3 pos3 = entity->GetPosition();
	pos = static_cast<XMFLOAT3>(pos3);
	rot = static_cast<XMFLOAT3>(vec3);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->posVector = XMLoadFloat3(&this->pos);
	UpdateWorldMatrix();
}

YogModel::YogModel(){

}


YogModel::~YogModel(){
}

bool YogModel::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11ShaderResourceView* texture,
                          ConstantBuffer<VS_CB_DATA>& cb_vs_data){
	m_device = device;
	m_context = context;
	m_texture = texture;
	m_cbData = &cb_vs_data;
	Dot v[] = {
	Dot{{-0.5f,-0.5f,0},{0.0f,1.0f}}, //Bottom left
	Dot{{-0.5f,0.5f,0},{0.0f,0.0f}}, //Top left
	Dot{{0.5f,0.5f,0},{1.0f,0.0f}}, //Top Right
	Dot{{0.5f,-0.5f,0},{1.0f,1.0f}}, //bottom right
	Dot{{-0.5f,-0.5f,1},{0.0f,1.0f}}, //Bottom left
	Dot{{-0.5f,0.5f,1},{0.0f,0.0f}}, //Top left
	Dot{{0.5f,0.5f,1},{1.0f,0.0f}}, //Top Right
	Dot{{0.5f,-0.5f,1},{1.0f,1.0f}} //bottom right
	};
	DWORD indices[] = {
		0,1,2,
		0,2,3,
		3,2,6,
		3,6,7,
		1,5,6,
		1,6,2,
		5,1,0,
		4,5,0,
		7,4,0,
		3,7,0,
		6,5,4,
		7,6,4
		// 4,6,1,
		// 1,0,4,
		// 4,0,3,
		// 3,5,4,
		// 7,2,1,
		// 1,6,7,
		// 4,5,7,
		// 7,6,4
	};
	HRESULT hr = this->vertexBuffer.Initialize(m_device, v, ARRAYSIZE(v));
	if (FAILED(hr))
	{
		YogDebugger::DebugError(hr);
	}
	hr = this->indexBuffer.Initialize(m_device, indices, ARRAYSIZE(indices));
	if (FAILED(hr)) {
		YogDebugger::DebugError(hr);
	}
	return true;

}

bool YogModel::Initialize(Environment* environment){
	return Initialize(environment->m_device.Get(), environment->m_deviceContext.Get(), environment->demoTexture.Get(), environment->vs_cb_data);
}

void YogModel::SetTexture(ID3D11ShaderResourceView* m_texture){
	this->m_texture = m_texture;
}

void YogModel::Draw(const XMMATRIX& viewProjectionMatrix){
	m_cbData->data.mat = this->worldMatrix * viewProjectionMatrix;
	m_cbData->data.mat = XMMatrixTranspose(m_cbData->data.mat);
	m_cbData->ApplyChanges(m_context);
	UINT stride = sizeof(Dot);
	UINT offset = 0;
	m_context->PSSetShaderResources(0, 1, &this->m_texture);
	m_context->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_context->VSSetConstantBuffers(0, 1, m_cbData->GetAddressOf());
	m_context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	m_context->DrawIndexed(indexBuffer.BufferSize(), 0, 0);
}

