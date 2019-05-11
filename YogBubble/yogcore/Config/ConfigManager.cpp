#include "ConfigManager.h"



ConfigManager::ConfigManager()
{
}


ConfigManager::~ConfigManager()
{
}

YID ConfigManager::GetId() { return 0; }
void ConfigManager::SetId(YID id){
	
}

std::string ConfigManager::GetName(){
	return "config manager";
}

void ConfigManager::SetName(std::string){
	
}
IYog* ConfigManager::GetTargetFromName(std::string name){
	Config*  config = &(configs[name]);
	IYog* res = static_cast<IYog*>(config);
	return res;
}
IYog* ConfigManager::GetTargetFromName(std::wstring name){
	return nullptr;
}
bool ConfigManager::RegisterTargetByName(std::string name, IYog* target){
	configs[name] = *dynamic_cast<Config*>(target);
	return false;
}
bool ConfigManager::RegisterTargetById(UINT yog_id, IYog* target){
	return false;
}
IYog* ConfigManager::GetTargetFromId(UINT id){
	return nullptr;
}
