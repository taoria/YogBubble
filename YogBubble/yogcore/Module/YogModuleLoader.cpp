#include "YogModuleLoader.h"
#include "../Manager/YogManager.h"
#include "ModuleManager.h"
#include "../YogWindow.h"
#include "../../mods/graphic/GFX.h"
#include "../../mods/physics/YogPhysics.h"


YogModuleLoader::YogModuleLoader()
{
}


YogModuleLoader::~YogModuleLoader(){
}



IYogModule* YogModuleLoader::load_mod(std::string loading_info) {
	ModuleManager*  module_manager = dynamic_cast<ModuleManager*>(YogManager::get_instance()->GetTargetFromName("module manager"));
	IYogModule* yog_window = YogWindow::get_instance();
	module_manager->RegisterTargetByName("yog window",yog_window);
	module_manager->RegisterTargetByName("renderer",new GFX(static_cast<YogWindow*>(yog_window)));
	module_manager->RegisterTargetByName("physics", new YogPhysics);
	return nullptr;
}

void YogModuleLoader::SetId(YID id) {
}

void YogModuleLoader::SetName(std::string) {
}
