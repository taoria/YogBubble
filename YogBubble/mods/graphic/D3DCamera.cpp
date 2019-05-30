#include "D3DCamera.h"
#include "../../tools/helper.h"


D3DCamera::D3DCamera(){
	this->pos = XMFLOAT3(0, 0, 0);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0, 0, 0);
	this->rotVector = XMLoadFloat3(&this->rot);
	UpdateViewMatrix();
}
D3DCamera::~D3DCamera()
{
}

void D3DCamera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ){
	float fovRadians = (fovDegrees / 360.0f) *XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const XMMATRIX& D3DCamera::GetViewMatrix() const{
	return viewMatrix;
}

const XMMATRIX& D3DCamera::GetProjectionMatrix() const{
	return projectionMatrix;
}

const XMVECTOR& D3DCamera::GetPositionVector() const{
	return posVector;
}

const XMFLOAT3& D3DCamera::GetPositionFloat3() const{
	return pos;
}

const XMVECTOR& D3DCamera::GetRotationVector() const{
	return rotVector;
}

const XMFLOAT3& D3DCamera::GetRotationFloat3() const{
	return rot;
}

void D3DCamera::SetPosition(const XMVECTOR& pos){
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateViewMatrix();
}

void D3DCamera::SetPosition(float x, float y, float z){
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void D3DCamera::AdjustPosition(const XMVECTOR& pos){
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateViewMatrix();
}

void D3DCamera::AdjustPosition(float x, float y, float z){
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void D3DCamera::SetRotation(const XMVECTOR& rot){
	XMStoreFloat3(&this->rot, rot);
	this->rotVector = rot;
	this->UpdateViewMatrix();
}

void D3DCamera::SetRotation(float x, float y, float z){
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector  = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void D3DCamera::AdjustRotation(const XMVECTOR& rot){
	this->rotVector + rot;
	XMStoreFloat3(&this->rot, rotVector);
	this->UpdateViewMatrix();
}

void D3DCamera::AdjustRotation(float x, float y, float z){
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void D3DCamera::SetLookAtPos(XMFLOAT3 lookAtPos){
	if (lookAtPos.x == pos.x && lookAtPos.y == pos.y&& lookAtPos.z == pos.z)
		return;
	lookAtPos.x = pos.x - lookAtPos.x;
	lookAtPos.y = pos.y - lookAtPos.y;
	lookAtPos.z = pos.z - lookAtPos.z;
	float pitch = 0.0f;
	if(lookAtPos.y !=0.0f){
		const float dis = sqrt(lookAtPos.x*lookAtPos.x + lookAtPos.z*lookAtPos.z);
		pitch = atan(lookAtPos.y / dis);
	}
	float yaw = 0.0f;
	if(lookAtPos.z !=0){
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += XM_PI;
	this->SetRotation(pitch, yaw, 0);

}

void D3DCamera::SetLookAtPos(float x, float y, float z){
	SetLookAtPos(XMFLOAT3(x, y, z));
}

XMVECTOR D3DCamera::RightVector(){
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0, rot.y, 0);
	return XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}

XMVECTOR D3DCamera::forwardVector(){
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0, rot.y, 0);
	return XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
}

void D3DCamera::UpdateViewMatrix(){
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);
	camTarget += this->posVector;
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRotationMatrix);
	this->viewMatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);
}

YID D3DCamera::GetId() { return 0; }
void D3DCamera::SetId(YID id){}
std::string D3DCamera::GetName() { return "Camera"; }
void D3DCamera::SetName(std::string){}
void D3DCamera::OnInit(){}
void D3DCamera::OnRelease(){}
void D3DCamera::UpdateFromEntity(){
	Vec3 vec3 = cameraEntity->GetRotation();
	Vec3 pos3 = cameraEntity->GetPosition();
	pos = static_cast<XMFLOAT3>(pos3);
	rot = static_cast<XMFLOAT3>(vec3);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->posVector = XMLoadFloat3(&this->pos);
	UpdateViewMatrix();
}

void D3DCamera::DrawGrid(){

}

void D3DCamera::Initialize(Entity* cameraEntity){
	this->cameraEntity = cameraEntity;
	initialized = true;
}


