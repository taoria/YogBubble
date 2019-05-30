#pragma once
#include "../Component/IComponent.h"
class YOG_DLL_EXPORT ICollider :public IComponent{
public:
	std::string GetName()override;
	ICollider();
	~ICollider();

};
class YOG_DLL_EXPORT BallCollider:public ICollider{
public:
	float radius = 1;
	Vec3 position;
	std::string GetName() override;
	~BallCollider();
	BallCollider();
};

