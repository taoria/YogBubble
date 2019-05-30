#include "YogManager.h"
#include "../../tools/helper.h"
#include "../Module/ModuleManager.h"
#include "../Event/EventSystem.h"
#include "../Config/ConfigManager.h"
#include "../Component/ComponentSystem.h"

YogManager* YogManager::yog_manager_ = nullptr;
YogManager::YogManager(){
	OnInit();
}


YogManager::~YogManager()
{
}

YID YogManager::GetId() {
	return 0;
}

std::string YogManager::GetName() {
	return "";
}

void YogManager::SetId(YID id) {

}

void YogManager::SetName(std::string) {

}

void YogManager::OnInit() {
	IYogManager *module_manager = new ModuleManager;
	IYogManager *event_system = EventSystem::get_instance();
	RegisterTargetByName("top manager", this);
	RegisterTargetByName("event system", event_system);
	IYogManager* component_system = new ComponentSystem;
	RegisterTargetByName("component system",component_system);
	RegisterTargetByName("config manager", new ConfigManager);
	RegisterTargetByName("module manager", module_manager);
}

void YogManager::OnRelease() {


}

// void YogManager::on_iterating_members() {
// }
//
//
// void YogManager::on_target_registered(IYog* target) {
// 	target->setId(0);
//
// }

IYog* YogManager::GetTargetFromName(std::string name) {
	if(manager_pool[name]) {
		return manager_pool[name];
	}
	return nullptr;
}

IYog* YogManager::GetTargetFromName(std::wstring name) {
	return GetTargetFromName(YogString::ws2s(name));
}

bool YogManager::RegisterTargetByName(std::string name, IYog* target) {
	if(manager_pool[name]==nullptr) {
		manager_pool[name] = dynamic_cast<IYogManager*>(target);
		return true;
	}
	return false;

}

bool YogManager::RegisterTargetById(UINT yog_id, IYog* target) {
	YogDebugger::FunctionNotInstalled("register_target_by_name");
	return false;
	
}

IYog* YogManager::GetTargetFromId(UINT id) {
	YogDebugger::FunctionNotInstalled("register_target_by_id");
	return nullptr;
}

IYogManager* YogManager::get_instance() {
	if(!yog_manager_) {
		return yog_manager_=new YogManager;
	}
	return yog_manager_;
	
}
