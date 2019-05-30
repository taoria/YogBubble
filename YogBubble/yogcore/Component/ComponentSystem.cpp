#include "ComponentSystem.h"
#include "IComponent.h"

IYog* ComponentSystem::GetTargetFromName(std::string name){
	return nullptr;
}

IYog* ComponentSystem::GetTargetFromName(std::wstring name){
	return nullptr;
}

bool ComponentSystem::RegisterTargetById(UINT yog_id, IYog* target){
	return false;
}

IYog* ComponentSystem::GetTargetFromId(UINT id){
	return nullptr;
}

bool ComponentSystem::RegisterTargetByName(std::string name, IYog* target){

	return false;


}

YID ComponentSystem::GetId(){
	return 0;
}

void ComponentSystem::SetId(YID id){
	
}

std::string ComponentSystem::GetName(){
	return "component system";
}

void ComponentSystem::SetName(std::string){
	
}

IComponent* ComponentSystem::GetComponentOfEntity(Entity* entity, std::string component){
	char buffer[32];
	sprintf(buffer, "%I64d&", entity->GetId());
	std::string str = buffer+component;
	return m_map[str];
}

bool ComponentSystem::RegisterTargetOfEntity(Entity* entity, IComponent* com){
	if (com == nullptr) {
		return false;
	}

	try {
		char buffer[32];
		com->AttachTo(entity);
		sprintf(buffer, "%I64d&", com->GetEntity()->GetId());
		std::string str = buffer + std::string("class ") + com->GetName();
		m_map[str] = com;
	}
	catch (...) {
		//TO SOME LOG HERE
	}
	com->OnInit();
	return true;
}
std::vector<IComponent*> ComponentSystem::GetComponentList(Entity *entity){
	char buffer[32];
	sprintf(buffer, "%I64d", entity->GetId());
	std::string key = buffer;
	auto iter = m_map.lower_bound(key);
	key[key.length() - 1] ++;
	auto iter2 = m_map.upper_bound(key);
	std::vector<IComponent*> result;
	for(;iter!=iter2;iter++){
		result.push_back((*iter).second);
	}
	return result;
}
std::vector<IComponent*> ComponentSystem::GetComponentList(){
	std::vector<IComponent*> result;
	for(auto m:m_map){
		result.push_back(m.second);
	}
	return result;
}

void ComponentSystem::CallForUpdate(){
	for(auto cp :m_map ){
		cp.second->OnUpdate();
		if(cp.second->GetComponentMark()==COMPONENT_RENDER){
			drawComs.push_back(dynamic_cast<IDrawComponent*>(cp.second));
		}
	}
}
void ComponentSystem::GCForEntity(Entity* entity){
	char buffer[32];
	sprintf(buffer, "%I64d", entity->GetId());
	std::string key = buffer;
	auto iter = m_map.lower_bound(key);
	key[key.length() - 1] ++;
	auto iter2 = m_map.upper_bound(key);
	std::vector<IComponent*> result;
	std::vector<std::string> v;
	for (; iter != iter2; iter++) {
		v.push_back((*iter).first);
	}
	for(auto key :v){
		m_map.erase(key);
	}
}
void ComponentSystem::CallForDraw(){
	for(auto dcoms : drawComs){
		dcoms->OnDraw();
	}
	drawComs.clear();
	
}
void ComponentSystem::CallForInit(){
	for (auto cp : m_map) {
		cp.second->OnInit();
	}
}
