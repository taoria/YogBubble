#include "ModuleManager.h"
#include "../../tools/helper.h"
#include "../yog.h"


ModuleManager::ModuleManager()
{
}
void ModuleManager::InitModule() {
	auto m_iterator = this->mod_pool.begin();
	for(auto mod: mod_pool) {
		mod.second->OnModuleInit();
	}
}
void ModuleManager::CallUpdate() {
	for (auto mod : mod_pool) {
		mod.second->OnModuleUpdate();
	}
}
ModuleManager::~ModuleManager(){

}

UINT ModuleManager::GetId() {
	return 0;
}

void ModuleManager::SetId(YID id) {
	
}

std::string ModuleManager::GetName() {
	return m_manager_name;
}

void ModuleManager::SetName(std::string name) {
	this->m_manager_name = name;
}

IYog* ModuleManager::GetTargetFromName(std::string name) {
	return mod_pool[name];
}

IYog* ModuleManager::GetTargetFromName(std::wstring name) {
	return mod_pool[YogString::ws2s(name)];
}

bool ModuleManager::RegisterTargetByName(std::string name, IYog* target) {
	if(mod_pool[name]) {
		YogDebugger::DebugError(L"mod duplicate");
	}else {
		IYogModule * i_yog_module  = dynamic_cast<IYogModule*>(target);
		mod_pool[name] = i_yog_module;
	}

	return true;
}

bool ModuleManager::RegisterTargetById(UINT yog_id, IYog* target) {
	YogDebugger::FunctionNotInstalled("register_target_by_id in ModuleManager");
	return false;
}

IYog* ModuleManager::GetTargetFromId(UINT id) {
	YogDebugger::FunctionNotInstalled("register_target_by_id in ModuleManager");
	return nullptr;
}
