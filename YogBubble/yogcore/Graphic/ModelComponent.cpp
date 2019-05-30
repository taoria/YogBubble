#include "ModelComponent.h"
#include "RendererData.h"
#include "../yog.h"
#include "../Resource/ModelManager.h"
#include "../Event/EventSystem.h"
void ModelComponent::OnInit(){
	RendererData::GetInstance()->push_back(this);
	EMIT_M("model construct", "data", new InfoWrapper<YID>(this->GetEntity()->GetId()));
	if(entity)
		EMIT_M("model construct", "entity", entity);
}

ModelComponent::~ModelComponent(){
	EMIT_M("model deconstruct", "data", new InfoWrapper<YID>(this->GetEntity()->GetId()));
	ModelManager::GetInstance()->RemoveReference(this, modelName);
}

std::string ModelComponent::GetName(){
	return "ModelComponent";
}

void ModelComponent::OnDraw(){
}
