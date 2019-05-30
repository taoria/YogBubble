#include "TransformComponent.h"
std::string TransformComponent::GetName(){
	return "TransformComponent";
}
Vec3 FORWARD_VECTOR = { 0,0,1 };
Vec3 UP_VECTOR = { 0,1,0 };
Vec3 RIGHT_VECTOR = { 1,0,0 };
Vec3 TransformComponent::GetForward(){
	const XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, 0);
	Vec3 vv = XMVector3TransformCoord(static_cast<XMVECTOR>(FORWARD_VECTOR), vecRotationMatrix);
	return vv;
}
Vec3 TransformComponent::GetRight() {
	const XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, 0);
	Vec3 vv = XMVector3TransformCoord(static_cast<XMVECTOR>(RIGHT_VECTOR), vecRotationMatrix);
	return vv;
}
Vec3 TransformComponent::GetUp()
{
	const XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, 0);
	Vec3 vv = XMVector3TransformCoord(static_cast<XMVECTOR>(UP_VECTOR), vecRotationMatrix);
	return vv;
}

TransformComponent::TransformComponent(){
	scale.x = 1;
	scale.y = 1;
	scale.z = 1;
}

void TransformComponent::LookAtPos(Vec3 lookAtPos){
	if (lookAtPos.x == position.x && lookAtPos.y == position.y&& lookAtPos.z == position.z)
		return;
	lookAtPos.x = position.x- lookAtPos.x ;
	lookAtPos.y = position.y - lookAtPos.y;
	lookAtPos.z = position.z - lookAtPos.z;
	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f) {
		const float dis = sqrt(lookAtPos.x*lookAtPos.x + lookAtPos.z*lookAtPos.z);
		pitch = atan(lookAtPos.y / dis);
	}
	float yaw = 0.0f;
	if (lookAtPos.x != 0) {
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += XM_PI;
	rotation.x = pitch;
	rotation.y = yaw;
}

