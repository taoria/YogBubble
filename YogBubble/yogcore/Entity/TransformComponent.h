#pragma once
#include "../Math/Vec3.h"
#include "../Component/IComponent.h"

class YOG_DLL_EXPORT TransformComponent :public IComponent{

public:
	std::string GetName() override;
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
	Vec3 GetForward();
	Vec3 GetRight();
	Vec3 GetUp();
	void LookAtPos(Vec3 pos);
};
