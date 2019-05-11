#pragma once
#include "../IYog.h"
#include "IYogModule.h"
interface IModuleLoader:IYog{
	YID GetId();
	std::string GetName();
	virtual IYogModule* load_mod(std::string loading_info) = 0;


};

inline YID IModuleLoader::GetId() {
	return 0;
}

inline std::string IModuleLoader::GetName() {
	return "";
}
