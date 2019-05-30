#pragma once
#include "../Component/IDrawComponent.h"
class UIComponent :public IDrawComponent{
public:
	void OnUpdate() override;
	void OnDraw() override;

	COMPONENT_MARK GetComponentMark() override;
};
