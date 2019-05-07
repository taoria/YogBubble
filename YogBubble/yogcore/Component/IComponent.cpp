#include "IComponent.h"
#include "../Entity/IDAssigner.h"

Entity* IComponent::GetEntity(){
	return nullptr;
}

UINT IComponent::GetId(){
	return 0;
}



void IComponent::SetId(YID id){
	
}

void IComponent::OnUpdate(){}

std::string IComponent::GetName(){
	return "IComponent";
}
void IComponent::SetName(std::string){}
void IComponent::OnInit(){}
void IComponent::OnRelease(){
	
}

void IComponent::AttachTo(Entity* entity){

}

IComponent::IComponent(){
	id = NEW_COMPONENT_ID;
}

