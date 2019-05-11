#pragma once
#include "../Entity/GameEntity.h"
#include "ModelComponent.h"


class RendererData:public std::vector<ModelComponent*> {
private:
	static RendererData * data ;
public:
	static RendererData* GetInstance();
};
