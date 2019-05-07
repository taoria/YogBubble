#pragma once
#include "../IYog.h"
#include "IYogModule.h"
interface IModuleLoader:IYog{

	UINT GetId();
	std::string GetName();
	virtual IYogModule* load_mod(std::string loading_info) = 0;


};

inline UINT IModuleLoader::GetId() {
	return 0;
}

inline std::string IModuleLoader::GetName() {
	return "";
}
