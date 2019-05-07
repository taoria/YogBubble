#pragma once
#include "IComponent.h"
#include "../Math/Vec3.h"

class IDrawComponent :public IComponent
{
public:
	virtual void OnDraw();
	virtual Vec3& GetTransformPosition();
	virtual Vec3& GetRotationVector();
};
