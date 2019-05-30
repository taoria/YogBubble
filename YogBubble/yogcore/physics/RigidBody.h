#pragma once
#include "../Component/IComponent.h"
class RigidBody:public IComponent{
public:
	std::string GetName() override;
	RigidBody();
	Vec3 velocity;
};
