#include "ModuleManager.h"
#include "../../tools/helper.h"
#include "../yog.h"


ModuleManager::ModuleManager()
{
}
void ModuleManager::InitModule() {
	auto m_iterator = this->m_modPool.begin();
	for(auto mod: this->m_modPool) {
		mod.second->OnModuleInit();
	}
}
void ModuleManager::CallUpdate() {
	for (auto mod : this->m_modPool) {
		mod.second->OnModuleUpdate();
	}
}
ModuleManager::~ModuleManager(){

}

YID ModuleManager::GetId() {
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
	return m_modPool[name];
}

IYog* ModuleManager::GetTargetFromName(std::wstring name) {
	return m_modPool[YogString::ws2s(name)];
}

bool ModuleManager::RegisterTargetByName(std::string name, IYog* target) {
	if(m_modPool[name]) {
		YogDebugger::DebugError(L"mod duplicate");
	}else {
		IYogModule * i_yog_module  = dynamic_cast<IYogModule*>(target);
		m_modPool[name] = i_yog_module;
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
