#pragma once
#include "../Entity/GameEntity.h"
#include "ModelComponent.h"


class RendererData:public std::vector<ModelComponent*> {
private:
	static RendererData * data ;
	static Entity* defaultLight;
public:
	static RendererData* GetInstance();
	static Entity* GetDefaultLight();
	void EraseData(ModelComponent* model);
};
