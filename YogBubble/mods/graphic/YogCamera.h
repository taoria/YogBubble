#pragma once
#include "../../yogcore/IYogObject.h"
class D3DCamera :public IYogObject{
public:
	D3DCamera();
	~D3DCamera();

	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

	const XMMATRIX & GetViewMatrix() const;
	const XMMATRIX & GetProjectionMatrix() const;
	const XMVECTOR & GetPositionVector() const;
	const XMFLOAT3 & GetPositionFloat3() const;
	const XMVECTOR & GetRotationVector() const;
	const XMFLOAT3 & GetRotationFloat3() const;

	void SetPosition(const XMVECTOR & pos);
	void SetPosition(float x,float y,float z);
	void AdjustPosition(const XMVECTOR &pos);
	void AdjustPosition(float x, float y, float z);
	void SetRotation(const XMVECTOR &rot);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const XMVECTOR &rot);
	void AdjustRotation(float x, float y, float z);
	void SetLookAtPos(XMFLOAT3 lookAtPos);
	void SetLookAtPos(float x, float y, float z);
	XMVECTOR RightVector();
	XMVECTOR UpVector();
	XMVECTOR forwardVector();
private:
	void UpdateViewMatrix();
public:
	UINT GetId() override;
	void SetId(UINT id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
private:
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;


	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(-1.0f, 0, 0,0);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};

