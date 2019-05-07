#pragma once
#include "../Math/Vec3.h"
#include "../Component/IComponent.h"

class TransformComponent :public IComponent{

public:
	std::string GetName() override;
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;

};
