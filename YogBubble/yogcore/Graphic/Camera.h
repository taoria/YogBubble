#pragma once

#include "../Math/Vec3.h"
#include "../Entity/Entity.h"

//这里有个镜头应该是Entity

class D3DCamera;

class YOG_DLL_EXPORT Camera :public Entity{
public:
	Camera();
	void CameraAttatchedToGraphicCamera(D3DCamera* yogCamera);
	void GetCamera();
	~Camera();
	//void SetPosition(const Vector3 & pos);
	// void AdjustPosition(const Vector3 &pos);
	// void AdjustPosition(float x, float y, float z);
	// void SetRotation(const Vector3 &rot);
	// void AdjustRotation(const Vector3 &rot);
	UINT GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
};

