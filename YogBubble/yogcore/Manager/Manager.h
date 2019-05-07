#pragma once
#include "YogManager.h"

namespace Manager {
	 IYogManager* get_manager_by_name(std::string manager_name) {
		 return static_cast<IYogManager*>(YogManager::get_instance()->GetTargetFromName(manager_name));
	}
}
