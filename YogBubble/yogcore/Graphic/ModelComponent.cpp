#include "ModelComponent.h"
#include "RendererData.h"

void ModelComponent::OnInit(){
	RendererData::GetInstance()->push_back(this);
}
