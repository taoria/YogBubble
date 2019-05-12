#pragma once
#include "../Component/IDrawComponent.h"

class YOG_DLL_EXPORT ModelComponent:public IDrawComponent{
public:
	std::string modelName;
	void OnInit() override;

	std::string GetName() override;
};
