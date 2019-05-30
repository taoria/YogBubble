#include "IComponent.h"
#include "../Entity/IDAssigner.h"
#include "ComponentSystem.h"

Entity* IComponent::GetEntity() {
	return this->entity;
}

YID IComponent::GetId(){
	return 0;
}



void IComponent::SetId(YID id){
	
}

void IComponent::OnUpdate(){}

COMPONENT_MARK IComponent::GetComponentMark(){
	return COMPONENT_NORMAL;
}

std::string IComponent::GetName(){
	return "IComponent";
}
void IComponent::SetName(std::string){}
void IComponent::OnInit(){}
void IComponent::OnRelease(){
	
}

void IComponent::AttachTo(Entity* entity){
	this->entity = entity;

}

IComponent::IComponent(){
	id = NEW_COMPONENT_ID;
}

