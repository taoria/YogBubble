#include "Entity.h"
#include "IDAssigner.h"
#include "../Manager/YogManager.h"
#include "../Component/IComponent.h"
#include "../Component/ComponentSystem.h"
#include "TransformComponent.h"

YID Entity::GetId(){
	return id;
}

void Entity::SetId(YID id){
	this->id = id;
}

std::string Entity::GetName(){
	return "Entity";
}

void Entity::SetName(std::string){
	
}

void Entity::OnInit(){
		
}

void Entity::OnRelease(){
	
}

std::string Entity::GameName(){
	return "default object";
}

IComponent* Entity::GetComponent(std::string name){
	ComponentSystem* cs = dynamic_cast<ComponentSystem*>(get_manager("component system"));
	return cs->GetComponentOfEntity(this, name);
}

void Entity::AddComponent(IComponent* component){
	ComponentSystem* cs = dynamic_cast<ComponentSystem*>(get_manager("component system"));
	cs->RegisterTargetOfEntity(this, component);
}

Entity::~Entity(){
	ComponentSystem* cs = dynamic_cast<ComponentSystem*>(get_manager("component system"));
	auto vecs = cs->GetComponentList(this);
	cs->GCForEntity(this);
	for(auto mem:vecs){
		delete mem;
	}
}

Entity::Entity(){
	id = NEW_ENTITY_ID;
}

Vec3& Entity::GetPosition(){
	return GetComponent< TransformComponent>()->position;
}

Vec3& Entity::GetRotation(){
	return GetComponent< TransformComponent>()->rotation;
}

Vec3& Entity::GetScale(){
	return GetComponent< TransformComponent>()->scale;
}

bool Entity::operator<(const Entity& other){
	return this->id < other.id;
}

