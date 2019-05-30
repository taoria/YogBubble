#pragma once
#include "../Component/IComponent.h"
class LightComponent:public IComponent{
public:
	std::string GetName() override;
	float lightStrength = 1.0f;
	Vec3 lightColor = Vec3(1,1,1);
};
