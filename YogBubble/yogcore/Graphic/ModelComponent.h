#pragma once
#include "../Component/IDrawComponent.h"

class YOG_DLL_EXPORT ModelComponent:public IDrawComponent{
public:
	std::string modelName ="";
	void OnInit() override;
	~ModelComponent();
	std::string GetName() override;
	void OnDraw() override;
};
