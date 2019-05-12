#include "ModelComponent.h"
#include "RendererData.h"

void ModelComponent::OnInit(){
	RendererData::GetInstance()->push_back(this);
	//一旦存在一个ModelComponent,便要在对应的模型渲染程序中添加一个渲染目标
	
}

std::string ModelComponent::GetName(){
	return "ModelComponent";
}
