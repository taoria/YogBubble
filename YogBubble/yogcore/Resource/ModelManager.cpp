#include "ModelManager.h"
#include "../Graphic/ModelComponent.h"
IYog* ModelManager::GetTargetFromName(std::string name){
	return m_map[name];
}

IYog* ModelManager::GetTargetFromName(std::wstring name){
	return m_map[YogString::ws2s(name)];
}

void ModelManager::AddReference(ModelComponent* modelComponent, std::string modelName){
	if (!modelComponent) return;
	auto res = m_map[modelName];
	modelComponent->modelName = modelName;
	if(res){
		res->m_users.push_back(&modelComponent->entity);
	}
}
void ModelManager::RemoveReference(ModelComponent* modelComponent, std::string modelName) {
	modelComponent->modelName = modelName;
	auto res = m_map[modelName];
	if (res) {
		const auto entity = std::find(res->m_users.begin(), res->m_users.end(),&modelComponent->entity);
		res->m_users.erase(entity);
		int i = res->m_users.size();
	}
}

bool ModelManager::RegisterTargetByName(std::string name, IYog* target){
	m_map[name] = dynamic_cast<ModelResource*>(target);
	return true;
}

bool ModelManager::RegisterTargetById(UINT yog_id, IYog* target){
	return false;
}

YID ModelManager::GetId(){
	return 0;
}

void ModelManager::SetId(YID id){
}

std::string ModelManager::GetName(){
	return "ModelManager";
}

void ModelManager::SetName(std::string){

}

bool ModelManager::RegisterModel(std::string file, std::string filepath){
	if (YogHelper::CheckFile(filepath) == false) {
		LOG_F(YOG_ERROR, "NO such resoruce:%s", filepath.c_str());
		return false;
	}
	ModelResource *modelResource = new ModelResource;
	modelResource->m_resourceAddress = filepath;
	RegisterTargetByName(file, modelResource);
	return true;
}

IYog* ModelManager::GetTargetFromId(UINT id){
	return nullptr;
}
ModelManager *ModelManager::manager = nullptr;
ModelManager* ModelManager::GetInstance(){
	if(manager==nullptr){
		manager = new ModelManager;
	}
	return manager;
}
