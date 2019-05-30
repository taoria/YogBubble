#include "IDrawComponent.h"
#include "../Entity/TransformComponent.h"

void IDrawComponent::OnDraw(){
	
}

COMPONENT_MARK IDrawComponent::GetComponentMark(){
	return COMPONENT_RENDER;
}

Vec3& IDrawComponent::GetTransformPosition(){
	return GetEntity()->GetComponent<TransformComponent>()->position;
}

Vec3& IDrawComponent::GetRotationVector(){
	return GetEntity()->GetComponent<TransformComponent>()->rotation;
}
