#pragma once
#include "../Component/IDrawComponent.h"
#include "../Math/Vec3.h"
#include "../../mods/graphic/D3DCamera.h"

class CameraComponent :public IDrawComponent{
public:
	void OnDraw() override;
	std::string GetName() override;

};
