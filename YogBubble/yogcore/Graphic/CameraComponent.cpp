#include "CameraComponent.h"
#include "../Entity/TransformComponent.h"

void CameraComponent::OnDraw(){
	TransformComponent*  tf = this->GetEntity()->GetComponent<TransformComponent>();
}
std::string CameraComponent::GetName(){
	return typeid(*this).name();
}
